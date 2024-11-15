/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 23:27:09 by rboulaga          #+#    #+#             */
/*   Updated: 2024/11/14 02:05:51 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../minishell.h"

// void    free_list(char **str)
// {
//     int i;

//     i = 0;
//     while (str[i])
//     {
//         free(str[i])
//         i++;
//     }
// }

void    copying_II(s_global *global, char *v)
{
    int i;
    char **tmp;

    i = 0;
    while (global->env_copy[i])
        i++;
    tmp = malloc((i + 2) * sizeof(char *));
    i = 0;
    while (global->env_copy[i])
    {
        tmp[i] = global->env_copy[i];
        i++;
    }
    tmp[i++] = ft_strdup(v);
    tmp[i] = NULL;
    free(global->env_copy);
    global->env_copy = tmp;
}

// ------>>>>>>>var+=value
int     var_parser(char *v, s_global *global)
{
    int i;

    i = 0;
    while (v[i] && v[i] != '=')
    {
        if ((ft_isalpha(v[i]) || ft_isdigit(v[i]) || v[i] == '_' ) && ft_isdigit(v[0]) == 0)
            i++;
        else
        {
            printf("minishell: export: `%s': not a valid identifier\n", v);
            return 0;
        }
    }
    if (v[0] == '=')
    {
        printf("minishell: export: `%s': not a valid identifier\n", v);
        return 0;
    }        
    copying_II(global, v);
    return 1;
}

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

// void    copying(s_global *global)
// {
//     int i;

//     i = 0;
//     while (global->env_copy[i])
//         i++;
//     global->export = malloc((i + 1) * sizeof(char *));
//     i = 0;
//     while (global->env_copy[i])
//     {
//         global->export[i] = ft_strdup(global->env_copy[i]);
//         i++;
//     }    
// }

int     export_listing(char **cmd, s_global *global)
{
    int len;
    
    len = 0;
    if (!cmd[1])
    {
        // copying(global);
        while (global->env_copy[len])
            len++;
        sort_list(global, len);
        len = 0;
        while (global->env_copy[len])
        {
            printf("declare -x ");
            putstr(global->env_copy[len]);
            len++;
        }
        return (1);
    }
    return 0;
}

int     export(char **cmd, s_global *global)
{
    int i;
    int j;

    j = 0;
    i = 1;

    if (export_listing(cmd, global))
        return 1;
    while (cmd[i])
    {
        j = 0;
        if (check_variable(cmd[i] ,global))
            j = 1;
        if (j != 1 && var_parser(cmd[i], global))
            printf("this is good\n");      
        i++;
    }  
    return 0;
}
