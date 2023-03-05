# YonaOS
a Hobby Operating System, minimalistic 32bit machine to run my weird code, check the gettoknow website for insight and code explaination, also if you have any seggestion or noticed something wrong I'll be happy if you contacted me.
## Tasks

### [X] Assembly + Bootable
### [X] Reading from the Disk
### [X] change to 32 bit mode
### [X] Coding in C/C++
### [X] Working on the display driver (Text Mode)
### [X] Defining and setting the IDT (Interrupts Descriptor Table).
### [' '] Working on the keyboard driver

## SHELL COMMANDS:
	YOT $> set time	; configure the time
	YOT $> set date	; configure the date
	YOT $> time		; show the time
	YOT $> date		; show the date
	YOT $> clear	; clears the display
	YOT $> draw		; draw a face (one of my arts)
	YOT $> exit		; now the cpu on hlt


## How To Test:
  simply have qemu and nasm installed and use:
   ```
    $> bash run.sh
   ```
