#include "key.h"

#include <stddef.h>

/* This is mapping for key => ascii, key is already parsed at this point. */
static const char* s_key_to_utf8_lower[] = {
    NULL,
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "å",
    "ä",
    "a",
    "´",
    NULL,
    NULL,
    "&",
    NULL,
    NULL,
    NULL,
    NULL,
    "*",
    "@",
    "b",
    "\\",
    NULL,
    "`",
    "c",
    NULL,
    NULL,
    "^",
    "}",
    ")",
    "]",
    ":",
    ",",
    "¤",
    "d",
    NULL,
    "$",
    "\"",
    "e",
    NULL,
    NULL,
    "=",
    NULL,
    "!",
    "f",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    "g",
    ">",
    "h",
    "½",
    "#",
    NULL,
    "-",
    "i",
    NULL,
    "j",
    "k",
    "l",
    NULL,
    NULL,
    "<",
    "m",
    NULL,
    NULL,
    NULL,
    NULL,
    "n",
    NULL,
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    ",",
    "/",
    NULL,
    "-",
    "*",
    "+",
    "ö",
    "o",
    "{",
    "(",
    "[",
    "p",
    NULL,
    NULL,
    "%",
    ".",
    "|",
    "+",
    "q",
    "?",
    "r",
    NULL,
    NULL,
    "s",
    "§",
    ";",
    "'",
    "/",
    " ",
    NULL,
    "t",
    "\t",
    "~",
    "¨",
    "u",
    "_",
    "v",
    NULL,
    NULL,
    NULL,
    "w",
    "x",
    "y",
    "z",
};

static const char* s_key_to_utf8_upper[] = {
    NULL,
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    "Å",
    "Ä",
    "A",
    "´",
    NULL,
    NULL,
    "&",
    NULL,
    NULL,
    NULL,
    NULL,
    "*",
    "@",
    "B",
    "\\",
    NULL,
    "`",
    "C",
    NULL,
    NULL,
    "^",
    "}",
    ")",
    "]",
    ":",
    ",",
    "¤",
    "D",
    NULL,
    "$",
    "\"",
    "E",
    NULL,
    NULL,
    "=",
    NULL,
    "!",
    "F",
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    NULL,
    "G",
    ">",
    "H",
    "½",
    "#",
    NULL,
    "-",
    "I",
    NULL,
    "J",
    "K",
    "L",
    NULL,
    NULL,
    "<",
    "M",
    NULL,
    NULL,
    NULL,
    NULL,
    "N",
    NULL,
    "0",
    "1",
    "2",
    "3",
    "4",
    "5",
    "6",
    "7",
    "8",
    "9",
    ",",
    "/",
    NULL,
    "-",
    "*",
    "+",
    "Ö",
    "O",
    "{",
    "(",
    "[",
    "P",
    NULL,
    NULL,
    "%",
    ".",
    "|",
    "+",
    "Q",
    "?",
    "R",
    NULL,
    NULL,
    "S",
    "§",
    ";",
    "'",
    "/",
    " ",
    NULL,
    "T",
    "\t",
    "~",
    "¨",
    "U",
    "_",
    "V",
    NULL,
    NULL,
    NULL,
    "W",
    "X",
    "Y",
    "Z",
};

const char* key_to_utf8(key_event_t* event) {
    int shift = !!(event->modifiers & KEY_EVENT_MODIFIERS_SHIFT);
    int caps  = !!(event->modifiers & KEY_EVENT_MODIFIERS_CAPS_LOCK);
    return (shift ^ caps) ? s_key_to_utf8_upper[event->key] : s_key_to_utf8_lower[event->key];
}
