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

//======
// setup
//======
void setup() {

  if (debug) {
    Serial.begin(9600);
    while (!Serial)
      ;
  }

  if (debug) {
    Serial.println("Demarrage de l'afficheur");
  }

  FastLED.addLeds<CHIPSET, DATA_PIN_ARDUINO, COLOR_ORDER >(leds, NUM_LEDS);  // GRB ordering is typical
  FastLED.setBrightness(10);                                                 // Number 0-255
  FastLED.clear(true);

  // effacement du tableau de leds 256
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
caractere = 'Y';
id = 0x17;
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
caractere = 'E';
id = 0x17;
  delay (2000);
 
  if ((caractere == 'E') and id == 0x17) {  // effacement afficheur id 0x17
    // effacement du tableau de leds 256
    for (int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB::Black;
      delay(1);
    }
    FastLED.show();
  }
}

/*
// ----- Allumer une LED en particulier ------------------------------

  leds.DrawPixel(3, 3, (CRGB::Green));
  FastLED.show();
  delay(pause);
  leds.DrawPixel(3, 4, (CRGB::Blue));
  FastLED.show();
  delay(pause);
  leds.DrawPixel(4, 3, (CRGB::Red));
  FastLED.show();
  delay(pause);
  leds.DrawPixel(4, 4, (CRGB::Yellow));
  FastLED.show();
  delay(pause);

  // effet miroir: on reproduit le même motif dans les 3 autres quadrants

  leds.QuadrantMirror();
  FastLED.show();
  delay(2 * pause);

  // ----- Déplacer le motif vers la droite --------------------------

  for (int i = 0; i <= 12; i++) {
    leds.ShiftRight();
    FastLED.show();
    delay(pause / 2);
  }

  // ------ dessiner une ligne droite -------------------------------

  leds.DrawLine(4, 0, 4, 255, (CRGB::Green));
  FastLED.show();
  delay(pause);
  leds.DrawLine(11, 0, 11, 255, (CRGB::Blue));
  FastLED.show();
  delay(pause);
  leds.DrawLine(0, 4, 255, 4, (CRGB::Red));
  FastLED.show();
  delay(pause);
  leds.DrawLine(0, 11, 255, 11, (CRGB::Pink));
  FastLED.show();
  delay(pause);


  // effet miroir ------------------------------------

  leds.QuadrantTopTriangleMirror();
  FastLED.show();
  delay(2 * pause);

  FastLED.clear(true);  // on éteint toutes les LEDs



  // -- dessiner un cercle plein ------------------------

  leds.DrawFilledCircle(4, 4, 2, (CRGB::Blue));
  FastLED.show();
  delay(pause);

  // -- miroir horizontal -------------------------
  leds.HorizontalMirror();
  FastLED.show();
  delay(pause);

  // -- miroir vertical --------------------------
  leds.VerticalMirror();
  FastLED.show();
  delay(pause);

  FastLED.clear(true);  // on éteint toutes les LEDs
*/
