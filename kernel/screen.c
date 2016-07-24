#include "screen.h"

t_screen	g_screen = {
  .y = 0,
  .x = 0,
  .attr = CHARATTR_DEFAULT,
};

void		set_color(unsigned char c)
{
  g_screen.attr &= ~CHARATTR_COLOR_MASK;
  g_screen.attr |= c;
}

void		set_bgcolor(unsigned char c)
{
  g_screen.attr &= ~CHARATTR_BGCOLOR_MASK;
  g_screen.attr |= c;
}

void		set_blink_on()
{
  g_screen.attr |= CHARATTR_BLINK;
}

void		set_blink_off()
{
  g_screen.attr &= ~CHARATTR_BLINK_MASK;
}

void		set_highlight_on()
{
  g_screen.attr |= CHARATTR_HIGHLIGHT;
}

void		set_highlight_off()
{
  g_screen.attr &= ~CHARATTR_HIGHLIGHT_MASK;
}

void		clear()
{
  unsigned char	*video;
  int		i;

  video = (unsigned char *)SCREEN_RAM_ADDR;
  for (i = 0; i < SCREEN_SIZE; i++, video += 2)
    {
      *video = ' ';
      *(video + 1) = g_screen.attr;
    }
  g_screen.y = 0;
  g_screen.x = 0;
}

void		scrollup()
{
  unsigned char	*dest, *src;
  int		i;

  src = (unsigned char *)GET_VIDEO_ADDR(1, 0);
  dest = (unsigned char *)SCREEN_RAM_ADDR;
  while (src < SCREEN_LIMIT)
    {
      *dest = *src;
      dest++;
      src++;
    }
  for (i = 0; i < SCREEN_COLS; i++)
    {
      *dest = ' ';
      *(dest + 1) = CHARATTR_DEFAULT;
      dest += 2;
    }
}

void		putchar(char c)
{
  unsigned char	*video;

  switch (c)
    {
    case '\n':
      if (g_screen.y == (SCREEN_ROWS - 1))
	scrollup();
      else
	g_screen.y++;
      g_screen.x = 0;
      return ;
    case '\r':
      g_screen.x = 0;
      return ;
    }
  video = (unsigned char *)GET_VIDEO_ADDR(g_screen.y, g_screen.x);
  *video = c;
  *(video + 1) = g_screen.attr;
  if (g_screen.y == (SCREEN_ROWS - 1) && (g_screen.x == SCREEN_COLS - 1))
    {
      scrollup();
      g_screen.x = 0;
    }
  else if (g_screen.x == (SCREEN_COLS - 1))
    {
      g_screen.y++;
      g_screen.x = 0;
    }
  else
    g_screen.x++;
}

void		putstr(char *str)
{
  while (*str)
    {
      putchar(*str);
      str++;
    }
}
