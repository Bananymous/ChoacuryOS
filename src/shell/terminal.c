#include "terminal.h"
#include "../drivers/utils.h"

// FIXME: This code should not be VGA dependant.
//        Currently there are only colors values
//        for VGA and no "general" ones.
#include "../drivers/vga.h"

#include <kernel/panic.h>
#include <memory/kmalloc.h>

typedef struct {
    u8 ch;
    u8 color;
} term_cell_t;

typedef struct {
    u32 width;
    u32 height;
    set_char_t set_char;
    move_cursor_t move_cursor;

    u32 row;
    u32 col;

    term_cell_t* buffer;
} term_info_t;

static term_info_t s_term_info;

void term_init(u32 width, u32 height, set_char_t set_char, move_cursor_t move_cursor) {
    s_term_info.width = width;
    s_term_info.height = height;
    s_term_info.set_char = set_char;
    s_term_info.move_cursor = move_cursor;
    s_term_info.buffer = kmalloc(width * height * sizeof(term_cell_t));
    if (s_term_info.buffer == NULL) {
        panic("Failed to allocate memory for terminal buffer");
    }
    term_clear();
}

void term_rerender_buffer() {
    /* loop over all cells in terminal buffer and write them to screen */
    u32 offset = 0;
    for (u32 y = 0; y < s_term_info.height; y++) {
        for (u32 x = 0; x < s_term_info.width; x++) {
            term_cell_t cell = s_term_info.buffer[offset++];
            s_term_info.set_char(x, y, cell.ch, cell.color);
        }
    }
}

void term_clear() {
    /* write all spaces to terminal buffer */
    u32 offset = 0;
    for (u32 y = 0; y < s_term_info.height; y++) {
        for (u32 x = 0; x < s_term_info.width; x++) {
            s_term_info.buffer[offset].ch = ' ';
            s_term_info.buffer[offset].color = TC_WHITE;
            offset++;
        }
    }

    /* render buffer of only spaces */
    term_rerender_buffer();

    /* move cursor to top left corner */
    s_term_info.row = 0;
    s_term_info.col = 0;
    s_term_info.move_cursor(s_term_info.col, s_term_info.row);
}

static void term_scroll() {
    /* Scroll all lines one up */
    for (u32 y = 1; y < s_term_info.height; y++) {
        term_cell_t* row_above = &s_term_info.buffer[(y - 1) * s_term_info.width];
        term_cell_t* row_current = &s_term_info.buffer[y * s_term_info.width];
        memmove(row_above, row_current, s_term_info.width * sizeof(term_cell_t));
    }

    /* Clear the last line */
    const u32 last_offset = (s_term_info.height - 1) * s_term_info.width;
    for (u32 x = 0; x < s_term_info.width; x++) {
        s_term_info.buffer[last_offset + x].ch = ' ';  // Use space character
        s_term_info.buffer[last_offset + x].color = TC_WHITE;  // Set to default color
    }

    /* Render the updated buffer */
    term_rerender_buffer();
}



void term_putchar_no_cursor_update(char ch, u8 color) {
    switch (ch) {
        case '\b':
            // move cursor one cell back
            if (s_term_info.col > 0) {
                s_term_info.col--;
            }
            break;
        case '\n':
            // move cursor too next line
            s_term_info.col = 0;
            s_term_info.row++;
            break;
		case '\t':
			term_putchar_no_cursor_update(' ', color);
			term_putchar_no_cursor_update(' ', color);
			term_putchar_no_cursor_update(' ', color);
			term_putchar_no_cursor_update(' ', color);
			break;
        default: {
            // put character into buffer
            u32 offset = s_term_info.row * s_term_info.width + s_term_info.col;
            term_cell_t* cell = &s_term_info.buffer[offset];
            cell->ch = ch;
            cell->color = color;

            // render new character to screen
            s_term_info.set_char(s_term_info.col, s_term_info.row, ch, color);

            // move cursor one right
            s_term_info.col++;
            break;
        }
    }

    /* handle cursor overflow from right */
    if (s_term_info.col >= s_term_info.width) {
        s_term_info.col = 0;
        s_term_info.row++;
    }

    /* handle terminal scrolling */
    if (s_term_info.row >= s_term_info.height) {
        term_scroll();
        s_term_info.row = s_term_info.height - 1;
    }
}

void term_putchar(char ch, u8 color) {
    term_putchar_no_cursor_update(ch, color);

    /* update shown cursor position */
    s_term_info.move_cursor(s_term_info.col, s_term_info.row);
}

void term_set_cursor(u32 x, u32 y) {
    /* update cursor column and clamp to terminal width */
    s_term_info.col = x;
    if (s_term_info.col >= s_term_info.width)
        s_term_info.col = s_term_info.width - 1;

    /* update cursor row and clamp to terminal height */
    s_term_info.row = y;
    if (s_term_info.row >= s_term_info.height)
        s_term_info.row = s_term_info.height - 1;

    /* update shown cursor position */
    s_term_info.move_cursor(s_term_info.col, s_term_info.row);
}

void term_write(const char* message, u8 color) {
    while (*message) {
        term_putchar_no_cursor_update(*message, color);
        message++;
    }

    /* update shown cursor position */
    s_term_info.move_cursor(s_term_info.col, s_term_info.row);
}

static char get_digit_char(int digit) {
    if (digit < 10) {
        return '0' + digit;
    }
    return 'A' + (digit - 10);
}

void term_write_u32(u32 value, u8 base, u8 color) {
    if (value == 0) {
        term_putchar('0', color);
        return;
    }

    char buffer[33];
    buffer[sizeof(buffer) - 1] = 0;

    // Build the integer string in reverse order
    char* ptr = buffer + sizeof(buffer) - 1;
    while (value != 0) {
        int digit = value % base;
        *--ptr = get_digit_char(digit);
        value /= base;
    }

    // Write the integer to the terminal
    term_write(ptr, color);
}
