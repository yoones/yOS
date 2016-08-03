#include "screen.h"
#include "utils.h"

#define OS_BANNER "yOS Kernel"

void	print_os_banner()
{
  int	skip;

  putchar('\n');
  skip = (SCREEN_COLS - strlen(OS_BANNER)) / 2;
  while (skip-- > 0)
    putchar(' ');
  
  putstr(OS_BANNER);
}

int	main(void)
{
  clear();
  set_color(CHARATTR_COLOR_RED);
  print_os_banner();
  
  while (1);
  return (0);
}
