#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
char i1[20], i2[20], i3[20], macron[30], cname[50][50],
    dname[50][50];
int size, a;
void write(char line[])
{
    FILE *fptr1;
    if ((fptr1 = fopen("output.txt", "a+")) == NULL)
    {
        printf("\n\t\t file error ....");
    }
    else
    {
        fputs(line, fptr1);
        fclose(fptr1);
    }
}
int cmp(char data[])
{
    int i, flag = 0;
    fflush(NULL);
    for (i = 0; i <= size; i++)
    {
        if (strcmp(dname[i], data) == 0)
        {
            write(cname[i]);
            // puts(cname[i]);
            flag = 1;
            break;
        }
    }
    if (flag != 1)
    {
        write(data);
        write(" ");
        // puts(data);
    }
    return 0;
}
void mdt()
{
    FILE *fptr;
    char line[100], msg[30], op1[20], data1[20], com[1] = {};
    int i, j = 0, k = 0, l = 0, m, n, o, flag;
    fflush(NULL);
    if ((fptr = fopen("mdt.txt", "r")) == NULL)
    {
        printf("\n\t\t file error ....");
    }
    else
    {
        while (!feof(fptr))
        {
            j = 0;
            line[j] = fgetc(fptr);
            while (line[j] != '\n' && line[j] != EOF)
            {
                j++;
                line[j] = fgetc(fptr);
            }
            line[j] = '\0';
            sscanf(line, "%s %s ", op1, msg);
            if (atoi(i2) == atoi(op1))
            {
                flag = 1;
                continue;
            }
            if (flag == 1)
            {
                if (strcmp(msg, "MEND") != 0)
                {
                    // puts(line);
                    for (k = strlen(op1) + 1, l = 0;
                         line[k] != '\0'; k++, l++)
                    {
                        if (line[k] == ' ')
                        {
                            data1[l] = '\0';
                            cmp(data1);
                            l = 0;
                            k++;
                        }
                        data1[l] = line[k];
                    }
                    data1[l] = '\0';
                    write(com);
                    cmp(data1);
                    write("\n");
                }
                else
                {
                    flag = 0;
                }
            }
        }
    }
    fclose(fptr);
}
void sepc(char arg[])
{
    char line[100];
    int i, j, k, l;
    l = 0, i = 0, j = 0;
    while (arg[i] != '\0')
    {
        if (isspace(arg[i]))
        {
            line[l] = '\0';
            strcpy(cname[j], line);
            j++;
            l = 0;
            i++;
        }
        line[l] = arg[i];
        l++;
        i++;
    }
    line[l] = '\0';
    strcpy(cname[j], line);
    size = j;
}
void sepd(char arg[])
{
    char line[100];
    int i, j, k, l;
    l = 0, i = 0, j = 0;
    while (arg[i] != '\0')
    {
        if (isspace(arg[i]))
        {
            line[l] = '\0';
            strcpy(dname[j], line);
            j++;
            l = 0;
            i++;
        }
        line[l] = arg[i];
        l++;
        i++;
    }
    line[l] = '\0';
    strcpy(dname[j], line);
}
int searchn(char op[])
{
    FILE *fptr;
    char line[100];
    int i, j, k;
    if ((fptr = fopen("mnt.txt", "r")) == NULL)
    {
        printf("\n\t\t file error ....");
    }
    else
    {
        while (!feof(fptr))
        {
            j = 0;
            line[j] = fgetc(fptr);
            while (line[j] != '\n' && line[j] != EOF)
            {
                j++;
                line[j] = fgetc(fptr);
            }
            line[j] = '\0';
            sscanf(line, "%s %s %s %s ", macron, i1, i2, i3);
            if (strcmp(macron, op) == 0)
            {
                return 1;
            }
        }
    }
    fclose(fptr);
    return 0;
}
int getarg()
{
    FILE *fptr;
    char line[100], dline[100], op1[10], op2[50];
    int i, j, k, l;
    if ((fptr = fopen("ala.txt", "r")) == NULL)
    {
        printf("\n\t\t file error ....");
    }
    else
    {
        while (!feof(fptr))
        {
            j = 0;
            line[j] = fgetc(fptr);
            while (line[j] != '\n' && line[j] != EOF)
            {
                j++;
                line[j] = fgetc(fptr);
            }
            line[j] = '\0';
            sscanf(line, "%s %s", op1, op2);
            k = strlen(op1) + 1;
            l = strlen(line);
            if (atoi(i3) == atoi(op1))
            {
                for (i = strlen(op1) + 1, l = 0; line[i] != '\0'; i++, l++)
                {
                    dline[l] = line[i];
                }
                dline[l] = '\0';
                // puts(dline);
                sepd(dline);
                return 1;
            }
        }
    }
    fclose(fptr);
    return 0;
}
void main()
{
    FILE *fptr, *fptr1;
    char fname[20], line[50], op[20], str[20], msg[20],
        arg[20], callline[50];
    int j = 0, cnt, flag = 0, i, l, m, o, k, argf;
    if ((fptr = fopen("input.txt", "r")) == NULL)
    {
        printf("\n\t\t file error ....");
    }
    else
    {
        while (!feof(fptr))
        {
            j = 0;
            line[j] = fgetc(fptr);
            while (line[j] != '\n' && line[j] != EOF)
            {
                j++;
                line[j] = fgetc(fptr);
            }
            line[j] = '\0';
            sscanf(line, " %s ", op);
            flag = searchn(op);
            if (flag != 1)
            {
                write(line);
                write("\n");
            }
            if (flag == 1)
            {
                for (i = strlen(macron) + 1, l = 0; line[i] != '\0'; i++, l++)
                {
                    if (line[i] == ',')
                    {
                        line[i] = ' ';
                    }
                    callline[l] = line[i];
                }
                callline[l] = '\0';
                // puts(callline);
                argf = getarg();
                if (argf == 1)
                {
                    sepc(callline);
                    mdt();
                    flag = 0;
                }
            }
        }
    }

printf("\n\n\t\tPass-2 of Two-Pass-Macro-Processor Compiled successfully!\n\t\t\t\tCheck the output.txt\n\t\t\t\t\tEnd\n\n");
fclose(fptr);
}