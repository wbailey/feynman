#ifndef SIMULATION_H
#define SIMULATION_H

#include "dbg.h"
#include "md.h"

double LJ_Epsilon = 0.997; // kJ/mol
double LJ_Sigma = 3.40;    // Angstroms

double t = 0;
double dt = 0.005;

double particle_count = 4;

int iterations  = 5000;
int reportcount = 500;

#endif
