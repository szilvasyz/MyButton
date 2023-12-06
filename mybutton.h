#ifndef _MYBUTTON_H_
#define _MYBUTTON_H_

#include <Arduino.h>


#define MAX_BUTTONS 14
#define BTN_LONG_PRESS (1<<14)
#define BTN_REPT_PRESS (1<<15)
#define BTN_BUTTONMASK ((1 << MAX_BUTTONS) - 1)

#ifndef BTN_DBNC_TIME
#define BTN_DBNC_TIME 50
#endif

#ifndef BTN_LONG_TIME
#define BTN_LONG_TIME 1000
#endif

#ifndef BTN_REPT_TIME
#define BTN_REPT_TIME 300
#endif

class MyButton {
  
  private:
    uint8_t buttons[MAX_BUTTONS + 1] = {};
    uint8_t cnt = 0;
    uint16_t prevbtn = 0;
    uint16_t button;
    bool emit = true;
    int retval = 0;
    unsigned long prevtime = millis();
    unsigned long debouncetime = BTN_DBNC_TIME;
    unsigned long longpresstime = BTN_LONG_TIME;
    unsigned long repeatedpresstime = BTN_REPT_TIME;
    
    
    void loop();
    
  public:
    MyButton();
    MyButton(byte b0);
    MyButton(byte b0, byte b1);
    MyButton(byte b0, byte b1, byte b2);
    MyButton(byte b0, byte b1, byte b2, byte b3);
    MyButton(byte b0, byte b1, byte b2, byte b3, byte b4);
    void flush();
    bool add(byte button);
    void begin();
    int peek();
    int get();
    int count();
    void setDebounceTime(int t);
    void setLongPressTime(int t);
    void setRepeatedPressTime(int t);
    
};

#endif
