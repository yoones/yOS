#ifndef GDT_H_
# define GDT_H_

/* Descripteur de segment */
struct			s_gdt_desc
{
  unsigned short	lim0_15;
  unsigned short	base0_15;
  unsigned char		base16_23;
  unsigned char		acces;
  unsigned char		lim16_19 : 4;
  unsigned char		other : 4;
  unsigned char		base24_31;
} __attribute__ ((packed));

typedef struct s_gdt_desc t_gdt_desc;

/* Registre GDTR */
struct			s_gdtr
{
  unsigned short	limite;
  unsigned int		base;
} __attribute__ ((packed));

typedef struct s_gdtr t_gdtr;

# define GDT_BASE_ADDR 0x0
# define GDT_SIZE 0xFF

/* extern t_gdt_desc	g_gdt_desc[GDT_SIZE]; */
/* extern t_gdtr		g_gdtr; */

void	init_gdt_desc(unsigned int base, unsigned int limite,
		      unsigned char acces, unsigned char other,
		      t_gdt_desc *desc);

void	init_gdt(void);

#endif
