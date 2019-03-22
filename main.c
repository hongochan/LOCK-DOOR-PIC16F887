/******************************************************************************
*		Project	:	EX6 - KEYPAD LAB - LCD 4BIT
*		MCU		:	PIC16F887
*		Xtal	:	4Mhz
*		Complier:	Hitech PIC C V9.83
*		
******************************************************************************/
#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF 
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

#include <pic.h>
#include "lcd.h"
#include <xc.h>
#define _XTAL_FREQ 20000000						

#define KEY_PORT		PORTC       //ket noi BAN PHIM 4x4
#define row_0  RC0
#define row_1  RC1
#define row_2  RC2
#define row_3  RC3
#define col_0   RC4
#define col_1   RC5
#define col_2   RC6
#define col_3   RC7

int i,j,count=0;

            char key[4][4]={ '1', '2', '3', 'A',
			     '4', '5', '6', 'B',
			     '7', '8', '9', 'C',
			     '*', '0', '#', 'D'};
	
        char row_code[4]={0b00001110,0b00001101,0b00001011,0b00000111};

   

//-------------------------------------------------------//
// KHAI BAO BIEN TOAN CUC						     	 
        char STR[4]={'2','0','1','9'};
        char str[4]={' ',' ',' ',' '};
        char key_code='n';    
        


//-------------------------------------------------------//
// INIT PORT FUNCTION							     	 

void Port_Init()
{
	
    TRISD=0;
    TRISC=0xf0; //4 bit cao PORTC = col : la ngo vao
    PORTC=0xff; //PORTC = 1111 1111 = HANG COT
	PORTD=0;
	
}
//------------------------------------------------------//
char scan_key()
{
	char row=0;

	
	for(row=0;row<4;row++)
	{
		KEY_PORT = row_code[row];      //xuat ma chon Hang = PORTC (row0 - xxxx1110)
		
		if(col_0==0)
            {  __delay_ms(100);
              while(col_0==0); 
              return key[row][0]; 
           };
		if(col_1==0)
           {
            __delay_ms(100);
            while(col_1==0); 
            return key[row][1];
           };
		if(col_2==0)
           {
            __delay_ms(100);
            while(col_2==0);
            return key[row][2];
            };
		if(col_3==0)
           { 
            __delay_ms(100);
            while(col_3==0);
            return key[row][3];
            };
	}
        return '\0';
}
				
void main()
{
    //ANSEL=ANSELH=0;
    Port_Init();
    lcd_4bit_init();
    PORTD=0X00;
    scan_key();
    char *temp0,*temp1,*temp2,*temp3;
    lcd_4bit_init();
	lcd_command(0x80);     
    lcd_write_string("ENTER PASSWORD");
   
    lcd_command(0xc0);
    //__delay_ms(1000);
    while(1)
    {
             key_code=scan_key() ;
             if(key_code)
                {
                    if(i==0)
                        {
                            str[0]=key_code;
                            char *temp0=str[0];
                            temp0='*';
                            lcd_write_char(temp0);
                            __delay_ms(100);
                        }
                    if(i==1)
                        {
                            str[1]=key_code;
                            char *temp1=str[1];
                            temp1='*';
                            lcd_write_char(temp1);
                            __delay_ms(100);
                        }
                    if(i==2)
                        {
                            str[2]=key_code;
                            char *temp2=str[2];
                            temp2='*';
                            lcd_write_char(temp2);
                            __delay_ms(100);
                        }
                    if(i==3)
                        {
                            str[3]=key_code;
                            char *temp3=str[3];
                            temp3='*';
                            lcd_write_char(temp3);
                            __delay_ms(100);
                            count=1;
                        }
                    i+=1;
                    

                }
                    if(count==1)
                        {
                            if(str[0]==STR[0]&& str[1]==STR[1]&& str[2]==STR[2]&& str[3]==STR[3])
                               {
                                   lcd_command(_LCD_CLEAR);
                                   lcd_write_string("CORRECT ^O^");
                                   lcd_command(0XC0);
                                   lcd_write_string("LOCK DOOR OPEN");
                                   i=0;
                                   count=0;
                                }
                            else
                               {
                                   lcd_command(_LCD_CLEAR);
                                   lcd_write_string("INCORRECT ~!~");
                                   __delay_ms(200);
                                   lcd_command(0xc0);
                                   lcd_write_string("TRY AGAIN ^-^");
                                   __delay_ms(200);
                                   lcd_command(_LCD_CLEAR);
                                  lcd_write_string("ENTER PASSWORD");
                                  __delay_ms(200);
                                  lcd_command(0xc0);
                                  
                                  i=0;
                                  count=0;
                                }
                       }
            }
                        //key_code=scan_key();
                        /*switch(key_code)
                        {
                            case '#':
                                lcd_command(_LCD_CLEAR);
                                lcd_write_string("CLOSED!!");
                                __delay_ms(300);
                                lcd_write_string("ENTER PASSWORD");
                                lcd_command(0xc0);
                                i=0;
                                break;
                        }*/
   

}
                       

                        
  


