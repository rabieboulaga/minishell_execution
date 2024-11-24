#include "minishell.h"


void    ft_initialize(char **env, s_global *global)
{
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
        i++;
    }
}

int main(int argc, char **argv, char **env)
{
    char *rl;
	(void)argc;
	(void)argv;
    char **tmp;
    s_global *global;
    s_input *input;

    global = malloc(sizeof(s_global)); 
    ft_initialize(env, global);
    while(1)
    {
        rl = readline("minishell --> ");
        add_history(rl);
        input = parsing(rl);
		if(!input)
			continue;
        tmp = ft_split(input->command, ' ');
        // while(input->right)
        // {
        //         if(input->tok==STR)
        //         {
        //             printf("%s\n", input->command);
        //         } 
        //     input = input->right;
        // }
        builtins(tmp, global);
		// printf("command: %s\n", input->command);
    }
	return 0;
}