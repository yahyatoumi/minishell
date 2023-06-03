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

void addtoarr(char **arr, char *new_value)
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

void	dup_3_intial(t_params_2 *p, char *start)
{
	p->i = 0;
	p->j = 0;
	p->d_lock = 0;
	p->s_lock = 0;
	p->holder = (char *)malloc(ft_strlen(start) + 1);
}

char *ft_strdup_3(char *start, int *add)
{
	t_params_2 p;

	dup_3_intial(&p, start);
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
	return (*add = *add + 0, ft_strdup(p.holder));
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
		token->type = 0;
		token->next = NULL;
	}
	token2 = (t_token *)malloc(sizeof(*token));
	if (!token2)
		return 0;
	token2->token_chars = ft_strdup_2(word_start, len_till_dollar(word_start + 1) + 1);
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
	*j += 0;
	if (params->sign_lock)
		return 1;
	params->d_lock = 1;
	return 0;
}

int ft_newtok_3(int *j, t_params_1 *params)
{
	*j += 0;
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
	if (p->d_lock && str[p->i] == '"')
	{
		if (ft_newtok_4(j, p))
			return (3);
		return (4);
	}
	else if (p->s_lock && str[p->i] == '\'')
	{
		if (ft_newtok_5(j, p))
			return (3);
		return 4;
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
	if (params->d_lock && word_start[params->i] == '\'' && word_start[params->i + 1] != '$')
		return (params->holder[params->x++] = word_start[params->i], 2);
	else if (params->s_lock && word_start[params->i] == '"' && word_start[params->i + 1] != '$')
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
		{
			printf("19\n");
			helper = 2;
		}
		else
		{
			helper = ft_newtok_while_3(word_start, params, j);
			if (helper == 1)
				return params->token;
			if (helper == 4)
			{
				params->i++;
				continue;
			}
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

void _free(t_cmd *cmds, char *input, char **splitted, t_fargs *fargs)
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
	while (fargs[i].args)
	{
		free(fargs[i].args);
		free(fargs[i].rdrs);
		i++;
	}
	free(fargs);
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

int ft_count_rdrs(t_token *start)
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
		p->fargs[p->i].rdrs[p->x] = p->tmp_token->token_chars;
		p->fargs[p->i].types2[p->x++] = p->tmp_token->type;
		if (p->tmp_token->next)
		{
			p->tmp_token = p->tmp_token->next;
			p->fargs[p->i].rdrs[p->x] = p->tmp_token->token_chars;
			p->fargs[p->i].types2[p->x++] = p->tmp_token->type;
		}
	}
	else
	{
		p->fargs[p->i].args[p->j++] = p->tmp_token->token_chars;
		p->fargs[p->i].types[p->y++] = p->tmp_token->type;
	}
	p->tmp_token = p->tmp_token->next;
}

void inside_while_0(t_params_3 *p)
{
	p->tmp_token = p->tmp_cmd->head_token->next;
	p->fargs[p->i].args = (char **)malloc(sizeof(char *) * (ft_lstsize2(p->tmp_token) - ft_count_rdrs(p->tmp_token) + 1));
	p->fargs[p->i].rdrs = (char **)malloc(sizeof(char *) * (ft_count_rdrs(p->tmp_token) + 1));
	p->fargs[p->i].types = (int *)malloc(sizeof(int) * (ft_lstsize2(p->tmp_token) - ft_count_rdrs(p->tmp_token) + 1));
	p->fargs[p->i].types2 = (int *)malloc(sizeof(int) * (ft_count_rdrs(p->tmp_token) + 1));
	p->j = 0;
	p->x = 0;
	p->y = 0;
}

t_fargs *ft_argnew(t_cmd *commands)
{
	t_params_3 p;

	p.fargs = (t_fargs *)malloc(sizeof(t_fargs) * (ft_lstsize(commands) + 1));
	if (!p.fargs)
		return (0);
	p.tmp_cmd = commands;
	p.i = 0;
	while (p.tmp_cmd)
	{
		inside_while_0(&p);
		while (p.tmp_token)
			inside_while(&p);
		p.fargs[p.i].args[p.j] = 0;
		p.fargs[p.i].rdrs[p.x] = 0;
		p.i++;
		p.tmp_cmd = p.tmp_cmd->next;
	}
	p.fargs[p.i].args = 0;
	return (p.fargs);
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

void set_expand2_values(t_params_4 *p, char **word)
{
	p->i = 0;
	p->j = 0;
	p->did = 0;
	p->s_lock = 0;
	p->d_lock = 0;
	p->cpy = *word;
}

void inside_while_expand(t_params_4 *p, char **expanded_values)
{
	if (p->did)
		p->i += len_till_dollar(p->cpy + p->i + 1) + 1;
	else if (p->cpy[p->i] == '$' && ft_isalpha(p->cpy[p->i + 1]))
	{
		addtoarr(expanded_values, ft_strdup(""));
		p->i++;
	}
	else
		p->i++;
}

int ft_expand2(char **word, char **env, char **expanded_values)
{
	t_params_4 p;

	set_expand2_values(&p, word);
	while (p.cpy[p.i])
	{
		p.j = 0;
		while (p.cpy[p.i] && p.cpy[p.i] != '$' && ft_isalpha(p.cpy[p.i + 1]))
			p.i++;
		if (p.cpy[p.i] == '$' && ft_isalpha(p.cpy[p.i + 1]))
		{
			p.j = 0;
			while (env[p.j])
			{
				if (!ft_strncmp(env[p.j], p.cpy + p.i + 1, len_till_dollar(p.cpy + p.i + 1)) && env[p.j][len_till_dollar(p.cpy + p.i + 1)] == '=')
				{
					p.did = 1;
					addtoarr(expanded_values, ft_strdup(env[p.j] + len_till_dollar(p.cpy + p.i + 1) + 1));
					break;
				}
				p.j++;
			}
		}
		inside_while_expand(&p, expanded_values);
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

void ft_what_will_do_1(t_params_5 *p, t_fargs *fargs, char **expanded_value)
{

	while (fargs[p->i].args[p->j][p->w])
	{
		if (fargs[p->i].args[p->j][p->w] == '$' && fargs[p->i].args[p->j][p->w + 1] == '?')
		{
			p->expanded = ft_strjoin(p->expanded, "123");
			p->x++;
			p->w += 3;
		}
		if (fargs[p->i].args[p->j][p->w] == '$' && ft_isalpha(fargs[p->i].args[p->j][p->w + 1]))
		{
			if (expanded_value[p->x])
				p->expanded = ft_strjoin(p->expanded, expanded_value[p->x]);
			p->x++;
			p->w += len_till_dollar(fargs[p->i].args[p->j] + p->w + 1);
		}
		else
		{
			p->expanded = add_char(p->expanded,
								   fargs[p->i].args[p->j][p->w]);
		}
		p->w++;
	}
	fargs[p->i].args[p->j] = p->expanded;
	p->j++;
}

void ft_what_will_do_2(t_params_5 *p, t_fargs *fargs, char **expanded_value)
{
	if (p->j > 0 && strcmp(fargs[p->i].rdrs[p->j - 1], "<<"))
	{
		p->did_expand = 0;
		while (fargs[p->i].rdrs[p->j][p->w])
		{
			if (fargs[p->i].rdrs[p->j][p->w] == '$' && ft_isalpha(fargs[p->i].rdrs[p->j][p->w + 1]))
			{
				if (expanded_value[p->x])
					p->expanded = ft_strjoin(p->expanded, expanded_value[p->x]);
				p->x++;
				p->w += len_till_dollar(fargs[p->i].rdrs[p->j] + p->w + 1);
				p->did_expand = 1;
			}
			else
				p->expanded = add_char(p->expanded,
									   fargs[p->i].rdrs[p->j][p->w]);
			p->w++;
		}
		fargs[p->i].rdrs[p->j] = p->expanded;
		p->x++;
	}
	else
		p->x += how_many_dollars(fargs[p->i].rdrs[p->j]);
	p->j++;
}

void while_1(t_params_5 *p, t_fargs *fargs, char **expanded_value)
{
	while (p->j < p->args_len)
	{
		p->expanded = ft_strdup("");
		p->w = 0;
		ft_what_will_do_1(p, fargs, expanded_value);
	}
}

int ft_what_will_do(t_fargs *fargs, char **expanded_value)
{
	t_params_5 p;

	p.i = 0;
	p.x = 0;
	while (fargs[p.i].args)
	{
		p.a_n_f_len = arr_len(fargs[p.i].rdrs);
		p.args_len = arr_len(fargs[p.i].args);
		p.j = 0;
		while_1(&p, fargs, expanded_value);
		p.j = 0;
		while (p.j < p.a_n_f_len)
		{
			p.expanded = ft_strdup("");
			p.w = 0;
			ft_what_will_do_2(&p, fargs, expanded_value);
		}
		p.i++;
	}
	p.i = 0;
	return 0;
}

int exit_status;

void quotes_while(char **splitted, t_params_6 *p)
{
	while (splitted[p->i][p->j])
	{
		if (p->d_lock && splitted[p->i][p->j] == '\'')
		{
			p->j++;
			continue;
		}
		else if (p->s_lock && splitted[p->i][p->j] == '"')
		{
			p->j++;
			continue;
		}
		else if (!p->d_lock && splitted[p->i][p->j] == '"')
			p->d_lock = 1;
		else if (!p->s_lock && splitted[p->i][p->j] == '\'')
			p->s_lock = 1;
		else if (p->d_lock && splitted[p->i][p->j] == '"')
			p->d_lock = 0;
		else if (p->s_lock && splitted[p->i][p->j] == '\'')
			p->s_lock = 0;
		p->j++;
	}
}

int ft_quotes(char **splitted)
{
	t_params_6 p;

	p.i = 0;
	while (splitted[p.i])
	{
		p.s_lock = 0;
		p.d_lock = 0;
		p.j = 0;
		quotes_while(splitted, &p);
		if (p.d_lock || p.s_lock)
		{
			printf("did not handle quotes. <%s>\n", splitted[p.i]);
			return 1;
		}
		p.i++;
	}
	return 0;
}

int rdr_while(t_fargs *fargs, int len, int i, int j)
{
	while (j < len)
	{
		if (fargs[i].types2[j] && fargs[i].types2[j - 1])
		{
			printf("parse error near '%s'\n", fargs[i].rdrs[j + 1]);
			return 1;
		}
		j++;
	}
	return 0;
}

int ft_check_rdr(t_fargs *fargs)
{
	int i;
	int j;
	int len;

	i = 0;
	while (fargs[i].args)
	{
		len = arr_len(fargs[i].rdrs);
		if (!len)
		{
			i++;
			continue;
		}
		if (fargs[i].types2[len - 1])
		{
			printf("parse error near '\\n'\n");
			return 1;
		}
		j = 1;
		if (rdr_while(fargs, len, i, j))
			return 1;
		i++;
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
			printf("///%s type == %i\n", token->token_chars, token->type);
			token = token->next;
		}
		tmp = tmp->next;
	}
}

void print_struct(t_fargs *fargs)
{
	int i;
	int j;

	i = 0;
	while (fargs[i].args)
	{
		j = 0;
		while (fargs[i].args[j])
		{
			printf("arg xx == |%s|\n", fargs[i].args[j]);
			j++;
		}
		j = 0;
		while (fargs[i].rdrs[j])
		{
			printf("arrs&files == |%s|\n", fargs[i].rdrs[j]);
			j++;
		}
		i++;
		printf("-------------------------------------------------\n");
	}
}

int check_pipes(char *line);

int	pipes_while(char *line, int d_lock, int s_lock, int i)
{
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

int check_pipes(char *line)
{
	int i;
	int s_lock;
	int d_lock;

	i = 0;
	s_lock = 0;
	d_lock = 0;
	if (line[i] == '|' || !line[i])
	{
		printf("minishell: parse error near `|'\n");
		return (1);
	}
	if (pipes_while(line, d_lock, s_lock, i))
		return 1;
	return 0;
}

void	split_while_1(t_params_7 *p, char **arr, int *types)
{
	while (arr[p->i])
	{
		if (types[p->i] == 2)
		{
			p->splitted = ft_split(arr[p->i], ' ');
			if (!p->splitted)
				exit(1);
			p->len += arr_len(p->splitted);
			free_arr(p->splitted);
		}
		else
			p->len++;
		p->i++;
	}
}

void	split_while_2(t_params_7 *p, char **arr, int *types)
{
	while (arr[p->i])
	{
		if (types[p->i] == 2)
		{
			p->splitted = ft_split(arr[p->i], ' ');
			if (!p->splitted)
				exit(1);
			p->j = 0;
			while (p->splitted[p->j])
			{
				p->new[p->len] = ft_strdup(p->splitted[p->j]);
				p->j++;
				p->len++;
			}
		}
		else
		{
			p->new[p->len] = ft_strdup(arr[p->i]);
			p->len++;
		}
		p->i++;
	}
}

char **do_split(char **arr, int *types)
{
	t_params_7 p;

	p.i = 0;
	p.len = 0;
	split_while_1(&p, arr, types);
	p.new = (char **)malloc(sizeof(char *) * (p.len + 1));
	if (!p.new)
		exit(1);
	p.i = 0;
	p.len = 0;
	split_while_2(&p, arr, types);
	p.new[p.len] = 0;
	free_arr(arr);
	return p.new;
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
	t_fargs *fargs;
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
			print_list(cmd_head_holder);
			// ft_line_up(commands);
			// ft_execution(cmd_head_holder);
			fargs = ft_argnew(commands);
			if (ft_check_rdr(fargs))
			{
				// printf("hohohoho\n");
				continue;
			}
			// printf("-----------------%s\n", fargs[0].rdrs[0]);
			ft_what_will_do(fargs, expanded_values);
			i = 0;
			print_struct(fargs);
			while (fargs[i].args)
			{
				if (fargs[i].args[0])
					fargs[i].args = do_split(fargs[i].args, fargs[i].types);
				if (fargs[i].rdrs[0])
					fargs[i].rdrs = do_split(fargs[i].rdrs, fargs[i].types2);
				i++;
			}
			print_struct(fargs);
			ft_execute(fargs, &env_cpy, &exp);
			printf("status = %d\n", status);
			// print_export(env_cpy, exp);
			_free(cmd_head_holder, input, splited_cmds, fargs);
		}
	}
}
