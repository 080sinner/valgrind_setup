#include "setup_val.h"
# define RED printf("\033[1;31m")
# define DEFAULT printf("\033[0m")
# define BLUE printf("\033[1;34m")

int		execute_valgrind_command(char *str, int r_flag)
{
	char	*val_cmd;

	if (!str)
		return (1);
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
	if (!r_flag)
		val_cmd = ft_strjoin("docker run -ti -v $(PWD):/test memory-test:0.1 bash -c \"cd /test/; make && valgrind --leak-check=full ", str);
	else
		val_cmd = ft_strjoin("docker run -ti -v $(PWD):/test memory-test:0.1 bash -c \"cd /test/; make && valgrind --leak-check=full --show-leak-kinds=all ", str);
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

char	*build_cmd_str(char **argv, int *r_flag)
{
	char	*cmd_str;
	char	*tmp;
	int		i;

	if (argv[1] && argv[1][0] == '-' && argv[1][1] == 'R')
	{
		*r_flag = 1;
		return (build_cmd_str(++argv, r_flag));
	}
	if (!argv[1])
		return (NULL);
	cmd_str = ft_strjoin(argv[1], " ");
	for (i = 2; argv[i]; i++)
	{
		tmp = cmd_str;
		cmd_str = ft_strjoin(tmp, argv[i]);
		free(tmp);
		tmp = cmd_str;
		cmd_str = ft_strjoin(tmp, " ");
		free(tmp);
	}
	cmd_str[ft_strlen(cmd_str) - 1] = ';';
	return (cmd_str);
}

int main(int argc, char *argv[])
{
	int	r_flag = 0;

	RED;
	if (argc < 2)
		return (printf("Invalid usage:\033[0m\n\033[1;34m./exec_valgrind ./your_program arg1 arg2\033[0m\n\033[1;31mIf you want to see still reachable leaks use it like this:\n\033[1;34m./exec_valgrind -R ./your_program arg1 arg2\033[0m\n\033[1;31mIf you want to see line numbers add the gcc flag -g to your Makefile\033[0m\n"));
	if (!check_if_correct_dir())
		return (0);
	printf("Starting Valgrind ...\033[0m\n");
	char *cmd_str = build_cmd_str(argv, &r_flag);
	execute_valgrind_command(cmd_str, r_flag);
}