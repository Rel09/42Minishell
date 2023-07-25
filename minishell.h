#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>// 									Printf
# include <stdlib.h>// 									Malloc & Free
# include <unistd.h>//									GetCWD
# include <signal.h>//									Signals
# include <stdbool.h>//									Bool
# include <fcntl.h>//									open / read
# include <sys/stat.h>//								File Stat

# include "./readline/readline.h"// 					Readline
# include "./readline/history.h"//						History


typedef struct
{
	char			**args;
	uint16_t		flags;
	struct t_input	*next;
}	t_input;

// Parsing
t_input *parse_input(char *input);

// Env
void	show_env();
void	free_env();
char    ***get_env();
void    init_env(char **env);
void	show_env_export(void);
void    add_to_env(char *str);
void    remove_from_env(char *str);
void	find_and_remove(char *str);

// Tools
char	*ft_strtok(char *str, char sepa);


bool	ft_isdigit(int c);
bool	ft_isalpha(int c);
char	*ft_strdup(char *src);
size_t	ft_strlen(const char *s);
void	ft_bzero(void *s, size_t n);
int		ft_strcmp(char *s1, char *s2);
bool	ft_iscorrectenvname(char *str);
char	*ft_strncat(char *dest, char *src, int nb);
int		ft_strncmp(char *s1, char *s2, unsigned int n);

// 2D Array
int 	ft_count2darray(char **s);
void	ft_sort2darray(char ***strings);
void    ft_copy2darray(char ***dist, char **src);
bool    ft_isin2darray(char **src, char *tofind);
void    ft_remove2darray(char ***dist, char **src, char *str);
void    ft_insert2darray(char ***dist, char **src, char *newstr);



#endif
