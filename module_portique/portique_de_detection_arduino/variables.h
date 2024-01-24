//========================================================
// Controls supression of the MonPrintf function to serial
//========================================================
#define SERIAL_BAUD 9600   // vitesse moniteur serie
#define SerialMonitor   1
#define DEBUG 1  // true for use Display log message if True

//==========================================
// Affectation des broches de l'arduino uno
//==========================================
#define ledsBlanches_1 8   // leds pour la lecture de la couleur du tsc3200 n°1
#define ledsBlanches_2 19  // leds pour la lecture de la couleur du tsc3200 n°2

//================================
// TCS3200 detecteur couleurs n° 1
//================================
/*  Pinout: 
 *      TCS3200   |     Arduino   
 *  ------------------------------------
 *      VCC       |     5V
 *      GND       |     GND
 *      OE        |     D
 *      S0        |     D3
 *      S1        |     D4
 *      S2        |     D5
 *      S3        |     D6
 *      OUT       |     D7
 */
#define S0_1 3
#define S1_1 4
#define S2_1 5
#define S3_1 6
#define sensorOut_1 7

//================================
// TCS3200 detecteur couleurs n° 2
//================================
#define S0_2 18
#define S1_2 17
#define S2_2 16
#define S3_2 15
#define sensorOut_2 14
// Declares the number of colors the program can recognise (number of calibrated colors)
#define num_of_colors 7 
int red, green, blue;

//==========
// Sensor IR
//==========
#define IRSensor  9 // connect IR sensor module to Arduino pin D9
bool sensor_ir = 0;            // variable pour l'etat actuel
bool sensor_ir_mem = 0;        // variable pour l'etat precedent

//==========================================
// Affectation des broches de l'arduino uno
// Association du CS du CAN MCP2515
//==========================================
#define mcp2515CSPin  10  // cs chip select du circuit mcp2515
char  caractere = '0';    // lecture can
int  id = 0x0;            // valeur hexa de l'identification id sur le can bus

//================
// bus can mcp2515
//================
const int SPI_CS_PIN = 10;  // CS du shield mcp2515



