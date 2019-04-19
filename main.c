#pragma config FOSC = HS        // Oscillator Selection bits (HS oscillator)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bit (BOR disabled)
#pragma config LVP = OFF        // Low-Voltage (Single-Supply) In-Circuit Serial Programming Enable bit (RB3 is digital I/O, HV on MCLR must be used for programming)
#pragma config CPD = OFF        // Data EEPROM Memory Code Protection bit (Data EEPROM code protection off)
#pragma config WRT = OFF        // Flash Program Memory Write Enable bits (Write protection off; all program memory may be written to by EECON control)
#pragma config CP = OFF 
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF 
#define uchar unsigned char
#define uint unsigned int
#define ulong unsigned long

#include <pic.h>
#include <xc.h>
#include "lcd.h"
#define _XTAL_FREQ 20000000	
#define ROW0 RB3
#define ROW1 RB2
#define ROW2 RB1
#define ROW3 RB0
#define COL0 RB4
#define COL1 RB5
#define COL2 RB6
#define COL3 RB7
#define Keypad_PORT  PORTB
#define Keypad_PORT_Direction  TRISB 
char Key='n';
char PS[4]={'1','4','8','7'};//mat khau mo cua
char ps[4]={' ',' ',' ',' '};
int i,j , count=0;
void InitKeypad(void);
char switch_press_scan(void);
char keypad_scanner(void) ;
void checkpass(void);

char switch_press_scan(void)                       // phim nhap tu nguoi dung
{
            char key = 'n';              // khong co phim nao duoc nhan
            while(key=='n')              // cho cho den khi co phim duoc nhan
            key = keypad_scanner();   // quet ma phim duoc nhan
            return key;                  //khi phim duoc nhan thi tra ve gia tri cua phim do
}
char keypad_scanner(void)  
{           
            COL0 = 0; COL1 = 1; COL2 = 1; COL3 = 1;//quet cot 0    
            if (ROW0 == 0) { __delay_ms(100); while (ROW0==0); return '*'; }
            if (ROW1 == 0) { __delay_ms(100); while (ROW1==0); return '7'; }
            if (ROW2 == 0) { __delay_ms(100); while (ROW2==0); return '4'; }
            if (ROW3 == 0) { __delay_ms(100); while (ROW3==0); return '1'; }
            
            COL0 = 1; COL1 = 0; COL2= 1; COL3 = 1; //quet cot1   
            if (ROW0 == 0) { __delay_ms(100); while (ROW0==0); return '0'; }
            if (ROW1== 0) { __delay_ms(100); while (ROW1==0); return '8'; }
            if (ROW2== 0) { __delay_ms(100); while (ROW2==0); return '5'; }
            if (ROW3== 0) { __delay_ms(100); while (ROW3==0); return '2'; }
            
            COL0 = 1; COL1 = 1; COL2 = 0; COL3 = 1;  //quet cot2  
            if (ROW0 == 0) { __delay_ms(100); while (ROW0==0); return '#'; }
            if (ROW1== 0) { __delay_ms(100); while (ROW1==0); return '9'; }
            if (ROW2== 0) { __delay_ms(100); while (ROW2==0); return '6'; }
            if (ROW3== 0) { __delay_ms(100); while (ROW3==0); return '3'; }
           
            COL0 = 1; COL1 = 1; COL2 = 1; COL3 = 0;    //quet cot 3
            if (ROW0 == 0) { __delay_ms(100); while (ROW0==0); return 'D'; }
            if (ROW1== 0) { __delay_ms(100); while (ROW1==0); return 'C'; }
            if (ROW2== 0) { __delay_ms(100); while (ROW2==0); return 'B'; }
            if (ROW3== 0) { __delay_ms(100); while (ROW3==0); return 'A'; }
            
    return 'n';                   
}
void InitKeypad(void)
{
            Keypad_PORT                = 0x00;       //PORT ket noi voi keypad
            Keypad_PORT_Direction = 0x0F;      // 4bit cuoi la input 4bir dau la output       
   
}
void checkpass()//kiem tra mat khau
{
    Key=switch_press_scan();//phim nhap tu nguoi dung duoc luu vao bien Key
    //char temp0,temp1,temp2,temp3;
    if(Key)
    {
        if(i==0)
        {
            ps[0]=Key;//phim thu nhat se duoc luu vao ps[0]
            //char *temp0=ps[0];
            //temp0='*';
            lcd_write_char(ps[0]);
            __delay_ms(100);
        }
        if(i==1)
        {
            ps[1]=Key;//phim thu hai se duoc luu vao ps[1]
            
            lcd_write_char(ps[1]);
            __delay_ms(100);
        }
        if(i==2)
        {
            ps[2]=Key;//phim thu ba se duoc luu vao ps[2]
            //char *temp2=ps[2];
            //temp2='*';
            lcd_write_char(ps[2]);
            __delay_ms(100);
        }
        if(i==3)
        {
            ps[3]=Key;//phim thu tu se duoc luu vao ps[3]
            //char *temp3=ps[3];
            //temp3='*';
            lcd_write_char(ps[3]);
            __delay_ms(100);
            count=1;
        }
        i++;
    }
    if(count==1)
    {
        if(ps[0]==PS[0] && ps[1]==PS[1] && ps[2]==PS[2] && ps[3]==PS[3])//kiem tra mat khau nhap vao co dung voi mat khau thiet lap hay khong
        {
           lcd_command(_LCD_CLEAR);
           lcd_write_string("CORRECT ^!^");
           __delay_ms(100);
           lcd_write_string("OPEN");
        }
        else
        {
            lcd_command(_LCD_CLEAR);
             __delay_ms(1000);
            lcd_write_string("INCORRECT @@");
            __delay_ms(1000);
            lcd_command(0xc0);
            lcd_write_string("TRY AGAIN");
            __delay_ms(1000);
            lcd_command(_LCD_CLEAR);
            __delay_ms(1000);
            lcd_write_string("ENTER PASSWORD");
            lcd_command(0xc0);
            i=0;
            count=0;
        }
    }
}
int main()
{
    ANSEL=ANSELH=0;
    nRBPU=0;
    WPUB0=1;
    TRISD=0;
    PORTD=0;
    InitKeypad();
    lcd_4bit_init();
    lcd_goto_row_col(0,0);
    lcd_write_string("ENTER PASSWORD");
    lcd_goto_row_col(1,0);
    while(1)
    {
        checkpass();
    }
  
    
    
}

