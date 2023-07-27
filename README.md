## Warning:
  the project got upgraded to [Yona2.0](https://github.com/Ayg0/Yona2.0)

# YonaOS
a Hobby Operating System, minimalistic 32bit machine to run my weird code, check the gettoknow website for insight and code explaination, also if you have any seggestion or noticed something wrong I'll be happy if you contacted me.
## Tasks:
### full ones = finished; still zeroes = need more work:
```
[1]     Assembly + Bootable + Reading from the Disk
[1]     change to 32 bit mode
[00011] Working on the display driver (Text Mode)
[1]     Defining and setting the IDT (Interrupts Descriptor Table).
[00001] Keyboard driver 
[00001] shell (basic)
[00000] file system
```

## SHELL COMMANDS:
```
	YOT $> set time		; configure the time
	YOT $> set date		; configure the date
	YOT $> time		; show the time
	YOT $> date		; show the date
	YOT $> clear		; clears the display
	YOT $> draw		; draw a face (one of my arts)
	YOT $> exit		; now the cpu on hlt
```
## How To Test:
  simply have qemu and nasm installed and use:
   ```
    $> bash run.sh
   ```
