/*  @para Raw_Data_Size ：the size of array
 *  @para epsilon :the margin in comparing two numbers
 *
 *
 *
 * Created by DongxuGuo on 3/5/2019.
 */

#ifndef __KMPM_H
#define __KMPM_H
#include "Parameters.h"

extern Parameters State;

int equal(unsigned short a, unsigned short b, unsigned short eps);
int pmatch(Parameters* State, int sl, int pl);
int hasPeriod(Parameters* State);
void getNext(unsigned short *p, int pl, Parameters* State);
int getMinPeriod(Parameters* State);





#endif //KMP_FOR_ARRAY_KMPM_H
