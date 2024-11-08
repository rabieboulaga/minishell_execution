/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:27:09 by rboulaga          #+#    #+#             */
/*   Updated: 2024/11/08 15:05:09 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    sort_list(s_global *global, int len)
{
    int i;
    char *tmp;
    int j;

    i = 0;
    j = 0;
    while (i < len - 1)
    {
        j = 0;
        while (j < len - i - 1)
        {
            if (global->export[j][0] > global->export[j + 1][0])
            {
                tmp = global->export[j];
                global->export[j] = global->export[j + 1];
                global->export[j + 1] = tmp;
            }
            j++;
        }
        i++;
    }
}

void    copying(s_global *global)
{
    int i;

    i = 0;
    while (global->env_copy[i])
        i++;
    global->export = malloc((i + 1) * sizeof(char *));
    i = 0;
    while (global->env_copy[i])
    {
        global->export[i] = ft_strdup(global->env_copy[i]);
        i++;
    }    
}

int     export_listing(char **cmd, s_global *global)
{
    int len;
    
    len = 0;
    if (!cmd[1])
    {
        if (!global->export)
            copying(global);
        while (global->export[len])
            len++;
        sort_list(global, len);
        
    }
    return 0;
}

int     export(char **cmd, s_global *global)
{
    int i = 0;
    export_listing(cmd, global);    
    while (global->export[i])
    {
        printf("%s\n", global->export[i]);
        i++;
    }
    return 0;
}
