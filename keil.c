#include"c8051f340.h"
#define LED P4
#define NULL 0

//using the sbit directive to assign labels to pin numbers so that we dont have to remember afterwards
sbit ir_sensor1=P3^0;
sbit ir_sensor2=P3^1;
sbit LCD_RS=P1^5;
sbit LCD_RW=P1^6;
sbit LCD_EN=P1^7;

//Forward declaration of the functions
void Write_Command_Lcd(unsigned char Command);
void Write_Data_Lcd(unsigned char Character);
void DelayMs(unsigned int Ms);
int count=0;
int i;
void main (void){
  XBR1    = 0x40;// Enable Crossbar
  P1MDOUT = 0xE0;// P1.5,P1.6&P1.7 output pins
  P3MDIN = 0x03;
  P2MDOUT = 0xFF;//P2 output port
  P4MDOUT = 0xFF;

Write_Command_Lcd(0x01);   // Clear Display Screen
DelayMs(50);
Write_Command_Lcd(0x38);  // 2 Lines and 5x7 matix
DelayMs(50);
Write_Command_Lcd(0X0C);    // Display ON, Cursor OFF
DelayMs(50);
Write_Command_Lcd(0X80);  // Force cursor to beginning of 1st line
    DelayMs(50);
while(1)
{
if (ir_sensor1 == 0 && ir_sensor2 == 1 )
{
LED=0x00;
          }
     else if(ir_sensor1 == 1 && ir_sensor2 == 0)
         {
LED=0xFF;
          }
}
}
//Classic delay function that gives the delay of Ms milliseconds

void DelayMs(unsigned int Ms){
unsigned int n,i;
{
for (n=0; n < Ms; n++)
{
for (i=0; i < 65; i++);
}
}
}
//function to send the commands to the LCD
void Write_Command_Lcd(unsigned char Command)
{
    LCD_RS = 0;
    LCD_RW = 0;
    P2 = Command;
    LCD_EN = 1;          // EN pin high->low to be latched in lcd
    DelayMs(15);
    LCD_EN = 0;
}
//function for making the LCD understand that data is being given to it
void Write_Data_Lcd(unsigned char Character)
{
    LCD_RS = 1;
    LCD_RW = 0;
    P2 = Character;
    LCD_EN = 1;
    DelayMs(15);
    LCD_EN = 0;
}
