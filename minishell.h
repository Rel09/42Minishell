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


typedef struct s_input// Final Input Conversion
{
    int				index;
    char			*str;
    uint16_t		flags;
    struct s_input	*next;
}	t_input;

typedef struct s_parser// strtok Conversion
{
    char			*str;
    uint16_t		flags;
}	t_parser;

enum e_flagstype
{
	LEFT_2SMALLER_THAN = 1 << 0,
	RIGHT_2SMALLER_THAN = 1 << 1,
	LEFT_2BIGGER_THAN = 1 << 2,
	RIGHT_2BIGGER_THAN = 1 << 3,
	LEFT_SMALLER_THAN = 1 << 4,
	RIGHT_SMALLER_THAN = 1 << 5,
	LEFT_BIGGER_THAN = 1 << 6,
	RIGHT_BIGGER_THAN = 1 << 7,
	LEFT_PIPE = 1 << 8,
	RIGHT_PIPE = 1 << 9
};

// Parsing
t_input 	*parse_input(char *input);
void		set_flags(uint16_t	*flags, uint8_t value, bool right);


// --- ENV ---

//		Display Env
void		show_env();
void		show_env_export(void);

//		Env
char   		***get_env();
void		free_env();
void    	init_env(char **env);

//		Add / Remove from Env
void    	add_to_env(char *str);
void		find_and_remove(char *str);

// -----------

// Tools
bool		ft_isdigit(int c);
bool		ft_isalpha(int c);
uint8_t		is_quote(char	*str);
char		*ft_strdup(char *src);
t_parser	*ft_sstrtok(char *str);//
size_t		ft_strlen(const char *s);
uint8_t		is_delimiter(char	*str);
void		ft_bzero(void *s, size_t n);
int			ft_strcmp(char *s1, char *s2);
bool		ft_iscorrectenvname(char *str);
char		*ft_strncat(char *dest, char *src, int nb);
int			ft_strncmp(char *s1, char *s2, unsigned int n);

// 2D Array
int 		ft_count2darray(char **s);
void		ft_sort2darray(char ***strings);
void    	ft_copy2darray(char ***dist, char **src);
bool    	ft_isin2darray(char **src, char *tofind);
void    	ft_remove2darray(char ***dist, char **src, char *str);
void    	ft_insert2darray(char ***dist, char **src, char *newstr);



#endif
