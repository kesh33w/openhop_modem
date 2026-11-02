// Reuse the official V4.3 LoRa/FEM map; leave expansion peripherals unused.
#pragma once
#define BOARD V43_REFERENCE_BOARD
#include "heltec_v43.h"
#undef BOARD
inline const BoardConfig BOARD = [] {
    BoardConfig b = V43_REFERENCE_BOARD;
    b.name = "Heltec V4.3 bench";
    b.fw_suffix = "heltec_v43_bench_625_sf9sf7";
    b.max_tx_power_dbm = -9;
    b.has_wifi = false;
    b.has_network = false;
    b.pin_i2c_sda = b.pin_i2c_scl = b.pin_i2c_oled_rst = -1;
    b.pin_vext_enable_low = -1;
    b.pin_gps_uart_rx = b.pin_gps_uart_tx = -1;
    b.pin_gps_enable = b.pin_gps_reset = -1;
    b.battery.pin = b.battery.enable_pin = -1;
    return b;
}();
