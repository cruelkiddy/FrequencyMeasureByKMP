/*
 *  调整Knuth,Morris,Pratt模式匹配算法，在一个数组(Raw_Data)内找到“子数组”的“最大的重复相似模式”
 *  用最大重复模式长度近似表达周期长度
 *
 *
 *  Todo:调整相等的误差容限。√
 *  Todo:将int 换成合适的类型以便用于STM32 √
 *  Todo:从数组一半的长度开始尝试寻找模式长度，递减到Pattern_Min_Length,若还未找到，停止并返回-1，否则返回模式长度 √
 *  Todo: int getPatternSize()  and testing for the rest √
 *	Todo: debug getPeriod函数，找到最小正周期
 *
 *
 *  @para pl: pattern length
 *  @para sl : "string" length , the size of array to be compared, in this case is the front-sub_array of Raw_Data
 *  @para p : pointer point to pattern
 *  @para Raw : pointer point to Raw_Data Array
 *  @para depth : recurrence depth 
 *
 * 	Created by DongxuGuo on 3/5/2019.
 *	Beta Finished on 3/7/2019. Tested no algorithm mistake
 *  Modified using structure, getMinPeriod Finished on 3/10/2019.
 */



#include "KMPM.h"


int equal(unsigned short a, unsigned short b, unsigned short eps){
    if(a - b < eps && a - b > -eps)     return 1;
    else                                return 0;
}

void getNext(unsigned short *p, int pl, Parameters* State) {
    int i = 0, j = -1;
		State->Next_Index[0] = -1;

    while (i < pl)
    {
        if (j == -1 || p[i] == p[j]) { ++i;++j;State->Next_Index[i] = j; }
        else    j = State->Next_Index[j];
    }
}


int pmatch(Parameters* State,int sl, int pl){
    int i = 0, j = 0;
    getNext(State->Array + sl, pl, State); //Generate the failure function
    while( i < sl && j < pl){
        if (equal(State->Array[i], State->Array[j + sl],State->Epsilon))   {i++;j++;}
        else  if(j == 0)    i++;
        else  j = State->Next_Index[j];
    }
    return ((j == pl) ? (i - pl) : -1);
}


int hasPeriod(Parameters* State){ 
    int index_found;
    int pattern_length = State->Array_Size/(2<<State->Recursion_Depth);
    while(pattern_length > State->Array_Size/(4<<State->Recursion_Depth)) { //Value?
        if ((index_found = pmatch(State, State->Array_Size/(1<<State->Recursion_Depth) - pattern_length, pattern_length)) != -1){
					State->Recursion_Depth ++;
					return  State->Array_Size/(1<<State->Recursion_Depth) - pattern_length - index_found;
				}
        pattern_length --;
    }
    return -1;
}

int getMinPeriod(Parameters* State){ //-1 Period not found
		int minPeriod = -1;
		int tmp;
		while(1){
			tmp = hasPeriod(State);
			if(tmp == -1)				{State->Recursion_Depth = 0;return minPeriod;}
			minPeriod = tmp;
		}
}

