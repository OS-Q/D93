#ifndef Btn_h
#define Btn_h

#if defined(ARDUINO) && ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <inttypes.h>


class Bounce
{
 public:


    Bounce();


/*!
    @brief  Attach to a pin and sets that pin's mode (INPUT, INPUT_PULLUP or OUTPUT).
            
    @param    pin
              The pin that is to be debounced.
    @param    mode
              A valid Arduino pin mode (INPUT, INPUT_PULLUP or OUTPUT).
*/
    void attach(int pin, int mode);

    /**
    Attach to a pin for advanced users. Only attach the pin this way once you have previously set it up. Otherwise use attach(int pin, int mode).
    */
    void attach(int pin);
    

    /**
    @brief  Sets the debounce interval in milliseconds.
            
    @param    interval_millis
    		The interval time in milliseconds.
     
     */
    void interval(uint16_t interval_millis);


/*!
    @brief   Updates the pin's state. 

    Because Bounce does not use interrupts, you have to "update" the object before reading its value and it has to be done as often as possible (that means to include it in your loop()). Only call update() once per loop().

    @return True if the pin changed state.
*/

    bool update();

    /**
     @brief Returns the pin's state (HIGH or LOW).

     @return HIGH or LOW.
     */
    bool read();

    /**
    @brief Returns true if pin signal transitions from high to low.
    */
    bool fell();

    /**
    @brief Returns true if pin signal transitions from low to high.
    */
    bool rose();

     
     /**
    @brief Deprecated (i.e. do not use). Included for partial compatibility for programs written with Bounce version 1
    */
    bool risingEdge() { return rose(); }
     /**
    @brief Deprecated (i.e. do not use). Included for partial compatibility for programs written with Bounce version 1
    */
    bool fallingEdge() { return fell(); }
     /**
    @brief Deprecated (i.e. do not use). Included for partial compatibility for programs written with Bounce version 1
    */
     Bounce(uint8_t pin, unsigned long interval_millis ) : Bounce() {
        attach(pin);
        interval(interval_millis);
    }
    
    /**
     @brief Returns the duration in milliseconds of the current state. 

     Is reset to 0 once the pin rises ( rose() ) or falls ( fell() ).
    
      @return The duration in milliseconds (unsigned long) of the current state.
     */

    unsigned long duration();

  /**
     @brief Returns the duration in milliseconds of the previous state. 

     Takes the values of duration() once the pin changes state.
    
      @return The duration in milliseconds (unsigned long) of the previous state. 
     */
    unsigned long previousDuration();     

 protected:
    unsigned long previous_millis;
    uint16_t interval_millis;
    uint8_t state;
    uint8_t pin;
    unsigned long stateChangeLastTime;
    unsigned long durationOfPreviousState;
    virtual bool readCurrentState() { return digitalRead(pin); }
    virtual void setPinMode(int pin, int mode) {
#if defined(ARDUINO_STM_NUCLEO_F103RB) || defined(ARDUINO_GENERIC_STM32F103C)
        pinMode(pin, (WiringPinMode)mode);
#else
        pinMode(pin, mode);
#endif
    }

  private:
    inline void changeState();
    inline void setStateFlag(const uint8_t flag)    {state |= flag;}
    inline void unsetStateFlag(const uint8_t flag)  {state &= ~flag;}
    inline void toggleStateFlag(const uint8_t flag) {state ^= flag;}
    inline bool getStateFlag(const uint8_t flag)    {return((state & flag) != 0);}
};

#endif
