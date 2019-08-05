/****************************************************
 * Light Switch                                     *
 * Written by Billy Snyder for public domain        *
 *                                                  *
 * A simple program to test a serial connection     *
 * for use with test.py to test a basic tkinter GUI *
 *                                                  *
 * Setup:                                           *
 *  Put an LED in Arduino Pin 13 and ground         *
 *                                                  * 
 ****************************************************/


char light_status = '1';

void setup() {
  // Set pin 13 to output and start a serial connection
  pinMode(13, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  if(Serial.available() > 0)
  {
    //Store the serial data in a char.
    light_status = Serial.read();
    if(light_status == '1')
    {
      digitalWrite(13, HIGH);
    }

    else if(light_status == '0')
    {
      digitalWrite(13, LOW);
    }
  } 
}
