#ifndef __DMA_H
#define	__DMA_H	   
#include "sys.h"
#include "Parameters.h"

//My configuration :


extern Parameters NState; 








//End of configuration

void MYDMA_Config(DMA_Channel_TypeDef*DMA_CHx,u32 cmar,u16 cndtr);//≈‰÷√DMA1_CHx

void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx);// πƒ‹DMA1_CHx
		   
void DMA1_Channel1_IRQHandler(void);

#endif




