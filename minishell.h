/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaubertin <aaubertin@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/04 09:25:41 by aaubertin         #+#    #+#             */
/*   Updated: 2024/12/08 12:23:38 by aaubertin        ###   ########.fr       */
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

 void   exit_shell(t_info *shell, t_commands commands);
 void pwd_shell(t_info *shell, t_commands commands, int end);
 void ft_printf_history(t_info *shell, int i);
 int ft_isnumeric(char *cmd);
 void history_shell(t_info *shell, t_commands commands, int end);
 int ft_is_valid_n_flag(char *cmd);
 void	echo_shell(t_info *shell, t_commands commands, int end);
 int handle_special_cd_args(t_info *shell, char **str, char *arg, int end);
 int validate_curr_dir(t_info *shell, char **current, char *pwd, int end);
 int update_directory(t_info *shell, char *str, int end);
 void cd_shell(t_info *shell, t_commands commands, int end);
 void remove_and_nullify_item(t_hashmap *hashmap, t_hash_item *item, unsigned long int i);
 void replace_with_next_item(t_hashmap *hashmap, t_hash_item *item, unsigned long int i);
void unlink_and_free_next_item(t_hashmap *hashmap, t_hash_item *item, char *key);
 int delete_in_hashmap(t_hashmap *hashmap, char *key);
 void detect_and_execute_command(t_info *shell, t_commands *commands);
 t_hashmap *duplicate_env_hashmap(t_hashmap *hashmap);
 void free_hashmap(t_hashmap *hashmap);
void env_shell(t_info *shell, t_commands commands, int end);
 int ft_is_valid_env_var_format(char *str);
 void handle_env_exit(t_info *shell, char *commands, t_hashmap *cpy_env, int end);
 void close_file_descriptors(t_info *shell, t_commands *commands);
 char *ft_path(t_info *shell, char *commands);
void ft_run_command(t_info *shell, t_commands *commands);
int ft_add_or_update_env(t_hashmap *env, char *str);
void configure_pipe(t_info *shell, int fd[2], int *count);
void free_execute_data(t_info *shell);
int ft_is_builtin_commands(const char *command);
int handle_builtin_commands(t_info *shell, t_commands commands, int end);
 void ft_execute_commands(t_info *shell);
 void redirect_io_for_command(t_commands *command);
 void create_child_process(t_info *shell, t_commands *command, int *pids, int count);
 void wait_for_processes(t_info *shell, int count);
 void setup_pipe_between_commands(t_commands *commands, t_commands *next_commands, int *fd);
 void run_command_in_pipeline(t_info *shell, int count);
 void    end_execution(char ***tab, int fd);
 void    execution(char  ***tab, char *command, char **env, char *path);
 void extract_key_value(char **var, char **key, char **value, int *count);
 int insert_custom_variables(t_info *shell, char **var, int *count);
 int ft_is_valid_identifier(char *key, int i, int expect_alpha);
 int process_export(t_info *shell, t_commands commands, int *count);
 void export_shell(t_info *shell, t_commands commands, int end);
 int find_char_index(char *str, char c);
 int fetch_hashmap_flag(t_hashmap *hashmap, char * key);
 int     ft_in_charset(const char *str, char *charset);
 char    *ft_in_var2(char *token, int index, t_info *shell, char *temp);
 char    *ft_in_var(char *token, int index, t_info *shell);
 char    *handle_variable_expand(t_info *shell, char *token, int state[2], int index);
 void    ft_expand(t_info *shell, char **tokenize);
 void    update_tab(char **tab, int index, int tab_len);
 char    *hanle_variable_home(char   *token, int index, int state[2], char *home);
 void ft_fd_utils(char *path, int state[2], t_info *shell);
 int ft_fd(int fd, char *path, int state[2], t_info *shell);
 t_commands *handle_output(t_commands *node, char **commands[2], int *i, t_info *shell);
 t_commands *handle_output_append(t_commands *node, char **commands[2], int *i, t_info *shell);
t_commands  *ft_node(t_info *shell, t_commands *node, char **commands[2], int *i);
void ft_node_error(char **commands[2], int *i, t_info *shell);
char **insert_token(char **commands, char *token, int index);
t_commands *handle_input(t_commands *node, char **commands[2], int *i, t_info *shell);
void ft_print_error2(int error);
void ft_print_error(char *argument, int error);
int   count_in_word(char *str, char *sep, int nb);
char    **ft_create_in_word(char **word, char *str, char *sep, int index[3]);
char    **ft_split_in_word(const char *str, char *sep);
char    **insert_in_word(char ***word, char **new_word, int index);
int     count_word(char *str, char *sep, int nb[2]);
char    **create_word(char **word, char *str, char *sep, int index[3]);
char    **ft_split_str(char *str, char *sep);
char    **ft_tabcpy(char **tokenize);
int     ft_len_token(char *token);
char    *ft_cut_token(char *token);
char    **ft_cut_tokenize(char **tokenize);
t_list  *ft_list_update(t_info *shell, char **tokenize, int index);
t_commands  *ft_create_node(void);
void    free_command(void *content);
t_list  *ft_exit_error(char **tokenize, t_list *commands, char **temp);
char *ft_heredoc_line(char *str[2], size_t size, char *end_heredoc, char *error);
int ft_heredoc_fd(char *end_heredoc, t_info *shell);
void ft_heredoc_error(char **commands, int *i, t_info *shell, t_commands *node);
t_commands *configure_heredoc_input(t_commands *node, char **commands[2], int *i, t_info *shell);
char *extract_key(char *line);
char    *extract_value(char *line);
t_hashmap   *creating_table(unsigned int size);
t_hashmap   *init_hashmap(char  **envp);
unsigned long int   djb2_hash(char *key, unsigned int size);
t_hash_item     *new_hashmap_item(char *key, char *value, int status);
void    free_item_hashmap(t_hash_item *item);
int new_item_in_hashmap(int i, t_hashmap *table, t_hash_item *new_item);
t_hash_item     *insertion_in_hashmap(t_hashmap *table, char *key, char *value, int status);
void hashmap_replace_value(int status, t_hash_item *current_item, char *value, t_hash_item *new_item);
void    hashmap_collisison(int status, t_hashmap *table,unsigned long int i, t_hash_item *new_item);
char    *cmds_in_hashmap(t_hashmap *table, char *key);
char	*ft_strjoin_3(char const *s1, char const *s2);
char    **hashmap_in_tab(t_hashmap *env_tab, char ***tab, unsigned int i, unsigned int j);
t_hash_item *search_in_hashmap(t_hashmap *hashmap, char *key);
void remove_env_var(t_info *shell, char *key);
t_info  *valid_env(t_info *shell, char **argv);
void create_and_store_pid(t_info *shell);
void    init_shell(t_info   *shell, char **argv, char **envp);
char    *ft_create_token(char *str);
void    input_manager(t_info *shell, char *str);
void ft_close(t_info *shell, t_commands *command);
void ft_free_item(t_hash_item *item);
void ft_free_hashmap(t_hashmap *hashmap);
void ft_exit_all(t_info *shell);
void    manage_exit(t_info *shell, char *arguments, int error, int end);
void process_sigint_for_execution(int signal_number);
void setup_execution_signals_handler(void);
void process_sigint_for_input(int signal_number);
void setup_input_signals_handler(void);
void	print_env(t_hash_item *env, int options);
void	hashmap_print_table(t_hashmap *table, int options);
int	ft_tab_len(char **tab);
void	ft_freetab(char ***tab);
char	**ft_extend_tab(char **tab, char *str);
char	*ft_strjoin_arg(unsigned int size, ...);
void    save_cmds_in_history(t_info *shell, char *cmd);
char    *ft_os(t_info *shell);
char    *ft_user(t_info *shell);
char    *ft_directory(t_info *shell);
char    *start_prompt(t_info *shell);
char    *prompt(t_info *shell);
int process_unset_command(t_info *shell, t_commands command, int *status);
void unset_shell(t_info *shell, t_commands command, int end);

#endif