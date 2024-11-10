/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:27:09 by rboulaga          #+#    #+#             */
/*   Updated: 2024/11/10 23:12:54 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//var=..

// var
// varsssss
// var=


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
        if (ft_ncmp(global->env_copy[i], var, len + 1) == 0)//this is the same variable (change the varible value 1-free 2-strdup)
        {
            free(global->env_copy[i]);
            global->env_copy[i]= ft_strdup(var);
            return 1;
            // printf("this is the same variable (change the varible value 1-free 2-strjoin)\n"); // return 1
        }
        else if (ft_ncmp(global->env_copy[i], var, len) == 0 && var[len + 1] == '\0')
            return 1; // is just var'0'
        // else if (ft_ncmp(global->env_copy[i], var, l))
        // { 
            // printf("is not the same variable,, you should add them without free anything\n"); // return 1 or somthing else because is another case
        // }        
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
            return 1;
        
        //if return 1->> change variable
        // else we not change it
        i++;
    }  
    return 0;
}
