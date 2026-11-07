/***********************************************************************************************************************
* DISCLAIMER
* This software is supplied by Renesas Electronics Corporation and is only intended for use with Renesas products.
* No other uses are authorized. This software is owned by Renesas Electronics Corporation and is protected under all
* applicable laws, including copyright laws. 
* THIS SOFTWARE IS PROVIDED "AS IS" AND RENESAS MAKES NO WARRANTIES REGARDING THIS SOFTWARE, WHETHER EXPRESS, IMPLIED
* OR STATUTORY, INCLUDING BUT NOT LIMITED TO WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NON-INFRINGEMENT.  ALL SUCH WARRANTIES ARE EXPRESSLY DISCLAIMED.TO THE MAXIMUM EXTENT PERMITTED NOT PROHIBITED BY
* LAW, NEITHER RENESAS ELECTRONICS CORPORATION NOR ANY OF ITS AFFILIATED COMPANIES SHALL BE LIABLE FOR ANY DIRECT,
* INDIRECT, SPECIAL, INCIDENTAL OR CONSEQUENTIAL DAMAGES FOR ANY REASON RELATED TO THIS SOFTWARE, EVEN IF RENESAS OR
* ITS AFFILIATES HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
* Renesas reserves the right, without notice, to make changes to this software and to discontinue the availability 
* of this software. By using this software, you agree to the additional terms and conditions found by accessing the 
* following link:
* http://www.renesas.com/disclaimer
*
* Copyright (C) 2011, 2020 Renesas Electronics Corporation. All rights reserved.
***********************************************************************************************************************/

/***********************************************************************************************************************
* File Name    : r_main.c
* Version      : CodeGenerator for RL78/G12 V2.04.05.01 [25 Nov 2020]
* Device(s)    : R5F102AA
* Tool-Chain   : CA78K0R
* Description  : This file implements main function.
* Creation Date: 28-11-2021
***********************************************************************************************************************/

/***********************************************************************************************************************
Pragma directive
***********************************************************************************************************************/
/* Start user code for pragma. Do not edit comment generated here */
/* End user code. Do not edit comment generated here */

/***********************************************************************************************************************
Includes
***********************************************************************************************************************/
#include "r_cg_macrodriver.h"
#include "r_cg_cgc.h"
#include "r_cg_port.h"
#include "r_cg_adc.h"
#include "r_cg_timer.h"
/* Start user code for include. Do not edit comment generated here */
int *buffer;
/* End user code. Do not edit comment generated here */
#include "r_cg_userdefine.h"

/***********************************************************************************************************************
Global variables and functions
***********************************************************************************************************************/
/* Start user code for global. Do not edit comment generated here */
int i;
unsigned int ADC16,ADC17,ADC1,flag=0,AS=0,AB=0,SlAv=50,BtAv=300,SLA=0,BTA=0,AO=0,OAV=0,OA=0,count1=0,BO=0;
unsigned long int count2=0;
void LEDBL();
void DELAY();
void LEDSC();
void ADC_read();
void mindelay();
void stop_loop(); 
/* End user code. Do not edit comment generated here */
void R_MAIN_UserInit(void);

/***********************************************************************************************************************
* Function Name: main
* Description  : This function implements main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void main(void)
{
    R_MAIN_UserInit();
    /* Start user code. Do not edit comment generated here */
    R_ADC_Create(); 
    R_ADC_Set_OperationOn();
    R_ADC_Start();
    R_TAU0_Channel0_Start();
    P3.1=1;
    P3.1=1;
    P2.3=1;
    P3.0=1;   
    BO = 0;
    while (1U)
    {   
	  if(BtAv == 0 && SlAv == 0)
	  {
		  
	  }
	else if(SlAv <= 500 && BtAv >= 260 && BO == 0)
	{
		count1++;
		if(count1 >= 8000 && count2 <= 158400)//276925
			{
				count2++;
				count1 = 0;
			}
			
		if(count2 <= 158400)
		{
		P2.3=1;
		P3.0=1;
		P3.1=1;
        	for(i=0;i<=2;i++);
        	P3.1=0;
        	for(i=0;i<=16;i++);
		P3.1=1;
		}
		else
		{
		P3.1=1;
		P2.3=1;
		count1 = 0;
		}
	}
	
	
	
	/*Charging Loop*/
	else if(SlAv >= 500 && BtAv >= 260 && BtAv <= 335)
	{
		P2.3=0;
		P3.0=1;
		P3.1=1;
		P6.0=1;
		//LEDSC();
		count2 = 0;
		BO = 0;
		mindelay();
	}
	
	
	/*Battery Low Loop*/
	
	
	else if(SlAv <= 500 && BtAv <= 260)/*Value Decreased from 265 to 260 because of low battery*/
	{
	  stop_loop(); /*New function added for stopping*/
        }
	
	
	/*Battery Overcharged Loop*/
	else if(SlAv >= 500 && BtAv >= 335)//355
	{
		P2.3=0;
   	        P3.0=0;
		P3.1=1;
		P6.0=0;
		//mindelay();
	}
    }
    /* End user code. Do not edit comment generated here */
}

/***********************************************************************************************************************
* Function Name: R_MAIN_UserInit
* Description  : This function adds user code before implementing main function.
* Arguments    : None
* Return Value : None
***********************************************************************************************************************/
void R_MAIN_UserInit(void)
{
    /* Start user code. Do not edit comment generated here */
    EI();
    /* End user code. Do not edit comment generated here */
}

/* Start user code for adding. Do not edit comment generated here */
void LEDBL()
{
	if(AS == 0)
	{
		P2.3=~P2.3;
	}
}
void LEDSC()
{
	if(AS == 0)
	{
		P3.0=~P3.0;
	}
}
void mindelay()
{
	int a,b;
	for(a=0; a<32000; a++)
	{
		for(b=0; b<8000; b++);
	}
}

void ADC_read()
{
	// ADS = _02_AD_INPUT_CHANNEL_2 ;
   	// R_ADC_Get_Result(&ADC1);
}

void stop_loop()
{
	        P2.3=1;
		P3.0=0;
		P3.1=1;
		//LEDBL();
		BO = 1;
}

/* End user code. Do not edit comment generated here */
