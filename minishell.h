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
    int				index;
    char			*str;
    uint16_t		flags;

	int				stdin;
	int				stdout;
	
    struct s_input	*next;
}	t_input;

typedef struct s_parser// ft_sstrtok Conversion
{
    char			*str;
    uint16_t		flags;
}	t_parser;

enum e_flagstype
{
	LEFT_2SMALLER_THAN = 1 << 0, // HEREDOC
	RIGHT_2SMALLER_THAN = 1 << 1,
	LEFT_2BIGGER_THAN = 1 << 2,	// OUT APPEND
	RIGHT_2BIGGER_THAN = 1 << 3,
	LEFT_SMALLER_THAN = 1 << 4, // INFILE
	RIGHT_SMALLER_THAN = 1 << 5,
	LEFT_BIGGER_THAN = 1 << 6, // OUT OVERWRITE
	RIGHT_BIGGER_THAN = 1 << 7,
	LEFT_PIPE = 1 << 8,
	RIGHT_PIPE = 1 << 9
};

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
uint8_t		is_quote(char	*str);
char		*ft_strdup(char *src);
char 		*ft_trimstr(char *str);
t_parser	*ft_sstrtok(char *str);//
uint8_t		ft_isvariable(char *str);
size_t		ft_strlen(const char *s);
uint8_t		is_delimiter(char	*str);
void		ft_bzero(void *s, size_t n);
int			ft_strcmp(char *s1, char *s2);
bool		ft_iscorrectenvname(char *str);
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
