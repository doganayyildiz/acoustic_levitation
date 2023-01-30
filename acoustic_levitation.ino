byte TP = 0b10101010; // Every other port receives the inverted signal
void setup() {
  DDRC = 0b11111111; // Set all analog ports to be outputs
  
  // Initialize Timer1
  noInterrupts(); // Disable interrupts
  
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1 = 0;
  OCR1A = 200; // Set compare register (16MHz / 200 = 80kHz square wave -> 40kHz full wave)
  
  TCCR1B |= (1 << WGM12); // CTC mode
  TCCR1B |= (1 << CS10); // Set prescaler to 1 ==> no prescaling
  TIMSK1 |= (1 << OCIE1A); // Enable compare timer interrupt
  
  interrupts(); // Enable interrupts
}
ISR(TIMER1_COMPA_vect) {
  PORTC = TP; // Send the value of TP to the outputs
  TP = ~TP; // Invert TP for the next run
}
void loop() {
  // Nothing left to do here :)
}
