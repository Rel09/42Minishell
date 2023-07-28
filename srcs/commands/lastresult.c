#include "../../minishell.h"

// Hold the last result of a command
int	*get_lastresult()
{
	static int	result;

	return (&result);
}
