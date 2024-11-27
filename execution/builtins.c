/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rboulaga <rboulaga@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 11:24:54 by rabie             #+#    #+#             */
/*   Updated: 2024/11/27 22:38:41 by rboulaga         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    builtins(char **cmd ,s_global *global)
{    
    if (ft_ncmp("echo", cmd[0], 4) == 0 && ft_strlen(cmd[0]) == 4)
        echo(cmd);
    else if (ft_ncmp("pwd", cmd[0], 3) == 0 && ft_strlen(cmd[0]) == 3)
        pwd();
    else if (ft_ncmp("cd", cmd[0], 2) == 0 && ft_strlen(cmd[0]) == 2)
        cd(cmd);
    else if (ft_ncmp("env", cmd[0], 3) == 0 && ft_strlen(cmd[0]) == 3)
        env(cmd, global);
    else if (ft_ncmp("unset", cmd[0], 5) == 0 && ft_strlen(cmd[0]) == 5)
        unset(cmd, global);
    else if (ft_ncmp("export", cmd[0], 6) == 0 && ft_strlen(cmd[0]) == 6)
        export(cmd, global);
    else
        cmd_execution(cmd, global);
    free_list(cmd);
}

