#include "mybutton.h"

#define BT1_PIN 18
#define BT2_PIN 19

MyButton btn;


void setup() {
  Serial.begin(115200);
  Serial.printf("start: %d\n", btn.count());

  btn.add(BT1_PIN);
  Serial.printf("btn1: %d\n", btn.count());
  btn.add(BT2_PIN);
  Serial.printf("btn2: %d\n", btn.count());
  btn.begin();
  
  Serial.printf("begin: %d\n", btn.count());
}

void loop() {
  //btn.loop();
  if (btn.peek())
    Serial.printf("\n%d ", btn.get());

  delay(100);
}
