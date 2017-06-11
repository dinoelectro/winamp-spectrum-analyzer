#include <SPI.h>        
#include <DMD.h>        
#include <TimerOne.h>   
#include "SystemFont5x7.h"
#include "Arial_black_16.h"
#define DISPLAYS_ACROSS 3
#define DISPLAYS_DOWN 1
byte count=0;
DMD dmd(DISPLAYS_ACROSS, DISPLAYS_DOWN);

void ScanDMD()
{ 
  dmd.scanDisplayBySPI();
}

byte serial_getch() {
  while (Serial.available() == 0);
  return Serial.read();
}

void setup(void)
{
  Serial.begin(19200);
  Timer1.initialize( 3000 );           
  Timer1.attachInterrupt( ScanDMD );   
  dmd.clearScreen( true ); 
  dmd.selectFont(Arial_Black_16);
}

void loop(void)
{

 
 byte rxbyte = serial_getch();
  if (rxbyte == 'j')
  {
    byte r1 = serial_getch()-48;// valor maximo 16
    byte r2 = serial_getch()-48;// valor maximo 2 (no lo utilizo)
    byte data = serial_getch()-97;// valor maximo 8
    drawLevel(r1,data);
  }
  else if (rxbyte == 'i')
  {
    byte r1 = serial_getch()-48;
    byte r2 = serial_getch()-48;
    dmd.drawChar(  r1,  r2, serial_getch(), GRAPHICS_NORMAL );
  }
  else if (rxbyte == 'k')
  {
  dmd.clearScreen( true ); 
  }  
 
}

void drawLevel(byte r1,byte data){
    byte wide=5;
    r1 = r1 + wide*r1;
 
      for (int i=0; i<=data; i++){
      dmd.drawLine(  r1, 15-2*i, r1+4, 15-2*i, GRAPHICS_NORMAL );
      }
      
      for (int i=data+1; i<=15; i++){
      dmd.drawLine(  r1, 15-2*i, r1+4, 15-2*i, GRAPHICS_INVERSE );
      }
     }

 
