// file: brace_topia.c 
// description: 
// 
// @author: sm9609@rit.edu Samuel Mensah
//

#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <string.h>
#include <errno.h>
#include "agent.h"
 


Agent **shuffle (int dim, Agent **grid ){
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            int k = random() % (dim);
            int l = random() % (dim);
            swap(&grid[i][j],&grid[k][l]);    
        }
    }
    return grid;
}

Agent **inti_grid (int dim, double vac, double end_lines){
    int index = 0;
    int max = (dim * dim);
    max -= (max*vac);

    Agent **grid = (Agent **) malloc(sizeof(Agent *) * dim);
    for(int i = 0; i < dim ; i++){
        grid[i] = (Agent *) malloc(sizeof(Agent ) * dim);
        for(int j = 0; j < dim; j++){
            if(index <= max){
                if(index < end_lines * max){
                    grid[i][j] = agent_new('e',j,i);
                }
                else{
                    grid[i][j] = agent_new('n',j,i);             
                }
            }
            else{
                grid[i][j] = agent_new('.',j,i);    
            }
            index++;
        }
    }
    return grid;
}

void print_grid(int dim,Agent **grid){
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            Agent agent = grid[i][j];
            if(agent != NULL){
                printf("%c", agent->style);
            }
            else{
                printf("ca null pointer detected");
            }
        }
        printf("\n");
    }
}

int arg_to_int(char *str){
    errno = 0;
    int temp = strtol(str,NULL,10);
    if(errno == ERANGE || temp < 0){ 
        return -1;
    }
    else{
        return temp;
    }
}

void run(int dim,Agent **grid, double thr){
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            count_neigh(dim,grid[i][j],grid);
            double hap = get_happiness(grid[i][j]);
            if(hap < thr && grid[i][j]->style != '.'){

                move(dim,grid[i][j],grid);   
                print_grid(dim,grid);
                printf("\n");
            }
        }
    }
}


/*
void print_mode_print(char*** grid,int dim, int cyc, int delay, double vac, double end, double thr ){
    for(int i = 0; i < cyc; i++){
        
        unsleep(delay);
    }
    
}
*/

int main(int argc,char *argv[] ){
    srandom(41);
    int dim = 15;
    int cycles = -1;
    int tdelay = 900000;
    double vacancy = 0.2;
    double end_lines = 0.6;
    double threshold = 0.5;
    const char *usage =  "usage: \n \
                       brace-topia [-h] [-t N] [-c N] [-d dim] [-s %%str] [-v %%vac] [-e %%end]\n \
                       Option      Default    Example  Description\n \
                       '-h'        NA        -h        print this usage message.\n \
                       '-t N'      900000    -t 5000   microseconds cycle delay.\n \
                       '-c N'      NA        -c4       count cycle maximum value.\n \
                       '-d dim'    15        -d 7      width and height dimension.\n \
                       '-s %%str'   50        -s 30     strength of preference.\n \
                       '-v %%vac'   20        -v30      percent vacancies.\n \
                       '-e %%endl'  60        -e75      percent Endline braces. Others want Newline.\n";
    int opt;
    while( (opt = (getopt(argc, argv,"ht:c:d:s:v:e:"))) != -1){
        int op_arg = 0;
        int temp; 
        switch (opt){
            case 'h':
                printf("%s",usage);
                return 0;
            case 't':
                tdelay = arg_to_int(optarg);
                if (tdelay < 0){
                    printf("invalid arg: -t %s \n", optarg);
                    return 1;
                }
                break;
            case 'c':
                cycles = arg_to_int(optarg);
                if(cycles < 0){
                    printf("invalid arg: -c %s \n", optarg);
                    return 1;
                }
                break;
            case 'd':
                dim = arg_to_int(optarg);
                if(dim < 0){
                    printf("invalid arg: -d %s \n", optarg);
                    return 1;
                }
                break;
            case 's':
                threshold = arg_to_int(optarg) / 100;
                if(threshold < 0 || threshold > 1){
                    printf("invalid arg: -s %s \n", optarg);
                    return 1;
                }
                break;
            case 'v':
                vacancy = arg_to_int(optarg) / 100;
                if(vacancy < 0 || vacancy > 1){
                    printf("invalid arg: -v %s \n", optarg);
                    return 1;
                }
                break;
            case 'e':
                end_lines = arg_to_int(optarg) / 100;
                if(end_lines < 0 || end_lines > 1){
                    printf("invalid arg: -e %s \n", optarg);
                    return 1;
                }
                break;
        }   
    }
/*
    if(cycles > 0){
        print_mode_run();
    }
    else if(cycles < 0){
       printf(""); 
    }
    else{
        fprintf(stderr,"failded to start with cycle arg";
        return 2;
    }
*/
    Agent **grid = inti_grid(dim,vacancy,end_lines);
    print_grid(dim,shuffle(dim,grid));
    printf("\n");
    run(dim,grid,threshold);
    print_grid(dim,grid);
    return 0;
}
