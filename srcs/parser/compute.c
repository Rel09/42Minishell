#include "../../minishell.h"

// Change Ouput and close it if its not the default one
static void	change_output(char *file, t_input *node, bool append)
{
	int	fd;
	int	ret;

	if (append)
		fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = open(file, O_WRONLY | O_CREAT , 0644);
	if (fd == -1)
		node->_stdout = STDOUT_FILE_NO_EXIST;
	else
	{
		ret = dup2(node->_stdout, fd);
		if (ret == -1)
			node->_stdout = STDOUT_FAILED_DUP2;
		else
		{
			if (node->_stdout != STDOUT_FILENO)
				close(node->_stdout);
			node->_stdout = fd;
		}
	}
}

// Change Input and close it if its not the default one
static void	change_input(char *file, t_input *node)
{
	int	fd;
	int	ret;
	
	fd = open(file, O_RDONLY);
	if (fd == -1)
		node->_stdin = STDIN_FILE_NO_EXIST;
	else
	{
		ret = dup2(node->_stdout, fd);
		if (ret == -1)
			node->_stdin = STDIN_FAILED_DUP2;
		else
		{
			if (node->_stdin != STDIN_FILENO)
				close(node->_stdin);
			node->_stdin = fd;
		}
	}
}

static char	*convert_all_args(char *command)
{
	int			i;
	char		*var;
	int			len;
	bool		quote;
	bool		edited;
	static char	newstr[2000];

	i = 0;
	quote = false;
	edited = false;
	ft_bzero(newstr, 2000);
	while (command[i])
	{
		if (command[i] == '\'' && !quote)
			quote = true;
		else if (command[i] == '\'' && quote)
			quote = false;
		if (!quote && ft_isvariable(&command[i]))
		{
			edited = true;
			len = ft_getvariablelen(&command[i]);
			var = ft_isvariable(&command[i]);
			ft_strncat(newstr, command, i);
			ft_strncat(newstr, var, i + ft_strlen(var) + 2);
			ft_strncat(newstr, &command[i + (len)], ft_strlen(newstr) + ft_strlen(&command[i + (len)]));
		}
		i++;
	}
	if (!edited)
		return (command);
	return (newstr);
}


// Apply the redirection
static void	do_redirect(char *type, char* file, t_input *node)
{
	if (!ft_strcmp(type, "<<"))
		change_input(file, node);
	else if (!ft_strcmp(type, ">>"))
		change_output(file, node, true);
	else if (!ft_strcmp(type, "<"))
		change_input(file, node);
	else if (!ft_strcmp(type, ">"))
		change_output(file, node, false);
}

// Backend for the Redirection and pretty much all
void     compute_node(char *command, t_input *node, int *index)
{
	char	*temp;
	char	*newstr;
	
	if (ft_isredir(command))
		do_redirect(command, ft_strtok_monkas(0), node);

	else {

		node->commands[(*index)++] = ft_strdup(convert_all_args(command));
	}
}
