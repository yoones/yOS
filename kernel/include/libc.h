#ifndef LIBC_H_
# define LIBC_H_

extern int	strlen(char *s);
extern void	*memcpy(void *dest, const void *src, unsigned int n);
extern void	*memset(void *s, int c, unsigned int n);

#endif
