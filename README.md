# mxhip EMW3080 mbed-os-example-wifi #

WiFi example for mbed OS using mxchip EMW3080.

## Getting started with the WiFi API ##

This is a quick example of a simple WiFi application using the WiFi and network-socket APIs that is provided as a part of [mbed-os](github.com/armmbed/mbed-os).

The program brings up the WiFi and the underlying network interface, and uses it to connect to a network, prints interface and connection details and performs simple HTTP operation.

#### Connecting the EMW3080 to Nucleo F401RE ####

By default, the shield will connect the TX/RX of the radio to D1/D0 on the Nuclo board. However, these serial lines are muxed with that for the USB serial connection, so stdio serial and D1/D0 cannot be used at the same time. You will instead connect the TX/RX of the shield to D2/D10. To accomplish this:
* Bend the TX/RX pins of the shield outward, so that they do not make contact with the board
* Place the shield on the board's arduino headers
* Wire the TX pin on the EMW3080 to D10 on the Nucleo
* Wire the RX pin on the EMW3080 to D2 on the Nucleo

##  Getting started

1. Import the example

  ```
  mbed import https://github.com/sarahmarshy/mbed-os-example-wifi
  cd mbed-os-example-wifi
  ```
2. Configure the WiFi credentials

  Edit ```mbed_app.json``` to include correct SSID and Password:

  ```
      "config": {
          "wifi-ssid": {
              "help": "WiFi SSID",
              "value": "\"SSID\""
          },
          "wifi-password": {
              "help": "WiFi Password",
              "value": "\"Password\""
          }
      },
  ```

3. Compile and generate binary

  For example, for `GCC`:

  ```
  mbed compile -t GCC_ARM -m NUCLEO_F401RE
  ```

## Documentation ##

More information on the network-socket API can be found in the [mbed handbook](https://docs.mbed.com/docs/mbed-os-api-reference/en/5.2/APIs/communication/network_sockets/).
