#ifndef SCREEN_H_
# define SCREEN_H_

# define SCREEN_RAM_ADDR	(unsigned char *)0xB8000       /* debut de la memoire video */
# define SCREEN_SIZE		0xFA0        /* 4000, nombres d'octets d'une page texte */
# define SCREEN_LIMIT		(SCREEN_RAM_ADDR + SCREEN_SIZE)
# define SCREEN_ROWS		25
# define SCREEN_COLS		80

# if (SCREEN_ROWS * SCREEN_COLS * 2) != SCREEN_SIZE
#  error "Screen size, rows and cols don't match"
# endif

/*
** Attributs:
** blink-bg-bg-bg-highlight-c-c-c (7 -> 0)
*/

# define CHARATTR_COLOR_MASK		(0b111 << 0)
# define CHARATTR_HIGHLIGHT_MASK	(0b1   << 3)
# define CHARATTR_BGCOLOR_MASK		(0b111 << 4)
# define CHARATTR_BLINK_MASK		(0b1   << 7)

# define CHARATTR_COLOR_BLACK		0b000
# define CHARATTR_COLOR_BLUE		0b001
# define CHARATTR_COLOR_GREEN		0b010
# define CHARATTR_COLOR_CYAN		0b011
# define CHARATTR_COLOR_RED		0b100
# define CHARATTR_COLOR_MAGENTA		0b101
# define CHARATTR_COLOR_YELLOW		0b110
# define CHARATTR_COLOR_WHITE		0b111

# define CHARATTR_HIGHLIGHT		(0b1 << 3)

# define CHARATTR_BGCOLOR_BLACK		(CHARATTR_COLOR_BLACK   << 4)
# define CHARATTR_BGCOLOR_BLUE		(CHARATTR_COLOR_BLUE    << 4)
# define CHARATTR_BGCOLOR_GREEN		(CHARATTR_COLOR_GREEN   << 4)
# define CHARATTR_BGCOLOR_CYAN		(CHARATTR_COLOR_CYAN    << 4)
# define CHARATTR_BGCOLOR_RED		(CHARATTR_COLOR_RED     << 4)
# define CHARATTR_BGCOLOR_MAGENTA	(CHARATTR_COLOR_MAGENTA << 4)
# define CHARATTR_BGCOLOR_YELLOW	(CHARATTR_COLOR_YELLOW  << 4)
# define CHARATTR_BGCOLOR_WHITE		(CHARATTR_COLOR_WHITE   << 4)

# define CHARATTR_BLINK			(0b1 << 7)

# define CHARATTR_DEFAULT		(CHARATTR_COLOR_WHITE | CHARATTR_BGCOLOR_BLACK)

# define GET_VIDEO_ADDR(y, x) (SCREEN_RAM_ADDR + (y * SCREEN_COLS * 2) + (x * 2))

typedef struct	s_screen
{
  char		y;
  char		x;
  char		attr;
}		t_screen;

extern t_screen	g_screen;

extern void	set_color(unsigned char c);
extern void	set_bgcolor(unsigned char c);
extern void	set_blink_on();
extern void	set_blink_off();
extern void	set_highlight_on();
extern void	set_highlight_off();

extern void	clear();
extern void	scrollup();
extern void	putchar(char c);
extern void	putstr(char *str);

# endif
