#include "../../minishell.h"

// Convert Value + Sides to Bitshift value
static enum e_flagstype	get_flags(uint8_t value, bool right)
{
	if (value == 1 && right)
		return (RIGHT_SMALLER_THAN);
	else if (value == 1 && !right)
		return (LEFT_SMALLER_THAN);
	if (value == 2 && right)
		return (RIGHT_BIGGER_THAN);
	else if (value == 2 && !right)
		return (LEFT_BIGGER_THAN);
	if (value == 3 && right)
		return (RIGHT_PIPE);
	else if (value == 3 && !right)
		return (LEFT_PIPE);
	if (value == 4 && right)
		return (RIGHT_2SMALLER_THAN);
	else if (value == 4 && !right)
		return (LEFT_2SMALLER_THAN);
	if (value == 5 && right)
		return (RIGHT_2BIGGER_THAN);
	else if (value == 5 && !right)
		return (LEFT_2BIGGER_THAN);
	return (0);
}

// Add the flags to the current Flags pointer
void	set_flags(uint16_t *flags, uint8_t value, bool right)
{
	*flags |= get_flags(value, right);
}
