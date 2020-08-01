/* this code is intended for atmega328 running at 3.3v 8Mhz */

uint16_t counter = 0;
uint16_t interval = 4000;
uint32_t t = 0;
uint32_t t_s = 0;

void setup() {
  DDRB = DDRB | 0b11111111;   // set PB7~0 as output
  PORTB = 0b11011111;         // set PB7~0 HIGH, except PB5/D13/LED
  
  Serial.begin(9600);
}

void loop() {
  t = micros();
  
  if (t - t_s >= interval) {
    if (Serial.available() > 0) {
      uint8_t command = Serial.read();
      counter = 0;
      send_command(command);
    }

    if (counter <= 5) {
      counter ++;               // increment counter if there's no serial data
    }                          
    else {
      PORTB = 0b11011111;       // reset all pins to HIGH after 5 loops
    }
    
    t_s = t;                    // update t_s
  }
}

void send_command(uint8_t x) {
  /* PB5 is set HIGH in call cases except default, thus giving visual indication when there's data coming */
  switch (x) {
     case '1': 
      PORTB = 0b11111011;  //forward 
      break;
     case '0': 
      PORTB = 0b11110111;  //reverse
      break;
     case '3': 
      PORTB = 0b11111110;  //right
      break;
     case '2': 
      PORTB = 0b11111101;  //left
      break;
     case '7': 
      PORTB = 0b11111010;  //forward_right
      break;
     case '5': 
      PORTB = 0b11111001;  //forward_left
      break;
     case '6': 
      PORTB = 0b11110110;  //reverse_right
      break;
     case '4': 
      PORTB = 0b11110101;  //reverse_left
      break;
     default:
      PORTB = 0b11011111;  //reset
      break;
    }
}
