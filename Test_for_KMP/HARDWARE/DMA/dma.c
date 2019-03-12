#include "dma.h"
#include "lcd.h"
#include "led.h"
#include "key.h"
#include "KMPM.h"
#include "usart.h"

u16 DMA1_MEM_LEN;//保存DMA每次数据传送的长度 	    

void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cmar,u16 cndtr)
{
	NVIC_InitTypeDef NVIC_InitStructure;     /* Configure one bit for preemption priority */
	DMA_InitTypeDef DMA_InitStructure;
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//使能DMA传输
	
  DMA_DeInit(DMA_CHx);   //将DMA的通道1寄存器重设为缺省值
	
	DMA1_MEM_LEN=cndtr;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;//0x40012400+0x4c;//外设基地址  //(u32)&ADC1->DR;
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  //DMA内存基地址
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //数据传输方向外设到内存
	DMA_InitStructure.DMA_BufferSize = cndtr;  //DMA通道的DMA缓存的大小
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //外设地址寄存器不变
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //内存地址寄存器递增
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //外设数据宽度为16位
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //内存数据宽度为16位之前写成外设数据大小为半字了，两者大小显然不同
	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);     
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;       
  NVIC_Init(&NVIC_InitStructure);
	
	DMA_ITConfig(DMA1_Channel1, DMA1_IT_TC1, ENABLE);
	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMA通道 x拥有中优先级 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMA通道x没有设置为内存到内存传输
	DMA_Init(DMA_CHx, &DMA_InitStructure);  //
	
} 
//开启一次DMA传输
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{ 
	DMA_Cmd(DMA_CHx, DISABLE );  //关闭USART1 TX DMA1 所指示的通道      
 	DMA_SetCurrDataCounter(DMA_CHx,DMA1_MEM_LEN);//DMA通道的DMA缓存的大小
 	DMA_Cmd(DMA_CHx, ENABLE);  //使能USART1 TX DMA1 所指示的通道 
}

void DMA1_Channel1_IRQHandler(void)
{		int i = 0;
		if(DMA_GetITStatus(DMA1_IT_TC1)){	
				
				DMA_Cmd(DMA1_Channel1, DISABLE);//Transfer finished , shut down dma
				
				//printf("\r\n???\r\n\r\n");
				//printf("\r\n %d \r\n\r\n",hasPeriod(&State));
				
				printf("\r\n %d \r\n\r\n",getMinPeriod(&NState));
				
				
//				for(;i<800;++i)
//			printf("\r\n%d:%u\r\n\r\n",i,NState.Array[i]);
				
				
				MYDMA_Config(DMA1_Channel1,(u32)NState.Array,NState.Array_Size);
				MYDMA_Enable(DMA1_Channel1);
    }
		DMA_ClearITPendingBit(DMA1_IT_GL1);
}

