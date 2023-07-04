# Car Accident Detection System

This project aims to develop a car accident detection system using the following components:

- ADXL335 accelerometer for detecting major axis changes
- NEO-6 GPS module for obtaining GPS location
- Buzzer for audible alerts
- Ultrasonic sensor for proximity detection
- LED for visual indication

## Functionality

The system is designed to detect and respond to car accidents in the following manner:

1. Proximity Detection:
    
    - The ultrasonic sensor measures the distance between the car and any nearby objects.
    - If the distance is less than 10 cm, indicating a potential collision, the system activates the warning signals.
2. Warning Signals:
    
    - The LED lights up to provide a visual indication of a potential collision.
    - The buzzer emits a loud beep to alert the driver of the impending danger.
3. Major Axis Change Detection:
    
    - The ADXL335 accelerometer measures the acceleration along the major axes of the car.
    - If a major axis change is detected, suggesting a significant impact or collision, the system triggers an email alert.
4. Email Alert:
    
    - The system utilizes an email account to send an accident alert along with the GPS location.
    - The email includes relevant information to notify the designated recipient about the accident.
## Components and Circuitry

The project requires the following hardware components:

- ADXL335 accelerometer module
- NEO-6 GPS module
- Buzzer
- Ultrasonic sensor
- LED

The components are connected and integrated to form the car accident detection system circuit.

## Installation and Setup

To set up the car accident detection system, follow these steps:

1. Connect the hardware components as per the circuit diagram.
2. Install the necessary libraries for the accelerometer, GPS module, and any other required dependencies.
3. Configure the email account details in the system to enable email alerts.
4. Upload the code to the microcontroller or development board.
5. Power up the system and ensure all components are functioning correctly.

## Usage

Once the system is set up and powered on, it will continuously monitor the car's surroundings and detect any potential accidents. The system will provide visual and audible warnings if a collision is imminent. In case of a major axis change, an email alert will be sent to the designated recipient with the GPS location.


## Conclusion

The car accident detection system provides an effective solution to detect and respond to potential accidents. By combining various sensors and modules, it enhances the safety measures in vehicles and contributes to reducing the severity of accidents.

**Note:** This project is intended for educational purposes and should be implemented responsibly and in compliance with local laws and regulations.

Feel free to use this Markdown content for your GitHub repository to document your car accident detection system project.
