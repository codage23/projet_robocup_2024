/***********************************************************************************************
    projet robocup 2024
    module afficheur
    mjc fablab atelier codage 2023 2024
    https://tutorial45.com/mcp2515-arduino-project-can-arduino/
    https://github.com/sandeepmistry/arduino-CAN/tree/master
    https://github.com/Jorgen-VikingGod/LEDMatrix
    https://electroniqueamateur.blogspot.com/2021/03/ecrire-des-nombres-sur-une-matrice-de.html
    https://electroniqueamateur.blogspot.com/2020/05/matrice-de-leds-rgb-16-x-16-ws2812b-et.html
    https://www.instructables.com/16x16-RGB-LED-Panel-Arduino-Projects/
*************************************************************************************************/

//=============================
// inclusion des bibliothèques
//=============================
#include <CAN.h>        // pour la bibliothèque CAN
#include <SPI.h>        // bus spi
#include "variables.h"  // fichier variables
#include <FastLED.h>    // https://github.com/FastLED/FastLED
#include <LEDMatrix.h>  // https://github.com/Jorgen-VikingGod/LEDMatrix


CRGB leds[NUM_LEDS];  // creation d'un objet leds avec la bibliotheque fastled

//cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

//==================================
//  CAN reception suite interruption
//==================================
void onReceive(int packetSize) {
  while (CAN.available()) {
    caractere = (char)CAN.read();  // lecture du bus can dans la variable caractere
    id = CAN.packetId();           // id du message can  dans la variable id
  }
}

//====================
// allumage d'une led
//====================
void allumageLedBlue(int num) {
  leds[num] = CRGB::Blue;
  delay(1);
  FastLED.show();
}
void allumageLedRed(int num) {
  leds[num] = CRGB::Red;
  delay(1);
  FastLED.show();
}
void allumageLedYellow(int num) {
  leds[num] = CRGB::Yellow;
  delay(1);
  FastLED.show();
}
void allumageLedGreen(int num) {
  leds[num] = CRGB::Green;
  delay(1);
  FastLED.show();
}


//======
// setup
//======
void setup() {

  if (debug) {
    Serial.begin(9600);
    while (!Serial)
      ;
    Serial.println("Demarrage de l'afficheur");
  }

  FastLED.addLeds<CHIPSET, DATA_PIN_ARDUINO, COLOR_ORDER >(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness(10);                                                 // Number 0-255
  FastLED.clear(true);

  // effacement du tableau de leds
  for (int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB::Black;
    delay(1);
    FastLED.show();
  }
  /*
  // start the CAN bus at 125 kbps
  if (!CAN.begin(125E3)) {
    if (debug) {
      Serial.println("Starting CAN failed!");
    }
    while (1)
      ;
  }

  // register the receive callback - interruption des l'arrivee d'un message sur le bus can
  CAN.onReceive(onReceive);
  */
}

//======
// loop
//======
void loop() {

  allumageLedBlue(120);
  allumageLedBlue(90);
  allumageLedRed(136);
  allumageLedYellow(200);
  allumageLedGreen(100);
  allumageLedGreen(91);
  allumageLedGreen(68);

  // pour test de bon fonctionnement
  //caractere = 'Y';
  //id = 0x17;

  // reception de la couleur du master id 0x17 - couleur du cube
  if ((caractere == 'R' or caractere == 'G' or caractere == 'B' or caractere == 'Y') and id == 0x17) {
    if (caractere == 'R') {
      // affichage de la couleur rouge
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Red;
        delay(10);
        FastLED.show();
      }
    } else if (caractere == 'G') {
      // affichage de la couleur verte
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Green;
        delay(1);
        FastLED.show();
      }
    } else if (caractere == 'B') {
      // affichage de la couleur bleue
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Blue;
        delay(1);
        FastLED.show();
      }
    } else if (caractere == 'Y') {
      // affichage de la couleur jaune
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Yellow;
        FastLED.show();
        delay(1);
      }
    }

    if (debug) {
      Serial.print("caractere recu : couleur cube ");
      if (caractere == 'R') Serial.print("red : ");
      if (caractere == 'G') Serial.print("green : ");
      if (caractere == 'B') Serial.print("blue : ");
      if (caractere == 'Y') Serial.print("yellow : ");
      Serial.print(caractere);
      Serial.print("   id  ");
      Serial.println(id, HEX);
    }

    caractere = '0';  // effacement du caratere apres lecture
    id = 0x0;         // effacement de la variable id apres lecture
  }

  // pour test de bon fonctionnement
  //caractere = 'E';
  //id = 0x17;

  // effacement afficheur id 0x17
  if ((caractere == 'E') and id == 0x17) {
    // effacement du tableau de leds 256
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
      delay(1);
    }
    FastLED.show();
  }
}
