// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>

char  caractere = '0';

void setup() {
  Serial.begin(9600);
  while (!Serial);

  Serial.println("CAN Receiver");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(125E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }

  // register the receive callback
  CAN.onReceive(onReceive);
}

//==========================
//  CAN reception suite irq
//==========================
void onReceive(int packetSize) {
  while (CAN.available()) {
    caractere = (char)CAN.read();
  }
}

void loop() {
  // reception irq
  if (caractere == 'P') {
    Serial.print("caractere reçu   ");
    Serial.println(caractere);
    caractere = '0';
    CAN.beginPacket(0x11);
    CAN.write('S');  // objet present commande stop
    CAN.endPacket();
  }

}
