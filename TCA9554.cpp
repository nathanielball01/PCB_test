/*
 * @file
 *
 * \brief  Driver for TCA9554 I2C GPIO expander
 *
 * Source of inspiration: https://github.com/balzreber/TCA9534
 * (under GPLv3.0, so can't reuse it directly)
 */

#include "TCA9554.hpp"
#include <Wire.h>
#include <Arduino.h>
#include <cstdint>


TCA9554::TCA9554(int i2c_address):
  i2c_address_(i2c_address),
  is_init_(false),
  configuration_state_(0b11111111),
  output_state_(0b11111111)
{

}


bool TCA9554::init()
{
  Wire.beginTransmission(i2c_address_);
  delay(100);
  is_init_ = Wire.endTransmission() == 0;

  return is_init_;
}


bool TCA9554::set_channel_mode(int channel, TCA9554::ChannelMode channel_mode)
{
  if (channel < 0 || channel > 7)
    return false;

  switch (channel_mode) {
    case ChannelMode::INPUT_CHANNEL:
      configuration_state_ |= (0x01 << channel);
      break;

    case ChannelMode::OUTPUT_CHANNEL:
      configuration_state_ &= ~(0x01 << channel);
      break;
  }

  Wire.beginTransmission(i2c_address_);
  Wire.write(0x03);  // select the configuration register
  Wire.write(configuration_state_);

  return Wire.endTransmission() == 0;
}


bool TCA9554::write_channel_value(int channel, bool value)
{
  if (channel < 0 || channel > 7)
    return false;

  output_state_ = (output_state_ & ~(1 << channel)) | (value << channel);

  Wire.beginTransmission(i2c_address_);
  Wire.write(0x01);  // select the output port register
  Wire.write(output_state_);

  return Wire.endTransmission() == 0;
}


bool TCA9554::read_channel_value(int channel, bool &value)
{
  if (channel < 0 || channel > 7)
    return false;

  Wire.beginTransmission(i2c_address_);
  Wire.write(0x00);  // select the input port register
  Wire.endTransmission();

  uint8_t data_len = Wire.requestFrom(i2c_address_, 1);
  uint8_t data = Wire.read();
  value = (data >> channel) & 1;

  return data_len == 1;
}


bool TCA9554::read_channel_configuration(uint8_t &value)
{
  Wire.beginTransmission(i2c_address_);
  Wire.write(0x03);  // select the input port register
  Wire.endTransmission();

  uint8_t data_len = Wire.requestFrom(i2c_address_, 1);
  value = Wire.read();

  return data_len == 1;
}
