#include "head.h"

int main(int argc, char *argv[])
{
    if(argc!=4){
        fprintf(stderr, "Error: Missing command line arguments!\n");
        fprintf(stderr, "Use:   ./main input_file_with_matches.txt input_file_with_nicknames.txt output_file.html\n");
        exit(EXIT_FAILURE);
    }else{
        Player p[max_players];
        char *fnameH = argv[1];
        char *fnameN = argv[2];
        char *fnameO = argv[3];
        consstr(p);
        read_matchF(fnameH, p);
        read_nicksF(fnameN, p);
        print_stats(fnameO,p);
    }
    
    return 0;
}
