#ifndef SIMULATION_H
#define SIMULATION_H

#include "dbg.h"
#include "md.h"

double LJ_Epsilon = 0.997; // kJ/mol
double LJ_Sigma = 3.40;    // Angstroms

double t = 0;
double dt = 0.005;

double MD_CollectionSize = 4;

int MD_Iterations  = 5000;
int MD_ReportCount = 1000;

#endif
