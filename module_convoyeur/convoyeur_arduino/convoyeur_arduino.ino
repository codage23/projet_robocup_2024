/***********************************************
    projet robocup 2024
    convoyeur
    jlm nov 2023
    https://passionelectronique.fr/tutoriel-l298n/
************************************************/

//=============================
// inclusion des bibliothèques
//=============================
#include <Wire.h>  //composants utilisant le protocole I2C
#include "variables.h"

//============
// sensor IR
//============
bool sensorIR() {
  bool sensorStatus = digitalRead(IRSensor);  // read IRsensor
  if (debug) {
    Serial.print("sensor statut : ");
    Serial.println(sensorStatus);
  }
  return sensorStatus;
}

//======
// setup
//======
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println("Demarrage du convoyeur avec le sensor ir");

  // Configuration des pins de l'Arduino en "sortie"
  pinMode(borneENB, OUTPUT);
  pinMode(borneIN3, OUTPUT);
  pinMode(borneIN4, OUTPUT);

  // sensor ir
  pinMode(IRSensor, INPUT);  // IR Sensor pin INPUT
  pinMode(LED, OUTPUT);      // LED Pin Output

#if I2C
  // Initialise la library Wire et se connecte au bus I2C en tant qu'esclave
  Wire.begin(I2C_SLAVE_CONVOYEUR);
  // Définition de la fonction qui prendra en charge les informations recues sur le bus I2
  Wire.onReceive(receiveEvents);
  Wire.onRequest(requestEvents);
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

//======
// loop
//======
void loop() {
  //if (marche and !objetPresent) {  // demarrage progessif une seule fois
  if (marche ) {  // demarrage progessif une seule fois
    //avant
    //sens de rotation du moteur en "marche avant"
    configurerSensDeRotationPontB(MARCHE_AVANT);

    // depart progresif du moteur, vitesse maxi 255
    for (vitesse = vitesseMinimale; vitesse < vitesseMaximale; vitesse++) {
      changeVitesseMoteurPontB(vitesse);  // vitesse moteur avec signal PWM
      delay(delaiChangementVitesse);
    }
    marche = 0;
  }

  // Check if the pin high or not IRsensor
  if (sensorIR() == 1) {  // objet absent
    // if the pin is high turn off the onboard Led
    digitalWrite(LED, LOW);  // LED LOW
    if (objetPresent == 1) {
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
