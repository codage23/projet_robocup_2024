/***********************************************************************************************************************
    projet robocup 2024
    module bras articule
    mjc fablab atelier codage 2023 2024
    https://tutorial45.com/mcp2515-arduino-project-can-arduino/
    https://github.com/sandeepmistry/arduino-CAN/tree/master
    Le bus de données CAN (Controller Area Network)
    est un bus système série très répandu dans beaucoup d'industries, notamment l'automobile.
    Il met en application une approche connue sous le nom de multiplexage,
    et qui consiste à raccorder à un même câble (un bus) un grand nombre de calculateurs qui communiqueront donc à tour de rôle.
    Cette technique élimine le besoin de câbler des lignes dédiées pour chaque information à faire transiter.
    https://community.element14.com/products/arduino/arduino-projects/b/blog/posts/6-axis-robotic-arm-with-servo-motors
    https://circuitdigest.com/microcontroller-projects/pca9685-multiple-servo-control-using-arduino
    http://wiki.sunfounder.cc/index.php?title=PCA9685_16_Channel_12_Bit_PWM_Servo_Driver
    https://www.gotronic.fr/pj-1835.pdf
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
void home(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // Servo Motor 5
  pca9685.setPWM(5, 0, posServo5);
  delay(velocidad);
  // Servo Motor 1
  pca9685.setPWM(1, 0, posServo1);
  delay(velocidad);
  // Servo Motor 2
  pca9685.setPWM(2, 0, posServo2);
  delay(velocidad);
  // Servo Motor 4
  pca9685.setPWM(4, 0, posServo4);
  delay(velocidad);
  // Servo Motor 3
  pca9685.setPWM(3, 0, posServo3);
  delay(velocidad);
  // Servo Motor 0
  pca9685.setPWM(0, 0, posServo0);
  delay(velocidad);
}

//================================
// fonction position ready du bras
//================================
// Position of the Servo Motors for the first movement of the Robot Arm
void ready(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // Servo Motor 4
  pca9685.setPWM(4, 0, posServo4);  // 295
  delay(velocidad);
  // Servo Motor 3
  pca9685.setPWM(3, 0, posServo3);  // 220
  delay(velocidad);
  // Servo Motor 2
  pca9685.setPWM(2, 0, posServo2);  // 300
  delay(velocidad);
  // Servo Motor 1
  pca9685.setPWM(1, 0, posServo1);  // 300
  delay(velocidad);
}

//=======================================================
// fonction position ready du bras pour attrapper le cube
//=======================================================
// Position of the Servo Motors to prepare to pick up the cube
void get_ready(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // Servo Motor 5
  pca9685.setPWM(5, 0, posServo5);  // 350
  delay(velocidad);
  // Servo Motor 3
  pca9685.setPWM(3, 0, posServo3);  // 150
  delay(velocidad);
  // Servo Motor 2
  pca9685.setPWM(2, 0, posServo2);  // 415
  delay(velocidad);
  // Servo Motor 4
  pca9685.setPWM(4, 0, posServo4);  // 200
  delay(velocidad);
  // Servo Motor 0
  pca9685.setPWM(0, 0, posServo0);  // 200
  delay(velocidad);
}

//===================================
// fonction prepare attrapper le cube
//===================================
// Position of the Servo Motors to prepare for download the cube
void prepare_download_object(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // Servo Motor 4
  pca9685.setPWM(4, 0, posServo4);  // 295
  delay(velocidad);
  // Servo Motor 3
  pca9685.setPWM(3, 0, posServo3);  // 220
  delay(velocidad);
  // Servo Motor 5
  pca9685.setPWM(5, 0, posServo5);  // 265
  delay(velocidad);
  // Servo Motor 2
  pca9685.setPWM(2, 0, posServo2);  // 300
  delay(velocidad);
}

//=================================================
// fonction position du bras pour attrapper le cube
//=================================================
// Position of the Servo Motors to pick up the cube
void pick_up_object(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // Servo Motor 4
  pca9685.setPWM(4, 0, posServo4);  // 210
  delay(velocidad);
  // Servo Motor 2
  pca9685.setPWM(2, 0, posServo2);  //405
  delay(velocidad);
  // Servo Motor 3
  // Loop for to move the Servo Motor 3 slowly  de 150  a  180
  for (int pos = 150; pos < 180; pos += 1) {
    pca9685.setPWM(3, 0, pos);
    delay(10);
  }
  // Servo Motor 2
  // Loop for to move the Servo Motor 2 slowly  de 405 a 350
  for (int pos = 405; pos > 350; pos -= 1) {
    pca9685.setPWM(2, 0, pos);
    delay(10);
  }
  // Servo Motor 0
  // Loop to close the clamp slowly  de 200 a 166
  for (int pos = 200; pos > 166; pos -= 1) {
    pca9685.setPWM(0, 0, pos);
    delay(10);
  }
}

//============================
// fonction attrapper le cube
//============================
// Position of the Servo Motors to download the objet
void download_object(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // Servo Motor 5
  pca9685.setPWM(5, 0, posServo5);  // 210
  delay(velocidad);
  // Servo Motor 3
  pca9685.setPWM(3, 0, posServo3);  // 175
  delay(velocidad);
  // Servo Motor 2
  pca9685.setPWM(2, 0, posServo2);  // 460
  delay(velocidad);
  // Servo Motor 4
  pca9685.setPWM(4, 0, posServo4);  // 195
  delay(velocidad);
  // Servo Motor 0
  // Loop to open the clamp slowly de 166 a 200
  for (int pos = 166; pos < 200; pos += 1) {
    pca9685.setPWM(0, 0, pos);
    delay(10);
  }
}

//================================
// fonction deplacement cube rouge
//================================
void deplacementCaseRed(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // deplacement a realiser
}

//================================
// fonction deplacement cube vert
//================================
void deplacementCaseGreen(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // deplacement a realiser
}

//================================
// fonction deplacement cube bleu
//================================
void deplacementCaseBlue(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // deplacement a realiser
}

//================================
// fonction deplacement cube jaune
//================================
void deplacementCaseYellow(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // deplacement a realiser
}

//==========================
// fonction relacher du cube
//==========================
void exit_download_object(int posServo0, int posServo1, int posServo2, int posServo3, int posServo4, int posServo5) {
  // Servo Motor 3
  // Loop to start slowly backing out the Robot Arm de 175 a 150
  for (int pos = 175; pos > 150; pos -= 1) {
    pca9685.setPWM(3, 0, pos);
    delay(10);
  }
  // Servo Motor 4
  pca9685.setPWM(4, 0, posServo4);  // 295
  delay(velocidad);
  // Servo Motor 5
  pca9685.setPWM(5, 0, posServo5);  // 265
  delay(velocidad);
  // Servo Motor 2
  pca9685.setPWM(2, 0, posServo2);  // 300
  delay(velocidad);
  // Servo Motor 1
  pca9685.setPWM(1, 0, posServo1);  // 300
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

  // Servo Motors position for Robot Arm home position
  home(NEUTREWAIST0, NEUTRESHOULDER1, NEUTREELBOW2, NEUTREWRISTROLL3, NEUTREWRISTPITCH4, NEUTREGRIPPER5);  // servo 0 , servo 1, ... servo 5
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
    ready();                      // Position of the Servo Motors for the first movement of the Robot Arm
    delay(1000);
    get_ready();                  // Position of the Servo Motors to prepare to pick up the cube
    delay(1000);
    pick_up_object();             // Position of the Servo Motors to pick up the cube
    delay(1000);
    prepare_download_object();    // Position of the Servo Motors to prepare for download the cube
    delay(1000);
    download_object();            // Position of the Servo Motors to download the objet
    delay(1000);
    if ( caractere == 'R') {
      deplacementCaseRed();       // deplacement du cube rouge
    } else if (caractere == 'G') {
      deplacementCaseGreen();     // deplacement du cube vert
    } else if (caractere == 'B') {
      deplacementCaseBlue();      // deplacement du cube bleu
    } else if (caratere == 'Y') {
      deplacementCaseYellow();    // deplacement du cube jaune
    }
    exit_download_object();       // relache du cube
    */
    caractere = '0';  // effacement du caratere apres lecture
    id = 0x0;         // effacement de la variable id apres lecture
  }
}
