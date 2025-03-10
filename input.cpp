#include <Arduino.h>
#include "input.h"
#include "constants.h"

#ifdef USE_INPUT_PULLUP
#define INPUT_MODE INPUT_PULLUP
#define INPUT_STATE 0
#else
#define INPUT_MODE INPUT
#define INPUT_STATE 1
#endif

#ifdef SNES_CONTROLLER
uint16_t buttons = 0;

void input_setup()
{
  // Set DATA_CLOCK normally HIGH
  pinMode(DATA_CLOCK, OUTPUT);
  digitalWrite(DATA_CLOCK, HIGH);

  // Set DATA_LATCH normally LOW
  pinMode(DATA_LATCH, OUTPUT);
  digitalWrite(DATA_LATCH, LOW);

  // Set DATA_SERIAL normally HIGH
  pinMode(DATA_SERIAL, OUTPUT);
  digitalWrite(DATA_SERIAL, HIGH);
  pinMode(DATA_SERIAL, INPUT);
}

void getControllerData(void)
{
  // Latch for 12us
  digitalWrite(DATA_LATCH, HIGH);
  delayMicroseconds(12);
  digitalWrite(DATA_LATCH, LOW);
  delayMicroseconds(6);
  buttons = 0;
  // Retrieve button presses from shift register by pulling the clock high for 6us
  for (uint8_t i = 0; i < 16; ++i)
  {
    digitalWrite(DATA_CLOCK, LOW);
    delayMicroseconds(6);
    buttons |= !digitalRead(DATA_SERIAL) << i;
    digitalWrite(DATA_CLOCK, HIGH);
    delayMicroseconds(6);
  }
}

bool input_left()
{
  return buttons & LEFT;
};

bool input_right()
{
  return buttons & RIGHT;
};

bool input_up()
{
  return buttons & UP;
};

bool input_down()
{
  return buttons & DOWN;
};

bool input_fire()
{
  return buttons & Y;
};

bool input_start()
{
  return buttons & START;
}
#else

void input_setup()
{
  pinMode(K_FIRE, INPUT_MODE);
}

bool input_left()
{
  return map(analogRead(27), 0, 1023, 0, 255) <= (XAXIS_BASE_VALUE - XAXIS_VARIATION_VALUE);
};

bool input_right()
{
  return map(analogRead(27), 0, 1023, 0, 255) >= (XAXIS_BASE_VALUE + XAXIS_VARIATION_VALUE);
};

bool input_up()
{
  return map(analogRead(26), 0, 1023, 0, 255) >= (XAXIS_BASE_VALUE + XAXIS_VARIATION_VALUE);
};

bool input_down()
{
  return map(analogRead(26), 0, 1023, 0, 255) >= (XAXIS_BASE_VALUE + XAXIS_VARIATION_VALUE);
};

bool input_fire()
{
  return digitalRead(K_FIRE) == INPUT_STATE;
};
#endif
