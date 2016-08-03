#include "gdt.h"
#include "libc.h"

t_gdt_desc	g_gdt_desc[GDT_SIZE];
t_gdtr		g_gdtr;

/*
 * 'init_desc' initialise un descripteur de segment situe en gdt ou en ldt.
 * 'desc' est l'adresse lineaire du descripteur a initialiser.
 */
void	init_gdt_desc(unsigned int base, unsigned int limite,
		      unsigned char acces, unsigned char other,
		      t_gdt_desc *desc)
{
  desc->lim0_15 = (limite & 0xffff);
  desc->base0_15 = (base & 0xffff);
  desc->base16_23 = (base & 0xff0000) >> 16;
  desc->acces = acces;
  desc->lim16_19 = (limite & 0xf0000) >> 16;
  desc->other = (other & 0xf);
  desc->base24_31 = (base & 0xff000000) >> 24;
}

/*
 * Cette fonction initialise la GDT apres que le kernel soit charge
 * en memoire. Une GDT est deja operationnelle, mais c'est celle qui
 * a ete initialisee par le secteur de boot et qui ne correspond
 * pas forcement a celle que l'on souhaite.
 */
void	init_gdt(void)
{

  /* initialisation des descripteurs de segment */
  init_gdt_desc(0x0, 0x0, 0x0, 0x0, &g_gdt_desc[0]);
  init_gdt_desc(0x0, 0xFFFFF, 0x9B, 0x0D, &g_gdt_desc[1]);      /* code */
  init_gdt_desc(0x0, 0xFFFFF, 0x93, 0x0D, &g_gdt_desc[2]);      /* data */
  init_gdt_desc(0x0, 0x0, 0x97, 0x0D, &g_gdt_desc[3]);          /* stack */

  /* initialisation de la structure pour GDTR */
  g_gdtr.limite = GDT_SIZE * 8;
  g_gdtr.base = GDT_BASE_ADDR;

  /* recopie de la GDT a son adresse */
  memcpy((char *)g_gdtr.base, (char *)g_gdt_desc, g_gdtr.limite);

  /* chargement du registre GDTR */
  asm("lgdtl (g_gdtr)");

  /* initialisation des segments */
  asm("   movw $0x10, %ax \n \
            movw %ax, %ds       \n \
            movw %ax, %es       \n \
            movw %ax, %fs       \n \
            movw %ax, %gs       \n \
            ljmp $0x08, $next   \n \
            next:               \n");
}
