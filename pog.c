#include "head.h"

Player *read_fnicks(char *filename, Player *p)

{

    FILE *fnicks;

    char line[60], *temp;

    char nick[20] = {0};

    unsigned id = 0;

    int i = 0;

    fnicks = fopen(filename, "rt");

    if (fnicks == NULL)

    {

        perror("Wrong file!");

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

        for (int k = 0; k < 2; k++)
        {

            for (int l = 0; l < 2; l++)
            {

                if (redid[k] == blueid[l])
                {

                    fprintf(stderr, "Error: Nonsense match format!\n");

                    exit(EXIT_FAILURE);
                }
            }
        }

        if (redid[0] == redid[1] || redid[1] == redid[2] || redid[2] == redid[0])
        {

            fprintf(stderr, "Error: Nonsense match format!\n");

            exit(EXIT_FAILURE);
        }

        if (blueid[0] == blueid[1] || blueid[1] == blueid[2] || blueid[2] == blueid[0])
        {

            fprintf(stderr, "Error: Nonsense match format!\n");

            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < max_players; i++)

        {

            if (j <= 2)

            {

                if (i == redid[j])

                {

                    p[i].kills += redk[j];

                    p[i].assists += reda[j];

                    p[i].deaths += redd[j];

                    if (strcmp(winner, "red") == 0)

                    {
                        p[i].matches += 1;
                        p[i].wins += 1;
                        float wi=0;
                        wi=p[i].wins;
                        float ma=0;
                        ma=p[i].matches;
                        p[i].winrate = (wi / ma) * 100;

                        p[i].elo = elo_calc(p, i, blueid[0], blueid[1], blueid[2], 1);

                        strcpy(div, division_calc(p, i));

                        strcpy(p[i].division, div);
                    }

                    else

                    {

                        p[i].matches += 1;
                        float wi=0;
                        wi=p[i].wins;
                        float ma=0;
                        ma=p[i].matches;
                        p[i].winrate = (wi / ma) * 100;

                        p[i].elo = elo_calc(p, i, blueid[0], blueid[1], blueid[2], 0);

                        strcpy(div, division_calc(p, i));

                        strcpy(p[i].division, div);
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

                if (i == blueid[j])

                {

                    p[i].kills += bluek[j];

                    p[i].assists += bluea[j];

                    p[i].deaths += blued[j];

                    if (strcmp(winner, "blue") == 0)

                    {

                        p[i].wins += 1;

                        p[i].matches += 1;
                        float wi=0;
                        wi=p[i].wins;
                        float ma=0;
                        ma=p[i].matches;
                        p[i].winrate = (wi / ma) * 100;

                        p[i].elo = elo_calc(p, i, redid[0], redid[1], redid[2], 1);

                        strcpy(div, division_calc(p, i));

                        strcpy(p[i].division, div);
                    }

                    else

                    {

                        p[i].matches += 1;
                        float wi=0;
                        wi=p[i].wins;
                        float ma=0;
                        ma=p[i].matches;
                        p[i].winrate = (wi / ma) * 100;

                        p[i].elo = elo_calc(p, i, redid[0], redid[1], redid[2], 0);

                        strcpy(div, division_calc(p, i));

                        strcpy(p[i].division, div);
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

Player *constr(Player *p)
{

    for (int j = 0; j < max_players; j++)

    {

        p[j].id = -1;

        strcpy(p[j].nick, "XXXXXXXX");

        p[j].elo = 1000;

        strcpy(p[j].division, "Bronze");

        p[j].kills = 0;

        p[j].assists = 0;

        p[j].deaths = 0;

        p[j].matches = 0;

        p[j].winrate =0;

        p[j].wins = 0;
    }

    return p;
}

void print_stats(Player *p)

{

    FILE *fout = fopen("output.html", "w");
    fprintf(fout, "<!DOCTYPE html>\n");
    fprintf(fout, "<html lang=\"en\">\n");
    fprintf(fout, "<head>\n");
    fprintf(fout, "    <meta charset=\"UTF-8\">\n");
    fprintf(fout, "    <title>LOL-stats</title>\n");
    fprintf(fout, "</head>\n");
    fprintf(fout, "<style>\n");
    fprintf(fout, "  .tab{\n");
    fprintf(fout, "    text-align: center;\n");
    fprintf(fout, "    border: 2px solid black;\n");
    fprintf(fout, "  }\n");
    fprintf(fout, "  th{\n");
    fprintf(fout, "    border: 1px solid black;\n");
    fprintf(fout, "    background-color: #000;\n");
    fprintf(fout, "    color: #fff;\n");
    fprintf(fout, "  }\n");
    fprintf(fout, "  td{\n");
    fprintf(fout, "    border: 1px solid black;\n");
    fprintf(fout, "  }\n");
    fprintf(fout, "</style>\n");
    fprintf(fout, "<body>\n");
    fprintf(fout, "<table class=\"tab\" cellspacing=\"0\" cellpadding=\"0\">\n");
    fprintf(fout, "  <tr class=\"bor\">\n");
    fprintf(fout, "    <th>ID</th>\n");
    fprintf(fout, "    <th>NICK</th>\n");
    fprintf(fout, "    <th>ELO</th>\n");
    fprintf(fout, "    <th>DIVISION</th>\n");
    fprintf(fout, "    <th>KILLS</th>\n");
    fprintf(fout, "    <th>ASSISTS</th>\n");
    fprintf(fout, "    <th>DEATHS</th>\n");
    fprintf(fout, "    <th>WIN RATE</th>\n");
    fprintf(fout, "    <th>WINS</th>\n");
    fprintf(fout, "    <th>MATCHES</th>\n");
    fprintf(fout, "  </tr>\n");

    int x = 0, y = 0;

    for (int i = 0; i < max_players; i++)

    {

        fprintf(fout, "    <tr>\n");

        if (p[i].id == -1)

        {
        }

        else

        {

            fprintf(fout, "<td>%d</td>\n", p[i].id);

            fprintf(fout, "<td>%s</td>\n", p[i].nick);

            fprintf(fout, "<td>%d</td>\n", p[i].elo);

            fprintf(fout, "<td>%s</td>\n", p[i].division);

            fprintf(fout, "<td>%d</td>\n", p[i].kills);

            fprintf(fout, "<td>%d</td>\n", p[i].assists);

            fprintf(fout, "<td>%d</td>\n", p[i].deaths);

            fprintf(fout, "<td>%.2f%%</td>\n", p[i].winrate);

            fprintf(fout, "<td>%d</td>\n", p[i].wins);

            fprintf(fout, "<td>%d</td>\n", p[i].matches);
        }

        fprintf(fout, "    </tr>\n");
    }

    fprintf(fout, "  </tr>\n");

    fprintf(fout, "</table>\n");

    fprintf(fout, "</body>\n");

    fprintf(fout, "</html>\n");
}

int main(int argc, char *argv[])

{

    Player p[max_players];

    char *fnameh = "matches.txt"; //argv[1];

    char *fnamen = "players.txt"; //argv[2];

    constr(p);

    read_matchF(fnameh, p);

    read_fnicks(fnamen, p);

    print_stats(p);

    return 0;
}
