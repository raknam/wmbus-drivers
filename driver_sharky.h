/*
  Based on: https://github.com/wmbusmeters/wmbusmeters/blob/master/src/driver_sharky.cc
*/

#pragma once

#include "driver.h"

#include <vector>
#include <string>

struct Sharky : Driver
{
  Sharky(std::string key = "") : Driver(std::string("sharky"), key){};
  virtual esphome::optional<std::map<std::string, double>> get_values(std::vector<unsigned char> &telegram) override {
    std::map<std::string, double> ret_val{};

    add_to_map(ret_val, "total_energy_consumption_kwh", this->get_0C06(telegram));
    add_to_map(ret_val, "total_volume_m3", this->get_0C13(telegram));
    add_to_map(ret_val, "volume_flow_m3h", this->get_0B3B(telegram));
    add_to_map(ret_val, "power_kw", this->get_0C2B(telegram));
    add_to_map(ret_val, "flow_temperature_c", this->get_0A5A(telegram));
    add_to_map(ret_val, "return_temperature_c", this->get_0A5E(telegram));
    add_to_map(ret_val, "temperature_difference_c", this->get_0A62(telegram));

    if (ret_val.size() > 0) {
      return ret_val;
    }
    else {
      return {};
    }
  };
};
