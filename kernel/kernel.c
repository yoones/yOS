#include "gdt.h"

int	main();

void	_start(void)
{
  init_gdt();
  main();
}
