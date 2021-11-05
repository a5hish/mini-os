[BITS 32]

MB_HDR_MAGIC: equ  0x1BADB002
MB_HDR_FLAGS: equ  0x0
MB_HDR_CHECKSUM: equ -(MB_HDR_MAGIC + MB_HDR_FLAGS)


SECTION .multiboot_hdr:
	dd MB_HDR_MAGIC
	dd MB_HDR_FLAGS
	dd MB_HDR_CHECKSUM

SECTION .text:
global start
extern main

start:
	cli			;; Disable INTR
	mov esp, kernel_stack	;; initialize stack
	call main		;; Call Main from kernel_main.c
	hlt			;; hlt CPU

SECTION .bss
resb 0x2000			;;Reserved 8K of memory.
kernel_stack:
