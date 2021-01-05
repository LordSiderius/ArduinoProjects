int state = 0;
bool firstRun = LOW;
void setup() {
  //start serial connection

  //configure pin2 as an input and enable the internal pull-up resistor
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT_PULLUP);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  Serial.begin(9600);

}


void loop() {
  //read the pushbutton value into a variable
  int bO = digitalRead(7);
  delay(10);
  int bC = digitalRead(8);
  delay(10);
  int bS = digitalRead(4);
  delay(10);
  int gO = digitalRead(2);
  delay(10);
  int gC = digitalRead(3);
  delay(10);
  //bool sCd = LOW; // state closed state 1
  //bool sOg = LOW; // state opening state 2
  //bool sOd = LOW; //state opened state 3
  //bool sCg = LOW; // state closing state 4
  //bool sS  = LOW; // state reset state 0
  bool t1 = LOW;
  bool t2 = LOW;
  bool t3 = LOW;
  bool t4 = LOW;
  bool t5 = LOW;
  bool tS = LOW;
  bool eF = LOW;
  bool eB = LOW;
  float etime = 0;  


  //Init run
  if ((firstRun == LOW) && (!gC)){
    state = 1;
    firstRun = HIGH;
    }
  else if (firstRun == LOW) {
    firstRun = HIGH;
    state = 4;
    }

  t1 = ((state == 1) && bO);
  t2 = ((state == 2) && !gO);
  t3 = ((state == 3) && bC);
  t4 = ((state == 4) && !gC);
  t5 = ((state == 0) && bC);
  tS = bS;
  
  if (t1) {state = 2;}
  else if (t2) {state = 3;}
  else if (t3 || t5) {state = 4;}
  else if (t4) {state = 1;}
  else if (tS) {state = 0;}
  
      
  if (state == 1){
     eF = LOW;
     eB = LOW;
  }
  else if (state == 2){
    eF = HIGH;
    eB = LOW;
  }
  else if(state == 3){
    eF = LOW;
    eB = LOW;
  }
  else if(state == 4){
    eF = LOW;
    eB = HIGH;
  }
  else {
    eF = LOW;
    eB = LOW;
  }
  // Keep in mind the pullup means the pushbutton's
  // logic is inverted. It goes HIGH when it's open,
  // and LOW when it's pressed. Turn on pin 13 when the
  // button's pressed, and off when it's not:

    digitalWrite(5, eF);
    digitalWrite(6, eB);

    Serial.print("state: ");
    switch (state) {
    case 1:
      Serial.println("Zavreno");
      break;
    case 2:
      Serial.println("Otevirani");
      break;
    case 3:
    Serial.println("Otevreno");
      break;
    case 4:
    Serial.println("Zavirani");
      break;
    default:
      Serial.println("Stop");
      break;
    }
   /* Serial.println(state);
    Serial.print("bO: ");
    Serial.println(bO);
    Serial.print("bC: ");
    Serial.println(bC);
    Serial.print("gO: ");
    Serial.println(gO);
    Serial.print("gC: ");
    Serial.println(gC);
    Serial.print("bS: ");
    Serial.println(bS);
    Serial.print("fRun: ");
    Serial.println(firstRun);*/
 
  delay(100);
}
