![ChoacuryLogo](https://pineconiumsoftware.neocities.org/choacury/assets/ChoacuryLogo.png)
Choacury, (pronounced as coch-curry or /kʰɔx-ˈkʌr.i/), is a custom-built OS written in C/C++ and Assembly. Choacury is currently in a very very **Pre-Alpha** stage, meaning some stuff isn't complete yet...

If you want to help or make your version of Choacury, don't worry, you are free to modify it to your liking. You are also free to help contribute to the project! (see TODO.MD for what is needed doing).

# System Requirements
Currently, Choacury only works best with virtual machines. However, you *can* use real hardware if you want, just there might be some issues that will be fixed down the line.

For VirtualBox Users, here are the recommended VM requirements:
- Operating System: Other/Unknown
- Base Memory: 64 MB.
- Video Memory: 9 MB.
- Hard Disk: 2.00 GB.

# Compile Choacury.
If you want to compile Choacury yourself from source code, here's what you'll need.
1. NASM, GCC, GRUB Multiboot, Makefile, and QEMU installed. (the compiler uses the `x86_64` version of QEMU. If you don't use that version of QEMU, replace `qemu-system-x86_64` in the compiler shell script with your version of QEMU)
2. A computer running any Linux distro (recommended but there is a Windows Compiler for Windows devices along as you have WSL enabled).
