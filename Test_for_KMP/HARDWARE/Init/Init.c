#include "Init.h"

void Init_All(Parameters * State, unsigned short* Array, int* Next){//LCD Î´³õÊ¼»¯
	int i = 0;
	State->Epsilon = 50;
	State->Array_Size = 800;
	State->ADC_SampleTime = ((uint8_t)0x00);
	State->Array = Array;
	State->Next_Index = Next;
	State->Recursion_Depth = 0;
	delay_init();  	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(115200);
	//LCD_Init();
	Adc_Init();
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
	MYDMA_Config(DMA1_Channel1,(u32)State->Array,800);//(u32)State->Array
	MYDMA_Enable(DMA1_Channel1);
}
