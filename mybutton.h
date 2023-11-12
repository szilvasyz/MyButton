#ifndef _MYBUTTON_H_
#define _MYBUTTON_H_

#include <Arduino.h>


#define MAX_BUTTONS 14
#define BTN_LONG_PRESS (1<<14)
#define BTN_REPT_PRESS (1<<15)

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
    uint8_t buttons[MAX_BUTTONS + 1];
    uint16_t prevbtn = 0;
    uint16_t button;
    bool emit;
    int retval;
    unsigned long prevtime;
    
    void init();
    void loop();
    
  public:
    MyButton::MyButton();
    bool add(byte button);
    int count();
    void begin();
    int peek();
    int get();
};

#endif
