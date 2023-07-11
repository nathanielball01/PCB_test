/*
 * @file
 *
 * \brief  Base class for all interfaces handling GPIOs (natively or through ICs)
 */

#ifndef GPIO_INTERFACE_BASE_HPP
#define GPIO_INTERFACE_BASE_HPP


/**
 * \brief  Base class for all interfaces handling GPIOs (natively or through ICs)
 *
 * This can be derived to for example handle a microcontroller's GPIOs, or a
 * GPIO expander IC. A "channel" is then a microcontroller pin or an IC
 * channel.
 *
 * All booleans functions return whether the operation was successful, unless
 * specified otherwise
 */
class GpioInterface
{
  public:
    /// Describes the mode a channel can be
    enum class ChannelMode {
      INPUT_CHANNEL,
      OUTPUT_CHANNEL,
      INPUT_PULLUP_CHANNEL,
      INPUT_PULLDOWN_CHANNEL
    };

    /// Initialises the interface
    virtual bool init()
    {
      return true;
    }

    /// Sets the mode of a channel
    virtual bool set_channel_mode(int channel, ChannelMode channel_mode) = 0;

    /// Writes the output value of a channel
    virtual bool write_channel_value(int channel, bool value) = 0;

    /// Reads the output value of a channel
    virtual bool read_channel_value(int channel, bool &value) = 0;
};

#endif
