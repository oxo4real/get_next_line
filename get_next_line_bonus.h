#ifndef GET_NEXT_LINE
# define GET_NEXT_LINE

# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <limits.h>

#ifndef	OPEN_MAX
# define OPEN_MAX 1024
#endif

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1024
#endif

size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s);
char	*custom_strjoin(char *s1, char *s2);
int		find_chr(char *str, char c);
char	*get_next_line(int fd);

#endif