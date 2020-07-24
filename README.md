# Wireless contol unit of electric desk
This is an Aalto University student project which aims to produce a functional prototype for a wireless controller of an electric desk. It is being developed in collaboration with Ensto. Software will be published under a rather permissive MIT license. See the licence file disclosed in this repository for details.
## Hardware
Our aim currently is to provide a working solution for only specific hardware. In our code there may or may not be useful generalizations for other types of hardware choices too but quite certainly our solution is not going to work right out the box.
### Microcontroller: NRF52840
NRF52840 provides adequate support for bluetooth low energy and potential for control via NFC tags.
## Software

### Zephyr OS

### C++
Programming language used is C++ or plain C. Not every feature of C++ is applicable due to constraints imposed by Zephyr OS.
See: https://docs.zephyrproject.org/1.9.0/kernel/other/cxx_support.html
However, note that the information provided in said webpage covers Zephyr version 1.9.0 and may not be in line with the latest release.
### Our code
See doc/API.md for our API reference.
## Getting started
Developing and building our project should be not very different from building any other zephyr project. As a bit of a warning Zephyr's work enviroment takes a lot of space (several gigabytes) from your hard drive. Developing Zephyr programs should be possible with any major operating system but so far we have used only Linux so other enviroments are a case of untested waters.
### Setting up the work enviroment
In order to build our code follow these instructions:
https://docs.zephyrproject.org/latest/getting_started/index.html
Then clone this git repository inside the zephyrproject/zephyr folder. With a little tweaking it probably is possible to build the project ouside zephyr folder too but just cloning this repository inside it seems to be the most convenient way available.
### Building our project
We use Zephyr's west tool to build our project in a similiar fashion as the tutorial above does. In order to build this project navigate to this git repository in your shell and then execute:
```
west build -p auto -b nrf52840dk_nrf52840 ./
```

However, if your microcontroller is not NRF52840, then -b option should naturally be something else than nrf52840_pca10056.
### Flashing into the microcontroller
```
west flash
```
should work just fine as with any other Zephyr project.
