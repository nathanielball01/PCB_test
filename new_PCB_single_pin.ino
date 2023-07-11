#include "TCA9554.hpp"

int gpio_expander_address = 0x38;
TCA9554 gpio_interface_(gpio_expander_address);

const auto output_mode = GpioInterface::ChannelMode::OUTPUT_CHANNEL;



unsigned long last_LED_time = 0;  // last time published whether the robot was having a sampling system

const float watchdog_frequency = 4.0;  // frequency at which to update the watchdog pulse (in Hz)
const unsigned long watchdog_update_dt = 1000 / (unsigned long)watchdog_frequency;  // time between each watchdog output update (in ms)

int watchdog_pulse_pin = 27;

volatile int watchdog_pin_state = 0;  // state sent to the watchdog output
/// Sends a pulse signal to the watchdog
hw_timer_t *watchdog_pulse_timer = nullptr;  // timer used during setup only

void IRAM_ATTR send_watchdog_cb()
{
  watchdog_pin_state = !watchdog_pin_state;
  digitalWrite(watchdog_pulse_pin, watchdog_pin_state);
}



void setup()
{
  Serial.begin(115200);

  // Start timer to pulse signal to watchdog during setup
  // We want the timer to run in a separate thread at start, while everything is
  // being set up.
  pinMode(watchdog_pulse_pin, OUTPUT);
  watchdog_pulse_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(watchdog_pulse_timer, &send_watchdog_cb, true);
  timerAlarmWrite(watchdog_pulse_timer, (watchdog_update_dt * 1e3), true);  // 1e3 to convert ms to µs
  timerAlarmEnable(watchdog_pulse_timer);

  gpio_interface_.init();
  gpio_interface_.set_channel_mode(4, output_mode); // LEDs
  gpio_interface_.set_channel_mode(5, output_mode); // LEDs
  gpio_interface_.set_channel_mode(6, output_mode); // PSU switch
  gpio_interface_.set_channel_mode(7, output_mode); // PSU switch

  
  pinMode(2,OUTPUT);
}


void loop()
{
  gpio_interface_.write_channel_value(6, HIGH);
  gpio_interface_.write_channel_value(7, HIGH);

  if (check_time(last_LED_time, 2000)){
    gpio_interface_.write_channel_value(4, HIGH);
    gpio_interface_.write_channel_value(5, HIGH);
    digitalWrite(2,HIGH);
  } else {
    gpio_interface_.write_channel_value(4, LOW);
    gpio_interface_.write_channel_value(5, LOW);
    digitalWrite(2,LOW);
  }
}



bool check_time(unsigned long &last_t, unsigned long action_dt)
{
  unsigned long t = millis();
  if (t - last_t >= action_dt) {
    last_t = t;
    return true;
  }
  return false;
}
