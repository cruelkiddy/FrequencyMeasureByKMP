#ifndef __Parameters_H
#define	__Parameters_H	   

/*	  #define ADC_SampleTime_1Cycles5                    ((uint8_t)0x00)
 *		#define ADC_SampleTime_7Cycles5                    ((uint8_t)0x01)
 *		#define ADC_SampleTime_13Cycles5                   ((uint8_t)0x02)
 *		#define ADC_SampleTime_28Cycles5                   ((uint8_t)0x03)
 *		#define ADC_SampleTime_41Cycles5                   ((uint8_t)0x04)
 *		#define ADC_SampleTime_55Cycles5                   ((uint8_t)0x05)
 *		#define ADC_SampleTime_71Cycles5                   ((uint8_t)0x06)
 *		#define ADC_SampleTime_239Cycles5                  ((uint8_t)0x07)
 *		
*/ 		

typedef struct {
	unsigned short * Array;
	
	int * Next_Index;
	
	int Array_Size;

	unsigned char ADC_SampleTime;

	unsigned short Epsilon;
	
	int Recursion_Depth;
	
}Parameters;




#endif
