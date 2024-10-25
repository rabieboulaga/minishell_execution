#include "minishell.h"


void    ft_initialize(char **env, s_global *global)
{
    global = malloc(sizeof(s_global)); 
    if (!global)
        return ;; 
    int i = 0;
    while(env[i])
        i++;
    global->env_copy = malloc((i + 1) * sizeof(char *));
    if(!global->env_copy)
        return;
    i = 0;
    while(env[i])
    {
        global->env_copy[i] = ft_strdup(env[i]);
        printf("%s\n", global->env_copy[i]);
        i++;
    }
}

int main(int argc, char **argv, char **env)
{
    char *rl;
	(void)argc;
	(void)argv;
    char **tmp;
    s_global *global = NULL;
    s_input *input;

    while(1)
    {
        rl = readline("minishell --> ");
        add_history(rl);
        ft_initialize(env, global);
        input = parsing(rl);
		if(!input)
			continue;
        tmp = ft_split(input->command, ' ');
        builtins(tmp, global);
		// printf("command: %s\n", input->command);
    }
	return 0;
}