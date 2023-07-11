/*
 * @file
 *
 * \brief  Driver for TCA9554 I2C GPIO expander
 *
 * Source of inspiration: https://github.com/balzreber/TCA9534
 * (under GPLv3.0, so can't reuse it directly)
 */

#ifndef TCA9554_HPP
#define TCA9554_HPP

#include "gpio_interface.hpp"
#include <cstdint>


/**
 * \brief  Driver for TCA9554 I2C GPIO expander
 *
 * All booleans functions return whether the operation was successful, unless
 * specified otherwise
 */
class TCA9554: public GpioInterface
{
  public:
    TCA9554(int i2c_address);

    /// Initialises I2C and returns whether the sensor is responding
    bool init() override;

    /// Sets the mode of a channel (between 0 and 7)
    bool set_channel_mode(int channel, ChannelMode channel_mode) override;

    /// Writes the output value of a channel
    bool write_channel_value(int channel, bool value) override;

    /// Reads the output value of a channel
    bool read_channel_value(int channel, bool &value) override;

    /// Reads the input/output configuration of all channels
    bool read_channel_configuration(uint8_t &value);

  private:
    const int i2c_address_;  ///< I2C address of the GPIO extender

    bool is_init_;                 ///< Whether the sensor was initialised successfully
    uint8_t configuration_state_;  ///< Current state of the configuration register
    uint8_t output_state_;         ///< Current state of the output port register
};

#endif
