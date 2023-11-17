#include "mybutton.h"


MyButton::MyButton(byte b0, byte b1, byte b2, byte b3, byte b4) {
  add(b0); add(b1); add(b2); add(b3); add(b4); 
}

MyButton::MyButton(byte b0, byte b1, byte b2, byte b3) {
  add(b0); add(b1); add(b2); add(b3); 
}

MyButton::MyButton(byte b0, byte b1, byte b2) {
  add(b0); add(b1); add(b2); 
}

MyButton::MyButton(byte b0, byte b1) {
  add(b0); add(b1); 
}

MyButton::MyButton(byte b0) {
  add(b0);
}

MyButton::MyButton() {
}


void MyButton::flush() {
  prevbtn = 0;
  emit = true;
  retval = 0;
  prevtime = millis();
}


bool MyButton::add(byte button) {
  if (cnt == MAX_BUTTONS)
    return false;

  buttons[cnt++] = button;
  return true;
}


void MyButton::begin() {
  for (int c = 0; c < cnt; c++) {
    // Serial.printf("pin%d ", buttons[c]);
    pinMode(buttons[c], INPUT_PULLUP);
  }
  flush();
}

int MyButton::peek() {
  loop();
  return retval;
}


int MyButton::get() {
  loop();
  int r = retval;
  retval = 0;
  return r;
}


int MyButton::count() {
  return cnt;
}


void MyButton::loop() {
  uint16_t button = 0;
  uint16_t bitval = 1;
  unsigned long btntime = millis();

  for (int c = 0; c < cnt; bitval <<= 1, c++)
    button |= digitalRead(buttons[c]) ? 0 : bitval;

  // Serial.printf("key%d ", button);
  
  if (prevbtn == button) {
    if ((btntime - prevtime > BTN_REPT_TIME) && !emit && button) {
      // Serial.printf("reptkey%d ", button);
      if (!retval) retval = button | BTN_REPT_PRESS;
      prevtime = btntime;
      return;
    }
    if ((btntime - prevtime > BTN_LONG_TIME) && emit && button) {
      // Serial.printf("longkey%d ", button);
      if (!retval) retval = button | BTN_LONG_PRESS;
      prevtime = btntime;
      emit = false;
      return;
    }
    return;
  }

  if ((btntime - prevtime > BTN_DBNC_TIME) && emit && prevbtn) {
    // Serial.printf("shortkey%d ", prevbtn);
    if (!retval) retval = prevbtn;
  }
  emit = true;
  prevbtn = button;
  prevtime = btntime;
}
