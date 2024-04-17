![ChoacuryLogo](https://pineconiumsoftware.neocities.org/choacury/assets/ChoacuryLogo.png)
Choacury, (pronounced as coch-curry or /kʰɔx-ˈkʌr.i/), is a custom-built OS written in C/C++ and Assembly. Choacury is currently in a very very **Pre-Alpha** stage, meaning some stuff isn't complete yet...

If you want to help or make your own version of Choacury, don't worry, you are free to modify it to your liking. You are also free to help contribute to the project! (see TODO.MD for what is needed doing).

![Choacury Screenshot](https://pineconiumsoftware.neocities.org/choacury/assets/screenshot.png)

# System Requirements
Choacury does work with real hardware but compatibility is pretty weird. Currently, it only works best with virtual machines.

For VirtualBox Users, here are the recommended VM requirements:
- Operating System: Other/Unknown
- Base Memory: 64 MB.
- Video Memory: 9 MB.
- Hard Disk: 2.00 GB.
  
You'll also need these if you're planning to help out the project or compile Choacury.
1. A text editing program like Notepad, or Visual Studio Code.
2. NASM, GCC, GRUB Multiboot, Makefile, and QEMU installed. (the compiler uses the `x86_64` version of QEMU. If you don't use that version of QEMU, replace `qemu-system-x86_64` in the compiler shell script with your version of QEMU)
5. A computer running any Linux distro (recommended but there is a Windows Compiler for Windows devices along as you have WSL enabled).
6. A standard knowledge of Assembly and C.
