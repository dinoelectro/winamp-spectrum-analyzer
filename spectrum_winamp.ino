#include <LiquidCrystal.h> 
//lcd pins        RS E  D4 D5 D6 D7
LiquidCrystal lcd(8, 9, 4, 5, 6, 7);
 
byte custChars[8][8] = {
//LEVEL    0        1       2       3       4       5       6       7
    { B00000, B00000, B00000, B00000, B00000, B00000, B00000, B11111 },
    { B00000, B00000, B00000, B00000, B00000, B00000, B11111, B11111 },
    { B00000, B00000, B00000, B00000, B00000, B11111, B11111, B11111 },
    { B00000, B00000, B00000, B00000, B11111, B11111, B11111, B11111 },
    { B00000, B00000, B00000, B11111, B11111, B11111, B11111, B11111 },
    { B00000, B00000, B11111, B11111, B11111, B11111, B11111, B11111 },
    { B00000, B11111, B11111, B11111, B11111, B11111, B11111, B11111 },
    { B11111, B11111, B11111, B11111, B11111, B11111, B11111, B11111 }
};

byte serial_getch() {
  while (Serial.available() == 0);
  return Serial.read();
}
 
void setup()
{
  Serial.begin(19200);
  lcd.begin(16, 2);
  lcd.clear();
  for (int i = 0; i<8; i++)
  {
    lcd.createChar(i, custChars[i]);
    delay(500);
  }
}

void loop()
{
  byte rxbyte = serial_getch();//inicio de trama puede ser i, j, k
  if (rxbyte == 'j')
  {
    byte coulumn = serial_getch()-'0';//indica columnas     0, 1, 2,... ,15
    byte row    = serial_getch()-'0';//indica filas        0, 1
    byte level  = serial_getch()-'a';//indica la amplitud  0, 1, 2,... ,7  
    lcd.setCursor(coulumn , row);
    lcd.write((uint8_t)(level));
  }
  else if (rxbyte == 'i')
  {
    byte coulumn = serial_getch()-'0';//indica columnas 0, 1, 2,... ,15
    byte row = serial_getch()-'0';    //indica filas    0, 1
    lcd.setCursor(coulumn , row);
    lcd.write((char)serial_getch());  //escribe un espacio, sirve para borrar columnas
  }
  else if (rxbyte == 'k')
  {
    lcd.clear();//borra toda la pantalla
  }
  }
