/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:27:09 by rboulaga          #+#    #+#             */
/*   Updated: 2024/11/09 18:51:58 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
int check_variable(char *var ,s_global *global)
{
    int i;
    int len;

    i = 0;
    len = 0;
    while (var[len] && var[len] != '=')
        len++;
    while (global->env_copy[i])
    {    
        if (ft_ncmp(global->env_copy[i], var, len + 1) == 0)
        {
            printf("this is the same %s like-> %s\n", var , global->env_copy[i]);
            return 1;        
        }
        i++;
    }
    return 0;
}

int     putstr(char *str)
{
    int i;
    int flag = 0;
    //flag usage if there is more than one = and we need just the first one

    i = 0;
    while (str[i])
    {
        printf("%c", str[i]);
        if (str[i] == '=' && flag == 0)
            printf("\"");
        i++;
    }
    printf("\"\n");
    return 1;
}

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
        len = 0;
        while (global->export[len])
        {
            printf("declare -x ");
            putstr(global->export[len]);
            len++;
        }
        return (1);
    }
    return 0;
}

int     export(char **cmd, s_global *global)
{
    int i;

    i = 1;
    if (export_listing(cmd, global))
        return 1;
    while (cmd[i])
    {
        check_variable(cmd[i] ,global);
        //function number 1 for check if any variable like the first variable
// 
        //function number 2 for add the variable to
        i++;
    }  
    return 0;
}
