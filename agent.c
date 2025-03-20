// file: agent.c
// description: contains the implimentation for the agent structure's functions
//
// @author: sm9609@rit.edu Samuel Mensah

#include <stdio.h>
#include <stdlib.h>
#include "agent.h"

Agent *agent_new(char s,int x, int y){
    Agent *a = NULL;
    a = malloc(sizeof(Agent));
    a->x = x;
    a->y = y;
    a->style = s;
    a->neighbors = 0;
    a->new_lines = 0;
    a->end_lines = 0;
    return a;
};

void scan_neigh(Agent *a, Agent *g, int x, int y, int x_off, int y_off, int x_end_off, int y_end_off){
    for(int i = y + y_off; y <= y + y_end_off;y++){
        Agent *row = g+i;
        for(int j = x + x_off; x <= x + x_end_off; x++){
            if(!(i == y && j == x)){
                Agent *ca = row+j; 
                if(ca->style =='e'){
                    a->neighbors++;
                    a->end_lines++;
                }
                else if(ca->style == 'n'){
                    a->neighbors++;
                    a->new_lines++;
                }
            }
        }
    }
}


void count_neigh(Agent *a,int dim,Agent *g){
    int y = a->y;
    int x = a->x;
    if(y == 0 && x == 0){
        scan_neigh(a,g,x,y,0,0,1,1);
    }
    else if(x == dim-1 && y == 0){
        scan_neigh(a,g,x,y,-1,0,0,1);
    }
    else if(x == dim-1 && y == dim-1){
        scan_neigh(a,g,x,y,-1,-1,0,0);
    }
    else if(x == 0 && y == dim-1){
        scan_neigh(a,g,x,y,0,-1,1,0);
    }

    else if(x == 0 && (y != 0 || y != dim-1)){
        scan_neigh(a,g,x,y,0,-1,1,1);
    }
    else if(x == dim-1 && (y != dim-1 || y != 0)){
        scan_neigh(a,g,x,y,-1,-1,0,1);
    }
    else if(y == 0 && (x != 0 && x != dim-1)){
        scan_neigh(a,g,x,y,-1,0,1,1);
    }
    else if(y == dim-1 && (x != dim-1)){
        scan_neigh(a,g,x,y,-1,0,1,-1);
    }
    else{
        scan_neigh(a,g,x,y,-1,-1,1,1);
    }
}

double get_happiness(Agent *a){
    if(a->style == 'e'){
        return a->end_lines / a->neighbors;    
    }
    else{
        return a->new_lines / a->neighbors;
    }
}

