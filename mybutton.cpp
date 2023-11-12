#include "mybutton.h"


MyButton::MyButton() {
  buttons[0] = 0;
  init();
}


void MyButton::init() {
  prevbtn = 0;
  emit = true;
  retval = 0;
  prevtime = millis();
}


bool MyButton::add(byte button) {
  int c = count();
  if (c == MAX_BUTTONS)
    return false;

  buttons[c++] = button;
  buttons[c] = 0;
  return true;
}


int MyButton::count() {  
  int c = 0;
  while (buttons[c] != 0) c++;
  return c;
}


void MyButton::begin() {
  for (int c = 0; c < count(); c++) {
    // Serial.printf("pin%d ", buttons[c]);
    pinMode(buttons[c], INPUT_PULLUP);
  }
  init();
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


void MyButton::loop() {
  uint16_t button = 0;
  uint16_t bitval = 1;
  unsigned long btntime = millis();

  for (int c = 0; buttons[c] != 0; bitval <<= 1, c++)
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
