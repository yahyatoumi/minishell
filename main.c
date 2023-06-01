#include "minishell.h"

int status;

int ft_isalpha(int c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
	{
		return (1);
	}
	return (0);
}

int len_till_dollar(char *str)
{
	int i;

	i = 0;
	while (str[i] && ft_isalpha(str[i]))
		i++;
	return (i);
}

int how_many_dollars(char *str)
{
	int i;
	int x;

	i = 0;
	x = 0;
	while (str[i])
	{
		if (str[i] == '$')
			x++;
		i++;
	}
	return (x);
}

void append_to_value_arr(char **arr, char *new_value)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	arr[i++] = new_value;
	arr[i] = 0;
}

int arr_len(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
		i++;
	return (i);
}

void free_arr(char **arr)
{
	int i;

	i = 0;
	while (i < arr_len(arr))
		free(arr[i++]);
	free(arr);
}

char *ft_strdup_2(char *start, int len)
{
	int i;
	char *ret;

	i = 0;
	ret = (char *)malloc(len + 1);
	while (i < len)
	{
		ret[i] = start[i];
		i++;
	}
	ret[i] = 0;
	return (ret);
}

char *ft_strdup_3(char *start, int *add)
{
	t_params_2 p;

	p.i = 0;
	p.j = 0;
	p.d_lock = 0;
	p.s_lock = 0;
	p.holder = (char *)malloc(ft_strlen(start) + 1);
	while (start[p.i] && ft_isalpha(start[p.i]))
	{
		if (p.d_lock && start[p.i] == '\'')
			p.holder[p.j++] = start[p.i];
		else if (p.s_lock && start[p.i] == '"')
			p.holder[p.j++] = start[p.i];
		else if (!p.d_lock && start[p.i] == '"')
			p.d_lock = 1;
		else if (!p.s_lock && start[p.i] == '\'')
			p.s_lock = 1;
		else if (p.d_lock && start[p.i] == '"')
			p.d_lock = 0;
		else if (p.s_lock && start[p.i] == '\'')
			p.s_lock = 0;
		else if (!p.s_lock && !p.d_lock && start[p.i] == ' ')
			break;
		else
			p.holder[p.j++] = start[p.i];
		p.i++;
	}
	p.holder[p.j] = 0;
	*add = *add + 0;
	printf("returned %s i==%i\n", ft_strdup(p.holder), p.i);
	return (ft_strdup(p.holder));
}

t_token *make_tokens_1(char *holder, char *word_start, int *j)
{
	t_token *token;
	t_token *token2;

	token = NULL;
	token2 = NULL;
	if (ft_strlen(holder))
	{
		token = (t_token *)malloc(sizeof(*token));
		if (!token)
			return 0;
		token->token_chars = ft_strdup(holder);
		printf("token == %s\n", token->token_chars);
		token->type = 0;
		token->next = NULL;
	}
	token2 = (t_token *)malloc(sizeof(*token));
	if (!token2)
		return 0;
	token2->token_chars = ft_strdup_2(word_start, len_till_dollar(word_start + 1) + 1);
	printf("token2 == %s\n", token2->token_chars);
	token2->type = 2;
	token2->next = NULL;
	if (ft_strlen(holder))
	{
		token->next = token2;
		*j = *j + ft_strlen(token->token_chars);
	}
	else
		token = token2;
	*j = *j + ft_strlen(token2->token_chars);
	return token;
}

t_token *make_tokens_2(char *holder, char *word_start, int *j)
{
	t_token *token;
	t_token *token2;

	token = NULL;
	token2 = NULL;
	printf("inko %s\n", word_start);
	printf("holder == %s\n", holder);
	if (ft_strlen(holder))
	{
		token = (t_token *)malloc(sizeof(*token));
		if (!token)
			return 0;
		token->token_chars = ft_strdup(holder);
		token->type = 0;
		token->next = NULL;
	}
	token2 = (t_token *)malloc(sizeof(*token));
	if (!token2)
		return 0;
	token2->token_chars = ft_strdup_3(word_start + 1, j);
	token2->type = 2;
	token2->next = NULL;
	if (token)
	{
		token->next = token2;
		*j = *j + ft_strlen(token->token_chars);
	}
	else
		token = token2;
	*j = *j + 1;
	// printf("here 666666666 %i\n", (int)ft_strlen(token2->token_chars));
	return token;
}

t_token *make_tokens_3(char *holder, int *j)
{
	t_token *token;
	t_token *token2;

	token = NULL;
	token2 = NULL;
	if (ft_strlen(holder))
	{
		token = (t_token *)malloc(sizeof(*token));
		if (!token)
			return 0;
		token->token_chars = ft_strdup(holder);
		token->type = 0;
		token->next = NULL;
	}
	token2 = (t_token *)malloc(sizeof(*token));
	if (!token2)
		return 0;
	token2->token_chars = ft_strdup("$?");
	token2->type = 2;
	token2->next = NULL;
	if (token)
	{
		token->next = token2;
		*j = *j + ft_strlen(token->token_chars);
	}
	else
		token = token2;
	*j = *j + 2;
	return token;
}

t_token *make_tokens_4(char *holder, char *word_start, int *j)
{
	t_token *token;
	t_token *token2;

	token = NULL;
	token2 = NULL;
	if (ft_strlen(holder))
	{
		token = (t_token *)malloc(sizeof(*token));
		if (!token)
			return 0;
		token->token_chars = ft_strdup(holder);
		token->type = 0;
		token->next = NULL;
	}
	if (word_start[1] == word_start[0])
	{
		token2 = (t_token *)malloc(sizeof(*token2));
		if (!token2)
			return 0;
		token2->token_chars = ft_strdup_2(word_start, 2);
		token2->type = 1;
		token2->next = NULL;
		if (token)
		{
			token->next = token2;
			*j += ft_strlen(token->token_chars);
		}
		else
			token = token2;
		*j += ft_strlen(token2->token_chars);
		return token;
	}
	else
	{
		printf("         money       money     money --%s--\n", holder);
		token2 = (t_token *)malloc(sizeof(*token2));
		if (!token2)
			return 0;
		token2->token_chars = ft_strdup_2(word_start, 1);
		token2->type = 1;
		token2->next = NULL;
		if (token)
		{
			token->next = token2;
			*j += ft_strlen(token->token_chars);
			printf("len == %i\n", (int)ft_strlen(token->token_chars));
		}
		else
			token = token2;
		*j += ft_strlen(token2->token_chars);
		printf("len == %i\n", (int)ft_strlen(token2->token_chars));
		return token;
	}
}

void new_tok_helper(t_params_1 *params, char *word_start)
{
	params->i = 0;
	params->s_lock = 0;
	params->d_lock = 0;
	params->token = NULL;
	params->sign_lock = 0;
	params->holder = (char *)malloc(ft_strlen(word_start) + 2);
	params->holder[0] = 0;
	while (word_start[params->i] == ' ')
		params->i++;
	params->x = 0;
}

t_token *new_tok_helper_2(t_params_1 *params, int *j)
{
	params->holder[params->x] = 0;
	params->token = (t_token *)malloc(sizeof(*params->token));
	if (!params->token)
		return 0;
	params->token->token_chars = ft_strdup(params->holder);
	*j = *j + params->i;
	params->token->type = 0;
	params->token->next = NULL;
	printf("didididididid\n");
	return (params->token);
}

int ft_newtok_2(int *j, t_params_1 *params)
{
	*j += 1;
	if (params->sign_lock)
		return 1;
	params->d_lock = 1;
	return 0;
}

int ft_newtok_3(int *j, t_params_1 *params)
{
	*j += 1;
	if (params->sign_lock)
		return 1;
	params->s_lock = 1;
	return 0;
}

int ft_newtok_4(int *j, t_params_1 *params)
{
	*j += 1;
	if (params->sign_lock)
		return 1;
	params->d_lock = 0;
	return 0;
}

int ft_newtok_5(int *j, t_params_1 *params)
{
	*j += 1;
	if (params->sign_lock)
		return 1;
	params->s_lock = 0;
	return 0;
}

int ft_newtok_while_3(char *str, t_params_1 *p, int *j)
{
	if (p->s_lock && str[p->i] == '\'')
	{
		if (ft_newtok_5(j, p))
			return (2);
	}
	else if (str[p->i] == '$' && ft_isalpha(str[p->i + 1]) && !p->s_lock && !p->d_lock)
		return (p->token = make_tokens_1(p->holder, str + p->i, j), 1);
	else if (str[p->i] == '$' && (str[p->i + 1] == '"' || str[p->i + 1] == '\'') && !p->s_lock && !p->d_lock)
		return (p->token = make_tokens_2(p->holder, str + p->i, j), 1);
	else if (str[p->i] == '$' && str[p->i + 1] == '?' && !p->s_lock && !p->d_lock)
		return (p->token = make_tokens_3(p->holder, j), 1);
	else if (!p->s_lock && !p->d_lock && (str[p->i] == '>' || str[p->i] == '<'))
		return (p->token = make_tokens_4(p->holder, str + (p->i), j), 1);
	else if (!p->s_lock && !p->d_lock && str[p->i] == ' ')
		return (2);
	if (str[p->i] == '$')
		p->sign_lock = 1;
	p->holder[p->x++] = str[p->i];
	p->holder[p->x] = 0;
	return (0);
}

int ft_newtok_while_2(char *word_start, t_params_1 *params, int *j)
{
	if (params->d_lock && word_start[params->i] == '\'')
		return (params->holder[params->x++] = word_start[params->i], 2);
	else if (params->s_lock && word_start[params->i] == '"')
		return (params->holder[params->x++] = word_start[params->i], 2);
	else if (!params->d_lock && word_start[params->i] == '"')
	{
		if (ft_newtok_2(j, params))
			return (1);
		return (2);
	}
	else if (!params->s_lock && word_start[params->i] == '\'')
	{
		if (ft_newtok_3(j, params))
			return (1);
		return (2);
	}
	else if (params->d_lock && word_start[params->i] == '"')
	{
		if (ft_newtok_4(j, params))
			return (1);
		return (2);
	}
	return (0);
}

t_token *ft_newtok_while(char *word_start, t_params_1 *params, int *j)
{
	int helper;

	while (word_start[params->i])
	{
		printf("wordstart == %c\n", word_start[params->i]);
		helper = ft_newtok_while_2(word_start, params, j);
		if (helper == 1)
			break;
		else if (helper == 2)
			helper = 2;
		else
		{
			helper = ft_newtok_while_3(word_start, params, j);
			if (helper == 1)
				return params->token;
			if (helper)
				break;
		}
		params->i++;
	}
	return (params->token);
}

t_token *ft_newtok(char *word_start, int *j)
{
	t_params_1 params;

	printf("word start [i] == %c\n", word_start[0]);
	new_tok_helper(&params, word_start);
	if (ft_newtok_while(word_start, &params, j))
	{
		printf("new tok == %s\n", params.token->token_chars);
		return params.token;
	}
	while (word_start[params.i] == ' ')
		params.i++;
	return (new_tok_helper_2(&params, j));
}

// int cmds_counter(char **cmds)
// {
// 	int i;

// 	i = 0;
// 	while (cmds[i])
// 	{
// 		// printf("%s****\n", cmds[i]);
// 		i++;
// 	}
// 	return i;
// }

// char *update_word(char *word, int new_word_len)
// {
// 	int i;
// 	int j;
// 	char *new_word;
// 	int s_lock;
// 	int d_lock;

// 	i = 0;
// 	j = 0;
// 	new_word = (char *)malloc(new_word_len + 1);
// 	if (!new_word)
// 		return 0;
// 	s_lock = 0;
// 	d_lock = 0;
// 	while (word[i])
// 	{
// 		if (d_lock && word[i] == '\'')
// 			new_word[j++] = word[i];
// 		else if (s_lock && word[i] == '"')
// 			new_word[j++] = word[i];
// 		else if (!d_lock && word[i] == '"')
// 			d_lock = 1;
// 		else if (!s_lock && word[i] == '\'')
// 			s_lock = 1;
// 		else if (d_lock && word[i] == '"')
// 			d_lock = 0;
// 		else if (s_lock && word[i] == '\'')
// 			s_lock = 0;
// 		else
// 			new_word[j++] = word[i];
// 		i++;
// 	}
// 	new_word[j] = 0;
// 	free(word);
// 	printf("here word == %s\n", new_word);
// 	return (new_word);
// }

// int check_quotes(char *word, char *new_word)
// {
// 	int i;
// 	int s_lock;
// 	int d_lock;
// 	char *word_holder;
// 	int new_word_len;

// 	i = 0;
// 	s_lock = 0;
// 	d_lock = 0;
// 	new_word_len = 0;
// 	while (word[i])
// 	{
// 		if (d_lock && word[i] == '\'')
// 			new_word_len++;
// 		else if (s_lock && word[i] == '"')
// 			new_word_len++;
// 		else if (!d_lock && word[i] == '"')
// 			d_lock = 1;
// 		else if (!s_lock && word[i] == '\'')
// 			s_lock = 1;
// 		else if (d_lock && word[i] == '"')
// 			d_lock = 0;
// 		else if (s_lock && word[i] == '\'')
// 			s_lock = 0;
// 		else
// 			new_word_len++;
// 		i++;
// 	}
// 	if (d_lock || s_lock)
// 	{
// 		printf("single %i | double %i\n", s_lock, d_lock);
// 		return (1);
// 	}
// 	word_holder = word;
// 	new_word = update_word(word, new_word_len);
// 	return 0;
// }

void to_lower_case(char *word)
{
	int i;

	i = 0;
	while (word[i])
	{
		if (word[i] >= 'A' && word[i] <= 'Z')
			word[i] += 32;
		i++;
	}
}

int ft_execution(t_cmd *commands)
{
	t_token *head;
	int i;

	i = 0;
	while (commands)
	{
		head = commands->head_token->next;
		to_lower_case(head->token_chars);
		printf("cmd ============= %s\n", commands->head_token->token_chars);
		while (head)
		{
			printf("will do --%s--\n", head->token_chars);
			head = head->next;
		}
		commands = commands->next;
	}
	return 0;
}

void ft_addbackcmd(t_cmd **head, t_cmd *new)
{
	t_cmd *tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = new;
		return;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

t_cmd *ft_newcmd(char *head_token)
{
	t_cmd *new_cmd;
	int will_not_use;

	new_cmd = (t_cmd *)malloc(sizeof(*new_cmd));
	if (!new_cmd)
		return (0);
	// printf("----allocated hehe\n");
	new_cmd->head_token = ft_newtok(head_token, &will_not_use);
	new_cmd->next = NULL;
	return (new_cmd);
}

void replace_char(char *str, char c1, char c2)
{
	int i;
	int d_lock;
	int s_lock;

	i = 0;
	d_lock = 0;
	s_lock = 0;
	while (str[i])
	{
		if (!d_lock && str[i] == '"')
			d_lock = 1;
		else if (!s_lock && str[i] == '\'')
			s_lock = 1;
		else if (d_lock && str[i] == '"')
			d_lock = 0;
		else if (s_lock && str[i] == '\'')
			s_lock = 0;
		else if (!d_lock && !s_lock && str[i] == c1)
			str[i] = c2;
		i++;
	}
}

void _free(t_cmd *cmds, char *input, char **splitted, t_final_args *final_args)
{
	t_token *t_holder;
	t_cmd *c_holder;
	int i;

	while (cmds)
	{
		c_holder = cmds->next;
		while (cmds->head_token)
		{
			t_holder = cmds->head_token->next;
			free(cmds->head_token->token_chars);
			free(cmds->head_token);
			cmds->head_token = t_holder;
		}
		free(cmds);
		cmds = c_holder;
	}
	i = 0;
	while (splitted[i])
		free(splitted[i++]);
	i = 0;
	while (final_args[i].args)
	{
		free(final_args[i].args);
		free(final_args[i].arrows_n_files);
		i++;
	}
	free(final_args);
	free(splitted);
	free(input);
}

int ft_lstsize(t_cmd *cmd)
{
	int i;
	t_cmd *tmp;

	i = 0;
	tmp = cmd;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return i;
}

int ft_lstsize2(t_token *token)
{
	int i;
	t_token *tmp;

	i = 0;
	tmp = token;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	// printf("ret %i\n", i);
	return i;
}

int ft_count_arrows_n_files(t_token *start)
{
	t_token *tmp;
	int len;

	tmp = start;
	len = 0;
	while (tmp)
	{
		if (!strcmp(tmp->token_chars, ">>") || !strcmp(tmp->token_chars, ">") || !strcmp(tmp->token_chars, "<<") || !strcmp(tmp->token_chars, "<"))
		{
			len++;
			if (tmp->next)
			{
				len++;
				tmp = tmp->next;
			}
		}
		tmp = tmp->next;
	}
	return len;
}

void inside_while(t_params_3 *p)
{
	if (p->tmp_token->type == 1)
	{
		p->final_args[p->i].arrows_n_files[p->x] = p->tmp_token->token_chars;
		p->final_args[p->i].types2[p->x++] = p->tmp_token->type;
		if (p->tmp_token->next)
		{
			p->tmp_token = p->tmp_token->next;
			p->final_args[p->i].arrows_n_files[p->x] = p->tmp_token->token_chars;
			p->final_args[p->i].types[p->x++] = p->tmp_token->type;
		}
	}
	else
	{
		p->final_args[p->i].args[p->j++] = p->tmp_token->token_chars;
		p->final_args[p->i].types[p->y++] = p->tmp_token->type;
	}
	p->tmp_token = p->tmp_token->next;
}

void inside_while_0(t_params_3 *p)
{
	p->tmp_token = p->tmp_cmd->head_token->next;
	p->final_args[p->i].args = (char **)malloc(sizeof(char *) * (ft_lstsize2(p->tmp_token) - ft_count_arrows_n_files(p->tmp_token) + 1));
	p->final_args[p->i].arrows_n_files = (char **)malloc(sizeof(char *) * (ft_count_arrows_n_files(p->tmp_token) + 1));
	p->final_args[p->i].types = (int *)malloc(sizeof(int) * (ft_lstsize2(p->tmp_token) - ft_count_arrows_n_files(p->tmp_token) + 1));
	p->final_args[p->i].types2 = (int *)malloc(sizeof(int) * (ft_count_arrows_n_files(p->tmp_token) + 1));
	p->j = 0;
	p->x = 0;
	p->y = 0;
}

t_final_args *ft_argnew(t_cmd *commands)
{
	t_params_3 p;

	p.final_args = (t_final_args *)malloc(sizeof(t_final_args)
			* (ft_lstsize(commands) + 1));
	if (!p.final_args)
		return (0);
	p.tmp_cmd = commands;
	p.i = 0;
	while (p.tmp_cmd)
	{
		inside_while_0(&p);
		while (p.tmp_token)
			inside_while(&p);
		p.final_args[p.i].args[p.j] = 0;
		p.final_args[p.i].arrows_n_files[p.x] = 0;
		p.i++;
		p.tmp_cmd = p.tmp_cmd->next;
	}
	p.final_args[p.i].args = 0;
	return (p.final_args);
}

int ft_expand(char **word, char **env)
{
	char *hold_to_free;
	int found_var;
	int i;

	found_var = 0;
	hold_to_free = *word;
	i = 0;
	while (env[i])
	{
		if (!strncmp(*word + 1, env[i], ft_strlen(*word + 1)))
		{
			found_var = 1;
			*word = ft_strdup(env[i] + ft_strlen(*word));
			if (!*word)
				return 1;
			break;
		}
		i++;
	}
	if (!found_var)
		*word[0] = 0;
	if (!*word)
		return 1;
	return 0;
}

int double_char_len(char **strs)
{
	int i;

	i = 0;
	while (strs[i])
		i++;
	return i;
}

void ft_addback(t_token **head, t_token *new)
{
	t_token *tmp;

	tmp = *head;
	if (!tmp)
	{
		*head = new;
		return;
	}
	while (tmp->next)
	{
		tmp = tmp->next;
	}
	tmp->next = new;
}

char **cpy_env(char **env)
{
	int h;
	int i;
	char **new_env;

	h = 0;
	while (env[h])
		h++;
	new_env = (char **)malloc((sizeof(char *) * h) + 1);
	if (!new_env)
	{
		printf("malloc failed!..\n");
		exit(1);
	}
	i = 0;
	while (i < h)
	{
		new_env[i] = ft_strdup(env[i]);
		i++;
	}
	new_env[i] = NULL;
	return (new_env);
}

int ft_expand2(char **word, char **env, char **expanded_values)
{
	int i;
	int j;
	int did;
	char *word_cpy;
	int s_lock;
	int d_lock;

	i = 0;
	j = 0;
	did = 0;
	s_lock = 0;
	d_lock = 0;
	word_cpy = *word;
	while (word_cpy[i])
	{
		j = 0;
		while (word_cpy[i] && word_cpy[i] != '$' && ft_isalpha(word_cpy[i + 1]))
			i++;
		if (word_cpy[i] == '$' && ft_isalpha(word_cpy[i + 1]))
		{
			j = 0;
			while (env[j])
			{
				if (!ft_strncmp(env[j], word_cpy + i + 1, len_till_dollar(word_cpy + i + 1)) && env[j][len_till_dollar(word_cpy + i + 1)] == '=')
				{
					did = 1;
					append_to_value_arr(expanded_values, ft_strdup(env[j] + len_till_dollar(word_cpy + i + 1) + 1));
					break;
				}
				j++;
			}
		}
		if (did)
			i += len_till_dollar(word_cpy + i + 1) + 1;
		else if (word_cpy[i] == '$' && ft_isalpha(word_cpy[i + 1]))
		{
			append_to_value_arr(expanded_values, ft_strdup(""));
			i++;
		}
		else
			i++;
	}
	return (0);
}

char *add_char(char *str, char c)
{
	int i;
	char *new;

	new = (char *)malloc(ft_strlen(str) + 2);
	if (!new)
		exit(1);
	i = 0;
	while (str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = c;
	new[i] = 0;
	return new;
}

int ft_what_will_do(t_final_args *final_args, char **expanded_value)
{
	int i;
	int j;
	int x;
	int w;
	int args_len;
	int a_n_f_len;
	char *expanded;
	int did_expand;

	i = 0;
	x = 0;
	while (final_args[i].args)
	{
		a_n_f_len = arr_len(final_args[i].arrows_n_files);
		args_len = arr_len(final_args[i].args);
		j = 0;
		while (j < args_len)
		{
			expanded = ft_strdup("");
			w = 0;
			while (final_args[i].args[j][w])
			{
				if (final_args[i].args[j][w] == '$' && final_args[i].args[j][w + 1] == '?')
				{
					// exit status
					expanded = ft_strjoin(expanded, "123");
					x++;
					w += 3;
				}
				if (final_args[i].args[j][w] == '$' && ft_isalpha(final_args[i].args[j][w + 1]))
				{
					expanded = ft_strjoin(expanded, expanded_value[x]);
					x++;
					w += len_till_dollar(final_args[i].args[j] + w + 1);
				}
				else
				{
					expanded = add_char(expanded, final_args[i].args[j][w]);
				}
				w++;
			}
			final_args[i].args[j] = expanded;
			j++;
		}
		j = 0;
		while (j < a_n_f_len)
		{
			expanded = ft_strdup("");
			w = 0;
			if (j > 0 && strcmp(final_args[i].arrows_n_files[j - 1], "<<"))
			{
				did_expand = 0;
				while (final_args[i].arrows_n_files[j][w])
				{
					if (final_args[i].arrows_n_files[j][w] == '$' && ft_isalpha(final_args[i].arrows_n_files[j][w + 1]))
					{
						expanded = ft_strjoin(expanded, expanded_value[x]);
						x++;
						w += len_till_dollar(final_args[i].arrows_n_files[j] + w + 1);
						did_expand = 1;
					}
					else
					{
						expanded = add_char(expanded, final_args[i].arrows_n_files[j][w]);
					}
					w++;
				}
				final_args[i].arrows_n_files[j] = expanded;
				x++;
			}
			else
			{
				x += how_many_dollars(final_args[i].arrows_n_files[j]);
			}
			j++;
		}
		i++;
	}
	i = 0;
	return 0;
}

int exit_status;

int ft_quotes(char **splitted)
{
	int i;
	int j;
	int s_lock;
	int d_lock;

	i = 0;
	while (splitted[i])
	{
		s_lock = 0;
		d_lock = 0;
		j = 0;
		while (splitted[i][j])
		{
			// printf("%c--", splitted[i][j]);
			if (d_lock && splitted[i][j] == '\'')
			{
				j++;
				continue;
			}
			else if (s_lock && splitted[i][j] == '"')
			{
				j++;
				continue;
			}
			else if (!d_lock && splitted[i][j] == '"')
				d_lock = 1;
			else if (!s_lock && splitted[i][j] == '\'')
				s_lock = 1;
			else if (d_lock && splitted[i][j] == '"')
				d_lock = 0;
			else if (s_lock && splitted[i][j] == '\'')
				s_lock = 0;
			j++;
		}
		// printf("here\n");
		if (d_lock || s_lock)
		{
			// printf("did not handle quotes. <%s>\n", splitted[i]);
			return 1;
		}
		i++;
	}
	return 0;
}

int ft_check_rdr(t_final_args *final_args)
{
	int i;
	int j;
	int len;

	i = 0;
	while (final_args[i].args)
	{
		len = arr_len(final_args[i].arrows_n_files);
		if (!len)
		{
			i++;
			continue;
		}
		// printf("size == %i\n", final_args[i].types[0]);
		if (final_args[i].types2[len - 1])
		{
			// printf("from 1\n");
			printf("parse error near '\\n'\n");
			return 1;
		}
		// printf("here\n");
		j = 1;
		while (j < len)
		{
			// printf("j == %i %i\n", j, final_args[i].types[j]);
			if (final_args[i].types2[j] && final_args[i].types2[j - 1])
			{
				// printf("from 2\n");
				printf("parse error near '%s'\n", final_args[i].arrows_n_files[j + 1]);
				return 1;
			}
			j++;
		}
		i++;
		// printf("-------------------------------------------------\n");
	}
	return 0;
}

void print_list(t_cmd *commands)
{
	t_cmd *tmp;
	t_token *token;

	tmp = commands;
	while (tmp)
	{
		token = tmp->head_token;
		while (token)
		{
			// printf("///%s type == %i\n", token->token_chars, token->type);
			token = token->next;
		}
		tmp = tmp->next;
	}
}

void print_struct(t_final_args *final_args)
{
	int i;
	int j;

	i = 0;
	while (final_args[i].args)
	{
		j = 0;
		while (final_args[i].args[j])
		{
			printf("arg xx == |%s|\n", final_args[i].args[j]);
			j++;
		}
		j = 0;
		while (final_args[i].arrows_n_files[j])
		{
			printf("arrs&files == |%s|\n", final_args[i].arrows_n_files[j]);
			j++;
		}
		i++;
		printf("-------------------------------------------------\n");
	}
}

int check_pipes(char *line)
{
	int i;
	int s_lock;
	int d_lock;

	i = 0;
	s_lock = 0;
	d_lock = 0;
	// printf("hohohohohpppp -%c-\n", line[i]);
	if (line[i] == '|' || !line[i])
	{
		printf("minishell: parse error near `|'\n");
		return (1);
	}
	while (line[i])
	{
		if (d_lock && line[i] == '\'')
			i++;
		else if (s_lock && line[i] == '"')
			i++;
		else if (!s_lock && line[i] == '\'')
			s_lock = i++;
		else if (!d_lock && line[i] == '\'')
			d_lock = i++;
		else if (line[i] == '|' && !s_lock && !d_lock)
		{
			if (check_pipes(line + i + 1))
				return 1;
			i++;
		}
		else
			i++;
	}
	return 0;
}

char **do_split(char **arr, int *types)
{
	int i;
	char **splitted;
	char **new;
	int len;
	int j;

	i = 0;
	len = 0;
	printf("len == %i\n", arr_len(arr));
	while (arr[i])
	{
		printf("%s-------\n", arr[i]);
		printf("hererererere %i\n", types[i]);
		if (types[i] == 2)
		{
			splitted = ft_split(arr[i], ' ');
			if (!splitted)
				exit(1);
			len += arr_len(splitted);
			free_arr(splitted);
		}
		else
			len++;
		i++;
	}
	new = (char **)malloc(sizeof(char *) * (len + 1));
	if (!new)
		exit(1);
	i = 0;
	len = 0;
	while (arr[i])
	{
		if (types[i] == 2)
		{
			splitted = ft_split(arr[i], ' ');
			if (!splitted)
				exit(1);
			j = 0;
			while (splitted[j])
			{
				new[len] = splitted[j];
				j++;
				len++;
			}
		}
		else
		{
			new[len] = arr[i];
			len++;
		}
		i++;
	}
	new[len] = 0;
	printf("zzzz\n");
	print_arr2d(new, 1);
	// free(arr);
	return new;
}

// void sigint_handler(int signum)
// {
// 	(void)signum;
// 	rl_replace_line("", 0);  // Replace the current line with an empty string
//     rl_redisplay();  // Redisplay the prompt
// 	printf("\n-> minishell$> ");
// 	// fflush(stdout);
// 	// Perform cleanup or other necessary actions
// 	// ...
// 	// signal(SIGINT, sigint_handler);
// }

void sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		rl_replace_line("", 0); // Replace the current line with an empty string
		printf("\n-> minishell$> ");
		rl_redisplay(); // Redisplay the prompt
		status = 1;
		// rl_on_new_line();
		// fflush(stdout);
	}
	else if (sig == SIGQUIT)
	{
		rl_replace_line("", 0); // Replace the current line with an empty string
		rl_redisplay();			// Redisplay the prompt
	}
}

// void sigquit_handler(int signum)
// {
// 	(void)signum;
// 	rl_replace_line("", 0);  // Replace the current line with an empty string
//     rl_redisplay();  // Redisplay the prompt
// }

int main(int c, char **v, char **env)
{
	// (void)c;
	// (void)v;
	// (void)env;

	// ft_export(v, env, exp);
	// printf("-----------------export----------------------\n");
	// print_export(env, exp);
	// printf("-----------------enverenment----------------------\n");
	// print_arr2d(env);
	// ft_export(v, env, exp);
	// printf("-----------------export----------------------\n");
	// print_export(env, exp);
	// printf("-----------------enverenment----------------------\n");
	// print_arr2d(env);
	// // envr = ft_env(env, argv , export);
	// // if (!envr)
	// // 	return 1;
	// // t_env *tmp;
	// // tmp = envr;
	// // while (tmp)
	// // {
	// // 	printf("%s=%s", tmp->var, tmp->value);
	// // 	tmp = tmp->next;
	// // }

	// return (0);

	char *input;
	char **splited_cmds;
	int i;
	int j;
	(void)c;
	(void)v;
	t_cmd *commands;
	t_cmd *cmd_head_holder;
	t_final_args *final_args;
	char **env_cpy = NULL;
	char **exp;
	char **expanded_values;

	exp = NULL;

	env_cpy = cpy_env(env);

	struct sigaction sig;
	rl_catch_signals = 0;
	sig.sa_handler = &sig_handler;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
	// print_arr2d(env_cpy);
	// printf("-----------******************--------\n");
	// print_arr2d(env_cpy);
	// printf("-----------******************--------\n");
	while (1)
	{
		input = readline("-> minishell$> ");
		if (!input)
			exit(0);
		input = ft_strtrim(input);
		if (ft_strlen(input))
		{
			add_history(input);
			// while (input[ft_strlen(input) - 1] == '|')
			// 	input = ft_strjoin(input, readline("-> pipe$> "));
			// check_pipes(ft_strtrim(input));
			if (check_pipes(input))
				continue;
			replace_char(input, '|', 11);
			splited_cmds = ft_split(input, 11);
			if (ft_quotes(splited_cmds))
				continue;
			commands = NULL;
			expanded_values = (char **)malloc(sizeof(char *) * (how_many_dollars(input) + 1));
			if (!expanded_values)
				exit(1);
			expanded_values[0] = NULL;
			i = 0;
			while (splited_cmds[i])
			{
				ft_expand2(&splited_cmds[i], env_cpy, expanded_values);
				i++;
			}
			i = 0;
			// print_arr2d(expanded_values);
			while (splited_cmds[i])
			{
				j = 0;
				ft_addbackcmd(&commands, ft_newcmd("ignored_first"));
				while (commands->next)
					commands = commands->next;
				if (i == 0)
					cmd_head_holder = commands;
				while (j < (int)ft_strlen(splited_cmds[i]))
				{
					while (splited_cmds[i][j] == ' ')
						j++;
					ft_addback(&commands->head_token, ft_newtok(splited_cmds[i] + j, &j));
				}
				i++;
			}
			i = 0;
			commands = cmd_head_holder;

			// ft_line_up(commands);
			// ft_execution(cmd_head_holder);
			final_args = ft_argnew(commands);
			if (ft_check_rdr(final_args))
			{
				// printf("hohohoho\n");
				continue;
			}
			// printf("-----------------%s\n", final_args[0].arrows_n_files[0]);
			ft_what_will_do(final_args, expanded_values);
			i = 0;
			print_struct(final_args);
			while (final_args[i].args)
			{
				if (final_args[i].args[0])
					final_args[i].args = do_split(final_args[i].args, final_args[i].types);
				if (final_args[i].arrows_n_files[0])
					final_args[i].arrows_n_files = do_split(final_args[i].arrows_n_files, final_args[i].types2);
				i++;
			}
			print_struct(final_args);
			ft_execute(final_args, &env_cpy, &exp);
			printf("status = %d\n", status);
			// print_export(env_cpy, exp);
			_free(cmd_head_holder, input, splited_cmds, final_args);
		}
	}
}
