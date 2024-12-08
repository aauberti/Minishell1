/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:25:41 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/07 19:04:01 by aaubertin        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include"libft.h"
# include <fcntl.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <stdarg.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <signal.h>
# include <errno.h>
# include <sys/ioctl.h>
# include <dirent.h>

 
 

extern int shell_signal;

enum e_shell
{
    SUCCESS,
    FAILURE,
    ERROR,
    INVALID_ARGS,
    FORK_ERROR,
    SYNTAX_ERROR,
    PIPE_ERROR,
    UNCLOSED_QUOTE,
    HASH_TABLE_FULL,
    OUT_OF_MEMORY,
    COMMAND_NOT_FOUND,
    IS_A_DIRECTORY,
    NOT_A_DIRECTORY,
    HISTORY_BAD_ARG,
    HISTORY_BAD_ARGS,
    CD_ERROR,
    NO_PERMISSION = 126,
    FILE_NOT_FOUND = 127
};

typedef struct s_commands
{
    int     fd1;
    int     fd2;
    char    *path;
    char    **command;
}   t_commands;

typedef struct s_hash_item
{
    char    *key;
    char    *value;
    int     status;
    struct s_hash_item *next;
}   t_hash_item;

typedef struct s_hashmap
{
    unsigned    int size;
    unsigned    int count;
    t_hash_item **item;
}   t_hashmap;

typedef struct s_info
{
    t_hashmap   *env;
    char        **history;
    t_list      *commands;
    pid_t       pid; 
    pid_t       *pids;
    char        *old_pwd;
    int         uid;
    int         exit_status;
}   t_info;

 void    free_item_hashmap(t_hash_item *item);
 void hashmap_replace_value(int status, t_hash_item *current_item, char *value, t_hash_item *new_item);
 void    hashmap_collisison(int status, t_hashmap *table,unsigned long int i, t_hash_item *new_item);
 t_hashmap   *init_hashmap(char  **envp);
 void	hashmap_print_table(t_hashmap *table, int options);
 t_hash_item     *insertion_in_hashmap(t_hashmap *table, char *key, char *value, int status);
 unsigned long int   djb2_hash(char *key, unsigned int size);
 char    *cmds_in_hashmap(t_hashmap *table, char *key);
 char    **hashmap_in_tab(t_hashmap *env_tab, char ***tab, unsigned int i, unsigned int j);
 char	**ft_extend_tab(char **tab, char *str);
 void	ft_freetab(char ***tab);
 void    execution(char  ***tab, char *command, char **env, char *path);
 void    save_cmds_in_history(t_info *shell, char *cmd);
 char	*ft_strjoin_arg(unsigned int size, ...);
 char    *prompt(t_info *shell);
 void    init_shell(t_info   *shell, char **argv, char **envp);
 char    **ft_split_str(char *str, char *sep);
 char    **ft_split_in_word(const char *str, char *sep);
 int	ft_tab_len(char **tab);
 char    **insert_in_word(char ***word, char **new_word, int index);
 void    ft_expand(t_info *shell, char **tokenize);
 char    *hanle_variable_home(char   *token, int index, int state[2], char *home);
 void    update_tab(char **tab, int index, int tab_len);
 t_list  *ft_exit_error(char **tokenize, t_list *commands, char **temp);
 void    free_command(void *content);
 void    manage_exit(t_info *shell, char *arguments, int error, int end);
 
#endif