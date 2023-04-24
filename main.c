# include <readline/readline.h> 
# include <readline/history.h>
# include <dirent.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <signal.h>

#include <stdio.h>
#include <stdlib.h>
#include "42_libft/libft.h"

int	main(int ac, char **av)
{
	int		case_q;
	int		case_dq;

	char	*cmd;
	char	*var;
	char	**cmd_split;
	char	*read;
	int		i;
	int		j;

	while (1)
	{

		read = readline("minishell~$ ");
		i = 0;
		j = 0;
		case_q = 0;
		case_dq = 0;
		cmd = (char *)calloc(1000, sizeof(*cmd));
		if (!cmd)
			return (0);
		var = (char *)calloc(1000, sizeof(*var));
		if (!cmd)
			return (0);
		cmd_split = ft_split(read, ' ');
		cmd = ft_strjoin(cmd, cmd_split[0]);
		i = ft_strlen(cmd);
		while (read[i])
		{
			if (read[i] == '\"' && case_dq == 0 && case_q != 1)
			{
				cmd = ft_strjoin(cmd, "\""); // leave the q or dq in place
				case_dq = 1;
			}
			else if (read[i] == '\"' && case_dq == 1)
			{
				cmd = ft_strjoin(cmd, "\""); // leave the q or dq in place
				case_dq = 0;
			}
			else if (read[i] == '\'' && case_q == 0 && case_dq != 1)
			{
				cmd = ft_strjoin(cmd, "'"); // leave the q or dq in place
				case_q = 1;
			}
			else if (read[i] == '\'' && case_q == 1)
			{
				cmd = ft_strjoin(cmd, "'"); // leave the q or dq in place
				case_q = 0;
			}
			else if (read[i] == '$' && case_q == 0)
			{
				j = i + 1;
				while (read[j] && read[j] != '\'' && read[j] != '\"' && read[j] != ' '
					&& read[j] != '$')
					j++;
				j -= i;
				var = ft_memcpy(var, read + i + 1, j - 1);
				if (getenv(var))
					cmd = ft_strjoin(cmd, getenv(var));
				else
					cmd = ft_strjoin(cmd, " ");

				i += j - 1;
			}
			else if (read[i] == ' ')
				cmd = ft_strjoin(cmd, " ");
			else if (read[i] == '\'' && case_dq == 1)
				cmd = ft_strjoin(cmd, "\1'");
			else
			{
				char *m;
				m = (char *)calloc(2, sizeof(*m));
				*m = read[i];
				cmd = ft_strjoin(cmd, m);
			}
			i++;

		}
		printf("%s\n", cmd + 5);
		free(cmd);
		free(read);
	}
}