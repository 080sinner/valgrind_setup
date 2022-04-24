#include "setup_val.h"
# define GREEN printf("\033[0;32m")
# define DEFAULT printf("\033[0m")


int	check_if_42repo_exists(void)
{
	FILE *file;
	char *path = ft_strjoin(getenv("HOME"), "/42toolbox/init_docker.sh");
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
		printf("\nThis program needs the 42toolbox to setup Docker, but it couldn't find it at the usual place.\nIf you didn't clone it yet, press Y,\notherwise press any key and type in the path afterwards.\n");
		DEFAULT;
		char c = getchar();
		fflush(STDIN_FILENO);
		if (ft_tolower(c) == 'y')
		{
			system("git clone https://github.com/alexandregv/42toolbox.git ~/42toolbox");
			toolbox_path = ft_strdup("~/");
		}
		else
		{
			GREEN;
			printf("Please type in the path to the 42toolbox\n");
			DEFAULT;
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
	{
		toolbox_path = ft_strdup("~/");
		GREEN;
		printf("\n42toolbox location found\n");
		DEFAULT;
	}
	GREEN;
	printf("Starting Docker ...\n");
	DEFAULT;
	char *tmp = toolbox_path;
	toolbox_path = ft_strjoin(tmp, "42toolbox/init_docker.sh");
	free(tmp);
	if (system(toolbox_path))
		exit(1);
	return (0);
}

int main(void)
{
	char	c;

	GREEN;
	printf("If you did not start Docker yet press Y,\notherwise press any key to continue\n");
	DEFAULT;
	c = getchar();
	fflush(STDIN_FILENO);
	if (ft_tolower(c) == 'y')
		init_docker();
	GREEN;
	printf("If you don't have a Dockerfile inside of this folder yet press Y,\notherwise press any key to continue\n");
	DEFAULT;
	c = getchar();
	fflush(STDIN_FILENO);
	if (ft_tolower(c) == 'y')
	{
		GREEN;
		printf("Creating Dockerfile ...\n\n");
		DEFAULT;
		system("touch Dockerfile");
		system(">Dockerfile printf \"FROM ubuntu:16.04\n\nRUN apt-get update\nRUN apt-get upgrade -y\nRUN apt-get install g++ valgrind -y\nRUN apt-get update && apt-get install make\nRUN apt-get install libreadline6 libreadline6-dev\"");

	}
	if (system("docker build -t memory-test:0.1 ."))
		return (printf("\033[1;31mCouldn't build Docker image\033[0m\n"));
	GREEN;
	printf("\nYou are ready to run execute_valgrind inside of the folder of your program.");
	DEFAULT;
	getchar();
	return (0);
}
