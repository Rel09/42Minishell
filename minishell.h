#ifndef MINISHELL_H
# define MINISHELL_H

# define COLOR_RESET	 "\033[0m"
# define COLOR_RED       "\033[31m"
# define COLOR_GREEN     "\033[32m"
# define COLOR_BLUE      "\033[34m"
# define COLOR_YELLOW    "\033[33m"
# define COLOR_MAGENTA   "\033[35m"
# define COLOR_CYAN      "\033[36m"
# define COLOR_WHITE     "\033[37m"
# define COLOR_KIRBY_PINK "\033[38;5;218m"

# include <stdbool.h>//									Bool
# include <stdio.h>// 									Printf
# include <unistd.h>//									GetCWD
# include <signal.h>//									Signals
# include <sys/stat.h>//								File Stat
# include <fcntl.h>//									Open / Read
# include <stdlib.h>// 									Malloc & Free

# include "./readline/history.h"//						History
# include "./readline/readline.h"// 					Readline



typedef struct s_input// Final Output
{
	char			**commands;
	int				_stdin;
	int				_stdout;
	struct s_input	*previous;
    struct s_input	*next;
}	t_input;

// Parsing
t_input 	*parse_input(char *input);
void 		free_input(t_input *head);
void		set_flags(uint16_t *flags, uint8_t value, bool right);


// --- ENV ---

//		Display Env
void		show_env();
void		show_env_export(void);
char		*find_and_return(char *str);

//		Env
char   		***get_env();
void		free_env();
void    	init_env(char **env);

//		Add / Remove from Env
void    	add_to_env(char *str);
void		find_and_remove(char *str);

// -----------

// Commands
int			*get_lastresult();

// Expander

// Tools
bool		ft_isdigit(int c);
bool		ft_isalpha(int c);
bool    	ft_isspace(char c);
uint8_t		ft_isquote(char	*str);
char		*ft_strdup(char *src);
char 		*ft_trimstr(char *str);
uint8_t		ft_isvariable(char *str);
size_t		ft_strlen(const char *s);
void		ft_bzero(void *s, size_t n);
int			ft_strcmp(char *s1, char *s2);
char		*ft_strtok_special(char *str);
bool		ft_iscorrectenvname(char *str);
char		*ft_strtok(char *str);
char    	*ft_strtok_monkas(char *str);
char		**ft_split(char const *s, char c);
char		*ft_strncat(char *dest, char *src, int nb);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
char		*ft_strncpy(char *dest, char *src, unsigned int n);

// 2D Array
int 		ft_count2darray(char **s);
void		ft_sort2darray(char ***strings);
void    	ft_copy2darray(char ***dist, char **src);
bool    	ft_isin2darray(char **src, char *tofind);
void    	ft_remove2darray(char ***dist, char **src, char *str);
void    	ft_insert2darray(char ***dist, char **src, char *newstr);

#endif
