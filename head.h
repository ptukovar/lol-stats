#ifndef HEAD_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define max_players 100

typedef struct
{
    int id;
    char nick[24];
    int elo;
    char division[24];
    int kills;
    int assists;
    int deaths;
    int matches;
    int wins;
    float winrate;
} Player;

Player *read_nicksF(char *filename, Player *p);
Player *read_matchF(char *filename, Player *p);
int elo_calc(Player *p, unsigned id, unsigned en1, unsigned en2, unsigned en3, unsigned sa);
char *division_calc(Player *p, unsigned id);
Player *consstr(Player *p);
void print_stats(char *filename,Player *p);

#endif
