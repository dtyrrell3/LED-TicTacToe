#include <TouchSensor.h>

void setup() {
   Serial.begin(9600); 
}


void loop() {
//  for (int i = 2; i < 18; i++) {
//    TouchSensor sensor(3, i, i - 1);
//    while (!sensor.touched()) {
//      Serial.print("Waiting for sensor ");
//      Serial.println(i - 1);
//    }
//  Serial.println("Sensor was touched");
//  }


//  for (int i = 2; i < 18; i++) {
//     TouchSensor sensor(4, i, i - 1);
//     if (sensor.touched()) {
//        Serial.print("Sensor ");
//        Serial.print(i);
//        Serial.println(" was touched.");
//     }
//  }

  TouchSensor touchSensorArray[16];
  touchSensorArray[0].initializeWithParams(4, 17, 0);
  for(int i = 1; i < 16; i++) {
     touchSensorArray[i].initializeWithParams(4, i + 1, i);
  }
  for(int i = 0; i < 16; i++) {
     if(touchSensorArray[i].touched()) {
        Serial.print("Sensor "); 
        Serial.print(i);
        Serial.println(" was touched.");
     }
  }
}

