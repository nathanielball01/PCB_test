/*
 * @file
 *
 * \brief  Interface for ESP native GPIOs
 */

#include "esp_gpio_interface.hpp"
#include <Arduino.h>


bool EspGpioInterface::set_channel_mode(int channel, ChannelMode channel_mode)
{
  switch (channel_mode) {
    case ChannelMode::INPUT_CHANNEL:
      pinMode(channel, INPUT);
      break;

    case ChannelMode::OUTPUT_CHANNEL:
      pinMode(channel, OUTPUT);
      break;

    case ChannelMode::INPUT_PULLUP_CHANNEL:
      pinMode(channel, INPUT_PULLUP);
      break;

    case ChannelMode::INPUT_PULLDOWN_CHANNEL:
      #ifdef ESP32
        pinMode(channel, INPUT_PULLDOWN);
      #else
        #warning "INPUT_PULLDOWN not supported"
      #endif
      break;
  }

  return true;
}


bool EspGpioInterface::write_channel_value(int channel, bool value)
{
  digitalWrite(channel, value);

  return true;
}


bool EspGpioInterface::read_channel_value(int channel, bool &value)
{
  return digitalRead(channel);
}
