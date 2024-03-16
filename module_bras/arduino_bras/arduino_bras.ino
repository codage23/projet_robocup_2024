/***********************************************************************************************************************
    projet robocup 2024
    module bras articule
    mjc fablab atelier codage 2023 2024
    https://tutorial45.com/mcp2515-arduino-project-can-arduino/
    https://github.com/sandeepmistry/arduino-CAN/tree/master
    Le bus de données CAN (Controller Area Network)
    est un bus système série très répandu dans beaucoup d'industries, notamment l'automobile
    https://community.element14.com/products/arduino/arduino-projects/b/blog/posts/6-axis-robotic-arm-with-servo-motors
***********************************************************************************************************************/

//=============================
// inclusion des bibliothèques
//=============================
#include <CAN.h>                      // bibliothèque CAN
#include <SPI.h>                      // bibliotheque SPI communications
#include <Wire.h>                     // Library for I2C communications
#include <Adafruit_PWMServoDriver.h>  // PCA9685 Library
#include "variables.h"                // fichier variables

// Implementation of an object of module PCA9685
Adafruit_PWMServoDriver pca9685 = Adafruit_PWMServoDriver();

//=======================
// fonction repos du bras
//=======================
// Servo Motors position for Robot Arm home position
void home(int servo0, int servo1, int servo2, int servo3, int servo4, int servo5) {
  // Servo Motor 5
  pca9685.setPWM(5, 0, servo5);
  delay(velocidad);
  // Servo Motor 1
  pca9685.setPWM(1, 0, servo4);
  delay(velocidad);
  // Servo Motor 2
  pca9685.setPWM(2, 0, servo3);
  delay(velocidad);
  // Servo Motor 4
  pca9685.setPWM(4, 0, servo2);
  delay(velocidad);
  // Servo Motor 3
  pca9685.setPWM(3, 0, servo1);
  delay(velocidad);
  // Servo Motor 0
  pca9685.setPWM(0, 0, servo0);
  delay(velocidad);
}

//================================
// fonction position ready du bras
//================================
// Position of the Servo Motors for the first movement of the Robot Arm
void ready() {
  // Servo Motor 4
  pca9685.setPWM(4, 0, 295);
  delay(velocidad);
  // Servo Motor 3
  pca9685.setPWM(3, 0, 220);
  delay(velocidad);
  // Servo Motor 2
  pca9685.setPWM(2, 0, 300);
  delay(velocidad);
  // Servo Motor 1
  pca9685.setPWM(1, 0, 300);
  delay(velocidad);
}

//=======================================================
// fonction position ready du bras pour attrapper le cube
//=======================================================
// Position of the Servo Motors to prepare to pick up the cube
void get_ready() {
  // Servo Motor 5
  pca9685.setPWM(5, 0, 350);
  delay(velocidad);
  // Servo Motor 3
  pca9685.setPWM(3, 0, 150);
  delay(velocidad);
  // Servo Motor 2
  pca9685.setPWM(2, 0, 415);
  delay(velocidad);
  // Servo Motor 4
  pca9685.setPWM(4, 0, 200);
  delay(velocidad);
  // Servo Motor 0
  pca9685.setPWM(0, 0, 200);
  delay(velocidad);
}

//===================================
// fonction prepare attrapper le cube
//===================================
// Position of the Servo Motors to prepare for download the cube
void prepare_download_object() {
  // Servo Motor 4
  pca9685.setPWM(4, 0, 295);
  delay(velocidad);
  // Servo Motor 3
  pca9685.setPWM(3, 0, 220);
  delay(velocidad);
  // Servo Motor 5
  pca9685.setPWM(5, 0, 265);
  delay(velocidad);
  // Servo Motor 2
  pca9685.setPWM(2, 0, 300);
  delay(velocidad);
}

//=================================================
// fonction position du bras pour attrapper le cube
//=================================================
// Position of the Servo Motors to pick up the cube
void pick_up_object() {
  // Servo Motor 4
  pca9685.setPWM(4, 0, 210);
  delay(velocidad);
  // Servo Motor 2
  pca9685.setPWM(2, 0, 405);
  delay(velocidad);
  // Servo Motor 3				// Loop for to move the Servo Motor 3 slowly
  for (int pos = 150; pos < 180; pos += 1) {
    pca9685.setPWM(3, 0, pos);
    delay(10);
  }
  // Servo Motor 2				// Loop for to move the Servo Motor 2 slowly
  for (int pos = 405; pos > 350; pos -= 1) {
    pca9685.setPWM(2, 0, pos);
    delay(10);
  }
  // Servo Motor 0				// Loop to close the clamp slowly
  for (int pos = 200; pos > 166; pos -= 1) {
    pca9685.setPWM(0, 0, pos);
    delay(10);
  }
}

//============================
// fonction attrapper le cube
//============================
// Position of the Servo Motors to download the first objet
void download_object() {
  // Servo Motor 5
  pca9685.setPWM(5, 0, 210);
  delay(velocidad);
  // Servo Motor 3
  pca9685.setPWM(3, 0, 175);
  delay(velocidad);
  // Servo Motor 2
  pca9685.setPWM(2, 0, 460);
  delay(velocidad);
  // Servo Motor 4
  pca9685.setPWM(4, 0, 195);
  delay(velocidad);
  // Servo Motor 0				// Loop to open the clamp slowly
  for (int pos = 166; pos < 200; pos += 1) {
    pca9685.setPWM(0, 0, pos);
    delay(10);
  }
}

//================================
// fonction deplacement cube rouge
//================================
deplacementCaseRed() {
  // deplacement a realiser
}

//================================
// fonction deplacement cube vert
//================================
deplacementCaseGreen() {
  // deplacement a realiser
}

//================================
// fonction deplacement cube bleu
//================================
deplacementCaseBlue() {
  // deplacement a realiser
}

//================================
// fonction deplacement cube jaune
//================================
deplacementCaseYellow() {
  // deplacement a realiser
}

//==========================
// fonction relacher du cube
//==========================
void exit_download_object() {
  // Servo Motor 3				// Loop to start slowly backing out the Robot Arm
  for (int pos = 175; pos > 150; pos -= 1) {
    pca9685.setPWM(3, 0, pos);
    delay(10);
  }
  // Servo Motor 4
  pca9685.setPWM(4, 0, 295);
  delay(velocidad);
  // Servo Motor 5
  pca9685.setPWM(5, 0, 265);
  delay(velocidad);
  // Servo Motor 2
  pca9685.setPWM(2, 0, 300);
  delay(velocidad);
  // Servo Motor 1
  pca9685.setPWM(1, 0, 300);
  delay(velocidad);
}

//======
// setup
//======
void setup() {
  // moniteur serie
  Serial.begin(9600);
  while (!Serial)
    ;

  Serial.println("Demarrage du distributeur");

  // demarrage pwm servo moteur
  pca9685.begin();
  pca9685.setPWMFreq(50);  // Analog servos run at 50 Hz ou 20ms

  // start the CAN bus at 125 kbps
  if (!CAN.begin(125E3)) {
    Serial.println("Starting CAN failed!");
    while (1)
      ;
  }

  // register the receive callback - interruption des l'arrivee d'un message sur le bus can
  CAN.onReceive(onReceive);

  home(320, 360, 250, 250, 250, 250);  // servo 0 , servo 1, ... servo 5
}

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
// loop
//======
void loop() {
  // reception de la couleur du master id 0x18 - couleur du cube
  if ((caractere == 'R' or caractere == 'G' or caractere == 'B' or caractere == 'Y') and id == 0x18) {
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
    /*
    ready();
    delay(1000);
    get_ready();
    delay(1000);
    pick_up_object();
    delay(1000);
    prepare_download_object();
    delay(1000);
    download_object();
    delay(1000);
    if ( caractere == R) {
      deplacementCaseRed();
    } else if (caractere == G) {
      deplacementCaseGreen();
    } else if (caractere == B) {
      deplacementCaseBlue();
    } else if (caratere == Y) {
      deplacementCaseYellow();
    }
    exit_download_object();
*/
    caractere = '0';  // effacement du caratere apres lecture
    id = 0x0;         // effacement de la variable id apres lecture
  }
}
