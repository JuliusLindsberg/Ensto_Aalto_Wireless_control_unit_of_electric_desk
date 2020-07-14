# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.13.1)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(app)

target_sources(app PRIVATE src/main.cpp src/DebugBlinker.cpp src/MotorController.cpp src/EncoderAnalyzer.cpp src/DebugPrinter.cpp src/BluetoothModule.cpp)

target_include_directories(app PRIVATE ./src)
