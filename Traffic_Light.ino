/*Name: Tiwari Ramesh Sanjana
Date: 14-2-2024
Title: Implement Traffic Light
Output Requirements: 1. Consider 2 RGB LED , Pedestrian_RGB, Vehicle_RGB
2. Initial state  Pedestrian_RGB -> RED, Vehicle_RGB -> GREEN.
3. On key press  Pedestrian_RGB -> GREEN, Vehicle_RGB -> RED.
4. After 90 sec Pedestrian_RGB -> GREEN .
5. After  60 sec Vehicle_RGB -> YELLOW, after 30sec Vehicle_RGB -> GREEN.
*/

//Initialize LED's for vehicles and pedestrains as output pins
const int vehicleRedLedPin = 0;
const int vehicleGreenLedPin = 3;
const int vehicleYellowLedPin = 1;
const int pedestrianRedLedPin = 4;
const int pedestrianGreenLedPin = 5;

//Initialize pushbutton as input pin
const int buttonPin = 2;

//Define MACROS for traffic light states
#define VEHICLE_RED     0
#define VEHICLE_YELLOW  1
#define VEHICLE_GREEN   2
#define PEDESTRIAN_RED  3
#define PEDESTRIAN_GREEN 4

//Variables to keep track of switch state and time in second
int vehicleState = VEHICLE_GREEN;
int pedestrianState = PEDESTRIAN_RED;
bool buttonPress = false;
unsigned long buttonPressTime = 0;

void setup() {
  //Initialize all output LED's
  pinMode(vehicleRedLedPin, OUTPUT);
  pinMode(vehicleGreenLedPin, OUTPUT);
  pinMode(vehicleYellowLedPin, OUTPUT);
  pinMode(pedestrianRedLedPin, OUTPUT);
  pinMode(pedestrianGreenLedPin, OUTPUT);
  
  //Initialize traffic lights
  updateTrafficLights();
  
  //Initialize pushbutton as input
  pinMode(buttonPin, INPUT_PULLUP);
}

void loop() {
  //Check if the button is pressed
  if (digitalRead(buttonPin) == LOW && !buttonPress) {
    //Store time elapsed
    buttonPressTime = millis();
    //Change button press status to true
    buttonPress = true;
  }

  //Condition for traffic lights change state based on button press time
  unsigned long elapsedTime = millis() - buttonPressTime;
  if (buttonPress) {
    //1st case for 60 sec
    if (elapsedTime < 60000) {
      vehicleState = VEHICLE_RED;
      pedestrianState = PEDESTRIAN_GREEN;
    }
    //2nd case for next 30 sec
    else if (elapsedTime > 60000 && elapsedTime < 90000) { 
      vehicleState = VEHICLE_YELLOW;
      pedestrianState = PEDESTRIAN_GREEN;
    } 
    else {
      vehicleState = VEHICLE_GREEN;
      pedestrianState = PEDESTRIAN_RED;
      //Change button press state to false after end of loop
      buttonPress = false;
    }
    //Function call to change LED colors
    updateTrafficLights();
  }

  //Delay for smoother traffic light change
  delay(100);
  }

// Update the RGB LED's based on current traffic light states
void updateTrafficLights() {
  switch (vehicleState) {
    case VEHICLE_RED:
      digitalWrite(vehicleRedLedPin, HIGH);
      digitalWrite(vehicleGreenLedPin, LOW);
      digitalWrite(vehicleYellowLedPin, LOW);
    break;
    case VEHICLE_YELLOW:
      digitalWrite(vehicleRedLedPin, LOW);
      digitalWrite(vehicleGreenLedPin, LOW);
      digitalWrite(vehicleYellowLedPin, HIGH);
    break;
    case VEHICLE_GREEN:
      digitalWrite(vehicleRedLedPin, LOW);
      digitalWrite(vehicleGreenLedPin, HIGH);
      digitalWrite(vehicleYellowLedPin, LOW);
    break;
  }
  
  switch (pedestrianState) {
    case PEDESTRIAN_RED:
      digitalWrite(pedestrianRedLedPin, HIGH);
      digitalWrite(pedestrianGreenLedPin, LOW);
      break;
    case PEDESTRIAN_GREEN:
      digitalWrite(pedestrianRedLedPin, LOW);
      digitalWrite(pedestrianGreenLedPin, HIGH);
      break;
  }
}

