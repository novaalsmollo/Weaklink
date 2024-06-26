
// Include Libraries
#include "Arduino.h"
#include "Keypad.h"
#include "Relay.h"
#include "SolenoidLock.h"


// Pin Definitions
#define KEYPADMEM3X4_PIN_ROW1	6
#define KEYPADMEM3X4_PIN_ROW2	7
#define KEYPADMEM3X4_PIN_ROW3	8
#define KEYPADMEM3X4_PIN_ROW4	9
#define KEYPADMEM3X4_PIN_COL1	3
#define KEYPADMEM3X4_PIN_COL2	4
#define KEYPADMEM3X4_PIN_COL3	5
#define RELAYMODULE_PIN_SIGNAL	10
#define SOLENOIDLOCK_PIN_GND	2



//Variables and defines
//Use this array to map out keys to favoured prfrence
chart keypadmem 3x4keys[ROWS][COLS] = {
{'1','2','3'},
{'4','5','6'},
{'7','8','9'},
{'*','0','#'}
};
// Initialization
Keypad keypadmem3x4(KEYPADMEM3X4_PIN_COL1,KEYPADMEM3X4_PIN_COL2,KEYPADMEM3X4_PIN_COL3,KEYPADMEM3X4_PIN_ROW1,KEYPADMEM3X4_PIN_ROW2,KEYPADMEM3X4_PIN_ROW3,KEYPADMEM3X4_PIN_ROW4);
Relay relayModule(RELAYMODULE_PIN_SIGNAL);
SolenoidLock solenoidLock(SOLENOIDLOCK_PIN_GND);


// define vars for testing menu
const int timeout = 10000;       //define timeout of 10 sec
char menuOption = 0;
long time0;

// Setup the essentials for your circuit to work. It runs first every time your circuit is powered with electricity.
void setup() 
{
    // Setup Serial which is useful for debugging
    // Use the Serial Monitor to view printed messages
    Serial.begin(9600);
    while (!Serial) ; // wait for serial port to connect. Needed for native USB
    Serial.println("start");
    
    //Initialize the keypad with selected key map
    keypadmem3x4.begin(keypadmem3x4keys);
    menuOption = menu();
    
}

// Main logic of your circuit. It defines the interaction between the components you selected. After setup, it runs over and over again, in an eternal loop.
void loop() 
{
    
    
    if(menuOption == '1') {
    // Membrane 3x4 Matrix Keypad - Test Code
    //Read keypad
    char keypadmem3x4Key = keypadmem3x4.getKey();
    if (isDigit(keypadmem3x4Key) ||  keypadmem3x4Key == '*' ||  keypadmem3x4Key == '#')
    {
    Serial.print(keypadmem3x4Key);
    }
    }
    else if(menuOption == '2') {
    // Relay Module - Test Code
    // The relay will turn on and off for 500ms (0.5 sec)
    relayModule.on();       // 1. turns on
    delay(500);             // 2. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    relayModule.off();      // 3. turns off.
    delay(500);             // 4. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    }
    else if(menuOption == '3') {
    // Lock-style Solenoid 12VDC - Test Code
    // The solenoid lock will turn on and off for 500ms (0.5 sec)
    solenoidLock.on(); // 1. turns on
    delay(500);       // 2. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.
    solenoidLock.off();// 3. turns off
    delay(500);       // 4. waits 500 milliseconds (0.5 sec). Change the value in the brackets (500) for a longer or shorter delay in milliseconds.

    }
    
    if (millis() - time0 > timeout)
    {
        menuOption = menu();
    }
    
}



// Menu function for selecting the components to be tested
// Follow serial monitor for instrcutions
char menu()
{

    Serial.println(F("\nWhich component would you like to test?"));
    Serial.println(F("(1) Membrane 3x4 Matrix Keypad"));
    Serial.println(F("(2) Relay Module"));
    Serial.println(F("(3) Lock-style Solenoid 12VDC"));
    Serial.println(F("(menu) send anything else or press on board reset button\n"));
    while (!Serial.available());

    // Read data from serial monitor if received
    while (Serial.available()) 
    {
        char c = Serial.read();
        if (isAlphaNumeric(c)) 
        {   
            
            if(c == '1') 
    			Serial.println(F("Now Testing Membrane 3x4 Matrix Keypad"));
    		else if(c == '2') 
    			Serial.println(F("Now Testing Relay Module"));
    		else if(c == '3') 
    			Serial.println(F("Now Testing Lock-style Solenoid 12VDC"));
            else
            {
                Serial.println(F("illegal input!"));
                return 0;
            }
            time0 = millis();
            return c;
        }
    }
}
