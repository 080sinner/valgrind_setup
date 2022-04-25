#include "setup_val.h"
# define RED printf("\033[1;31m")
# define DEFAULT printf("\033[0m")

int		execute_valgrind_command(void)
{
	char	*str;
	char	*val_cmd;

	RED;
	printf("Please type in the command to execute your program, for example \"./push_swap 5 3 94 6\"\033[0m\n");
	str = get_next_line(1);
	if (ft_strcmp(str, "\n"))
	{
		free(str);
		return (0);
	}
	str[ft_strlen(str) - 1] = ';';
	char *rm_exec = ft_strdup(str);
	if (ft_strchr(rm_exec, ' '))
		*(ft_strchr(rm_exec, ' ')) = '\0';
	char *tmp = rm_exec;
	rm_exec = ft_strjoin(tmp, "\"");
	free(tmp);
	val_cmd = ft_strjoin(str, "rm -f ");
	free(str);
	str = ft_strjoin(val_cmd, rm_exec);
	free(val_cmd);
	val_cmd = ft_strjoin("docker run -ti -v $(PWD):/test memory-test:0.1 bash -c \"cd /test/; make && valgrind --leak-check=full ", str);
	system(val_cmd);
	free(val_cmd);
	return (0);
}

int	check_if_correct_dir(void)
{
	FILE *file;
	if ((file = fopen("setup_val.h", "r")))
	{
		RED;
		printf("Please drag this executable into the folder of your program and run it again.\n");
		DEFAULT;
		fclose(file);
		return (0);
	}
	else
		return (1);
}

int main()
{
	if (!check_if_correct_dir())
		return (0);
	execute_valgrind_command();
}