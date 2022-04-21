#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
char data;
int buzzer = 13;// le buzzer sur le pin 13 de Arduino
const int waterSens = A0; //definir la valeur du capteur de niveau d'eau.
int waterVal; //Pour stocker la valeur du niveau d'eau reçue par le capteur
int i=0;
void setup() {
  // put your setup code here, to run once:

lcd.begin(16,2);
pinMode(waterSens, INPUT);//Definir le capteur de niveau d'eau comme entree/input
pinMode(buzzer, OUTPUT);//Definir le buzzer en tant que sortie/output
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  waterVal = analogRead(waterSens); //on lit la valeur du lcd puis on la stock dans waterVal 

//String dataSend = String(waterVal);
//for (int i = 0; i < dataSend.length(); i++)
//  {
//    Serial.write(dataSend[i]);   // Push each char 1 by 1 on each loop pass
//  }

  if(waterVal <600)
  {
    Serial.write('0');
    delay(1000);

  }
  else
  {
    Serial.write('1');
    delay(1000);
  }
  

 data=Serial.read();
 
  if(data!='0')
  {

  lcd.setCursor(0,0);
  lcd.print(data);
  delay(1000);
    
  lcd.setCursor(0,0);
  lcd.print(waterVal);  
  lcd.setCursor(0,1);
  lcd.print("ml");
  delay(1000);

  }
  
  if(i==0 &&  waterVal <600)
  {
    tone(13 ,300,1000);
  }
  if(data=='0')
  {
    i=1;
    noTone(13);//on eteind le buzzer
    //Serial.write('0');
  }


} 
