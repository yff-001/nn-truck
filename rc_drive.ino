int counter;
int interval = 4000;
unsigned long startTime;

void setup() {
  GPIOA->regs->CRL = 0x00003333;         // set PA0/PA1/PA2/PA3 as OUTPUT

  GPIOA->regs->ODR = 0b0000000000001111; // set PA0/PA1/PA2/PA3 pin HIGH
  
  Serial.begin(9600);
}

void loop() {
  startTime = micros();
  
  if (Serial.available() > 0) {
    char j = Serial.read(); // switch case takes int/char, Serial.read() returns first byte of serial data
    counter = 0;
    drive_command(j);
  }

  if (counter <= 5) {
    counter ++;             // if no new command is received, command is reset after 5 loops
  }             
  else {
    GPIOA->regs->ODR = 0b0000000000001111;  //reset all 4 pins to HIGH
  }
  
  while (micros() - startTime < interval) {
    // this makes sure main program loops every 4000 microseconds
  }
}

void drive_command(char i){
  switch (i){
     case '1': 
      GPIOA->regs->ODR = 0b0000000000001110;  //forward 
      break;
     case '0': 
      GPIOA->regs->ODR = 0b0000000000001101;  //reverse
      break;
     case '3': 
      GPIOA->regs->ODR = 0b0000000000001011;  //right
      break;
     case '2': 
      GPIOA->regs->ODR = 0b0000000000000111;  //left
      break;
     case '7': 
      GPIOA->regs->ODR = 0b0000000000001010;  //forward_right
      break;
     case '5': 
      GPIOA->regs->ODR = 0b0000000000000110;  //forward_left
      break;
     case '6': 
      GPIOA->regs->ODR = 0b0000000000001001;  //reverse_right
      break;
     case '4': 
      GPIOA->regs->ODR = 0b0000000000000101;  //reverse_left
      break;
     default:
      GPIOA->regs->ODR = 0b0000000000001111;  //reset
      break;
    }
}
