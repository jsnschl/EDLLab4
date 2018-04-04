/*
ECEN2830 motor position control example (left wheel only)
*/

// define pins
const int pinON = 6;         // connect pin 6 to ON/OFF switch, active HIGH

const int pinCW_Left = 7;    // connect pin 7 to clock-wise PMOS gate
const int pinCC_Left = 8;    // connect pin 8 to counter-clock-wise PMOS gate
const int pinSpeed_Left = 9; // connect pin 9 to speed reference

int distance = 0;
int degree = 0;


const int pinCW_Right = 11;    // connect pin 11 to clock-wise PMOS gate
const int pinCC_Right = 12;    // connect pin 12 to counter-clock-wise PMOS gate
const int pinSpeed_Right = 10; // connect pin 10 to speed reference

int err = 215; //This is 1 inch too far try 210-230

// encoder counter variable
volatile int enc_count_Left = 0; // "volatile" means the variable is stored in RAM
volatile int enc_count_Right = 0; 

// setup pins and initial values
void setup() {
  pinMode(pinON,INPUT);
  pinMode(pinCW_Left,OUTPUT);
  pinMode(pinCC_Left,OUTPUT);
  pinMode(pinSpeed_Left,OUTPUT);
  pinMode(13,OUTPUT);             // on-board LED
  digitalWrite(13,LOW);           // turn LED off
  digitalWrite(pinCW_Left,LOW);   // stop clockwise
  digitalWrite(pinCC_Left,LOW);   // stop counter-clockwise
  analogWrite(pinSpeed_Left,70);  // set speed reference, duty-cycle = 50/255
  digitalWrite(pinON,HIGH);

  
  pinMode(pinCW_Right,OUTPUT);
  pinMode(pinCC_Right,OUTPUT);
  pinMode(pinSpeed_Right,OUTPUT);
  digitalWrite(pinCW_Right,LOW);   // stop clockwise
  digitalWrite(pinCC_Right,LOW);   // stop counter-clockwise
  analogWrite(pinSpeed_Right,70);  // set speed reference, duty-cycle = 50/255
   
  /* 
    Connect left-wheel encoder output to pin 2 (external Interrupt 0) via a 1k resistor
    Rising edge of the encoder signal triggers an interrupt 
    count_Left is the interrupt service routine attached to Interrupt 0 (pin 2)
  */
  attachInterrupt(0, count_Left, RISING);
  attachInterrupt(1, count_Right, RISING); 
}

/*
  Interrupt 0 service routine
  Increment enc_count_Left on each rising edge of the 
  encoder signal connected to pin 2
*/ 
void count_Left(){
  enc_count_Left++;
}


void count_Right(){
  enc_count_Right++;
}


void loop() {
  do {
    enc_count_Left = 0;                     // reset encoder counter to 0
    enc_count_Right = 0;                  // encoder reset RIGHT *****
  } while (digitalRead(pinON) == LOW);      // wait for ON switch
  forward(2);
  /*
  digitalWrite(13,HIGH);                    // turn LED on
  //Forward (currently left)
  digitalWrite(pinCW_Left,HIGH);            // go clockwise
  do {} while (enc_count_Left < 3*12*64);   // do nothing until wheel makes 3 rotations
  digitalWrite(pinCW_Left,LOW);             // stop
  digitalWrite(13,LOW);                     // turn LED off
  delay(1000);                              // wait 1 second
  int onoff_switch = digitalRead(pinON);   // read switch on/off state
  Serial.println(onoff_switch);            // send value as ASCII-encoded decimal 
  delay(500);                              // wait 0.5 seconds
  */
}

int forward(char distance){
  int d = (distance/0.0017)-err ;                 // d = distance in ft * ft to cm conversion
  digitalWrite(pinCC_Left,HIGH);
  digitalWrite(pinCW_Right,HIGH);            // go clockwise
  do {} while (enc_count_Left < d); //& enc_count_Right < d*12*64);   // do nothing until wheel makes d rotations
  digitalWrite(pinCC_Left,LOW);
  digitalWrite(pinCW_Right,LOW);// stop
  digitalWrite(13,LOW);                     // turn LED off
  delay(1000);                              // wait 1 second
  int onoff_switch = digitalRead(pinON);   // read switch on/off state
  Serial.println(onoff_switch);            // send value as ASCII-encoded decimal 
  delay(500);
  enc_count_Left = 0;                     // reset encoder counter to 0
  enc_count_Right = 0; 
}
int reverse(char distance){
  int d = distance/0.0017 ;
  digitalWrite(pinCW_Left,HIGH);
  digitalWrite(pinCC_Right,HIGH);            // go clockwise
  do {} while (enc_count_Left < d); //& enc_count_Right < d*12*64);   // do nothing until wheel makes d rotations
  digitalWrite(pinCW_Left,LOW);
  digitalWrite(pinCC_Right,LOW);// stop
  digitalWrite(13,LOW);                     // turn LED off
  delay(1000);                              // wait 1 second
  int onoff_switch = digitalRead(pinON);   // read switch on/off state
  Serial.println(onoff_switch);            // send value as ASCII-encoded decimal 
  delay(500);
  enc_count_Left = 0;                     // reset encoder counter to 0
  enc_count_Right = 0; 
}
int turn_left(char degree){
  int deg = degree/0.0006;
  digitalWrite(pinCC_Left,HIGH);
  digitalWrite(pinCC_Right,HIGH);            // go clockwise
  do {} while (enc_count_Left < deg); //& enc_count_Right < degree/0.0006);   // do nothing until wheel makes d rotations
  digitalWrite(pinCC_Left,LOW);
  digitalWrite(pinCC_Right,LOW);// stop
  digitalWrite(13,LOW);                     // turn LED off
  delay(1000);                              // wait 1 second
  int onoff_switch = digitalRead(pinON);   // read switch on/off state
  Serial.println(onoff_switch);            // send value as ASCII-encoded decimal 
  delay(500);
  enc_count_Left = 0;                     // reset encoder counter to 0
  enc_count_Right = 0; 
}
int turn_right(char degree){
  int deg = degree/0.0006;
  digitalWrite(pinCW_Left,HIGH);
  digitalWrite(pinCW_Right,HIGH);            // go clockwise
  do {} while (enc_count_Left < deg); //& enc_count_Right < degree/0.0006);   // do nothing until wheel makes d rotations
  digitalWrite(pinCW_Left,LOW);
  digitalWrite(pinCW_Right,LOW);// stop
  digitalWrite(13,LOW);                     // turn LED off
  delay(1000);                              // wait 1 second
  int onoff_switch = digitalRead(pinON);   // read switch on/off state
  Serial.println(onoff_switch);            // send value as ASCII-encoded decimal 
  delay(500);
  enc_count_Left = 0;                     // reset encoder counter to 0
  enc_count_Right = 0; 
}

