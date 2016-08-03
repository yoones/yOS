#include "libc.h"

int		strlen(char *s)
{
  int		i;

  i = 0;
  while (s[i])
    i++;
  return (i);
}

void		*memcpy(void *dest, const void *src, unsigned int n)
{
  unsigned int	i;
  char		*d, *s;

  d = (char *)dest;
  s = (char *)src;
  for (i = 0; i < n; i++)
    d[i] = s[i];
  return (dest);
}

void		*memset(void *s, int c, unsigned int n)
{
  unsigned int	i;
  char		*ptr;

  ptr = (char *)s;
  for (i = 0; i < n; i++)
    ptr[i] = c;
  return (s);
}
