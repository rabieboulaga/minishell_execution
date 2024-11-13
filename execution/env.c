/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/27 17:42:59 by rabia             #+#    #+#             */
/*   Updated: 2024/11/12 17:41:47 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int     env(char **cmd, s_global *global)
{
    int i;
    // int j = 0;
    // while (global->env_copy[j])
    //     j++;
    // printf("%d\n\n", j);
    
    i = 0;
    if (cmd[1])
    {
        printf("env: ‘%s’: No such file or directory\n", cmd[1]);
        return 1;
    }
    while (global->env_copy[i])
    {
        printf("%s\n", global->env_copy[i]);
        i++;
    }
    return (0);
}
// ‘%s’ check if there is any problem