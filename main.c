/**
  Generated Main Source File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    This is the main file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  Description:
    This header file provides implementations for driver APIs for all modules selected in the GUI.
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.81.5
        Device            :  PIC16F18857
        Driver Version    :  2.00
 */

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
 */

#include "mcc_generated_files/mcc.h"
#include "lcd_lib.h"
#include <stdio.h>

/*  グローバル変数定義　*/
long Period;
double Freq, Hodo;

unsigned char Msg1[] = "Hodo Test"; //タイトル表示
unsigned char Msg2[] = "Freq=XXXXXXXX"; //Freq用に配列データ確保
unsigned char Msg3[] = "Hode=XXXXXXXX"; //Hodo用に配列データ確保

void main(void)
{
    // initialize the device
    SYSTEM_Initialize();

    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();



    /*  液晶表示器の電源　オフしオンする　*/
    LCDPWR_SetLow(); //LCD電源OFF
    __delay_ms(10);
    LCDPWR_SetHigh(); //LCD電源ON
    lcd_init();
    lcd_cmd(0x80); //1行目指定
    lcd_str(Msg1);
    __delay_ms(500);

    while (1) {
        SMT1_DataAcquisitionEnable(); //SMT計測開始
        while (PIR8bits.SMT1PRAIF == 0); //完了待ち
        PIR8bits.SMT1PRAIF = 0; //フラグクリア
        Period = SMT1_GetCapturedPeriod(); //理想周波数で有れば、125ms ÷ 0.03125us = 4000000
        Freq = (128 * 32000.0) / (Period * 0.03125); //PR2 = 31(32カウント)
        Hodo = (1.0 - 32.768 / Freq) * 86400.0;

        sprintf(Msg2, "Freq=%.4f KHz", Freq); //Msg2(文字配列)に書式設定でFreqを設定
        lcd_cmd(0x80); //2行目指定
        lcd_str(Msg2); //Freq出力
        sprintf(Msg3, "Hodo=%+.3f s/d", Hodo);
        lcd_cmd(0xC0); //2行目指定
        lcd_str(Msg3); //Hodo出力
        //__delay_ms(50);

        __delay_ms(1000);


    }
}

///*  低レベル入出力関数の上書き */
//void putch(char Data)
//{
//    while (!TX1STAbits.TRMT);
//    TX1REG = Data;
//}

/*
                         Main application
 */
//void main(void)
//{
//    // initialize the device
//    SYSTEM_Initialize();
//
//    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
//    // Use the following macros to:
//
//    // Enable the Global Interrupts
//    //INTERRUPT_GlobalInterruptEnable();
//
//    // Enable the Peripheral Interrupts
//    //INTERRUPT_PeripheralInterruptEnable();
//
//    // Disable the Global Interrupts
//    //INTERRUPT_GlobalInterruptDisable();
//
//    // Disable the Peripheral Interrupts
//    //INTERRUPT_PeripheralInterruptDisable();
//
//    while (1) {
//        // Add your application code
//        SMT1_DataAcquisitionEnable(); //SMT計測開始
//        while (PIR8bits.SMT1PRAIF == 0); //完了待ち
//        PIR8bits.SMT1PRAIF = 0; //フラグクリア
//        Period = SMT1_GetCapturedPeriod(); //理想周波数で有れば、125ms ÷ 0.03125us = 4000000
//        Freq = (128 * 32000.0) / (Period * 0.03125); //PR2 = 31(32カウント)
//        Hodo = (1.0 - 32.768 / Freq) * 86400.0;
//        printf("\r\nCount= %7lu Freq= %2.6f KHz Hodo= %2.3f s/d", Period, Freq, Hodo);
//        __delay_ms(1000);
//    }
//}
/**
 End of File
 */