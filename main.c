#include "head.h"
Player *read_nicksF(char *filename, Player *p)
{
    FILE *nicksF;
    char line[60], *temp;
    int id, i = 0;
    for (int j = 0; j < max_players; j++)
    {
        p[j].id = -1;
    }
    nicksF = fopen(filename, "rt");
    if (nicksF == NULL)
    {
        perror("Error: ");
        exit(-1);
    }

    while (fgets(line, sizeof(line), nicksF) != NULL)
    {
        temp = strtok(line, ",");
        id = atoi(temp);
        p[i].id = id;

        temp = strtok(NULL, "\n");
        strcpy(p[i].nick, temp);
        i++;
    }
    fclose(nicksF);
    return p;
}
void print_nicks(Player *p)
{
    int x = 0, y = 0;
    for (int i = 0; i < max_players; i++)
    {
        if (p[i].id == -1)
        {
        }
        else
        {
            printf("Nick:\t%s\tId: %d\n", p[i].nick, p[i].id);
        }
    }
}
Player *read_matchF(char *filename, Player *p)
{
    FILE *fhistory;
    Match *m[max_players];
    fhistory = fopen(filename, "rt");
    int id = 0;
    char *temp, *a, *b, *c;
    char line[60];
    int x = 0, s = 0;
    while (fgets(line, sizeof(line), fhistory) != NULL)
    {
        if (strcmp(line, "match\n") == 0)
        {
            printf("%s", line);
            x = 1;
        }
        else if (x == 1)
        {
            temp = strtok(line, ",");
            for (int i = 0; i < 3; i++)
            {
                id = atoi(temp);
                temp = strtok(NULL, ",");
                printf("ID: %d\n", id);
            }
            x = 2;
        }
        else if (x == 2)
        {
            a = strtok(line, ",");
            b = strtok(NULL, ",");
            c = strtok(NULL, ",");
            a = strtok(a, ";");
            for (int i = 0; i < 3; i++)
            {
                s = atoi(a);
                a = strtok(NULL, ";");
                printf("A %d\n", s);
            }
            b = strtok(b, ";");
            for (int i = 0; i < 3; i++)
            {
                s = atoi(b);
                b = strtok(NULL, ";");
                printf("B %d\n", s);
            }
            c = strtok(c, ";");
            for (int i = 0; i < 3; i++)
            {
                s = atoi(c);
                c = strtok(NULL, ";");
                printf("C %d\n", s);
            }
            x=3;
        }
        else if (x == 3)
        { //scnd team
            temp = strtok(line, ",");
            for (int i = 0; i < 3; i++)
            {
                id = atoi(temp);
                temp = strtok(NULL, ",");
                printf("ID: %d\n", id);
            }
            x = 4;
        }
        else if (x == 4)
        { //scnd team
            a = strtok(line, ",");
            b = strtok(NULL, ",");
            c = strtok(NULL, ",");
            a = strtok(a, ";");
            for (int i = 0; i < 3; i++)
            {
                s = atoi(a);
                a = strtok(NULL, ";");
                printf("A %d\n", s);
            }
            b = strtok(b, ";");
            for (int i = 0; i < 3; i++)
            {
                s = atoi(b);
                b = strtok(NULL, ";");
                printf("B %d\n", s);
            }
            c = strtok(c, ";");
            for (int i = 0; i < 3; i++)
            {
                s = atoi(c);
                c = strtok(NULL, ";");
                printf("C %d\n", s);
            }
            x = 5;
        }
        else if (x == 5)
        {
            if(strcmp(line, "red") == 0){
                
            }else if(strcmp(line, "blue") == 0){

            }
            x=0;
        }
        else
        {
            break;
        }
    }
    fclose(fhistory);
}

int main(int argc, char *argv[])
{

    FILE *fnicks;
    Player p[max_players];
    char *fnameh = "matches.txt"; //argv[1];
    char *fnamen = "players.txt"; //argv[2];
    read_nicksF(fnamen, p);
    read_matchF(fnameh, p);
    //print_nicks(p);
    return 0;
}
