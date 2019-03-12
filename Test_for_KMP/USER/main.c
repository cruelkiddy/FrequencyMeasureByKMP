#include "Init.h"

Parameters NState;
unsigned short Buffer[800] = {0};
int Next[400] = {0};

 int main(void){
	int i = 0;
	Init_All((Parameters*)&NState, Buffer, Next);
	
	while(1){
				//printf("\r\n %u \r\n\r\n",NState.Array[0]);
	}

	
}

