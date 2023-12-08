/***********************************************
    projet robocup 2024
    convoyeur
    jlm nov 2023
    https://passionelectronique.fr/tutoriel-l298n/
    https://tutorial45.com/mcp2515-arduino-project-can-arduino/
************************************************/

//=============================
// inclusion des bibliothèques
//=============================
#include <Wire.h>  //composants utilisant le protocole I2C
#include <SPI.h>   // pour la bibliothèque CAN
//#include "mcp_can.h"             // bibliothèque CAN
#include <CAN.h>
#include "variables.h"  // fichier variables

//MCP_CAN CAN(mcp2515CSPin);

//============
// sensor IR
//============
bool sensorIR() {
  bool sensorStatus = digitalRead(IRSensor);  // read IRsensor
  if (debug) {
    //Serial.print("sensor statut : ");
    //Serial.println(sensorStatus);
  }
  return sensorStatus;
}

//======
// setup
//======
void setup() {
  Serial.begin(SERIAL_BAUD);
  Serial.println();
  Serial.println("Demarrage du convoyeur avec le sensor ir");

  // Configuration des pins de l'Arduino en "sortie"
  pinMode(borneENB, OUTPUT);
  pinMode(borneIN3, OUTPUT);
  pinMode(borneIN4, OUTPUT);

  // sensor ir
  pinMode(IRSensor, INPUT);  // IR Sensor pin INPUT
  pinMode(LED, OUTPUT);      // LED Pin Output

  // start the CAN bus at 125 kbps
  if (!CAN.begin(125E3)) {
    Serial.println("Starting CAN failed!");
    while (1)
      ;
  }

#if I2C
  // Initialise la library Wire et se connecte au bus I2C en tant qu'esclave
  Wire.begin(I2C_SLAVE_CONVOYEUR);
  // Définition de la fonction qui prendra en charge les informations recues sur le bus I2
  Wire.onReceive(receiveEvents);
  Wire.onRequest(requestEvents);
#endif

  // register the receive callback
  CAN.onReceive(onReceive);
}


//=========================================
// Fonction configurerSensDeRotationPontB()
// Definit le sens de rotation du moteur
//=========================================
void configurerSensDeRotationPontB(bool sensDeRotation) {
  if (sensDeRotation == MARCHE_AVANT) {
    // L298N en "marche avant", Selon sa table de verite
    digitalWrite(borneIN3, HIGH);  // IN3 niveau haut
    digitalWrite(borneIN4, LOW);   // IN4 niveau bas
  }
  if (sensDeRotation == MARCHE_ARRIERE) {
    // L298N en "marche avant", Selon sa table de verite
    digitalWrite(borneIN3, LOW);   // IN3 niveau bas
    digitalWrite(borneIN4, HIGH);  // IN4 niveau haut
  }
}

//=========================================================================
// Fonction changeVitesseMoteurPontB()
// Change la vitesse de rotation du moteur (valeur comprise entre 0 et 255)
//=========================================================================
void changeVitesseMoteurPontB(int nouvelleVitesse) {
  // signal PWM rapport cyclique "nouvelleVitesse"
  analogWrite(borneENB, nouvelleVitesse);
}

//==========================
//  CAN reception suite irq
//==========================
void onReceive(int packetSize) {
   while (CAN.available()) {
    caractere = (char)CAN.read();
  }
}

//======
// loop
//======
void loop() {
  /*
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  Serial.print("Sending packet ... ");
  CAN.beginPacket(0x12);
  CAN.write('h');
  CAN.write('e');
  CAN.write('l');
  CAN.write('l');
  CAN.write('o');
  CAN.endPacket();
  Serial.println("done");
*/
  if (marche) {  // demarrage progessif une seule fois
    //sens de rotation du moteur en "marche avant"
    configurerSensDeRotationPontB(MARCHE_AVANT);
    // depart progresif du moteur, vitesse maxi 255
    for (vitesse = vitesseMinimale; vitesse < vitesseMaximale; vitesse++) {
      changeVitesseMoteurPontB(vitesse);  // vitesse moteur avec signal PWM
      delay(delaiChangementVitesse);
    }
    marche = 0;  // pour avoir un seul demarrage progessif
  }

  // Check if the pin high or not IRsensor
  if ((sensorIR() == 0) and (presentAbsent == 0)) {
    digitalWrite(LED, HIGH);      // LED High
   // changeVitesseMoteurPontB(0);  // arret moteur
    presentAbsent = 1;            // objet present
    CAN.beginPacket(0x12);
    CAN.write('P');  // objet present
    CAN.endPacket();
    if (debug) {
      Serial.println("Sending packet objet present");
    }
  } else if ((sensorIR() == 1) and (presentAbsent == 1)) {
    digitalWrite(LED, LOW);  // LED LOW
    presentAbsent = 0;       // objet absent
    marche = 1;              //  pour valider un nouveau demarrage des que l'objet n'est plus present
    CAN.beginPacket(0x12);
    CAN.write('A');  // objet absent
    CAN.endPacket();
    if (debug) {
      Serial.println("Sending packet objet absent");
    }
    if (caractere == 'S') {
      changeVitesseMoteurPontB(0);  // arret moteur
    }
  }

#if AUTONOME
  if (marche) {  // demarrage progessif une seule fois
    //sens de rotation du moteur en "marche avant"
    configurerSensDeRotationPontB(MARCHE_AVANT);
    // depart progresif du moteur, vitesse maxi 255
    for (vitesse = vitesseMinimale; vitesse < vitesseMaximale; vitesse++) {
      changeVitesseMoteurPontB(vitesse);  // vitesse moteur avec signal PWM
      delay(delaiChangementVitesse);
    }
    marche = 0;  // pour avoir un seul demarrage progessif
  }

  // Check if the pin high or not IRsensor
  if (sensorIR() == 1) {      // objet absent
    digitalWrite(LED, LOW);   // LED LOW
    if (objetPresent == 1) {  //  pour valider un nouveau demarrage des que l'objet n'est plus present
      marche = 1;
    }
    objetPresent = 0;  // pas d'objet 0
    if (debug) {
      Serial.println("objet absent");
    }
  }
  if (sensorIR() == 0) {  // objet present
    //else turn on the onboard LED
    digitalWrite(LED, HIGH);  // LED High
    // arret moteur
    changeVitesseMoteurPontB(0);
    objetPresent = 1;  // objet present 1
    if (debug) {
      Serial.println("objet present");
    }
  }
#endif
#if TEST
  //avant
  //sens de rotation du moteur en "marche avant"
  configurerSensDeRotationPontB(MARCHE_AVANT);
  // depart progresif du moteur, vitesse maxi 255
  for (vitesse = vitesseMinimale; vitesse < vitesseMaximale; vitesse++) {
    changeVitesseMoteurPontB(vitesse);  // vitesse moteur avec signal PWM
    delay(delaiChangementVitesse);
  }
  delay(10000);
  // deceleration progressive
  for (vitesse = vitesseMaximale; vitesse > vitesseMinimale; vitesse--) {
    changeVitesseMoteurPontB(vitesse);  // vitesse moteur avec signal PWM
    delay(delaiChangementVitesse);
  }
  // arret moteur
  changeVitesseMoteurPontB(0);
  delay(1000);
  //arriere
  //sens de rotation du moteur en "marche arriere"
  configurerSensDeRotationPontB(MARCHE_ARRIERE);
  //depart progresif du moteur, vitesse maxi 255
  for (vitesse = vitesseMinimale; vitesse < vitesseMaximale; vitesse++) {
    changeVitesseMoteurPontB(vitesse);  // vitesse moteur avec signal PWM
    delay(delaiChangementVitesse);
  }
  delay(10000);
  // deceleration progressive
  for (vitesse = vitesseMaximale; vitesse > vitesseMinimale; vitesse--) {
    changeVitesseMoteurPontB(vitesse);  // vitesse moteur avec signal PWM
    delay(delaiChangementVitesse);
  }
  // arret moteur
  changeVitesseMoteurPontB(0);
  delay(1000);
#endif
}


//======
// wire
//======
#if I2C
// requestEvents
void requestEvents() {
  if (requestI2C) {
    Wire.write(sensorIR());
  } else {
    requestI2C = 0;
  }
}
// receiveEventys
void receiveEvents(int howMany) {
  // Check for incoming data
  // Lecture du module I2C
  if (Wire.available() > 0) {
    // raz du message
    for (int i = 0; i < MAX_MESSAGE_LENGTH; i++) {
      message[i] = '\0';
    }
    if (debug) {
      // prints the received data
      Serial.print("I received: ");
    }
    for (int i = 0; i < MAX_MESSAGE_LENGTH; i++) {
      dataI2C = Wire.read();        // lecture de l'i2c
      if (dataI2C == 0xFFFFFFFF) {  // fin du message avant la longueur maxi
        break;
      }
      message[i] = dataI2C;  // constitution du message
      if (debug) {
        Serial.print(dataI2C, HEX);
        Serial.print(message[i]);
      }
    }
    //int taille = sizeof(message); // taille du tableau
    int taille = strlen(message);  // taille de la chaine
    if (debug) {
      Serial.println("");
      Serial.print("taille message : ");
      Serial.println(taille);
    }
    char dataInS[taille];
    // reception du message c convoyeur
    if (message[0] == 99) {  // c convoyeur
      requestI2C = 1;        // demande du master i2c
      if (debug) {
        Serial.println(requestI2C);
      }
    }
    // reception du message vxxx vitesse 60 to 255
    if (message[1] == 118) {  // v vitesse speed
      // Extract only the number. E.g. from "v150" to "150"
      for (int i = 0; i < taille; i++) {
        dataInS[i] = message[i + 1];
      }
      motorSpeed = atoi(dataInS);  // char to int
      if (debug) {
        Serial.print("Motor speed : ");
        Serial.println(motorSpeed);
      }
    }
    // reception du message sx sens
    if (mmessage[1] == 115) {  // s sens
      // Extract only the number. E.g. from "s1" to "1"
      for (int i = 0; i < taille; i++) {
        dataInS[i] = message[i + 1];
      }
      motorSens = atoi(dataInS);  // char to int, 1 marche avant, 0 marche arriere
      if (debug) {
        Serial.print("Motor Inverse : ");
        Serial.println(motorSens);
      }
    }
    // reception du message arret
    if (message[0] == 65) {  // A pour arret
      arret = 1;
      marche = 0;
      if (debug) {
        Serial.print("Arret : ");
        Serial.println(arret);
      }
    }
    // reception du message marche
    if (message[0] == 77) {  // M pour marche
      marche = 1;
      arret = 0;
      if (debug) {
        Serial.print("Marche : ");
        Serial.println(smarche);
      }
    }
  }
}
#endif
