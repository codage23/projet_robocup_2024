//=========
// Controls
//=========
#define SERIAL_BAUD 9600  // vitesse moniteur serie

//========================================================
// Differentes fonctions du programme
//========================================================
#define debug 1      // for use Display log message if True

//==========================================
// Affectation des broches de l'arduino uno
// Association du CS du CAN MCP2515
//==========================================
#define mcp2515CSPin  10  // cs du circuit mcp2515

//========================
// for non-bloking delays
//========================
unsigned long nextTime;   // For non-blocking delays

//================
// bus can mcp2515
//================
const int SPI_CS_PIN = 10;  // CS du shield mcp2515

//==========
// Variables
//==========
char  caractere = '0';     // lecture can
int  id = 0x0;             // valeur hexa de l'identification id sur le can bus

//==========
// afficheur
//==========
// si debug activé alors la memoire le l'arduino est trop petite , il faut mettre un seul panneau donc 256 leds
#define NUM_LEDS 256   // ----- Allumer une LED en particulier ------------------------------
#define NUM_LIGNE 16   // nombre de lignes
#define NUM_COLONNE 16  // nombre de colonnes


// nombre de leds par panneau 256 leds 16x16
#define DATA_PIN_ARDUINO 9      // broche arduino
#define COLOR_ORDER         GRB
#define CHIPSET             WS2812B
// initial matrix layout (to get led strip index by x/y)
#define MATRIX_WIDTH        16
#define MATRIX_HEIGHT       16
#define MATRIX_TYPE         VERTICAL_ZIGZAG_MATRIX
#define MATRIX_SIZE         (MATRIX_WIDTH*MATRIX_HEIGHT)
#define NUMPIXELS           MATRIX_SIZE
#define pause 300
