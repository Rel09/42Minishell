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

# include "./readline/readline.h"// 					Readline
# include "./readline/history.h"//						History

int	g_last_result;

typedef struct s_input// Final Output
{
	char			**commands;
	int				_stdin;
	int				_stdout;
	struct s_input	*previous;
	struct s_input	*next;
}	t_input;

typedef struct s_fd_chain {
	int					pid;
	int					fd[2];
	struct s_fd_chain	*next;
	struct s_fd_chain	*previous;
}	t_fd_chain;

enum e_std_save
{
	SAVE_IN = 1 << 0,
	SAVE_OUT = 1 << 1,
	CLOSE_IN = 1 << 2,
	CLOSE_OUT = 1 << 3,
	RESTORE_IN = 1 << 4,
	RESTORE_OUT = 1 << 5
};

// Parsing
void		free_input(t_input *head);
t_input		*parse_input(char *input);
char		*remove_quotes(char	*str);
char		*convert_all_args(char *command);
char		*convert_all_the_shit_and_malloc(char *str);
void		compute_node(char *command, t_input *node, int *index);

// --- ENV ---

//		Display Env
void		show_env(void);				// env
void		show_env_export(void);	// export
char		*find_and_return(char *str);

//		Env
char		***get_env(void);
void		free_env(void);
void		init_env(char **env);
void		find_and_remove(char *str);

//		Add / Remove from Env
void		add_to_env(char *str);	// send ARG=WHATEVEREARUIASDFI
void		rem_from_env(char *argname);// just the argname here (without =)

// -----------

// Tools
char		*ft_itoa(int n);	// this NEED to malloc (im freeing it)
bool		ft_isdigit(int c);
bool		ft_isalpha(int c);
bool		ft_isspace(char c);
bool		ft_isredir(char *str);	//new
uint8_t		ft_isquote(char	*str);	//new
char		*ft_strdup(char *src);
char		*ft_isvariable(char *str);	//new
size_t		ft_strlen(const char *s);
void		ft_bzero(void *s, size_t n);
int			ft_getvariablelen(char *str);
int			ft_strcmp(const char *s1, const char *s2);
bool		ft_iscorrectenvname(char *str);	//new
char		*ft_strcpy(char *dest, char *src);
char		*ft_charncat(char *dest, char c, size_t n);	//new
char		*ft_strncat(char *dest, char *src, int nb);
int			ft_strncmp(char *s1, char *s2, unsigned int n);
char		*ft_strncpy(char *dest, char *src, unsigned int n);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
void		free_double_array(void	**ptr);
char		*ft_substr(char const *s, unsigned int start, size_t len);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		**ft_split(char const *s, char c);
int			ft_atoi(const char *nptr);
int			is_str_int(const char *str);
int			get_array_size(char	**array);
void		ft_putstr_fd(char *s, int fd);

// Strtoks - SUPER cursed stuff
char		*ft_strtok(char *str);
void		strtok_two(char **stock);
char		*ft_strtok_monkas(char *str);
int			count_strtok_monkas(char *str);
bool		stok3(char **stock, char *last_char);
void		strtok_one(uint8_t *swtch, char **output, char *stock);
void		ft_strtokhelper2(uint8_t *swtch, uint8_t *quote, char **stock);
void		ft_strtokhelper3(char **output, uint8_t *quote, uint8_t *swtch);

// 2D Array
int			ft_count2darray(char **s);
void		ft_sort2darray(char ***strings);
void		ft_copy2darray(char ***dist, char **src);
bool		ft_isin2darray(char **src, char *tofind);
void		ft_remove2darray(char ***dist, char **src, char *str);
void		ft_insert2darray(char ***dist, char **src, char *newstr);

// execution
int			intercept_signals(void);
void		here_doc_sighandler(int sig);
void		sigint_interactive(int sig);
void		sigint_running_shell(int sig);
bool		sig_received(int receiving_sig);

void		ms_pipes(t_input *input, t_fd_chain *fd_chain);
t_fd_chain	*open_new_pipe(t_fd_chain *fd_chain);
t_fd_chain	*close_fd_chain(t_fd_chain *fd_chain);
void		save_std(int option);
void		close_unused_fd(t_fd_chain *fd_chain);
t_fd_chain	*open_new_pipe(t_fd_chain *fd_chain);
t_fd_chain	*free_fd_chain(t_fd_chain *fd_chain);
void		pipeline_error_cleaning(t_input *input, t_fd_chain *fd_chain, \
	char	*msg, bool	exiting_process);
void		close_other_redirection_pipe_fd(t_input *input);
void		close_redirection(t_input *input);
void		ms_unset(char **args);
void		ms_pwd(char **args);
bool		accesschanged(int fd);
void		ms_cd(char **args);
void		ms_exe(t_input *input);
void		ms_exit(t_input *input);
void		ms_echo(char **args);
void		command_handler(t_input *input);
void		single_command_handler(t_input *input);
void		ms_env(char **args);
void		perror_global(char *str);
void		clean_static_memory(void);
void		*ft_calloc(size_t nitems, size_t size);
#endif
