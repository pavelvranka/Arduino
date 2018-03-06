
/* 
  
PRACE S MOTORY
==============================================
Author: Pavel Vranka
Date: 2018-03-07

*/

// Nastaveni promennych
// ====================

// nastaveni servomotoru

#include <Servo.h>        // zahrnutí knihovny pro ovládání servo motoru

Servo servoLeft;          // každý motor má svou proměnnou typu Servo
Servo servoRight;         // každý motor má svou proměnnou typu Servo
int servoLeftPin = 9;     // pin motor servoLeft
int servoRightPin = 8;    // pin motor servoLeft

// nastaveni joystiku

int xPin = 1;              // pin pro osu x
int yPin = 2;              // pin pro osu y
int pushPin = 3;           // pin pro tlacitko
int xValue = 90;           // vychozi hodnota pro osu x
int yValue = 90;           // vychozi hodnota pro osu y
int pushState = 0;         // vychozi hodnota tlacitka

//nastaveni promenne pro vypis komunikace seriove linky

int serialSpeed = 9600;    // Rychlost komunikace po seriove lince
long oldTime = 0;          // nastaveni promenne oldTime
int serialPeriod = 1000;    // nastaveni periody vypisu na seriovy monitor v milisekundach


// Inicializace
// ============


void setup()
{
  Serial.begin(serialSpeed);  // nastaveni frekvence seriove linky pro vycitani na konzoli na zaklade promenne serialSpeed
  
  servoLeft.attach(servoLeftPin);   // pripojeni motoru servoLeft na pin defonovany promennou servoLeftPin
  servoRight.attach(servoRightPin); // pripojeni motoru servoRight na pin defonovany promennou servoRightPin
}

void loop() 
{ 
// Read joystick position

  xValue = analogRead(xPin);         // Read x
  yValue = analogRead(yPin);         // Read y
  xValue = map(xValue, 0, 1023, 0, 180); //převod z 0 až 1023 na 0 až 180
  yValue = map(yValue, 0, 1023, 180, 0); //převod z 0 až 1023 na 180 až 0 - obracena orientace otaceni

// Nastaveni polohy motoru

  servoLeft.write(xValue);             //nastavení polohy podle joystiku X osy
  servoRight.write(yValue);             //nastavení polohy podle joystiku X osy
  delay(15);                 //chvilka čekání než se motor natočí

// Vypis na seriovy monitor

  if ((millis()-oldTime) > serialPeriod){
    Serial.print("X: ");
    Serial.print(xValue);
    Serial.print(" | Y: ");
    Serial.print(yValue);
    Serial.print(" | Button: ");
    Serial.println(pushState);
    oldTime = millis();
    }

}
