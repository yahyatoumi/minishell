#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void print_arr(char **arr)
{
    int i;

    i = 0;
    while (arr[i])
        printf("%s\n", arr[i++]);
}

void append_to_arr(char **arr, char *new_value)
{
    int i;

    i = 0;
    while (arr[i])
        i++;
    arr[i++] = new_value;
    arr[i] = 0;
}

char **ft_make_tokens(char *cmd)
{
    int i;
    int d_lock;
    int s_lock;
    char holder[1000];
    char **tokens;
    int x;

    i = 0;
    d_lock = 0;
    s_lock = 0;
    tokens = (char **)malloc(sizeof(char *));
    tokens[0] = 0;
    x = 0;
    holder[0] = 0;
    printf("cmd %s\n", cmd);
    while (cmd[i])
    {
        if (!d_lock && cmd[i] == '"')
            d_lock = 1;
        else if (!s_lock && cmd[i] == '\'')
            s_lock = 1;
        else if (d_lock && cmd[i] == '"')
            d_lock = 0;
        else if (s_lock && cmd[i] == '\'')
            s_lock = 0;
        else if (!s_lock && !d_lock && cmd[i] == ' ')
        {
            holder[x] = 0;
            append_to_arr(tokens, strdup(holder));
            x = 0;
            i++;
            continue;
        }
        else if (!s_lock && !d_lock && (cmd[i] == '>' || cmd[i] == '<'))
        {
            if (x)
            
        }
        holder[x++] = cmd[i];
        i++;
    }
    if (x)
    {
        holder[x] = 0;
        append_to_arr(tokens, strdup(holder));
        printf("here %s\n", holder);
    }
    return tokens;
}

int main(int ac, char **av)
{
    char **tokens;

    tokens = ft_make_tokens("\"$USER xx\"");
    print_arr(tokens);
}