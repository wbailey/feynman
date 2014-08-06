#ifndef LENNARD_JONES_H
#define LENNARD_JONES_H

#include <stdio.h>
#include <math.h>
#include <assert.h>

double LJ_R6(double);
double LJ_R12(double);
double LJ_Force(double);
double LJ_Potential_Energy(double);

extern double LJ_Epsilon;
extern double LJ_Sigma;

#endif
