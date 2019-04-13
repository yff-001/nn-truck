int counter;
int interval = 4000; 
unsigned long startTime;

void setup() {
  DDRB = DDRB | 0b11111111;  // set all pins on port B as output, using operator 'bitwise or'
  PORTB = 0b11111111;        // set all pins on port B HIGH
  
  Serial.begin(9600);
}

void loop() {
  startTime = micros();
  
  if (Serial.available() > 0) {
    byte j = Serial.read();
    counter = 0;
    send_command(j);
  }

  if (counter <= 5) {
    counter ++;          // if no new command comes in, last command will be reset after 5 cycles
  }             
  else {
    PORTB = 0b11111111;  // reset all pins to HIGH
  }
  
  while (micros() - startTime < interval) {
                         // this makes sure main program loops every 4000 microseconds
  }
}

void send_command(char i){
  switch (i){
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
      PORTB = 0b11111111;  //reset
      break;
    }
}
