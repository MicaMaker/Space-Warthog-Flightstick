//Libraries
  #include <Joystick.h>

//FlightStick
  //Define FlightStick Input Pins
  #define joyAxisX A2 // Thumbstick X Axis (Roll)
  #define joyAxisY A3 // Thumbstick Y Axis (Pitch)
  #define joyAxisZ A1 // Thumbstick Z Axis (Twist)
  #define joyButton1 6 // Trigger
  #define joyButton2 5 // Thumb Button Left
  #define joyButton3 2 // Thumb Button Right
  #define joyButton4 0 // Index
  #define joyButton5 4 // Side Thumb
  #define joyButton6 3 // Pinky

  // Hat Switch Bottom Pins
  #define hatSwitch1_Up 10 
  #define hatSwitch1_Down 8
  #define hatSwitch1_Left 7
  #define hatSwitch1_Right 9
  // Hat Switch Top Pins
  #define hatSwitch2_Up 18
  #define hatSwitch2_Down 16
  #define hatSwitch2_Left 14
  #define hatSwitch2_Right 15

  int xAxis_ = 0;
  int yAxis_ = 0;
  int zAxis_ = 0;

  //Set Button Default States
  int lastButton1State = 0;
  int lastButton2State = 0;
  int lastButton3State = 0;
  int lastButton4State = 0;
  int lastButton5State = 0;
  int lastButton6State = 0;

  //Joystick(Joystick HID ID, Joystick Type, Button Count, Hat Switch Count, Include X, Include Y, Include Z,
  //  Include Rx, Include Ry, Include Rz, Include Rudder, Include Throttle, Include Accelerator, Include Brake, Include Steering)

  Joystick_ Joystick(0x15, JOYSTICK_TYPE_JOYSTICK, 6, 2, true, true, true, false, false, false, false, false, false, false, false);

  const bool initAutoSendState = true;


void setup() {
 
  // Button Inputs
  pinMode(joyButton1, INPUT_PULLUP);
  pinMode(joyButton2, INPUT_PULLUP);
  pinMode(joyButton3, INPUT_PULLUP);
  pinMode(joyButton4, INPUT_PULLUP);
  pinMode(joyButton5, INPUT_PULLUP);
  pinMode(joyButton6, INPUT_PULLUP);
  
  // Hat Switch Bottom Inputs
  pinMode(hatSwitch1_Up, INPUT_PULLUP);
  pinMode(hatSwitch1_Down, INPUT_PULLUP);
  pinMode(hatSwitch1_Left, INPUT_PULLUP);
  pinMode(hatSwitch1_Right, INPUT_PULLUP);
  // Hat Switch Top Inputs
  pinMode(hatSwitch2_Up, INPUT_PULLUP);
  pinMode(hatSwitch2_Down, INPUT_PULLUP);
  pinMode(hatSwitch2_Left, INPUT_PULLUP);
  pinMode(hatSwitch2_Right, INPUT_PULLUP);

  SPCR &= ~_BV(SPE); // Disable SPI if it's active
  Joystick.begin();
} 

void loop() {
  //Main
  xAxis_ = analogRead(joyAxisX);
  xAxis_ = map(xAxis_,0,1023,0,255);
  Joystick.setXAxis(xAxis_);

  yAxis_ = analogRead(joyAxisY);
  yAxis_ = map(yAxis_,1023,0,0,255);
  Joystick.setYAxis(yAxis_);
  
  const int deadzone = 15;  // Adjust as needed (0-255 scale)
  const int midPoint = 127; // Neutral position

  zAxis_ = analogRead(joyAxisZ);
  zAxis_ = map(zAxis_, 0, 1023, 0, 255);

  // Apply deadzone with smooth transition
  if (abs(zAxis_ - midPoint) < deadzone) {
    zAxis_ = midPoint; // Stay neutral inside deadzone
  } else {
    if (zAxis_ > midPoint) {
        zAxis_ = map(zAxis_, midPoint + deadzone, 255, midPoint, 255);
    } else {
        zAxis_ = map(zAxis_, midPoint - deadzone, 0, midPoint, 0);
    }
  }

  Joystick.setZAxis(zAxis_);


  //Button States
  int currentButton1State = !digitalRead(joyButton1);
  if (currentButton1State != lastButton1State){
  Joystick.setButton (0, currentButton1State);
  lastButton1State = currentButton1State;
  }
  int currentButton2State = !digitalRead(joyButton2);
  if (currentButton2State != lastButton2State){
  Joystick.setButton (1, currentButton2State);
  lastButton2State = currentButton2State;
  }
  int currentButton3State = !digitalRead(joyButton3);
  if (currentButton3State != lastButton3State){
  Joystick.setButton (2, currentButton3State);
  lastButton3State = currentButton3State;
  }
  int currentButton4State = !digitalRead(joyButton4);
  if (currentButton4State != lastButton4State){
  Joystick.setButton (3, currentButton4State);
  lastButton4State = currentButton4State;
  }
  int currentButton5State = !digitalRead(joyButton5);
  if (currentButton5State != lastButton5State){
  Joystick.setButton (4, currentButton5State);
  lastButton5State = currentButton5State;
  }
  int currentButton6State = !digitalRead(joyButton6);
  if (currentButton6State != lastButton6State){
  Joystick.setButton (5, currentButton6State);
  lastButton6State = currentButton6State;
  }

  // Read Hat Switch 1
  int hatSwitch1 = -1;
  if (!digitalRead(hatSwitch1_Up)) hatSwitch1 = 0;
  if (!digitalRead(hatSwitch1_Up) && !digitalRead(hatSwitch1_Right)) hatSwitch1 = 45;
  if (!digitalRead(hatSwitch1_Right)) hatSwitch1 = 90;
  if (!digitalRead(hatSwitch1_Down) && !digitalRead(hatSwitch1_Right)) hatSwitch1 = 135;
  if (!digitalRead(hatSwitch1_Down)) hatSwitch1 = 180;
  if (!digitalRead(hatSwitch1_Down) && !digitalRead(hatSwitch1_Left)) hatSwitch1 = 225;
  if (!digitalRead(hatSwitch1_Left)) hatSwitch1 = 270;
  if (!digitalRead(hatSwitch1_Up) && !digitalRead(hatSwitch1_Left)) hatSwitch1 = 315;

  Joystick.setHatSwitch(0, hatSwitch1);

  // Read Hat Switch 2
  int hatSwitch2 = -1;
  if (!digitalRead(hatSwitch2_Up)) hatSwitch2 = 0;
  if (!digitalRead(hatSwitch2_Up) && !digitalRead(hatSwitch2_Right)) hatSwitch2 = 45;
  if (!digitalRead(hatSwitch2_Right)) hatSwitch2 = 90;
  if (!digitalRead(hatSwitch2_Down) && !digitalRead(hatSwitch2_Right)) hatSwitch2 = 135;
  if (!digitalRead(hatSwitch2_Down)) hatSwitch2 = 180;
  if (!digitalRead(hatSwitch2_Down) && !digitalRead(hatSwitch2_Left)) hatSwitch2 = 225;
  if (!digitalRead(hatSwitch2_Left)) hatSwitch2 = 270;
  if (!digitalRead(hatSwitch2_Up) && !digitalRead(hatSwitch2_Left)) hatSwitch2 = 315;

  Joystick.setHatSwitch(1, hatSwitch2);

  // Polling Delay
  delay(10);

}
