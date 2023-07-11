/*
 * @file
 *
 * \brief  Interface for ESP native GPIOs
 */

#ifndef ESP_GPIO_INTERFACE_HPP
#define ESP_GPIO_INTERFACE_HPP

#include "gpio_interface.hpp"


/**
 * \brief  Handles native GPIOs from an ESP
 *
 * All booleans functions return whether the operation was successful, unless
 * specified otherwise
 */
class EspGpioInterface: public GpioInterface
{
  public:
    /// Sets the mode of a channel
    bool set_channel_mode(int channel, ChannelMode channel_mode) override;

    /// Writes the output value of a channel
    bool write_channel_value(int channel, bool value) override;

    /// Reads the output value of a channel
    bool read_channel_value(int channel, bool &value) override;
};


#endif
