#include <LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

class Buton;
class Led;
class Potentiometer;

int Stare_Irigatii = 0; //0 - Irigatiile sunt oprite / 1 - Irigatiile sunt pornite


Led *Led_Verde;
Led *Led_Rosu;
Led *Led_Galben;
Potentiometer *Potentiometru;

class Led{
 private:
   uint8_t pin;
 public:
  Led(uint8_t set_pin)
  {
    pin = set_pin;
    pinMode(pin, OUTPUT);
  }
  void ON()
  {
    digitalWrite(pin, HIGH);
  }
  void OFF()
  {
   digitalWrite(pin, LOW); 
  }
};

class Potentiometer{
private:
  uint8_t pin;
  int value;
public:
  Potentiometer(uint8_t set_pin)
  {
    pin = set_pin;
    pinMode(pin,INPUT);
    value = 0;
  }
  int procente()
  {
  value = analogRead(pin);
  return map(value,0,1023,0,100);
  }
};

void Citire_Umiditate()
{
  int p = Potentiometru->procente();
  lcd.clear();
  lcd.home();
  lcd.print("Umiditate: ");
  lcd.print(p);
  lcd.print("%");
  if(p < 50 && Stare_Irigatii == 0)
  {
    Stare_Irigatii = 1;
    lcd.setCursor(0,1);
    lcd.print("Pornire irigatii");
    delay(1000);
    lcd.clear();
    lcd.home();
    lcd.print("Umiditate: ");
    lcd.print(p);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Irigatii pornite");
    Led_Verde->ON();
    Led_Rosu->OFF();
  }
  else if(p < 50 && Stare_Irigatii == 1)
  {
    lcd.setCursor(0,1);
    lcd.print("Irigatii pornite");
    Led_Verde->ON();
    Led_Rosu->OFF();
  }
  if(p > 50 && Stare_Irigatii == 1)
  {
    Stare_Irigatii = 0;
    lcd.setCursor(0,1);
    lcd.print("Oprire irigatii");
    delay(1000);
    lcd.clear();
    lcd.home();
    lcd.print("Umiditate: ");
    lcd.print(p);
    lcd.print("%");
    lcd.setCursor(0,1);
    lcd.print("Irigatii oprite");
    Led_Verde->OFF();
    Led_Rosu->ON();
  }
  else if(p > 50 && Stare_Irigatii == 0)
  {
    lcd.setCursor(0,1);
    lcd.print("Irigatii oprite");
    Led_Verde->OFF();
    Led_Rosu->ON();
  }
}


void setup() {

  Led_Rosu = new Led(10);
  Led_Galben = new Led(8);
  Led_Verde = new Led(9);
  Potentiometru = new Potentiometer(A0);
  lcd.begin(16,2);
  lcd.clear();
  lcd.home();
}
void loop() {
 Citire_Umiditate();
 delay(1000);
}
