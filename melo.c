#include "head.h"
Player *read_fnicks(char *filename, Player *p)
{
    FILE *fnicks;
    char line[60], *temp;
    char nick[20] = {0};
    unsigned id = 0;
    int i = 0;
    for (int j = 0; j < max_players; j++)
    {
        p[j].id = -1;
        strcpy(p[j].nick, "");
        p[j].elo = 1000;
        strcpy(p[j].division, "Bronze");
        p[j].kills = 0;
        p[j].assists = 0;
        p[j].deaths = 0;
        p[j].matches = 0;
        p[j].wins = 0;
    }
    fnicks = fopen(filename, "rt");
    if (fnicks == NULL)
    {
        perror("Error: ");
        exit(-1);
    }

    while (!feof(fnicks))
    {
        fscanf(fnicks, "%u,%s\n", &id, nick);
        p[id].id = id;
        strcpy(p[id].nick, nick);
    }
    fclose(fnicks);
    return p;
}
int elo_calc(Player *p, unsigned id, unsigned en1, unsigned en2, unsigned en3, unsigned sa)
{
    int ra = 0, rb = 0;
    ra = p[id].elo;
    rb = (p[en1].elo + p[en2].elo + p[en3].elo) / 3;
    float ea = 0;
    ea = 1 / (1 + pow(10, ((rb - ra) / 400)));
    int k = 30;

    float novy_rating = (int)round(ra + k * (sa - ea));
    return novy_rating;
}
char *division_calc(Player *p, unsigned id)
{
    if (p[id].elo <= 1149)
    {
        return "Bronze";
    }
    else if (p[id].elo <= 1499)
    {
        return "Silver";
    }
    else if (p[id].elo <= 1849)
    {
        return "Gold";
    }
    else if (p[id].elo <= 2199)
    {
        return "Platinum";
    }
    else
    {
        return "Diamond";
    }
}
Player *read_matchF(char *filename, Player *p)
{
    FILE *fhistory;
    fhistory = fopen(filename, "rt");
    char *line = malloc(sizeof(char) * 256);
    unsigned *redid = malloc(sizeof(unsigned) * 3);
    unsigned *redk = malloc(sizeof(unsigned) * 3);
    unsigned *reda = malloc(sizeof(unsigned) * 3);
    unsigned *redd = malloc(sizeof(unsigned) * 3);
    unsigned *blueid = malloc(sizeof(unsigned) * 3);
    unsigned *bluek = malloc(sizeof(unsigned) * 3);
    unsigned *bluea = malloc(sizeof(unsigned) * 3);
    unsigned *blued = malloc(sizeof(unsigned) * 3);
    char *winner = malloc(sizeof(char) * 16);
    char div[16];
    while (!feof(fhistory))
    {
        fscanf(fhistory, "%s\n", line);
        if (strcmp(line, "match") != 0)
        {
            printf("invalid format\n");
            exit(1);
        }
        fscanf(fhistory, "%u,%u,%u\n", &redid[0], &redid[1], &redid[2]);
        fscanf(fhistory, "%u;%u;%u,%u;%u;%u,%u;%u;%u\n",
               &redk[0], &reda[0], &redd[0],
               &redk[1], &reda[1], &redd[1],
               &redk[2], &reda[2], &redd[2]);
        fscanf(fhistory, "%u,%u,%u\n", &blueid[0], &blueid[1], &blueid[2]);
        fscanf(fhistory, "%u;%u;%u,%u;%u;%u,%u;%u;%u\n",
               &bluek[0], &bluea[0], &blued[0],
               &bluek[1], &bluea[1], &blued[1],
               &bluek[2], &bluea[2], &blued[2]);
        fscanf(fhistory, "%s\n", winner);
        int j = 0;
        for (int i = 0; i < max_players; i++)
        {
            if (j <= 2)
            {
                if (p[i].id == redid[j])
                {
                    p[i].kills += redk[j];
                    p[i].assists += reda[j];
                    p[i].deaths += redd[j];
                    if (strcmp(winner, "red") == 0)
                    {
                        p[i].wins += 1;
                        p[i].matches += 1;
                        p[i].winrate = (p[i].wins / p[i].matches) * 100;
                        p[i].elo = elo_calc(p, i, blueid[0], blueid[1], blueid[2], 1);
                        strcpy(div,division_calc(p,i));
                        strcpy(p[i].division,div);
                    }
                    else
                    {
                        p[i].matches += 1;
                        p[i].winrate = (p[i].wins / p[i].matches) * 100;
                        p[i].elo = elo_calc(p, i, blueid[0], blueid[1], blueid[2], 0);
                        strcpy(div,division_calc(p,i));
                        strcpy(p[i].division,div);
                    }
                    j++;
                }
            }
        }
        j = 0;
        for (int i = 0; i < max_players; i++)
        {
            if (j <= 2)
            {
                if (p[i].id == blueid[j])
                {
                    p[i].kills += bluek[j];
                    p[i].assists += bluea[j];
                    p[i].deaths += blued[j];
                    if (strcmp(winner, "blue") == 0)
                    {
                        p[i].wins += 1;
                        p[i].matches += 1;
                        p[i].winrate = (p[i].wins / p[i].matches) * 100;
                        p[i].elo = elo_calc(p, i, redid[0], redid[1], redid[2], 1);
                        strcpy(div,division_calc(p,i));
                        strcpy(p[i].division,div);
                    }
                    else
                    {
                        p[i].matches += 1;
                        p[i].winrate = (p[i].wins / p[i].matches) * 100;
                        p[i].elo = elo_calc(p, i, redid[0], redid[1], redid[2], 0);
                        strcpy(div,division_calc(p,i));
                        strcpy(p[i].division,div);
                    }
                    j++;
                }
            }
        }
    }
    free(line);
    line = NULL;
    free(redid);
    redid = NULL;
    free(redk);
    redk = NULL;
    free(reda);
    reda = NULL;
    free(redd);
    redd = NULL;
    free(blueid);
    blueid = NULL;
    free(bluek);
    bluek = NULL;
    free(bluea);
    bluea = NULL;
    free(blued);
    blued = NULL;
    free(winner);
    winner = NULL;
    fclose(fhistory);
}

void print_stats(Player *p)
{
    int x = 0, y = 0;
    for (int i = 0; i < max_players; i++)
    {
        if (p[i].id == -1)
        {
        }
        else
        {
            printf("ID:\t\t%d\n", p[i].id);
            printf("Nick:\t\t%s\n", p[i].nick);
            printf("Elo:\t\t%d\n", p[i].elo);
            printf("Division:\t%s\n",p[i].division);
            printf("Kills:\t\t%d\n", p[i].kills);
            printf("Assists:\t%d\n", p[i].assists);
            printf("Deaths:\t\t%d\n", p[i].deaths);
            printf("Win rate:\t%.2f%%\n", p[i].winrate);
            printf("Wins:\t\t%d\n", p[i].wins);
            printf("Matches:\t%d\n", p[i].matches);
            printf("----------------------------\n");
        }
    }
}
int main(int argc, char *argv[])
{
    Player p[max_players];
    char *fnameh = "matches.txt"; //argv[1];
    char *fnamen = "players.txt"; //argv[2];
    read_fnicks(fnamen, p);
    read_matchF(fnameh, p);
    print_stats(p);
    return 0;
}
