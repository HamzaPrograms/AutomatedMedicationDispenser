/* 
 * APSC 101 Example Sketch
 * 
 * M.Malik for APSC 101, 10-Sep-2023
 * 
 * Example Sketch to interface with the Peristaltic Pump, LED and IR sensor.
 * 
 * The pump runs when an object is detected by the IR Sensor. 
 * 
 * !!! Must have the IR sensor connected on pin A0 as demonstrated in step 2 of Arduino Instrcutions. !!!
 *  
 */



#include <AFMotor.h>
#define IRpin A0
#define LEDpin A4

AF_DCMotor pump(4);
AF_DCMotor DCmotor(1);
#define pushButtonForwards A1
#define pushButtonBackwards A2
#define limitSwitch A3
bool pushButtonStateForwards = HIGH;
bool pushButtonStateBackwards = HIGH;
bool limitSwitchState = HIGH;
#include <Servo.h>
Servo Servo1;

int servo_pos = 0;
int num = 0;

int count = 0;  //initializing count variable for 5 vials


void setup() {
  Serial.begin(9600);
  Serial.println("Pump test!");
  pinMode(IRpin, INPUT);
  pinMode(LEDpin, OUTPUT);
  DCmotor.setSpeed(255);
  DCmotor.run(RELEASE);
  pinMode(pushButtonForwards, INPUT_PULLUP);
  pinMode(pushButtonBackwards, INPUT_PULLUP);
  pinMode(limitSwitch, INPUT_PULLUP);
  Servo1.attach(9);
}

void loop() {


  pushButtonStateForwards = digitalRead(pushButtonForwards);
  pushButtonStateBackwards = digitalRead(pushButtonBackwards);
  limitSwitchState = digitalRead(limitSwitch);
  if (pushButtonStateForwards == LOW) {
    Serial.println("forwards");
    DCmotor.run(FORWARD);
    
  }
  /* else if (pushButtonStateBackwards==LOW){   //never needed
    Serial.println("backwards");
    DCmotor.run(BACKWARD);
  } */
  else if (limitSwitchState == LOW) {
    return 0;
    //not nedded I don't think >>
    DCmotor.run(RELEASE);
    pump.run(RELEASE);
    Servo1.run(RELEASE);
  }

  if (!digitalRead(IRpin) && limitSwitchState == HIGH)  // Check to see if object detcted by IR -- !!! Note the direct passing of IR Value to the 'if' condition - An easier way to handle conditional inputs !!!
  {
    DCmotor.run(RELEASE);
    digitalWrite(LEDpin, HIGH);  // Turn on indicator LED

    Serial.println("Pumping");
    pump.run(FORWARD);   // Change between FORWARD or BACKWARD (all upper case,  Case sensitive) depending on what directon the liquid flows in the pump.
    pump.setSpeed(255);  // Set the speed of pump. Uses an 8 bit value, 255 = 100% speed.


    count++;  // Choose how long the pump should run, depending on how much volume to fill.



    if (count == 1) {  // On first vial, dispensing for 5000 ms
     delay(19900);
     pump.run(RELEASE);

      for (servo_pos = 180; servo_pos >= 0; servo_pos -= 1) {  //Dispensing mass 1st vial
        Servo1.write(180);
        delay(10);
        break;
      }
      for (servo_pos = 0; servo_pos <= 180; servo_pos += 1) {
        Servo1.write(0);
        delay(10);
        //break;
      }
      Servo1.write(90);

      
    } else if (count == 2) {  // On first vial, dispensing for 4000 ms
    delay(15900);
     pump.run(RELEASE);
    Servo1.write(0);
      
      for (servo_pos = 180; servo_pos >= 0; servo_pos -= 1) {  //Dispensing mass 1st vial
        Servo1.write(180);
        delay(10);
        break;
      }
      for (servo_pos = 0; servo_pos <= 180; servo_pos += 1) {
        Servo1.write(0);
        delay(10);
        //break;
      }
      Servo1.write(90);

    } else if (count == 3) { 
      delay(15900);
     pump.run(RELEASE);
     Servo1.write(0);

     for (servo_pos = 180; servo_pos >= 0; servo_pos -= 1) {  //Dispensing mass 1st vial
        Servo1.write(180);
        delay(10);
        break;
      }
      for (servo_pos = 0; servo_pos <= 180; servo_pos += 1) {
        Servo1.write(0);
        delay(10);
        //break;
      }
      for (servo_pos = 180; servo_pos >= 0; servo_pos -= 1) {  //Dispensing mass 1st vial
        Servo1.write(180);
        delay(10);
        break;
      }
      for (servo_pos = 0; servo_pos <= 180; servo_pos += 1) {
        Servo1.write(0);
        delay(10);
        //break;
      }
      Servo1.write(90);

      

    } else if (count == 4) {  // On first vial, dispensing for 2000 ms
      delay(15900);
     pump.run(RELEASE);

     Servo1.write(0);

     for (servo_pos = 180; servo_pos >= 0; servo_pos -= 1) {  //Dispensing mass 1st vial
        Servo1.write(180);
        delay(10);
        break;
      }
      for (servo_pos = 0; servo_pos <= 180; servo_pos += 1) {
        Servo1.write(0);
        delay(10);
        //break;
      }
      for (servo_pos = 180; servo_pos >= 0; servo_pos -= 1) {  //Dispensing mass 1st vial
        Servo1.write(180);
        delay(10);
        break;
      }
      for (servo_pos = 0; servo_pos <= 180; servo_pos += 1) {
        Servo1.write(0);
        delay(10);
        //break;
      }
      Servo1.write(90);


    } else {  // On first vial, dispensing for 1000 ms
      delay(15900);
     pump.run(RELEASE);
     Servo1.write(0);

      for (servo_pos = 180; servo_pos >= 0; servo_pos -= 1) {  //Dispensing mass 1st vial
        Servo1.write(180);
        delay(10);
        //break;
      }

      for (servo_pos = 0; servo_pos <= 180; servo_pos += 1) {  //Dispensing mass 2nd vial
        Servo1.write(0);
        delay(10);
        //break;
      }
      Servo1.write(90);
    }




    pump.run(RELEASE);          // Stop the pump
    digitalWrite(LEDpin, LOW);  // Turn LED off

    if (count == 5) {  // if statement to check if 5 vials have been dispensed
      return 0;
    }

    Serial.println("Done");
    DCmotor.run(FORWARD);
  }

  delay(10);
}
