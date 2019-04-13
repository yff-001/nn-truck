char command; // switch case takes int/char, Serial.read() returns first byte of serial data
int counter;
int interval = 4000; // this makes sure main program loops every 4000 microseconds
unsigned long startTime;

void setup() {
  DDRB = DDRB | 0b11111111;  // set all pins on port B as output, using operator 'bitwise or'
  PORTB = 0b11111111;  // set all pins on port B HIGH
  
  Serial.begin(9600);
}

void loop() {
  startTime = micros();
  
  if (Serial.available() > 0) {
    command = Serial.read();
    counter = 0;
    send_command(command);
  }

  if (counter <= 5) {
    counter ++; // if serial data available, counter is reset, or first block of loop not excuted, counter value is retained 
  }             // after 5 main loops without serial data, command is reset. number determines how long command remains
  else {
    PORTB = 0b11111111;  //reset all pins to HIGH
  }
  
  while (micros() - startTime < interval) {
    // this holds main loop until 4000 microseconds passes
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
