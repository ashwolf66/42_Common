#include "minishell.h"

void quote_check(int *temp)
{
    if (*temp == 0)
        *temp = 1;
    else if (*temp == 1) 
        *temp = 0;
}
int oper_check(char *cmd)
{
    int indx;

    indx = 1;

}

int cmd_eff_ch(char *cmd)
{
    int single_check;
    int double_check;
    int index;

    single_check = 0;
    double_check = 0;
    index = 0;
    while (cmd[index] != '\0')
    {
        if (index == 0 && cmd[index] != '\'' && cmd[index] != '|')
            index++;
        else if (index != 0 && cmd[index] == '\'')
            quote_check(&single_check);
        else if (index != 0 && cmd[index] == '\"')
            quote_check(&double_check);
        else if (index != 0 && (cmd[index] == '<' || cmd[index] == '>' || cmd[index] == '|'))
            if (oper_check(&(cmd[index])) == 1)
                return (1);
        index++;
    }
    return (0);
}
