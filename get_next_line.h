#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <string.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*custom_strjoin(char *s1, char *s2);
int		find_chr(char *str, char c);
char	*get_next_line(int fd);

#endif