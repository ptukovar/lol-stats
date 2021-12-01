#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define max_players 100

typedef struct {
    int id;
    char nick[24]; 
    int elo;
    int played;
    int wins;
    float winrate;
}Players;


int main(){
    FILE *fnicks;
    Players p[max_players];//(Players*)malloc(sizeof(Players)+max_players);
    char line[20];
    char *temp;
    int id;
    fnicks=fopen("nicks.txt","rt");
    if (fnicks == NULL){
        perror("Error: ");
        return (-1);
    }
    int i=0;
    while(fgets(line,sizeof(line),fnicks)!=NULL){
        temp=strtok(line,",");
        id=atoi(temp);
        p[i].id=id;
        //printf("%d\n",p[id].id);
        temp=strtok(NULL,"\n");
        strcpy(p[i].nick,temp);
        //printf("%s\n",p[id].p->nick);
        i++;
    }
    for(int j=0;j<i;j++){
        printf("%d ",p[j].id);
        printf("%s\n",p[j].nick);
    }
    
    fclose(fnicks);
    return 0;
}
