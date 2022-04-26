#include "setup_val.h"
# define GREEN printf("\033[0;32m")
# define DEFAULT printf("\033[0m")


int	check_for_dockerfile(void)
{
	FILE *file;
	if ((file = fopen("Dockerfile", "r")))
	{
		fclose(file);
		return (1);
	}
	return (0);
}

int	check_if_42repo_exists(void)
{
	FILE *file;
	char *path = ft_strjoin(getenv("HOME"), "/42toolbox");
	if ((file = fopen(path, "r")))
	{
		free(path);
		fclose(file);
		return (1);
	}
	else
	{
		free(path);
		return (0);
	}
}

int	init_docker(void)
{
	char	*toolbox_path;

	if (!check_if_42repo_exists())
	{
		GREEN;
		printf("\nThis program requires the 42toolbox to work properly.\nIf you already cloned it press Y,\notherwise press any key to continue\n");
		DEFAULT;
		char c = getchar();
		fflush(STDIN_FILENO);
		if (ft_tolower(c) != 'y')
		{
			system("git clone https://github.com/alexandregv/42toolbox.git ~/42toolbox");
			toolbox_path = ft_strdup("~/");
		}
		else
		{
			GREEN;
			printf("Please type in the path to the 42toolbox\033[0m\n");
			toolbox_path = get_next_line(1);
			if (ft_strcmp(toolbox_path, "\n"))
			{
				free(toolbox_path);
				toolbox_path = ft_strdup("~/");
			}
			else
				toolbox_path[ft_strlen(toolbox_path) - 1] = '\0';
		}
	}
	else
		toolbox_path = ft_strdup("~/");
	GREEN;
	printf("\nStarting Docker ...\033[0m\n");
	char *tmp = toolbox_path;
	if (tmp[ft_strlen(tmp) - 1] == '/')
		toolbox_path = ft_strjoin(tmp, "42toolbox/init_docker.sh");
	else
		toolbox_path = ft_strjoin(tmp, "/42toolbox/init_docker.sh");
	free(tmp);
	if (system(toolbox_path))
	{
		free(toolbox_path);
		exit(printf("\033[1;31m\nCouldn't start Docker\033[0m\n"));
	}
	sleep(30);
	return (0);
}

int main(void)
{
	char	c;

	if (!check_for_dockerfile())
	{
		GREEN;
		printf("Creating Dockerfile ...\033[0m\n\n");
		system("touch Dockerfile");
		system(">Dockerfile printf \"FROM ubuntu:16.04\n\nRUN apt-get update\nRUN apt-get upgrade -y\nRUN apt-get install g++ valgrind -y\nRUN apt-get update && apt-get install make\nRUN apt-get install libreadline6 libreadline6-dev\"");
	}
	GREEN;
	printf("If you started Docker already press Y,\notherwise press any key to continue\n");
	DEFAULT;
	c = getchar();
	fflush(STDIN_FILENO);
	if (ft_tolower(c) != 'y')
		init_docker();
	if (system("docker build -t memory-test:0.1 ."))
		return (printf("\033[1;31m\nCouldn't build Docker image\033[0m\n"));
	GREEN;
	printf("\nYou are ready to run exec_valgrind inside of the folder of your program.");
	DEFAULT;
	getchar();
	return (0);
}
