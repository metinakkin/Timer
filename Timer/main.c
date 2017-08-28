#include "stm32f4xx.h"                  // Device header

int main()
{
	//Counter register CNT
	//Prescaler register PSC
	//Auto-reload register ARR
	//Repetition counter register RCR
	//Capture/Compare registers CCR
	GPIO_InitTypeDef         GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
	
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 ;
	GPIO_InitStructure.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_100MHz;
	GPIO_Init(GPIOD,&GPIO_InitStructure);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	
	TIM_TimeBaseStructure.TIM_Prescaler          =8399; //+1den baslar isleme
	TIM_TimeBaseStructure.TIM_CounterMode        = TIM_CounterMode_Up;// Saymaya 0'dan baslar
	TIM_TimeBaseStructure.TIM_Period             =9999;
	TIM_TimeBaseStructure.TIM_ClockDivision      =TIM_CKD_DIV4; //Cloccku kaça bölmesi gerektigini söyler.
	TIM_TimeBaseStructure.TIM_RepetitionCounter  =0; //overflow underflow >update event>update interrupt
	TIM_TimeBaseInit(TIM2,&TIM_TimeBaseStructure);
	TIM_Cmd(TIM2,ENABLE);
	
	
	//Update_event=Tim_CLK/((PSC+1)*(ARR+1)(RCR+1))
	//Counter register CNT
	//Prescaler register PSC
	//Auto-reload register ARR
	//Repetition counter register RCR
	/*    
    TIM4 is connected to APB1 bus, which has on F407 device 42MHz clock                 
    But, timer has internal PLL, which double this frequency for timer, up to 84MHz     
    Remember: Not each timer is connected to APB1, there are also timers connected     
    on APB2, which works at 84MHz by default, and internal PLL increase                 
    this to up to 168MHz                                                             
    
    Set timer prescaller 
    Timer count frequency is set with 
    
    timer_tick_frequency = Timer_default_frequency / (prescaller_set + 1)    10k  
    
    In our case, we want a max frequency for timer, so we set prescaller to 0         
    And our timer will have tick frequency        
   
      (Period) * (Prescaler)
sn   = ----------------------
      (Clock Speed)
   
	 timer_tick_frequency = 84000000 / (0 + 1) = 84000000 
*/ 
/*
    Set timer period when it have reset
    First you have to know max value for timer
    In our case it is 16bit = 65535
    To get your frequency for PWM, equation is simple
    
    PWM_frequency = timer_tick_frequency / (TIM_Period + 1)
    
    If you know your PWM frequency you want to have timer period set correct
    
    TIM_Period = timer_tick_frequency / PWM_frequency - 1
    
    In our case, for 10Khz PWM_frequency, set Period to
    
    TIM_Period = 84000000 / 10000 - 1 = 8399
    
    If you get TIM_Period larger than max timer value (in our case 65535),
    you have to choose larger prescaler and slow down timer tick frequency
*/
 while(1)
 {
 if(TIM_GetCounter(TIM2)<2500)
 {
 
		GPIO_SetBits(GPIOD,GPIO_Pin_12 );
	  GPIO_ResetBits(GPIOD,GPIO_Pin_13 );
	  GPIO_ResetBits(GPIOD,GPIO_Pin_14 );
	  GPIO_ResetBits(GPIOD,GPIO_Pin_15 );
		
	}
 if((TIM_GetCounter(TIM2)>=2500) && (TIM_GetCounter(TIM2))<5000)
 {
 
		GPIO_ResetBits(GPIOD,GPIO_Pin_12 );
	  GPIO_SetBits(GPIOD,GPIO_Pin_13 );
	  GPIO_ResetBits(GPIOD,GPIO_Pin_14 );
	  GPIO_ResetBits(GPIOD,GPIO_Pin_15 );
		
	}
if((TIM_GetCounter(TIM2)>=5000) && (TIM_GetCounter(TIM2))<7500)
 {
 
	  GPIO_ResetBits(GPIOD,GPIO_Pin_12 );
	  GPIO_ResetBits(GPIOD,GPIO_Pin_13 );
	  GPIO_SetBits(GPIOD,GPIO_Pin_14 );
	  GPIO_ResetBits(GPIOD,GPIO_Pin_15 );
		
	}
 if((TIM_GetCounter(TIM2)>=7500) && (TIM_GetCounter(TIM2))<10000)
 {
 
		GPIO_ResetBits(GPIOD,GPIO_Pin_12 );
	  GPIO_ResetBits(GPIOD,GPIO_Pin_13 );
	  GPIO_ResetBits(GPIOD,GPIO_Pin_14 );
	  GPIO_SetBits(GPIOD,GPIO_Pin_15 );
		
	}
 
 }
 } 
	



	