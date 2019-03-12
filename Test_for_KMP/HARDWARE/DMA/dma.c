#include "dma.h"
#include "lcd.h"
#include "led.h"
#include "key.h"
#include "KMPM.h"
#include "usart.h"

u16 DMA1_MEM_LEN;//����DMAÿ�����ݴ��͵ĳ��� 	    

void MYDMA_Config(DMA_Channel_TypeDef* DMA_CHx,u32 cmar,u16 cndtr)
{
	NVIC_InitTypeDef NVIC_InitStructure;     /* Configure one bit for preemption priority */
	DMA_InitTypeDef DMA_InitStructure;
 	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//ʹ��DMA����
	
  DMA_DeInit(DMA_CHx);   //��DMA��ͨ��1�Ĵ�������Ϊȱʡֵ
	
	DMA1_MEM_LEN=cndtr;
	DMA_InitStructure.DMA_PeripheralBaseAddr = (u32)&ADC1->DR;//0x40012400+0x4c;//�������ַ  //(u32)&ADC1->DR;
	DMA_InitStructure.DMA_MemoryBaseAddr = cmar;  //DMA�ڴ����ַ
	DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralSRC;  //���ݴ��䷽�����赽�ڴ�
	DMA_InitStructure.DMA_BufferSize = cndtr;  //DMAͨ����DMA����Ĵ�С
	DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;  //�����ַ�Ĵ�������
	DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Enable;  //�ڴ��ַ�Ĵ�������
	DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;  //�������ݿ��Ϊ16λ
	DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord; //�ڴ����ݿ��Ϊ16λ֮ǰд���������ݴ�СΪ�����ˣ����ߴ�С��Ȼ��ͬ
	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);     
  NVIC_InitStructure.NVIC_IRQChannel = DMA1_Channel1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;       
  NVIC_Init(&NVIC_InitStructure);
	
	DMA_ITConfig(DMA1_Channel1, DMA1_IT_TC1, ENABLE);
	
	DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
	DMA_InitStructure.DMA_Priority = DMA_Priority_Medium; //DMAͨ�� xӵ�������ȼ� 
	DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;  //DMAͨ��xû������Ϊ�ڴ浽�ڴ洫��
	DMA_Init(DMA_CHx, &DMA_InitStructure);  //
	
} 
//����һ��DMA����
void MYDMA_Enable(DMA_Channel_TypeDef*DMA_CHx)
{ 
	DMA_Cmd(DMA_CHx, DISABLE );  //�ر�USART1 TX DMA1 ��ָʾ��ͨ��      
 	DMA_SetCurrDataCounter(DMA_CHx,DMA1_MEM_LEN);//DMAͨ����DMA����Ĵ�С
 	DMA_Cmd(DMA_CHx, ENABLE);  //ʹ��USART1 TX DMA1 ��ָʾ��ͨ�� 
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

