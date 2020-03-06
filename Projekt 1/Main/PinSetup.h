// Defining BME 280-pins
#define BME_SCK 13
#define BME_MISO 12
#define BME_MOSI 11
#define BME_CS 10
unsigned long time_now = 0;
unsigned long time_nowA = 0;
unsigned long time_nowB1 = 0;
unsigned long time_nowB2 = 0;
int period = 400;
int periodA = 2000;
int periodB1 = 600000;
int periodB2 = 300000;

// ButtonState
int buttonState = 0;         // variable for reading the pushbutton status
const int buttonPin = 2;     // the number of the pushbutton pin
int n = 1; // even or odd
