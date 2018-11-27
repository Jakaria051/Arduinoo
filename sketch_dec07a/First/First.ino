int led = 13;
int message;

void setup() {
 
  pinMode(led,OUTPUT);
  Serial.begin(9600);
}

void loop(){

if (Serial.available() > 0){
  message = Serial.read();

if (message == '1') {
  digitalWrite(led,HIGH);
}
  
 else if (message == '2'){
  digitalWrite(led,LOW);
 }
}
}

