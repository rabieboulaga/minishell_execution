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
void print_tree_helper(s_input *input, int depth)
{
    // Create indentation string based on depth
    char indent[depth * 2 + 1];
    for (int i = 0; i < depth * 2; i++) {
        indent[i] = ' ';
    }
    indent[depth * 2] = '\0';

    // Handle NULL input
    if (input == NULL) {
        printf("%s(null)\n", indent);
        return;
    }

    // Print current node details with indentation
    printf("%sNode {\n", indent);
    
    // Print token if it's a pipe
    if (input->tok == PIPE) {
        printf("%s  Token: PIPE\n", indent);
    }

    // Print command if exists
    if (input->command != NULL) {
        printf("%s  Command: %s\n", indent, input->command);
    }

    // Recursively print left and right subtrees with increased depth
    printf("%s  Left Subtree:\n", indent);
    print_tree_helper(input->left, depth + 1);
    
    printf("%s  Right Subtree:\n", indent);
    print_tree_helper(input->right, depth + 1);
    
    printf("%s}\n", indent);
}

// Wrapper function to start the tree printing from depth 0
void print_tree(s_input *input)
{
    print_tree_helper(input, 0);
}

int main(int argc, char **argv, char **env)
{
    char *rl;
	(void)argc;
	(void)argv;
    char **tmp;// free if the user command is pipes.. (++)
    
    s_global *global;
    s_input *input;

    global    = malloc(sizeof(s_global)); 
    ft_initialize(env, global);
    while(1)
    {
        rl = readline("minishell --> ");
        add_history(rl);
        input = parsing(rl);
		if(!input)
			continue;
        if (input->tok == STR)
            tmp = ft_split(input->command, ' ');
        exe(tmp , input, global);
        // if (input->tok == PIPE)    
        //     printf("pipe\n");
		// printf("command: %s\n", input->command);
    }
	return 0;
}