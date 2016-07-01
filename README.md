# foosballino

## Description
Arduino Due code to augment a foosball table with goal detection, LED strips and a display to show the score.

## Authors

* [Talal El Afchal](https://github.com/talalelafchal)
* [Jacques Dafflon](https://github.com/jacquesd)
* [Yehia Moubayed](https://github.com/YehiaMob)
* [Samantha Rosso](https://github.com/Sauuman)

## Install
This project uses [PlatformIO](http://platformio.org/).

Simply [initialize the project](http://docs.platformio.org/en/latest/userguide/cmd_init.html).

Then compile and upload it to your Arduino due using the PlatformIo editor or CLI.

Configuration -- such as pin numbers or LED colors -- is done through the [`config.h`](src/config.h) file.

## Supported boards
 * Arduino due

> Other boards may be supported but have not been tested.

> Note that the LED strips will require a significant amount of memory. Combined with the other components such as the screen and its library, smaller, less powerfull Arduino boards may not be able to run this project.
