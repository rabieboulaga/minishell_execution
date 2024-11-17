/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_execution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/15 18:39:32 by rboulaga          #+#    #+#             */
/*   Updated: 2024/11/17 23:45:08 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_list(char **str)
{
    int i;

    i = 0;
    while (str[i])
    {
        free(str[i]);
        i++;
    }
    free(str);
}

int     help(char **cmd, s_global *global)
{
    char **test;
    char *tmp;
    int i;

    tmp = global->path;
    i = 0;
    while (*tmp != '=')
        tmp++;
    tmp++;
    if (*tmp)
    {
        test = ft_split(tmp, ':');
        while (test[i])
        {
            free(global->path);
            tmp = ft_strjoin(test[i], "/");
            global->path = ft_strjoin(tmp, cmd[0]);
            if (access(global->path, X_OK) == 0)
                return(free_list(test), 1);
            i++;
        }
    }
    return 0;
}

int     find_path(char **cmd, s_global *global)
{
    int i;
    
    i = 0;
    while (global->env_copy[i])
    {
        if (ft_ncmp("PATH", global->env_copy[i], 4) == 0 && global->env_copy[i][4] == '=')
        {    
            global->path = ft_strdup(global->env_copy[i]);
            if (help(cmd, global))
                return 1;
        }
        i++;
    }
    return 0;
}

int     cmd_execution(char **cmd, s_global *global)
{
    
    if (find_path(cmd, global))
    {
        printf("all is good\n ");
    }
    else
        printf("wa hmaaaar\n");
        
    
    
    return 0;
}