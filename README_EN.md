This is an automatic translation, may be incorrect in some places. See sources and examples!

# Directtimers
Library for expanded manual control of timer ATMEGA2560, Atmega328, Atmega32U4
- The functions of the library allow access to all capabilities and modes of working with timer/meters + Watchdog interruptions
- Nothing is cut and not simplified, all the functionality described in the Datite is available

## compatibility
Atmega2560, Atmega328, Atmega32u4

### Documentation
There is [expanded documentation] to the library (https://alexgyver.ru/directtimers/)

## Content
- [installation] (# Install)
- [initialization] (#init)
- [use] (#usage)
- [Example] (# Example)
- [versions] (#varsions)
- [bugs and feedback] (#fedback)

<a id="install"> </a>
## Installation
- The library can be found by the name ** Directtimers ** and installed through the library manager in:
    - Arduino ide
    - Arduino ide v2
    - Platformio
- [download library] (https://github.com/gyverlibs/directtimers/archive/refs/heads/main.zip). Zip archive for manual installation:
    - unpack and put in * C: \ Program Files (X86) \ Arduino \ Libraries * (Windows X64)
    - unpack and put in * C: \ Program Files \ Arduino \ Libraries * (Windows X32)
    - unpack and put in *documents/arduino/libraries/ *
    - (Arduino id) Automatic installation from. Zip: * sketch/connect the library/add .Zip library ... * and specify downloaded archive
- Read more detailed instructions for installing libraries [here] (https://alexgyver.ru/arduino-first/#%D0%A3%D1%81%D1%82%D0%B0%BD%D0%BE%BE%BE%BED0%B2%D0%BA%D0%B0_%D0%B1%D0%B8%D0%B1%D0%BB%D0%B8%D0%BE%D1%82%D0%B5%D0%BA)
### Update
- I recommend always updating the library: errors and bugs are corrected in the new versions, as well as optimization and new features are added
- through the IDE library manager: find the library how to install and click "update"
- Manually: ** remove the folder with the old version **, and then put a new one in its place.“Replacement” cannot be done: sometimes in new versions, files that remain when replacing are deleted and can lead to errors!


<a id="init"> </a>
## initialization
No

<a id="usage"> </a>
## Usage
`` `CPP
// n - timer number (0, 1 or 2)
VOID Timern_compa_attachinterrapt (VOID (*ISR) ());
VOID Timern_compb_attachinterrapt (VOID (*ISR) ());
VOID Timern_compa_detachinterrapt (VOID);
VOID Timern_compb_detachinterrapt (VOID);
VOID Timern_SetClock (Byte CLK);
VOID Timern_Setmode (Byte Mode);
VOID Timern_compa_mode (byte mode);
VOID Timern_compb_mode (byte mode);
Byte Timern_GetCounter (VOID);
VOID Timern_Setcounter (Byte Value);
VOID TIMERN_COMPA_SETVALUE (BYTE VALUE);
VOID Timern_compb_Setvalue (Byte Value);

// interruptions Watchdog
VOID WDT_ATTACHINTERRRUPT (VOID (*isr) (), Intscaler);
VOID WDT_DetachinterPT (VOID);

/ * Constants for Timern_Clock () */
Stopped // Tactting will be stopped, the timer is "frozen"
External_falling // Tacting by an external shock up to 8 MHz by decline
External_rising // Tacting by an external shock up to 8 MHz on the front

// divider
PressCaler_1
PressCaler_8
PressCaler_32
PressCaler_64
PressCaler_128
PressCaler_256
PressCaler_1024

/ * Constants for setting the operating mode of timers */
Standard_mode // Timer counts up to 255 and drops at 0, (maybe up to 511/1023 for Tymeasure 1)
CTC_Mode // Timer counts from 0 to the number specified by the function Timern_compa_Setvalue (), after which it is discarded (at that moment the interruption may cause)
FAST_PWM_8BIT // hardware shim 8 bits
FAST_PWM_9BIT // for timer 1
FAST_PWM_10BIT

// Shim with correction
PHASECORRECT_PWM_8BIT
PHASECORRECT_PWM_9BIT
PHASECORRECT_PWM_10BIT
Fast_pwm_custom // shim with custom depth, depth is set by Timer0/2_compa_Setvalue () and Timer1_Settop ();
Phasecorrect_pwm_custom // The same thing but with correction

/ * Constants to manage hardware outputs from timers */
Disable_comp // The output is disconnected from the leg, you can use your foot
Norm_PWM // The output generates shim >>> +5V when dumping the timer, 0V when coincided
INVERT_PWM // The output generates inverted PWM >>> 0V when a timer reset, +5V when coincided
Toggle_pin // Exit generates meandr >>> Inversion of the Ping state when coincided
`` `

<a id="EXAMPLE"> </a>
## Example
The rest of the examples look at ** Examples **!
`` `CPP
#include <Directtimers.h>

/* example of the generation of PWM with the selected frequency in timer 1
  The formula for the counting of the account limit is given in the Readme *checker

/*
  For FAST PWM >>> TOP = (FAMIRER/FUCH) -1;
  For the Phasecorrect PWM >>> Top = Fastimer/(2*Fam);
*/

// Let the frequency of Shim be 25 kHz in phase correction mode >>> top = 8000000/25000 >>> top = 320;

VOID setup () {
  Pinmode (9, 1);// setting the channel and as a way out
  Pinmode (10, 1);// setting the channel in as an output

  Timer1_SetClock (PRESCALER_1);// set the maximum frequency for the timer
  Timer1_Setmode (phasecorrect_pwm_custom);// Turn on the mode of the custom limit
  Timer1_Settop (320);// set the limit of account 320 to get a frequency of 25 kHz with phase correction
  Timer1_compa_mode (norm_pwm);// set up hardware outputs from the timer in the PWM mode
  Timer1_compb_mode (norm_pwm);
}

VOID loop () {
  intletya = map (analogread (a0), 0, 1023, 0, 320);// Counting the range of the potentiometer into the timer range 0 ... top >>> 0 ... 320
  intletyb = map (analogread (a1), 0, 1023, 0, 320);

  Timer1_compa_Setvalue (dutya);// Install at the output a by filling with a potentiometer (PIN 9)
  Timer1_compb_Setvalue (dutyb);// (PIN 10)
}

`` `

<a id="versions"> </a>
## versions
- V1.0

<a id="feedback"> </a>
## bugs and feedback
Create ** Issue ** when you find the bugs, and better immediately write to the mail [alex@alexgyver.ru] (mailto: alex@alexgyver.ru)
The library is open for refinement and your ** pull Request ** 'ow!


When reporting about bugs or incorrect work of the library, it is necessary to indicate:
- The version of the library
- What is MK used
- SDK version (for ESP)
- version of Arduino ide
- whether the built -in examples work correctly, in which the functions and designs are used, leading to a bug in your code
- what code has been loaded, what work was expected from it and how it works in reality
- Ideally, attach the minimum code in which the bug is observed.Not a canvas of a thousand lines, but a minimum code