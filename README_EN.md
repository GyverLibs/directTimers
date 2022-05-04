This is an automatic translation, may be incorrect in some places. See sources and examples!

#directTimers
Library for advanced manual control of ATMega2560, ATMega328, ATMega32u4 timers
- Library functions allow you to access all the features and modes of working with timers / counters + watchdog interrupts
- Nothing has been truncated or simplified, all the functionality described in the datasheet is available

### Compatibility
ATMega2560, ATMega328, ATMega32u4

### Documentation
The library has [extended documentation](https://alexgyver.ru/directTimers/)

## Content
- [Install](#install)
- [Initialization](#init)
- [Usage](#usage)
- [Example](#example)
- [Versions](#versions)
- [Bugs and feedback](#feedback)

<a id="install"></a>
## Installation
- The library can be found under the name **directTimers** and installed via the library manager in:
    - Arduino IDE
    - Arduino IDE v2
    - PlatformIO
- [Download library](https://github.com/GyverLibs/directTimers/archive/refs/heads/main.zip) .zip archive for manual installation:
    - Unzip and put in *C:\Program Files (x86)\Arduino\libraries* (Windows x64)
    - Unzip and put in *C:\Program Files\Arduino\libraries* (Windows x32)
    - Unpack and put in *Documents/Arduino/libraries/*
    - (Arduino IDE) automatic installation from .zip: *Sketch/Include library/Add .ZIP library…* and specify the downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE% D0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)

<a id="init"></a>
## Initialization
Not

<a id="usage"></a>
## Usage
```cpp
// n - timer number (0, 1 or 2)
void TIMERn_COMPA_attachInterrupt(void (*isr)());
void TIMERn_COMPB_attachInterrupt(void (*isr)());
void TIMERn_COMPA_detachInterrupt(void);
void TIMERn_COMPB_detachInterrupt(void);
void TIMERn_setClock(byte clk);
void TIMERn_setMode(byte mode);
void TIMERn_COMPA_mode(byte mode);
void TIMERn_COMPB_mode(byte mode);
byte TIMERn_getCounter(void);
void TIMERn_setCounter(byte value);
void TIMERn_COMPA_setValue(byte value);
void TIMERn_COMPB_setValue(byte value);

// watchdog interrupts
void WDT_attachInterrupt(void (*isr)(),int prescaler);
void WDT_detachInterrupt(void);

/* constants for TIMERn_clock() */
STOPPED // clock will be stopped, the timer is "frozen"
EXTERNAL_FALLING // clocking by an external clock up to 8 MHz on a fall
EXTERNAL_RISING // clocking by an external clock up to 8 MHz on the front

// divisors
PRESCALER_1
PRESCALER_8
PRESCALER_32
PRESCALER_64
PRESCALER_128
PRESCALER_256
PRESCALER_1024

/* constants for setting the mode of operation of timers */
STANDARD_MODE // timer counts up to 255 and resets to 0, (maybe up to 511/1023 for timer 1)
CTC_MODE // the timer counts from 0 to the number set by the TIMERn_COMPA_setValue() function, after which it is reset (at this moment it may cause an interrupt)
FAST_PWM_8BIT // hardware PWM 8 bit
FAST_PWM_9BIT // for timer 1
FAST_PWM_10BIT

// shim with correction
PHASECORRECT_PWM_8BIT
PHASECORRECT_PWM_9BIT
PHASECORRECT_PWM_10BIT
FAST_PWM_CUSTOM // PWM with custom depth, depth is set by TIMER0/2_COMPA_setValue() and TIMER1_setTop();
PHASECORRECT_PWM_CUSTOM // same but with correction

/* constants for controlling hardware outputs from timers */
DISABLE_COMP // output disabled from leg, leg can be used
NORM_PWM// output generates PWM >>> +5V on timer reset, 0V on match
INVERT_PWM // output generates inverted PWM >>> 0V on timer reset, +5V on match
TOGGLE_PIN // output generates a square wave >>> invert pin state on match
```

<a id="example"></a>
## Example
See **examples** for other examples!
```cpp
#include <directTimers.h>

/* example of generating a PWM with the selected frequency on timer 1
  the formula for calculating the account limit is given in the cheat sheet README */

/*
  For FAST PWM mode >>> top = (Ftimer/Fpm)-1;
  For PHASECORRECT PWM mode >>> top = Ftimer/(2*Fpm);
*/

// let the PWM frequency be 25 kHz in phase correction mode >>> top = 8000000/25000 >>> top = 320;

void setup() {
  pinMode(9, 1); // set up channel A as an output
  pinMode(10, 1); // set channel B as output

  TIMER1_setClock(PRESCALER_1); // set the timer to the maximum frequency
  TIMER1_setMode(PHASECORRECT_PWM_CUSTOM); // enable custom account limit mode
  TIMER1_setTop(320); // set count limit to 320 to get 25kHz with phase correction
  TIMER1_COMPA_mode(NORM_PWM); // set hardware outputs from timer to PWM mode
  TIMER1_COMPB_mode(NORM_PWM);
}

void loop() {
  int dutyA = map(analogRead(A0), 0, 1023, 0, 320); // recalculate the potentiometer range to the timer range 0...top >>> 0...320
  int dutyB = map(analogRead(A1), 0, 1023, 0, 320);

  TIMER1_COMPA_setValue(dutyA); // set output A to fill with potentiometer (pin 9)
  TIMER1_COMPB_setValue(dutyB); // (pin 10)
}

```

<a id="versions"></a>
## Versions
- v1.0

<a id="feedback"></a>
## Bugs and feedback
When you find bugs, create an **Issue**, or better, immediately write to the mail [alex@alexgyver.ru](mailto:alex@alexgyver.ru)
The library is open for revision and your **Pull Request**'s!