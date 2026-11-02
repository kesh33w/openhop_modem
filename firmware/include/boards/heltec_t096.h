// HT-n5262G T096. Pin sources are recorded in hardware-reference/.
// Manufacturer identity GPIO mapping; MeshCore confirms SX1262 and KCT8103L wiring.
#pragma once
inline const BoardConfig BOARD = [] {
    BoardConfig b{};
    b.name = "Heltec T096 bench";
    b.fw_suffix = "heltec_t096_bench_625_sf9sf7";
    b.mdns_prefix = "t096";
    b.pin_lora_nss = 5;
    b.pin_lora_rst = 16;
    b.pin_lora_busy = 19;
    b.pin_lora_dio1 = 21;
    b.pin_lora_sck = 40;
    b.pin_lora_miso = 14;
    b.pin_lora_mosi = 11;
    b.rf_switch = {-1, 0, -1, -1, true};
    b.pin_lora_tx_led = 28;
    b.lora_tx_led_active_high = true;
    b.pin_i2c_sda = -1;
    b.pin_i2c_scl = -1;
    b.pin_i2c_oled_rst = -1;
    b.pin_vext_enable_low = -1;
    b.pin_user_button = 42;
    b.user_button_active_low = true;
    // This bench build cannot command more than the SX1262 minimum power.
    // The external PA adds gain; -9 is chip drive, not measured antenna power.
    b.max_tx_power_dbm = -9;
    b.use_dio3_tcxo = true;
    b.tcxo_voltage = 1.8f;
    b.sx126x_current_limit_ma = 140;
    b.sx126x_rx_boosted_gain = true;
    b.has_lora_radio = true;
    b.has_wifi = false;
    b.has_network = false;
    b.pin_protocol_uart_rx = -1;
    b.pin_protocol_uart_tx = -1;
    b.protocol_uart_baud = 921600;
    // Keep the KCT8103L powered/enabled, CTX HIGH for TX and RX LNA bypass.
    // These match the official MeshCore T096 init/tx paths with LNA disabled.
    b.static_gpios[0] = {30, true};
    b.static_gpios[1] = {12, true};
    b.static_gpios[2] = {41, true};
    // GPS enable is active LOW. Keep it off; TFT and GPS rail stays unclaimed.
    b.static_gpios[3] = {6, true};
    b.static_gpio_count = 4;
    return b;
}();
