# Smart-Garbage-Monitoring-System

This project uses an ESP8266 microcontroller to monitor the level of a dustbin and publish the data to Adafruit IO using MQTT protocol. The dustbin level is measured using an ultrasonic sensor, and the data is sent to Adafruit IO to be monitored remotely.

## Table of Contents
- [Introduction](#introduction)
- [Components](#components)
- [Circuit Diagram](#circuit-diagram)
- [Installation](#installation)
- [Usage](#usage)
- [Code](#code)
- [License](#license)

## Introduction

This project aims to create a smart dustbin level monitoring system using ESP8266 and Adafruit IO. The system measures the level of the dustbin using an ultrasonic sensor and sends the data to Adafruit IO, where it can be monitored remotely.

## Components

- ESP8266 (e.g., NodeMCU)
- Ultrasonic Sensor (HC-SR04)
- Breadboard and Jumper Wires
- WiFi Network
- Adafruit IO Account

## Circuit Diagram

![Circuit Diagram]()

## Installation
Install the Required Libraries:

- ESP8266WiFi
- Adafruit MQTT Library
- ArduinoJson Library
You can install these libraries using the Arduino Library Manager.

1. **Clone the Repository:**
   ```sh
   git clone https://github.com/yourusername/smart-dustbin-monitor.git
   cd smart-dustbin-monitor
