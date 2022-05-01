#include <stdio.h>
#include <string.h>
char line[100], line1[100], line2[100];
int imnt = 0;
int imdt = 0;
int iala = 0;
void mntproc(char a1[50]);
void alaproc(char a2[50]);
void mdtproc(char ln1[50]);
struct mnt
{
    int index;
    char mname[50];
} n[50];
struct mdt
{
    char instr[50];
} d[50];
struct ala
{
    char arg[50];
} a[50];
int main()
{
    int i;
    char s1[50], s2[50];
    printf("\n\t Pass-1 of Two-Pass-Macro-Processor\n\n");
    static const char filename[] = "input.txt";
    FILE *file = fopen(filename, "r");
    if (file != NULL)
    {
        while (fgets(line, sizeof line, file) != NULL) //
        {
            sscanf(line, "%s", s1);
            if (strcmp(s1, "MACRO") == 0)
            {
                imnt++;
                fgets(line1, sizeof line1, file);
                sscanf(line1, "%s%s", s1, s2);
                mntproc(s1);
                alaproc(s2);
            }
            while (strcmp(s1, "MEND") != 0)
            {
                imdt++;
                fgets(line2, sizeof line2, file);
                sscanf(line2, "%s%s", s1, s2);
                mdtproc(line2);
            }
        }
    }
    FILE *fptr1;
    fptr1 = fopen("MNT.txt", "w");
    printf("\n\t\t MNT TABLE");
    printf("\n\tINDEX\t\tMACRO NAME\tMDT INDEX\n");
    for (i = 0; i < imnt; i++)
    {
        printf("\n\t%d\t\t%s\t\t%d", i + 1, n[i + 1].mname, n[i + 1].index);
        fprintf(fptr1, "\n\t%d\t\t%s\t\t%d", i + 1, n[i + 1].mname, n[i + 1].index);
    }
    fclose(fptr1);
    FILE *fptr2;
    fptr2 = fopen("MDT.txt", "w");
    printf("\n\n\n\t\t MDT TABLE");
    printf("\n\tINDEX\t\tINSTRUCTIONS\n\n");
    for (i = 0; i < imdt; i++)
    {
        printf("\t%d\t\t%s", i + 1, d[i + 1].instr);
        fprintf(fptr2, "\t%d\t\t%s", i + 1, d[i + 1].instr);
    }
    fclose(fptr2);
    FILE *fptr3;
    fptr3 = fopen("ALA.txt", "w");
    printf("\n\n\n\t\t ALA TABLE");
    printf("\n\tINDEX\t\tARGUMENT LIST\n\n");
    for (i = 0; i < iala; i++)
    {
        printf("\n\t%d\t\t%s", i + 1, a[i + 1].arg);
        fprintf(fptr3, "\n\t%d\t\t%s", i + 1, a[i + 1].arg);
    }
    fclose(fptr3);
    fclose(file);
    return 0;
}
void mntproc(char a1[50])
{
    strcpy(n[imnt].mname, a1);
    n[imnt].index = imdt + 1;
}
void alaproc(char a2[50])
{
    iala++;
    strcpy(a[iala].arg, a2);
}
void mdtproc(char ln1[50])
{
    strcpy(d[imdt].instr, ln1);
}