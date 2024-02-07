/***********************************************
  projet robocup 2024
    detecteur de couleur
    mjc fablab atelier codage 2023 2024
  url: https://github.com/Panjkrc/TCS3200_library
************************************************/

//=============================
// inclusion des bibliothèques
//============================
#include <SPI.h>  // pour la bibliothèque CAN
#include <CAN.h>
#include <tcs3200.h>    // Include TCS3200 library
#include "variables.h"  // fichier variables

//==================
// TCS3200 detecteur
//==================

// distinctColors[] array declares values to be returned from closestColor() function if specified color is recognised
int distinctColors[num_of_colors] = { 0, 1, 2, 3, 4, 5, 6 };
String colorNames[num_of_colors] = { "white", "noir", "red", "yellow", "green", "tree", "blue" };
char colorLetter[num_of_colors] = { 'W', 'N', 'R', 'Y', 'G', 'T', 'B' };

// distinctRGB[] array declares calibration values for each declared color in distinctColors[] array
int distinctRGB_1[num_of_colors][3] = { { 23, 21, 24 }, { 8, 7, 8 }, { 25, 19, 20 }, { 66, 58, 55 }, { 45, 50, 50 }, { 24, 21, 20 }, { 38, 41, 52 } };
int distinctRGB_2[num_of_colors][3] = { { 21, 20, 23 }, { 8, 7, 8 }, { 19, 12, 14 }, { 47, 38, 29 }, { 21, 28, 25 }, { 20, 16, 17 }, { 16, 21, 33 } };

tcs3200 tcs_1(S0_1, S1_1, S2_1, S3_1, sensorOut_1);  // (S0, S1, S2, S3, output pin) //  https://www.mouser.com/catalog/specsheets/TCS3200-E11.pdf
tcs3200 tcs_2(S0_2, S1_2, S2_2, S3_2, sensorOut_2);

//======================
// sensor IR infra rouge
//======================
bool sensorIR() {
  bool sensorStatus = digitalRead(IRSensor);  // read IRsensor
  return sensorStatus;
}

//================
// tcs3200 colors
//================
int color_1() {
  Serial.print("color_1   ");
  int couleur = tcs_1.closestColor(distinctRGB_1, distinctColors, num_of_colors);
  Serial.print(couleur);
  Serial.print(" ");
  Serial.print(colorNames[couleur]);
  Serial.print("  ");

  red = tcs_1.colorRead('r', 20);  //reads color value for red
  Serial.print("R_1 = ");
  Serial.print(red);
  Serial.print("    ");

  green = tcs_1.colorRead('g', 20);  //reads color value for green
  Serial.print("G_1 = ");
  Serial.print(green);
  Serial.print("    ");

  blue = tcs_1.colorRead('b', 20);  //reads color value for blue
  Serial.print("B_1 = ");
  Serial.print(blue);
  Serial.print("    ");
  Serial.println();
  delay(100);
  return (couleur);
}

int color_2() {
  Serial.print("color_2   ");
  int couleur = tcs_2.closestColor(distinctRGB_2, distinctColors, num_of_colors);
  Serial.print(couleur);
  Serial.print(" ");
  Serial.print(colorNames[couleur]);
  Serial.print("  ");

  red = tcs_2.colorRead('r', 20);  //reads color value for red
  Serial.print("R_2 = ");
  Serial.print(red);
  Serial.print("    ");

  green = tcs_2.colorRead('g', 20);  //reads color value for green
  Serial.print("G_2 = ");
  Serial.print(green);
  Serial.print("    ");

  blue = tcs_2.colorRead('b', 20);  //reads color value for blue
  Serial.print("B_2 = ");
  Serial.print(blue);
  Serial.print("    ");

  Serial.println();
  delay(100);
  return (couleur);
}

void portiqueIR() {
  sensor_ir = sensorIR();  // lit l'etat actuel du sensor IR
  //Serial.println(sensor_ir);
  // compare l'etat actuel du sensor IR a l'etat precedent memorise
  if (sensor_ir != sensor_ir_mem) {  // si l'etat du sensor IR a change
    // on memorise l'etat courant du sensor IR pour les prochains passages dans la boucle loop
    sensor_ir_mem = sensor_ir;
    if (sensor_ir == 0) {
      int couleur_1 = color_1();
      CAN.beginPacket(0x16);              // id 0x16 pour le detecteur de couleur_1
      CAN.write(colorLetter[couleur_1]);  // ecriture de la couleur detectee
      //Serial.println(colorLetter[couleur_1]);
      CAN.endPacket();  // envoi sur le bus can
    } else if (sensor_ir == 1) {
      int couleur_2 = color_2();
      CAN.beginPacket(0x19);              // id 0x19 pour le detecteur de couleur_2
      CAN.write(colorLetter[couleur_2]);  // ecriture de la couleur detectee
      //Serial.println(colorLetter[couleur_2]);
      CAN.endPacket();  // envoi sur le bus can
    }
  }
}


//==========================
//  CAN reception suite irq
//==========================
void onReceive(int packetSize) {
  while (CAN.available()) {
    caractere = (char)CAN.read();  // lecture du bus can dans la variable caractere
    id = CAN.packetId();           // id du message can  dans la variable id
  }
}

//=======
// setup
//=======
void setup() {
  Serial.begin(SERIAL_BAUD);
  Serial.println();
  Serial.println("Demarrage du detecteur de couleurs");

  // leds blanches du detecteur de couleurs
  pinMode(ledsBlanches_1, OUTPUT);
  digitalWrite(ledsBlanches_1, LOW);

  pinMode(ledsBlanches_2, OUTPUT);
  digitalWrite(ledsBlanches_2, LOW);

  // sensor ir
  pinMode(IRSensor, INPUT);  // Initialization of sensor pin

  // start the CAN bus at 125 kbps
  if (!CAN.begin(125E3)) {
    Serial.println("Starting CAN failed!");
    while (1)
      ;
  }

  // register the receive callback - interruption des l'arrivee d'un message sur le bus can
  CAN.onReceive(onReceive);
}

//=====
// loop
//=====
void loop() {
  portiqueIR();
  //color_1();
  //color_2();
}
