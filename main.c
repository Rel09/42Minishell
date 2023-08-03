#include "minishell.h"

void	print_linkedlist(t_input *LL)
{
	int	i;

	while (LL)
	{
		i = 0;
		while (LL->commands[i])
			printf("[%s] ", LL->commands[i++]);
		printf("     STDIN:[%i]  STDOUT:[%i]\n", LL->_stdin, LL->_stdout);
		LL = LL->next;
	}
}

bool	check_fd(t_input *input)
{
	while (input)
	{
		if (input->_stdin == -1 || input->_stdout == -1)
		{
			free_input(input);
			return (false);
		}
		input = input->next;
	}
	return (true);
}

void	read_input(void)
{
	char	*input;
	t_input	*linkedlist;

	while (true)
	{
		input = readline("Minishell > ");
		signal(SIGINT, sigint_running_shell);
		if (!input)
			ms_exit(NULL);
		add_history(input);
		linkedlist = parse_input(input);
		if (!linkedlist)
			continue ;
		if (!check_fd(linkedlist))
			continue ;
		command_handler(linkedlist);
		signal(SIGINT, sigint_interactive);
	}
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	init_env(env);
	intercept_signals();
	read_input();
	return (0);
}
