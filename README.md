# Home Harmony: Smart Living Simplified

## Overview

**Home Harmony** is a home automation system. By leveraging the Arduino Uno microcontroller and integrating various sensors and controllers, this system enables comprehensive monitoring and control of different areas within a home.

## Features

- **Motion Detection**: Uses PIR (Passive Infrared) motion sensors to monitor environmental conditions and detect motion in real-time.
- **Light Control**: Adjusts lighting based on detected motion and user input, creating personalized and comfortable living spaces.
- **Security Enhancements**: Enhances home security by alerting users to potential intrusions through motion detection.
- **User Interface**: Interacts with the system using a 16x2 LCD, rotary encoders, and keypads to control light levels and view system status.
- **Cost-Effective**: Utilizes affordable components to make smart home technology accessible to a broader audience.
- **Remote Access**: Allows remote monitoring and control of the home environment.

## Components

### Hardware

- **Microcontroller**: Arduino Uno
- **Sensors**: PIR Motion Sensor
- **Displays**: SSD1306 OLED, 16x2 or 20x4 LCD
- **Input Devices**: Keypad, Rotary Encoders, Potentiometers
- **LEDs**: Standard and RGB LEDs

### Software

- **Development Environment**: WOKWI Online Emulator
- **Programming Language**: AVR C

## System Design

The system integrates various hardware components with the Arduino Uno to monitor and control home environments. The key components and their functions are as follows:

- **PIR Motion Sensor**: Detects motion and triggers LED activation for a specified duration.
- **RGB LED**: Controlled by potentiometers to set the desired color intensity.
- **LCD Display**: Shows user inputs, system status, and motion alerts.
- **Keypad**: Allows users to set the duration for LED activation when motion is detected.

## Installation

1. **Clone the Repository**: 
   ```bash
   git clone https://github.com/FEgebilge/HomeHarmony-Light-Control-System.git
   cd home-harmony
   ```
   

2. **Upload the Code to Arduino**:
   - Open the project in the Arduino IDE.
   - Connect your Arduino Uno to your computer.
   - Select the correct board and port in the Arduino IDE.
   - Upload the code to the Arduino Uno.

3. **Set Up the Hardware**:
   - Connect the PIR motion sensor, LEDs, LCD display, keypad, and potentiometers to the Arduino Uno as per the wiring diagram provided in the repository.

4. **Run the System**:
   - Power on the Arduino Uno.
   - Use the keypad to set the duration for LED activation.
   - Adjust the RGB LED color using the potentiometers.
   - Monitor the system status and motion alerts on the LCD display.

## Usage

- **Motion Detection**: The PIR motion sensor will detect motion and activate the LED for the duration set by the user.
- **Light Control**: Adjust the RGB LED color using the potentiometers.
- **User Interface**: Use the keypad to set the LED activation duration and monitor the system status on the LCD display.

## Development

### System Design

The system design involves integrating sensors, controllers, and user interface components to create a seamless smart home experience. The interactions between components are mapped out to ensure efficient and reliable operation.

### Coding

The software is developed using AVR C within the WOKWI online emulator environment. Key functions include:

- **Motion Detection**: Reads data from PIR motion sensors and triggers LED activation.
- **Light Control**: Adjusts light intensity based on user input.
- **User Interface**: Handles user input from the keypad and displays system status on the LCD screen.
- **System Initialization**: Initializes all sensors, displays, and inputs when the system is powered on or reset.

### Testing

The software is tested in the WOKWI emulator to simulate real-world conditions. This allows for validation of sensor readings, user interactions, and system responses. Issues identified during testing are addressed through iterative debugging and code refinement.

## Future Work

- **Enhanced Remote Access**: Implement remote control capabilities using IoT platforms.
- **Additional Sensors**: Integrate more sensors (e.g., temperature, humidity) for comprehensive home monitoring.
- **Mobile App**: Develop a mobile app for easier remote control and monitoring.

## Contributing

Contributions are welcome! Please follow these steps to contribute:

1. Fork the repository.
2. Create a new branch (`git checkout -b feature-branch`).
3. Commit your changes (`git commit -m 'Add new feature'`).
4. Push to the branch (`git push origin feature-branch`).
5. Open a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for more details.

## Acknowledgments

- **Advisor**: Assist. Prof.(PhD) Ömer ÇETİN
- **Course**: COMP 3328: Embedded Systems Project Term Project

## Contact

For any questions or inquiries, please contact Fahrettin Ege Bilge at [e.egebilge@gmail.com].

---
<img width="578" alt="Screenshot 2024-05-27 at 18 56 57" src="https://github.com/FEgebilge/HomeHarmony-Light-Control-System/assets/93092469/08191c1a-67c3-4033-9336-d372e69871c0">



