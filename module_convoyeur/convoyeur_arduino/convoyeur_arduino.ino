/***********************************************
    projet robocup 2024
    convoyeur
    jlm nov 2023
    nema 17 sur X (shield CNC arduino uno)
************************************************/

//=============================
// inclusion des bibliothèques
//============================
//#include "Timer.h"      //http://github.com/JChristensen/Timer
#include <Wire.h>       //composants utilisant le protocole I2C
#include "variables.h"

//Timer timer;                        //instantiate the timer object

//============
// sensor IR
//============
bool sensorIR() {
  //int sensorStatus = digitalRead(IRSensor); // Set the GPIO as Input
  int sensorStatus = 1;

  //Serial.print("sensor statut : ");
  //Serial.print(sensorStatus);
  // Check if the pin high or not
  if (sensorStatus == 1)   {
    // if the pin is high turn off the onboard Led
    digitalWrite(LED, LOW); // LED LOW
    //Serial.println("   objet absent");      // print Motion Detected! on the serial monitor window
  }
  else  {
    //else turn on the onboard LED
    digitalWrite(LED, HIGH);                 // LED High
    //Serial.println("   objet present");         // print Motion Ended! on the serial monitor window
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

  // stepper nema17
  pinMode(enPin, OUTPUT);  // enable driver X
  digitalWrite(enPin, LOW);

  pinMode(stepPin, OUTPUT);  // impulsion effectue une step.
  pinMode(dirPin, OUTPUT);   // permet d'indiquer la direction de rotation du moteur
/*
  // timer entre deux implulsions - utilise milli()
  timer.oscillate(stepPin, motorSpeed, HIGH);
  timer.oscillate(stepPin, motorSpeed, LOW);
*/
  // sensor ir
  pinMode(IRSensor, INPUT); // IR Sensor pin INPUT
  pinMode(LED, OUTPUT);     // LED Pin Output

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
// Wire
// requestEvents
void requestEvents() {
  if (requestI2C) {
    Wire.write(sensorIR());
  } else {
    requestI2C = 0;
  }
}
// Wire
// receiveEventys
void receiveEvents(int howMany) {
  // Check for incoming data
  // Lecture du module I2C
  if (Wire.available() > 0) {
    // raz du message
    for (int i = 0; i < MAX_MESSAGE_LENGTH; i++) {
      message[i] = '\0';
    }
    // prints the received data
    //Serial.print("I received: ");
    for (int i = 0; i < MAX_MESSAGE_LENGTH ; i++) {
      dataI2C =  Wire.read(); // lecture de l'i2c
      if (dataI2C == 0xFFFFFFFF ) {  // fin du message avant la longueur maxi
        break;
      }
      message[i] = dataI2C;  // constitution du message
      //Serial.print(dataI2C,HEX);
      //Serial.print(message[i]);
    }
    //Serial.println("");
    //int taille = sizeof(message); // taille du tableau
    int taille = strlen(message); // taille de la chaine
    //Serial.print("taille message : ");
    //Serial.println(taille);

    char dataInS[taille];

    // reception du message sc
    if (message[0] == 115 and message[1] == 99) { // s situation et c convoyeur
      requestI2C = 1; // demande du master i2c
      //Serial.println(requestI2C);
    }

    // reception du message mvxx vitesse rpm
    if (message[0] == 109 and message[1] == 118) { // m motor et v vitesse speed
      // Extract only the number. E.g. from "mv10" to "10"
      for (int i = 0; i < taille; i++) {
        dataInS[i] = message[i + 2];
      }
      motorSpeed = atoi(dataInS); // char to int
      //Serial.print("Motor speed : ");
      //Serial.println(motorSpeed);
    }
  /*
    // reception du message mpxx pas
    if (message[0] == 109 and message[1] == 112) { // m motor et p pas
      // Extract only the number. E.g. from "mp120" to "120"
      for (int i = 0; i < taille; i++) {
        dataInS[i] = message[i + 2];
      }
      motorStep = atoi(dataInS); // char to int
      //Serial.print("motor step : ");
      //Serial.println(motorStep);
    }
    */
    // reception du message msx sens
    if (message[0] == 109 and message[1] == 115) { // m motor et s sens
      // Extract only the number. E.g. from "ms1" to "1"
      for (int i = 0; i < taille; i++) {
        dataInS[i] = message[i + 2];
      }
      motorInverse = atoi(dataInS); // char to int
      //Serial.print("Motor Inverse : ");
      //Serial.println(motorInverse);
    }
    // reception du message STOP
    if (message[0] == 83 and message[1] == 84 and message[2] == 79 and message[3] == 80) {  // STOP
      stopStart = 0;
      //Serial.print("Stop : ");
      //Serial.println(stopStart);
    }
    // reception du message START
    if (message[0] == 83 and message[1] == 84 and message[2] == 65 and message[3] == 82 and message[4] == 84) {  // START
      stopStart = 1;
      //Serial.print("Start : ");
      //Serial.println(stopStart);
    }
  }
}
#endif

//======
// loop
//======
void loop() {
  // timer entre deux implulsions - utilise milli()
  //timer.oscillate(stepPin, motorSpeed, HIGH);
  //timer.oscillate(stepPin, motorSpeed, LOW);
  
  // sens de rotation
  if (motorInverse) {
    //sens horaire, LOW pour inverser
    digitalWrite(dirPin, HIGH); // Enables the motor to move in a particular direction
  } else {
    digitalWrite(dirPin, LOW); //Changes the rotations direction
  }

  // stop start
  if ( sensorIR() and stopStart) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(pulseWidthMicros);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(pulseWidthMicros);
    //timer.update(); // mise a jour du timer - utilise milli
  }

#if TEST
// test du stepper nema17
  Serial.println(F("Running clockwise"));
  //sens horaire, LOW pour inverser
  digitalWrite(dirPin, HIGH); // Enables the motor to move in a particular direction

  // Makes 200 pulses for making one full cycle rotation
  for (int i = 0; i < stepsPerRev; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(pulseWidthMicros);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(pulseWidthMicros);
  }
  delay(1000); // One second delay

  Serial.println(F("Running counter-clockwise"));
  digitalWrite(dirPin, LOW); //Changes the rotations direction

  // Makes 400 pulses for making two full cycle rotation
  for (int i = 0; i < 2 * stepsPerRev; i++) {
    digitalWrite(stepPin, HIGH);
    delayMicroseconds(pulseWidthMicros);
    digitalWrite(stepPin, LOW);
    delayMicroseconds(pulseWidthMicros);
  }
  delay(1000);
#endif

}
