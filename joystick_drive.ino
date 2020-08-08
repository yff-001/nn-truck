/* declare global & volatile variables */
volatile bool flagA = false;

void setup() {
  DDRB |= 0b11111111;                   // set PB7~0 as output
  PORTB = 0b11011111;                   // set PB7~0 HIGH, except PB5/D13/LED
  
  init_timer0();
  Serial.begin(115200);
}

void loop() {
  static uint16_t counter = 0;          // static variables are initialized only once,
                                        // and retain values between function calls
  if (flagA) {
    if (Serial.available()) {
      uint8_t command = Serial.read();
      drive_command(command);

      counter = 0;                      // start/reset counter
    }

    if (counter < 5) {
      counter ++;                       // increment counter if there's no serial data
    }                          
    else {
      PORTB = 0b11011111;               // reset all pins to HIGH after 5 * 0.004s
    }
  }
}

ISR(TIMER0_COMPA_vect) {
    flagA = true;
}

void init_timer0() {
    cli();
    TCCR0A = 0;                         // clear register
    TCCR0B = 0;
    TCNT0 = 0;

    TCCR0A |= (1<<WGM01);               // turn on ctc mode
    TCCR0B |= (1<<CS02);                // clk/256
    OCR0A = 124;                        // count up to 124, yield p = 0.004s (clk=8000000)

    TIMSK0 |= (1<<OCIE0A);              // turn on output compare A match
    sei();
}

void drive_command(uint8_t x) {
  switch (x) {
     case '1': 
      PORTB = 0b11111011;               //forward 
      break;
     case '0': 
      PORTB = 0b11110111;               //reverse
      break;
     case '3': 
      PORTB = 0b11111110;               //right
      break;
     case '2': 
      PORTB = 0b11111101;               //left
      break;
     case '7': 
      PORTB = 0b11111010;               //forward_right
      break;
     case '5': 
      PORTB = 0b11111001;               //forward_left
      break;
     case '6': 
      PORTB = 0b11110110;               //reverse_right
      break;
     case '4': 
      PORTB = 0b11110101;               //reverse_left
      break;
     default:
      PORTB = 0b11011111;               //reset pins to HIGH
      break;
    }
}