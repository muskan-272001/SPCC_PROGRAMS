#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 128
#define ROW 6
#define COL 7
#define MAX 1000
struct product
{
    char str[100];
    int len;
} prod[20];
int table[100][TABLE_SIZE];
char terminal[TABLE_SIZE];
char nonterminal[26];
int productions_count;
char first[26][TABLE_SIZE];
char follow[26][TABLE_SIZE];
char first_rhs[100][TABLE_SIZE];
char non_terminals[10][2];
char terminals[10][2];
char productions_arr[10][10];
int n_terminals;
int n_non_terminals;
int n_prods;
char reserved_recursion_chars[10][2];
int n_reserved_index = 0;
int used_reserved_chars = 0;
FILE *rfp_fptr;
char stack[MAX][80];
int top = -1;
int z = 0, count = 0;
void create_reserved_chars()
{
    char reserved_cand[11][2] = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "S"};
    int k = 0;
    for (int i = 0; i < 10; i++)
    {
        int flag = 0;
        for (int j = k; j < n_non_terminals; j++)
        {
            if (strcmp(non_terminals[j], reserved_cand[i]) == 0)
            {
                flag = 1;
                break;
            }
        }
        if (!flag)
        {
            snprintf(reserved_recursion_chars[n_reserved_index], sizeof(reserved_recursion_chars[n_reserved_index]), "%s",
                     reserved_cand[i]);
            n_reserved_index++;
            k++;
        }
        if (n_reserved_index == n_prods)
        {
            break;
        }
    }
}
int is_terminal(char symbol)
{
    if (symbol >= 97 && symbol <= 122)
    {
        return 1;
    }
    return 0;
}
void remove_left_recursion(char init_productions[][10], int n_productions, char final_productions[][20], int *fp)
{
    char non_terminals;
    char alpha_str[10];
    char beta_str[10];
    char buffer[10];
    int f = *fp;
    for (int i = 0; i < n_productions; i++)
    {
        non_terminals = init_productions[i][0];
        if (non_terminals == init_productions[i][3])
        {
            int j = 4;
            int m = 0;
            while (init_productions[i][j] != '\0' &&
                   init_productions[i][j] != '|')
            {
                alpha_str[m] = init_productions[i][j];
                m++;
                j++;
            }
            alpha_str[m] = '\0';
            if (init_productions[i][j++] != '\0')
            {
                m = 0;
                while (init_productions[i][j] != '\0')
                {
                    beta_str[m] = init_productions[i][j];
                    m++;
                    j++;
                }
                beta_str[m] = '\0';
            }
            snprintf(final_productions[f],
                     sizeof(final_productions[f]), "%c->%s%s", non_terminals,
                     beta_str, reserved_recursion_chars[used_reserved_chars]);
            f++;
            snprintf(final_productions[f],
                     sizeof(final_productions[f]), "%s->%s%s|^",
                     reserved_recursion_chars[used_reserved_chars], alpha_str,
                     reserved_recursion_chars[used_reserved_chars]);
            f++;
            used_reserved_chars++;
        }
        else
        {
            snprintf(final_productions[f],
                     sizeof(final_productions[f]), "%s", init_productions[i]);
            f++;
        }
    }
    *fp = f;
}
int is_non_terminal(char c)
{
    return c >= 'A' && c <= 'Z';
}
void read_recursion_free_grammar()
{
    FILE *fptr;
    fptr = fopen("recursion_free_productions.txt", "r");
    char buffer[255];
    int i, j;
    while (fgets(buffer, sizeof(buffer), fptr))
    {
        j = 0;
        nonterminal[buffer[0] - 'A'] = 1;
        for (i = 0; i < strlen(buffer) - 1; ++i)
        {
            if (buffer[i] == '|')
            {
                ++productions_count;
                prod[productions_count - 1].str[j] = '\0';
                prod[productions_count - 1].len = j;
                prod[productions_count].str[0] =
                    prod[productions_count - 1].str[0];
                prod[productions_count].str[1] =
                    prod[productions_count - 1].str[1];
                prod[productions_count].str[2] =
                    prod[productions_count - 1].str[2];
                j = 3;
            }
            else
            {
                prod[productions_count].str[j] = buffer[i];
                ++j;
                if (!is_non_terminal(buffer[i]) && buffer[i] != '-' && buffer[i] != '>')
                {
                    terminal[buffer[i]] = 1;
                }
            }
        }
        prod[productions_count].len = j;
        ++productions_count;
    }
}
void fa_to_flb(char A, char B)
{
    int i;
    for (i = 0; i < TABLE_SIZE; ++i)
    {
        if (i != '^')
            follow[B - 'A'][i] = follow[B - 'A'][i] || first[A - 'A'][i];
    }
}
void fla_to_flb(char A, char B)
{
    int i;
    for (i = 0; i < TABLE_SIZE; ++i)
    {
        if (i != '^')
            follow[B - 'A'][i] = follow[B - 'A'][i] || follow[A - 'A'][i];
    }
}
void find_follow()
{
    int t = 0;
    int i, j, k, x;
    while (t++ < productions_count)
    {
        for (k = 0; k < 26; ++k)
        {
            if (!nonterminal[k])
            {
                continue;
            }
            char nt = k + 'A';
            for (i = 0; i < productions_count; ++i)
            {
                for (j = 3; j < prod[i].len; ++j)
                {
                    if (nt == prod[i].str[j])
                    {
                        for (x = j + 1; x < prod[i].len; ++x)
                        {
                            char src = prod[i].str[x];
                            if (is_non_terminal(src))
                            {
                                fa_to_flb(src, nt);
                                if (first[src - 'A']['^'])
                                {
                                    continue;
                                }
                            }
                            else
                            {
                                follow[nt - 'A'][src] = 1;
                            }
                            break;
                        }
                        if (x == prod[i].len)
                            fla_to_flb(prod[i].str[0], nt);
                    }
                }
            }
        }
    }
}
void fa_to_fb(char A, char B)
{
    int i;
    for (i = 0; i < TABLE_SIZE; ++i)
    {
        if (i != '^')
        {
            first[B - 'A'][i] = first[A - 'A'][i] || first[B -
                                                           'A'][i];
        }
    }
}
void find_first()
{
    int i, j;
    int t = 0;
    while (t < productions_count)
    {
        for (i = 0; i < productions_count; ++i)
        {
            for (j = 3; j < prod[i].len; ++j)
            {
                char src = prod[i].str[j];
                if (is_non_terminal(src))
                {
                    fa_to_fb(src, prod[i].str[0]);
                    if (first[src - 'A']['^'])
                        continue;
                }
                else
                {
                    first[prod[i].str[0] - 'A'][src] = 1;
                }
                break;
            }
            if (j == prod[i].len)
                first[prod[i].str[0] - 'A']['^'] = 1;
        }
        ++t;
    }
}
void fa_to_rhs_fb(char A, int B)
{
    int i;
    for (i = 0; i < TABLE_SIZE; ++i)
    {
        if (i != '^')
            first_rhs[B][i] = first[A - 'A'][i] || first_rhs[B][i];
    }
}
void rhs_first()
{
    int i, j;
    int t = 0;
    while (t < productions_count)
    {
        for (i = 0; i < productions_count; ++i)
        {
            for (j = 3; j < prod[i].len; ++j)
            {
                char src = prod[i].str[j];
                if (is_non_terminal(src))
                {
                    fa_to_rhs_fb(src, i);
                    if (first[src - 'A']['^'])
                    {
                        continue;
                    }
                }
                else
                {
                    first_rhs[i][src] = 1;
                }
                break;
            }
            if (j == prod[i].len)
                first_rhs[i]['^'] = 1;
        }
        ++t;
    }
}
char matrix[ROW][COL][20] = {
    {" ", "+", "*", " (", ")", "i", "$"},
    {"E", " ", " ", "E->TE'", " ", "E->TE'", " "},
    {"E'", "E'->+TE'", " ", " ", "E'->e", " ", "E'->e"},
    {"T", " ", " ", "T->FT'", " ", "T->FT'", " "},
    {"T'", "T'->e", "T'->*FT'", " ", "T'->e", " ", "T'->e"},
    {"F", " ", " ", "F->(E)", " ", "F->i", " "},
};
void push(char data[2])
{
    if (top < MAX)
    {
        top++;
        strcpy(stack[top], data);
    }
    else
    {
        printf("Stack is Full");
    }
}
void pop()
{
    if (top == -1)
    {
        printf("Empty");
    }
    else
    {
        top = top - 1;
    }
}
void print_stack()
{
    if (top == -1)
    {
        printf("Stack is Empty");
    }
    else
    {
        printf("\nElements in Stack :");
        for (int i = top; i >= 0; i--)
        {
            printf("\n|%s| -> %d", stack[i], i);
        }
    }
}
int main()
{
    int i, j, k;
    char recursion_free_prods[10][20];
    int fp = 0;
    // Terminal Input
    printf("Enter number of terminals: ");
    scanf("%d", &n_terminals);
    printf("Enter Terminal :\n");
    for (i = 0; i < n_terminals; i++)
    {
        scanf("%s", &terminals[i]);
    }
    // Non-Terminal Input
    printf("Enter number of non-terminals: ");
    scanf("%d", &n_non_terminals);
    printf("Enter non-terminal :\n");
    for (i = 0; i < n_non_terminals; i++)
    {
        scanf("%s", &non_terminals[i]);
    }
    // Productions Input
    printf("Enter number of productions: ");
    scanf("%d", &n_prods);
    printf("Enter productions :\n");
    for (i = 0; i < n_prods; i++)
    {
        scanf("%s", &productions_arr[i]);
    }
    // Removal of left recursion
    create_reserved_chars();
    remove_left_recursion(productions_arr, n_prods,
                          recursion_free_prods, &fp);
    rfp_fptr = fopen("recursion_free_productions.txt", "w");
    printf("Non-recursive grammar:\n");
    if (rfp_fptr != NULL)
    {
        for (i = 0; i < fp; i++)
        {
            fprintf(rfp_fptr, "%s\n", recursion_free_prods[i]);
            printf("%s\n", recursion_free_prods[i]);
        }
    }
    fclose(rfp_fptr);
    // Finding first and follow of the grammar
    read_recursion_free_grammar();
    follow[prod[0].str[0] - 'A']['$'] = 1;
    find_first();
    find_follow();
    rhs_first();
    printf("\n");
    for (i = 0; i < productions_count; ++i)
    {
        if (i == 0 || (prod[i - 1].str[0] != prod[i].str[0]))
        {
            char c = prod[i].str[0];
            printf("FIRST OF %c: ", c);
            for (j = 0; j < TABLE_SIZE; ++j)
            {
                if (first[c - 'A'][j])
                {
                    printf("%c ", j);
                }
            }
            printf("\n");
        }
    }
    printf("\n");
    for (i = 0; i < productions_count; ++i)
    {
        if (i == 0 || (prod[i - 1].str[0] != prod[i].str[0]))
        {
            char c = prod[i].str[0];
            printf("FOLLOW OF %c: ", c);
            for (j = 0; j < TABLE_SIZE; ++j)
            {
                if (follow[c - 'A'][j])
                {
                    printf("%c ", j);
                }
            }
            printf("\n");
        }
    }
    terminal['$'] = 1;
    terminal['^'] = 0;
    // Print parse table
    printf("\n");
    printf("\nLL(1) PARSING TABLE\n");
    printf("%-10s", "");
    for (i = 0; i < TABLE_SIZE; ++i)
    {
        if (terminal[i])
        {
            printf("%-10c", i);
        }
    }
    printf("\n");
    int p = 0;
    for (i = 0; i < productions_count; ++i)
    {
        if (i != 0 && (prod[i].str[0] != prod[i - 1].str[0]))
            p = p + 1;
        for (j = 0; j < TABLE_SIZE; ++j)
        {
            if (first_rhs[i][j] && j != '^')
            {
                table[p][j] = i + 1;
            }
            else if (first_rhs[i]['^'])
            {
                for (k = 0; k < TABLE_SIZE; ++k)
                {
                    if (follow[prod[i].str[0] - 'A'][k])
                    {
                        table[p][k] = i + 1;
                    }
                }
            }
        }
    }
    k = 0;
    for (i = 0; i < productions_count; ++i)
    {
        if (i == 0 || (prod[i - 1].str[0] != prod[i].str[0]))
        {
            printf("%-10c", prod[i].str[0]);
            for (j = 0; j < TABLE_SIZE; ++j)
            {
                if (table[k][j])
                {
                    printf("%-10s", prod[table[k][j] - 1].str);
                }
                else if (terminal[j])
                {
                    printf("%-10s", "");
                }
            }
            ++k;
            printf("\n");
        }
    }
    char input_buffer[20][3];
    char input_expr[1][20];
    printf("Enter expression: ");
    scanf("%s", input_expr[0]);
    i = 0;
    printf("%c", input_expr[0][7]);
    while (input_expr[0][i] != '\0')
    {
        snprintf(input_buffer[i], sizeof(input_buffer[i]), "%c\0", input_expr[0][i]);
        i++;
    }
    printf("\nInput String taken :");
    // Input String
    for (int l = 0; l < 6; l++)
    {
        printf("\t%s", input_buffer[l]);
    }
    printf("\n");
    // Stack Initialize
    push("$");
    push("E");
    // Output Generation
    printf("\nOutput Generation :");
    // Traversing the input character array
    while (z < 5)
    {
        if (strcmp("E", stack[top]) == 0 && strcmp("i",
                                                   input_buffer[z]) == 0)
        {
            printf("\n%s", matrix[1][5]);
            pop();
            push("E'");
            push("T");
        }
        if (strcmp("T", stack[top]) == 0 && strcmp("i",
                                                   input_buffer[z]) == 0)
        {
            printf("\n%s", matrix[3][5]);
            pop();
            push("T'");
            push("F");
        }
        if (strcmp("F", stack[top]) == 0 && strcmp("i",
                                                   input_buffer[z]) == 0)
        {
            printf("\n%s", matrix[5][5]);
            pop();
            push("i");
        }
        if (strcmp("i", stack[top]) == 0)
        {
            pop();
            z++;
        }
        if (strcmp("T'", stack[top]) == 0 && strcmp("*",
                                                    input_buffer[z]) == 0)
        {
            printf("\n%s", matrix[4][2]);
            pop();
            push("T'");
            push("F");
            push("*");
        }
        if (strcmp("*", stack[top]) == 0)
        {
            pop();
            z++;
        }
        if (strcmp("T'", stack[top]) == 0 && strcmp("+",
                                                    input_buffer[z]) == 0)
        {
            printf("\n%s", matrix[4][1]);
            pop();
        }
        if (strcmp("E'", stack[top]) == 0 && strcmp("+",
                                                    input_buffer[z]) == 0)
        {
            printf("\n%s", matrix[2][1]);
            pop();
            push("E'");
            push("T");
            push("+");
        }
        if (strcmp("+", stack[top]) == 0)
        {
            pop();
            z++;
        }
    }
    printf("\n");
    print_stack();
    getch();
    return 0;
}