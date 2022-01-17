int counter=2;
#define pin_13 13
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(pin_13,OUTPUT);
}

void loop() {
  if (counter==10){
    Serial.print(1);
  }
  else if (counter==50){
    Serial.print(0);
  }
  else{
        
  }
  // put your main code here, to run repeatedly:
  delay(1000);
  counter+=1;
}
