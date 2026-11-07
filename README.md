# Kesh's OpenHop USB bench modem

This fork of [OpenHop Modem](https://github.com/openhop-dev/openhop_modem) contains the `kesh/heltec-bench` branch for [Kesh's OpenHop bridge](https://github.com/kesh33w/kesh-openhop-bridge). It adds restricted USB modem builds for Heltec T096 and V4.3 radios.

The modem handles LoRa transmission, reception, channel-activity detection and radio configuration. OpenHop Core and Repeater run on the host and handle packets, encryption and routing. These modem builds are separate from the MeshCore Observer-based TFT and OLED iLink firmware.

## Choose the target

| PlatformIO environment | Board | Configuration |
| --- | --- | --- |
| `heltec_t096_bench` | Heltec HT-n5262G T096 | nRF52840, USB-only, no autonomous mesh identity |
| `heltec_v43_bench` | Heltec WiFi LoRa 32 V4.3 | ESP32-S3, USB-only, Wi-Fi and network support disabled in the board configuration |

The T096 target is distinct from the upstream T114 target. Select the exact board before building or flashing. The V4.3 bench configuration leaves display, GPS and battery-monitor pins unused.

Both bench targets accept only these host-selected profiles:

| Frequency | Bandwidth | Spreading factor | Coding rate | SX1262 power setting |
| --- | --- | --- | --- | --- |
| 917.450 MHz | 62.5 kHz | SF9 | 4/5 | -9 dBm |
| 917.550 MHz | 62.5 kHz | SF7 | 4/5 | -9 dBm |

The first profile is the boot default. The firmware rejects other frequency, bandwidth, spreading-factor, coding-rate or power combinations. It does not transmit on boot; each packet needs a host request.

The -9 dBm setting is chip drive, not measured antenna output. The external amplifier adds gain. Use suitable bench equipment and radio settings permitted at your location. These restrictions do not establish RF compliance or hardware safety on their own.

## Build from source

Install PlatformIO, then build the target that matches your board:

```sh
git clone --branch kesh/heltec-bench --single-branch https://github.com/kesh33w/openhop_modem.git
cd openhop_modem/firmware
pio run -e heltec_t096_bench
# Or, for the V4.3:
pio run -e heltec_v43_bench
```

These commands compile firmware without flashing a device. The T096 environment pins Nordic nRF52 platform 10.11.0 and RadioLib 7.1.2. The V4.3 bench environment extends `heltec_v43`; its dependencies and build flags are in [firmware/platformio.ini](firmware/platformio.ini).

Do not substitute an upstream browser-flasher image for a bench build. The checked-in images for other environments do not include these target-specific restrictions. Review the exact target and its output before using the general [installation reference](INSTALL.md). Flashing replaces firmware and may replace saved settings.

For compatible host components, use the hub's [reconstruction instructions](https://github.com/kesh33w/kesh-openhop-bridge#reconstruct-and-test). Its dated `components.current.json` snapshot is separate from historical release manifests. Neither materialization nor a successful build verifies a connected radio.

## Source and reference

- [firmware/src/main.cpp](firmware/src/main.cpp) sets the bench defaults and rejects unsupported profiles in `applyConfig`.
- [T096 board configuration](firmware/include/boards/heltec_t096.h) defines the pin map, USB-only behavior and power ceiling.
- [V4.3 bench configuration](firmware/include/boards/heltec_v43_bench.h) overrides the upstream board's network and peripheral settings.
- [firmware/include/protocol.h](firmware/include/protocol.h) defines host commands and modem responses.
- [API.md](API.md) describes the general modem API.
- [MODEM-REFERENCE.md](MODEM-REFERENCE.md) retains the previous board and protocol reference. Its general defaults and network setup do not apply to the two bench targets.

The inherited regression scripts in `firmware/tools` test specific modem subsystems with host stubs. A passing host test or firmware build does not prove bench RF behavior. Follow the hub's recorded verification scope rather than treating all upstream boards as tested by this project.

## Credits and license

OpenHop Modem and its contributors supply the original firmware. The [MIT License](LICENSE) remains unchanged. The T096 Arduino variant retains its Arduino, Sandeep Mistry and Adafruit LGPL-2.1-or-later notices. See the hub's [license notice](https://github.com/kesh33w/kesh-openhop-bridge/blob/kesh/openhop-bridge/NOTICE.md) for the project-wide acknowledgments.
