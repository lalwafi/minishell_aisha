/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/30 07:35:24 by lalwafi           #+#    #+#             */
/*   Updated: 2025/03/07 03:40:16 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "aish_libft/libft.h"

# include "readline/readline.h"
# include "readline/history.h"
# include <stdio.h>
# include <stdlib.h>
# include <stdint.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <signal.h>
# include <string.h>
# include <dirent.h>
# include <sys/stat.h>
# include <errno.h>
# include <termios.h>
# include <curses.h>
# include <term.h>
#define BUFF_SIZE 1024 

typedef struct	s_environment	t_environment;
typedef struct	s_shell			t_shell;
typedef struct	s_values		t_values;
typedef struct	s_command		t_command;
typedef enum	e_state			t_state;
typedef struct	s_direct		t_direct;

extern int g_sig;

typedef struct s_shell
{
	int				exit_code;			// exit code i think im not sure
	char			*input_L;			// the input line
	char			**pipe_split_L;		// input split by pipes
	int				parse_fail_L;		// 0 for pass, -1 for fail
	int				num_of_cmds;
	t_command		*commands;
	t_environment	*environment;
} t_shell;

typedef struct s_command
{
	char				**cmd_args;		// double array of arguments in command line including cmd;
	char				*cmd_line_L;	// the pipe split line to parse
	char				*words_L;		// for parsing
	int					num_of_redir;	// number of redirects in the line
	t_direct			*redir;			// redirects
	int					save_statues;	// save the statues of the command
	t_command			*next;
} t_command;

typedef struct s_environment
{
	char				*cwd;			// current working directory
	char				*owd;			// old working directory
	char				**path;			// $PATH variable split to double array, probably for execution
	char 				**export_env;	// Environment variables for export (what is this for?? -lyall)
	t_values			*vals;			// contains all the elements in env
}	t_environment;

typedef struct s_values
{
	char				*key; 			// before "=" (eg; USER)
	char				*value; 		// after "=" (eg; lalwafi)
	t_values			*next;
} t_values;

typedef enum e_state
{
	RE_INPUT,	// <
	RE_OUTPUT,	// >
	HERE_DOC,	// <<
	APPEND		// >>
}	t_state;

typedef struct s_direct
{
	char				*file; 	// file name
	t_state				direct; // what do to with the files
	t_direct			*next;
}	t_direct;

typedef struct s_context
{
	int					inputfd;
	int					outputfd;
	char				**args;
	char				*cmd;
	int					error;
	struct s_context	*next;
}	t_context;

typedef struct s_split		// for parsing
{
	char	**result;
	int		i;
	int		len;
	int		counter;
}	t_split;

// ================================================================================== //

// functions lyall
void		handle_signal(int signal);
void		initialize_shell(t_shell *shell);
t_command	*initialize_commands(void);
t_split		*init_split(void);
void		get_env(t_shell *shell, char **env);
char		*key_time(char *env);
void		make_values_node(char *key, t_shell *shell);
void		minishell(t_shell *shell);
char		**split_pipes(char const *s, char c);
char		**make_letters(t_split *split, char const *s, char c, int count);
t_split		*make_letters_2(t_split *sp, char const *s, char c);
int			make_words(char const *s, char c);
char		**one_word(char const *s, t_split *split);
char		**free_array(char **result);
int			skip_quotes(const char *str, int i);
char		*rmv_extra_spaces(char *str);
int			count_rmv_extra_spaces(int i, int j, char *str);
char		*rmv_extra_spaces_2(char *result, char *str, int i, int j);
int			open_quote_or_no(char *str);
int			count_pipes(char *str);
int			check_pipes(char *input);
char		**remake_env(t_environment *env);
char		**remake_path(t_environment *env);
char		*find_value(char *key, t_values *env);
int			parser(t_shell *shell);
void		parse_end(t_shell *shell);
bool		syntax_check(t_shell *shell);
bool		only_spaces(char *str);

// utils lyall

int			ft_strcmp_l(char *s1, char *s2);
char		*ft_strdup(const char *s1);
char 		*ft_substr_free(char *s, unsigned int start, size_t len);
char		*ft_strtrim_free(char *s1, char const *set);
char		*ft_strjoin_free(char *s1, char *s2, int flag);
int			ft_strncmp_lyall(const char *s1, const char *s2, size_t n);
int			values_size(t_values *vals);
t_values	*ft_lstlast_values(t_values *lst);
void		ft_lstadd_back_values(t_values **lst, t_values *new);
void		ft_lstclear_values(t_values *lst);
void		ft_lstdelone_values(t_values *prev, t_values *del, t_values *nxt);
int			ft_lstsize_cmds(t_command *lst);
t_command	*ft_lstlast_cmds(t_command *lst);
void		ft_lstadd_back_cmds(t_command **lst, t_command *new);
int			ft_lstsize_redir(t_direct *lst);
t_direct	*ft_lstlast_redir(t_direct *lst);
void		ft_lstadd_back_redir(t_direct **lst, t_direct *new);
void		ft_lstclear_redir(t_direct *lst);
char		*rmv_quotes(char *str);
int			count_rmv_quotes(char *str , int i, int len);
void		free_all(t_shell *shell);
void		free_cmds(t_shell	*shell);
void		free_env(t_environment *env);
bool		operator_valid(char *input);

// tokenize lyall

void		tokenize_it(t_shell *shell, char *str, int i);
int			tokenize_loop(t_shell *shell, t_command **ctemp, int i);
int			token_quotes(t_command **ctemp, int i);
char		*expand_them_vars(char *str, t_shell *shell);
char		*expand_word_vars(char *str, int i, int len, t_shell *sh);
char		*string_but_string_2(char *pushed, char *pusher, int start, int rmv);
char		*string_but_string(char *pushed, char *pusher, int start, int rmv);
char		*return_var(char *str, int start, int len, t_environment *env);
void		operator_tokens(t_shell *shell, t_command *cmds , int i);
char		*copy_file(char *str, int i, t_command *cmds, int start);
t_state		operators_check(char *str, int i);
void		print_enum(t_state en);
// void		print_commands(t_command *cmds);


// ================================================================================== //

// aisha utils

bool		is_valid_env(const char *env_var);
t_context	*create_context(void);
void		safe_close(int fd);

//aisha bulid_in

int			 my_cd(t_environment *env, char *path);
char		*get_new_path(t_environment *env, char *path);
int			update_env(t_environment *env, char *current_dir);
 void 		set_env_var(t_environment *env,  char *key, char *value);
char 		*ft_get_env(char *key, t_values *env);
int 		my_unset(t_values **head, char *args);
void 		print_list(t_environment *head) ;
int 		my_echo(t_context *context);
int			get_fd(t_context *ctx);
void		print_args(int fd, char **args, int i);
int 		ms_pwd(t_context *context);
char  		*add_quotes(char *value);
void		print_env(t_values *env, bool export, int fd);
int 		env_add(char *value, char ***env);
bool		ft_export(t_context *cntx, t_values *env, t_shell *shell);
int 		exec_bulidin( t_shell *shell,t_context *cntx, t_environment *env);
int			ft_env(t_values *env, t_context *context);
bool  		run_bulidin( t_shell *shell,t_context *context, t_environment *env);
bool  		is_bulidin(char *str);
int			ft_strcmp(char *s1, char *s2);
void		execution(t_shell *shell, t_environment *env);
void		exit_utils(t_shell *shell, t_context *cntx);
void		exit_utils2(t_shell *shell, char *arg, t_context *cntx);
void		free_exit(t_shell *shell, t_context *cntx);
int			ft_str_isnum(char *c);
int			ft_exit(t_shell *shell, t_context *cntx);
char		*find_path(char *cmd, char **env);
void		free_context_list(t_context *context);
bool		handle_heredoc(t_context *context, char *delim, t_shell *shell);
int			heredoc_child(int fds[2], char *delim, t_shell *shell);
void		heredoc_signal(int signum);
bool		find_heredoc_after(t_direct *direct);
t_context	*handle_heredocs(t_command *command, int inputfd, t_shell *shell);
t_context	*create_context_list(t_command *cmd, \
			t_environment *env, t_shell *shell);
void		free_context(t_context *context);
char		**copy_strs(char **strs);
void		free_context_list(t_context *context);
int			execute_context(t_shell *shell, t_context *context, t_environment *env);
int			execute_command( t_shell *shell, t_context *context, t_environment *env,int errnum);
void		handle_everything(t_context *context, t_command *commands, char **env);
void		handle_redirects(t_context *context, t_command *command);
void		handle_output(t_context *context, char *file, bool append);
void		handle_input(t_context *context, char *file, bool ignore);
int			handle_signaled(int signal);


#endif
