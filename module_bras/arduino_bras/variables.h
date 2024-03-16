//=========
// Controls
//=========
#define SERIAL_BAUD 9600  // vitesse moniteur serie
#define SerialMonitor 1

//========================================================
// Differentes fonctions du programme
//========================================================
#define TEST 0   // if 1 true,  0 false
#define debug 1  // for use Display log message if True

//==========================================
// Affectation des broches de l'arduino uno
// Association du CS du CAN MCP2515
//==========================================
#define mcp2515CSPin 10  // cs du circuit mcp2515

//========================
// for non-bloking delays
//========================
unsigned long nextTime;  // For non-blocking delays

//================
// bus can mcp2515
//================
const int SPI_CS_PIN = 10;  // CS du shield mcp2515

//==========
// Variables
//==========
char caractere = '0';  // lecture can
int id = 0x0;          // valeur hexa de l'identification id sur le can bus

//==========
// Servo
//==========
#define SERVOMIN 100  // This is the 'minimum' pulse length count (out of 4096)
#define SERVOMAX 500  // This is the 'maximum' pulse length count (out of 4096)
int velocidad = 450;  // Velocidad du mouvement
// variables pour le servo moteur
int neutre;  // position neutre
int maxi;
int mini;
int servo;  // numero
