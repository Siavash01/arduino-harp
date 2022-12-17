#define IRPin 2
#define model 1080

int distance;
int a = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

}

void loop() {
  for (int i = 0; i < 5; ++i) {
    distance = distance + analogRead(IRPin);
    delay(100);
  }
  distance = (int) distance / 5;
  Serial.println( distance );
  distance < 1300 ? a = 0 : a = 1;
  //distance = analogRead(IRPin);

  Serial.println( a );
  //delay(500);
}
