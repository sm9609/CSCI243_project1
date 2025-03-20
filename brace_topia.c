// file: brace_topia  
// description: 
// 
// @author: sm9609@rit.edu Samuel Mensah
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <errno.h>
#include "agent.h"

Agent ***inti_grid (int dim, double vac, double end_lines){
    int index = 0;
    int max = (dim * dim);
    max = max - (max*vac);

    Agent ***grid =(Agent ***) malloc(sizeof(Agent **) * dim);
    for(int i = 0; i < dim; i++){
        grid[i] = (Agent **) malloc(sizeof(Agent *) * dim);
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
        }
    }
    return grid;
}

void print_grid(int dim,Agent ***grid){
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            Agent *agent = grid[i][j];
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

int main(int argc,char *argv[] ){
    int dim = 15;
    int cycles = -1;
    int tdelay = 900000;
    double vacancy = 0.2;
    double end_lines = 0.6;
    double threshold = 0.5;

    int opt;
    while( (opt = (getopt(argc, argv,"ht:c:d:s:v:e:"))) != -1){
        int op_arg = 0;
        int temp; 
        switch (opt){
            case 'h':
                printf("usage: \n"
                       "brace-topia [-h] [-t N] [-c N] [-d dim] [-s %%str] [-v %%vac] [-e %%end]\n"
                       "Option      Default    Example  Description\n"
                       "'-h'        NA        -h        print this usage message.\n"
                       "'-t N'      900000    -t 5000   microseconds cycle delay.\n"
                       "'-c N'      NA        -c4       count cycle maximum value.\n"
                       "'-d dim'    15        -d 7      width and height dimension.\n"
                       "'-s %%str'   50        -s 30     strength of preference.\n"
                       "'-v %%vac'   20        -v30      percent vacancies.\n"
                       "'-e %%endl'  60        -e75      percent Endline braces. Others want Newline.\n");
                return 0;
            case 't':
                tdelay = arg_to_int(optarg);
                if (tdelay < 0){
                    printf("invalid arg: -t %s \n", optarg);
                    return 1;
                }
                break;
            case 'c':
                if(isdigit(optarg)){
                    cycles = atoi(optarg);
                }
                else{
                    printf("invalid arg: -c %s \n", optarg);
                }
                break;
            case 'd':
                if(isdigit(atoi(optarg))){
                    dim = atoi(optarg);
                }else{
                    printf("invalid arg: -d %s \n", optarg);
                }
                break;
            case 's':
                if(isdigit(optarg)){
                    threshold = atoi(optarg)/100;
                }
                else{
                    printf("invalid arg: -s %s \n", optarg);
                }
                break;
            case 'v':
                if(isdigit(optarg)){
                    vacancy = atoi(optarg)/100;
                }
                else{
                    printf("invalid arg: -v %s \n", optarg);
                }
                break;
            case 'e':
                if(isdigit(optarg)){
                    end_lines = atoi(optarg)/100;
                }
                else{
                    printf("invalid arg: -e %s \n", optarg);
                }
                break;
        }   
    }

    //Agent ***grid = inti_grid(dim,vacancy,end_lines);
    //print_grid(dim,grid);
    return 0;
}
