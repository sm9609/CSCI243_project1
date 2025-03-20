// file: agent.h
// description: provides the interface for the agent structure.
//
// @author: sm9609@rit.edu  Samuel Mensah
// 
#ifndef AGENT_H
#define AGENT_H

#include <stdio.h>

typedef struct agent_s Agent;

struct agent_s{
    int neighbors;
    int end_lines;
    int new_lines;
    int x;
    int y;
    char style;
};

Agent *agent_new(char s,int x,int y);

/// check the eight adjacent cells for their agents and add them to an array.
/// @param a the current agent.
/// @param s the simulation the agent is a part
void count_neigh(Agent *a,int dim,Agent *g);

void scan_neigh(Agent *a,Agent *g,int x,int y,int x_off,int y_off,int x_end_off,int y_end_off);

/// gets the percent average of the neighbors with the same style.
/// @param a the current agent.
/// @param s the simulation the agent is a part of.
/// @return a double representing the percent happiness of the current agent.
double get_happiness(Agent *a);

/// gets the coding style of the current agent.
/// @param a the current agent.
/// @return a char representing the style
char get_style(Agent a);

/// moves the agent to the first vacant cell in the provided simulation's grid.
/// @param a the current agent.
/// @param s the simulation the agent is a part of
void move(Agent a);

int get_x(Agent a);

int get_y(Agent a);

#endif // AGENT_H

