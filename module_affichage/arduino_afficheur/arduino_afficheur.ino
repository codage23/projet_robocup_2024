/***********************************************************************************************
    projet robocup 2024
    module afficheur
    mjc fablab atelier codage 2023 2024
    https://tutorial45.com/mcp2515-arduino-project-can-arduino/
    https://github.com/sandeepmistry/arduino-CAN/tree/master
    https://github.com/Jorgen-VikingGod/LEDMatrix
    https://electroniqueamateur.blogspot.com/2021/03/ecrire-des-nombres-sur-une-matrice-de.html
    https://electroniqueamateur.blogspot.com/2020/05/matrice-de-leds-rgb-16-x-16-ws2812b-et.html
    https://electroniqueamateur.blogspot.com/2021/02/esp8266-et-esp32-controle-dune-matrice.html
    https://www.instructables.com/16x16-RGB-LED-Panel-Arduino-Projects/

*************************************************************************************************/

//=============================
// inclusion des bibliothèques
//=============================
#include <CAN.h>           // pour la bibliothèque CAN
#include <SPI.h>           // bus spi
#include "variables.h"     // fichier variables
#include <avr/pgmspace.h>  // pour utiliser la memoire flash et augmenter la memoire de travail
#include <FastLED.h>       // https://github.com/FastLED/FastLED
//#include <LEDMatrix.h>  // https://github.com/Jorgen-VikingGod/LEDMatrix


CRGB leds[NUM_LEDS];  // creation d'un objet leds avec la bibliotheque fastled

CRGB laCouleur = CRGB::Black;
//cLEDMatrix<MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_TYPE> leds;

// tableau representant la matrice de leds multicolores Noir Red Green Blue Yellow Fuchsia
const char tableau[NUM_LIGNE][NUM_COLONNE] PROGMEM = {
  //  0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 15
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 14
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 13
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 12
  { 'N', 'N', 'N', 'N', 'N', 'N', 'G', 'B', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 11
  { 'N', 'N', 'N', 'N', 'N', 'G', 'G', 'R', 'B', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 10
  { 'N', 'N', 'N', 'N', 'N', 'G', 'R', 'R', 'R', 'B', 'N', 'N', 'N', 'N', 'N', 'N' },  // 9
  { 'N', 'N', 'N', 'W', 'N', 'R', 'R', 'R', 'R', 'R', 'N', 'N', 'N', 'N', 'N', 'N' },  // 8
  { 'N', 'N', 'W', 'W', 'N', 'N', 'R', 'R', 'R', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 7
  { 'N', 'W', 'W', 'W', 'N', 'N', 'N', 'R', 'N', 'W', 'N', 'N', 'N', 'N', 'N', 'N' },  // 6
  { 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'W', 'N', 'N', 'N', 'N', 'N', 'N' },  // 5
  { 'W', 'W', 'N', 'W', 'N', 'N', 'N', 'N', 'W', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 4
  { 'W', 'W', 'N', 'W', 'W', 'N', 'W', 'W', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 3
  { 'W', 'W', 'W', 'N', 'N', 'N', 'W', 'W', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 2
  { 'W', 'W', 'W', 'W', 'W', 'N', 'W', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' },  // 1
  { 'W', 'W', 'W', 'W', 'W', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N', 'N' }   // 0
};

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
void allumageLed(int i, int y, CRGB laCouleur) {
  /*
  int num;
  if ((i % 2) == 0) {
    num = (i * 16) + y;  // ligne pair
  } else {
    num = (i * 16) + 15 - y;  // ligne impair
  }
  */

   int num;
  if ((i % 2) == 0) {
    num = 255 - (i * 16) - 15 + y;  // ligne pair
  } else {
    num = 255 - (i * 16) + y;  // ligne impair
  }

  leds[num] = laCouleur;
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

  // affichage tableau
  for (int i = 0; i < NUM_LIGNE; i++) {
    for (int y = 0; y < NUM_COLONNE; y++) {
      char valCouleur = pgm_read_byte_near(&tableau[i][y]);
      //Serial.print("valeur de la couleur = : ");
      //Serial.println (valCouleur);
      if (valCouleur == 'N') {
        laCouleur = CRGB::Black;
        allumageLed(i, y, laCouleur);
      } else if (valCouleur == 'R') {
        laCouleur = CRGB::Red;
        allumageLed(i, y, laCouleur);
      } else if (valCouleur == 'G') {
        laCouleur = CRGB::Green;
        allumageLed(i, y, laCouleur);
      } else if (valCouleur == 'B') {
        laCouleur = CRGB::Blue;
        allumageLed(i, y, laCouleur);
      } else if (valCouleur == 'Y') {
        laCouleur = CRGB::Yellow;
        allumageLed(i, y, laCouleur);
      } else if (valCouleur == 'F') {
        laCouleur = CRGB::Fuchsia;
        allumageLed(i, y, laCouleur);
      } else if (valCouleur == 'W') {
        laCouleur = CRGB::White;
        allumageLed(i, y, laCouleur);
        
      } else {
        laCouleur = CRGB::Black;
        allumageLed(i, y, laCouleur);
      }
    }
  }

  // start the CAN bus at 125 kbps
  if (!CAN.begin(125E3)) {
    if (debug) {
      Serial.println("Starting CAN failed!");
    }
    while (1)
      ;
  } else {
    if (debug) {
      Serial.println("Starting CAN");
    }
  }

  // register the receive callback - interruption des l'arrivee d'un message sur le bus can
  CAN.onReceive(onReceive);
}

//======
// loop
//======
void loop() {
  /*
    // pour test de bon fonctionnement
    caractere = 'G';
    id = 0x17;
  */

  // reception de la couleur du master id 0x17 - couleur du cube
  if ((caractere == 'R' or caractere == 'G' or caractere == 'B' or caractere == 'Y') and id == 0x17) {
    if (caractere == 'R') {
      // affichage de la couleur rouge
      for (int i = 0; i < NUM_LEDS; i++) {
        leds[i] = CRGB::Red;
        delay(1);
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
