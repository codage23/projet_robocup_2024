/***************************************************************
    projet robocup 2024
    module afficheur
    mjc fablab atelier codage 2023 2024
    https://tutorial45.com/mcp2515-arduino-project-can-arduino/
    https://github.com/sandeepmistry/arduino-CAN/tree/master
***************************************************************/

//=============================
// inclusion des bibliothèques
//=============================
#include <CAN.h>        // pour la bibliothèque CAN
#include <SPI.h>        // bus spi
#include "variables.h"  // fichier variables
#include <FastLED.h>    //https://github.com/FastLED/FastLED
#include <LEDMatrix.h>  //https://github.com/Jorgen-VikingGod/LEDMatrix


CRGB leds[NUM_LEDS];  // creation d'un objet leds avec la bibliotheque fastled

//==================================
//  CAN reception suite interruption
//==================================
void onReceive(int packetSize) {
  while (CAN.available()) {
    caractere = (char)CAN.read();  // lecture du bus can dans la variable caractere
    id = CAN.packetId();           // id du message can  dans la variable id
  }
}

//======
// setup
//======
void setup() {
  /*
  if (debug) {
  Serial.begin(9600);
  while (!Serial)
    ;
  }
  */

  /*
  if (debug) {
    Serial.println("Demarrage de l'afficheur");
  }
  */

  FastLED.addLeds<WS2812B, DATA_PIN_ARDUINO, RGB>(leds, NUM_LEDS);  // GRB ordering is typical

  // start the CAN bus at 125 kbps
  if (!CAN.begin(125E3)) {
    /*
    if (debug) {
      Serial.println("Starting CAN failed!");
    }
    */
    while (1)
      ;
  }

  // register the receive callback - interruption des l'arrivee d'un message sur le bus can
  CAN.onReceive(onReceive);
}

//======
// loop
//======
void loop() {

  // reception de la couleur du master id 0x17 - couleur du cube
  if ((caractere == 'R' or caractere == 'G' or caractere == 'B' or caractere == 'Y') and id == 0x17) {

    if (caractere == 'R') {
      // affichage de la couleur rouge
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Red;
        FastLED.show();
      }
    } else if (caractere == 'G') {
      // affichage de la couleur verte
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Green;
        FastLED.show();
      }
    } else if (caractere == 'B') {
      // affichage de la couleur bleue
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Blue;
        FastLED.show();
      }
    } else if (caractere == 'Y') {
      // affichage de la couleur jaune
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Yellow;
        FastLED.show();
      }
    }
    // effacement des tableaux de leds 2 x 256
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
      FastLED.show();
      //delay(100);
    }

    /*
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
    */
    caractere = '0';  // effacement du caratere apres lecture
    id = 0x0;         // effacement de la variable id apres lecture
  }
}
