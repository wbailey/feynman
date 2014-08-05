#ifndef SIMULATION_H
#define SIMULATION_H

#include "dbg.h"
#include "md.h"

double LJ_Epsilon = 0.997; // kJ/mol
double LJ_Sigma = 3.40;    // Angstroms

double t = 0;
double dt = 0.01;

double MD_Collection_Size = 3;
double MD_Box_Length = 18;

int MD_Iterations  = 2000;
int MD_ReportCount = 1000;

#endif
