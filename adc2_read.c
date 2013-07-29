/*

  * Based on MikroElectronika ADC on LCD example
 
  * Uses self written ADC_Read function

*/

unsigned char ch;
unsigned int adc_rd;
char *text;
long tlong;

sbit LCD_RS at RB4_bit;
sbit LCD_EN at RB5_bit;
sbit LCD_D4 at RB0_bit;
sbit LCD_D5 at RB1_bit;
sbit LCD_D6 at RB2_bit;
sbit LCD_D7 at RB3_bit;

sbit LCD_RS_Direction at TRISB4_bit;
sbit LCD_EN_Direction at TRISB5_bit;
sbit LCD_D4_Direction at TRISB0_bit;
sbit LCD_D5_Direction at TRISB1_bit;
sbit LCD_D6_Direction at TRISB2_bit;
sbit LCD_D7_Direction at TRISB3_bit;

unsigned adc_read2(char channel)
{

   switch (channel) {
    case 0: {
        ADCON0.CHS0 = 0;
        ADCON0.CHS1 = 0;
        ADCON0.CHS2 = 0;
        ADCON0.CHS3 = 0;
    }
    case 1: {
        ADCON0.CHS0 = 1;
        ADCON0.CHS1 = 0;
        ADCON0.CHS2 = 0;
        ADCON0.CHS3 = 0;
    }
    case 2: {
        ADCON0.CHS0 = 0;
        ADCON0.CHS1 = 1;
        ADCON0.CHS2 = 0;
        ADCON0.CHS3 = 0;
    }
    case 3: {
        ADCON0.CHS0 = 1;
        ADCON0.CHS1 = 1;
        ADCON0.CHS2 = 0;
        ADCON0.CHS3 = 0;
    }
    case 4: {
        ADCON0.CHS0 = 0;
        ADCON0.CHS1 = 0;
        ADCON0.CHS2 = 1;
        ADCON0.CHS3 = 0;
    }

   
   }



   ADCON0.GO_DONE = 1; // start conversion
   while (ADCON0.GO_DONE); // wait for conversion
   return (ADRESH << 8) + ADRESL; // return value
}


void main() {
  INTCON = 0;       // disable all interrupts
  ANSEL  = 0x04;    // Configure AN2 pin as analog input
  TRISA  = 0x04;
  ANSELH = 0;       // Configure other AN pins as digital I/O

  ADCON1.VCFG0 = 0; // set internal
  ADCON1.VCFG1 = 0;
  ADCON0.ADCS0 = 1; // use Vdd as reference
  ADCON0.ADCS1 = 0; // use Vcc as reference
  ADCON1.ADFM = 1;  // result is right Justified
  ADCON0.ADON = 1;  // enable A/D converter


 
  Lcd_Init();
  LCD_Cmd(_LCD_CURSOR_OFF);     // send command to LCD (cursor off)
  LCD_Cmd(_LCD_CLEAR);                      // send command  to LCD (clear LCD)

  text = "mikroElektronika";    // assign text to string
  LCD_Out(1,1,text);            // print string a on LCD, 1st row, 1st column
  text = "LCD example";         // assign text to string
  LCD_Out(2,1,text);            // print string a on LCD, 2nd row, 1st column

  ADCON1     = 0x82;            // configure VDD as Vref, and analog channels
  TRISA      = 0xFF;            // designate PORTA as input
  Delay_ms(2000);
  text  = "voltage:";           // assign text to string
  while (1) {
    // let's use our open source function
    adc_rd  = ADC_read2(2);     // get ADC value from 2nd channel
    LCD_Out(2,1,text);          // print string a on LCD, 2nd row, 1st column

    tlong = (long)adc_rd * 5000;   // covert adc reading to milivolts
    tlong = tlong / 1023;          // 0..1023 -> 0-5000mV

    ch     = tlong / 1000;        // extract volts digit
    LCD_Chr(2,9,48+ch);           // write ASCII digit at 2nd row, 9th column
    LCD_Chr_CP('.');

    ch    = (tlong / 100) % 10;   // extract 0.1 volts digit
    LCD_Chr_CP(48+ch);            // write ASCII digit at cursor point

    ch    = (tlong / 10) % 10;   // extract 0.01 volts digit
    LCD_Chr_CP(48+ch);           // write ASCII digit at cursor point

    ch    = tlong % 10;       // extract 0.001 volts digit
    LCD_Chr_CP(48+ch);        // write ASCII digit at cursor point
    LCD_Chr_CP('V');

    Delay_ms(1);
  }
}
