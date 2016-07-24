	%define	BASE	0x100
	%define	KSIZE	50

	[BITS 16]
	[ORG 0x0]

	;; --------------------------------------------------------------------
	;; .TEXT
	;; --------------------------------------------------------------------
	
start:
	;; initialiser les segments
	mov	ax, 0x07C0	; bootloader chargé par le bios à 0x07C00
	mov	ds, ax
	mov	es, ax
	mov	ax, 0x8000
	mov	ss, ax
	mov	sp, 0xF000	; stack de 0x8F000 à 0x80000

	;; récupérer le numéro du drive
	mov	[bootdrv], dl

	;; charger le noyau
	xor	ax, ax		; reset disk drive
	int	0x13

	push	es
	mov	ax, BASE
	mov	es, ax
	mov	bx, 0

	mov	ah, 2		; read sector from drive
	mov	al, KSIZE	; number of sectors to read
	mov	ch, 0		; cylinder
	mov	cl, 2		; sector
	mov	dh, 0		; head
	mov	dl, [bootdrv]	; drive
	int	0x13
	pop	es

	;; initialisation du pointeur sur la GDT
	;; - calcule la limite de GDT (gdtptr.limit = &gdtend - &gdt)
	mov	ax, gdtend
	mov	bx, gdt
	sub	ax, bx
	mov	word [gdtptr], ax
	;; - calcule l'adresse lineaire de GDT (gdtptr.base = 0x07C00 + &gdt)
	xor	eax, eax	; eax = 0
	xor	ebx, ebx	; ebx = 0
	mov	ax, ds		; eax = 0x07C0
	mov	ecx, eax	; ecx = 0x07C0
	shl	ecx, 4		; ecx = (ecx << 4) = 0x07C00
	mov	bx, gdt		; ebx = &gdt
	add	ecx, ebx	; ecx += &gdt
	mov	dword [gdtptr + 2], ecx

	;; passage en mode protégé
	cli
	lgdt	[gdtptr]    	; charge la gdt
	mov	eax, cr0
	or	ax, 1
	mov	cr0, eax        ; CR0 |= 1

	;; pourquoi ce near jump???
	jmp next
next:

	;; réinitialisation des segments
	;; - data
	mov	ax, 0x10
	mov	ds, ax
	mov	fs, ax
	mov	gs, ax
	mov	es, ax
	;; - stack
	mov	ss, ax
	mov	esp, 0x9F000

	;; far jump vers le kernel pour que le processeur réinitialise le segment de code
	jmp dword 0x8:0x1000	; offset 0x8 dans la GDT => &gdt_cs
	
exit:
	jmp	exit

	;; --------------------------------------------------------------------
	;; .DATA
	;; --------------------------------------------------------------------
	
bootdrv:
	db	0
gdt:
	db 0, 0, 0, 0, 0, 0, 0, 0
gdt_cs:
	db 0xFF, 0xFF, 0x0, 0x0, 0x0, 10011011b, 11011111b, 0x0
gdt_ds:
	db 0xFF, 0xFF, 0x0, 0x0, 0x0, 10010011b, 11011111b, 0x0
gdtend:
gdtptr:
.limite:
	dw 0
.base:
	dd 0

	;; --------------------------------------------------------------------
	
	times 510 - ($ - $$) db 0
	dw 0xAA55

	;; --------------------------------------------------------------------
