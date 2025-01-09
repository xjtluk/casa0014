# Chrono Lumina - Light Control with Vibration and Sound Sensors

## Project Overview
One of the most compelling aspects of Internet-connected devices is their ability to monitor phenomena that are otherwise challenging to observe directly. This project, developed as part of the CASA0014 coursework, focuses on designing an IoT device to visualize and quantify classroom engagement.

### Purpose
**The Problem**: Measuring student engagement in real-time is a persistent challenge for educators. Subjective observations and post-class feedback lack the precision required for immediate teaching adjustments.

**The Solution**: The Student Engagement Detector provides a dynamic visual representation of classroom engagement using Chrono Lumina neopixels, helping educators assess participation levels and adapt their strategies accordingly.

### Features
- **Interactive Visual Feedback**:
  - **Sound Sensor**: Measures verbal participation, adjusting the number of active neopixels based on sound intensity.
  - **Vibration Sensor**: Captures classroom movement, triggering color changes to indicate physical activity.
- **IoT-Enabled Communication**:
  - Built on the Arduino MKR WiFi 1010, the system connects to an MQTT network for real-time data transmission and control.
- **Customizable and Scalable Design**:
  - Easily adaptable for various educational or workplace environments.

## Components and Hardware
### Core Hardware
- **Arduino MKR WiFi 1010**: Enables seamless integration with the school's MQTT system.
- **Chrono Lumina Neopixels**: Provides dynamic visual feedback.
- **Sound Sensor (V1.6)**: Detects sound levels in the classroom.
- **Vibration Sensor (V1.1)**: Captures subtle vibrations caused by student activity.

### Enclosure Design
- **Custom 3D-Printed Shell**: Protects components while ensuring accurate sensor readings with features like perforations for sound detection and open areas for vibration sensing.

## How It Works
### Data Visualization
- **Brightness Control via Sound**:
  - Sound intensity determines the number of active neopixels:
    - Low (0–341): Activates 4 pixels.
    - Medium (342–682): Activates 8 pixels.
    - High (683–1023): Activates all 12 pixels.
- **Color Control via Vibration**:
  - Vibrations exceeding a threshold trigger color changes, representing activity levels. A timing constraint ensures smooth transitions.

### Usage Scenario
Designed for indoor classroom environments, the system translates sound and movement data into intuitive visual feedback, making abstract engagement metrics tangible.

## Software
### Programming Approach
- **Modular Implementation**:
  - Tested each sensor independently before integrating them.
- **Threshold-Based Logic**:
  - Adjusted thresholds for meaningful sensor data processing.
- **MQTT Integration**:
  - Used the `arduino_secrets.h` template to securely configure network settings.

## Setup Instructions
### Hardware Assembly:
1. Connect sensors and neopixels to the Arduino MKR WiFi 1010.
2. Secure components in the 3D-printed enclosure.

### Software Setup:
1. Clone the repository.
2. Install required libraries: `Arduino_MQTT` and `Adafruit_NeoPixel`.
3. Upload the code to the Arduino board.

### Network Configuration:
1. Add WiFi credentials to the `arduino_secrets.h` file.
2. Deploy the MQTT client on the same network.

## Results and Reflection
### Achievements
- Successfully visualized classroom engagement with dynamic lighting.
- Enabled real-time feedback for teachers to adapt teaching methods.
- Demonstrated the potential of IoT in educational environments.

### Challenges and Solutions
- **Sensor Limitations**:
  - Adjusted system logic to accommodate vibration sensors that only detect presence, not magnitude.
- **Visual Clarity**:
  - Grouped sound intensity levels to ensure noticeable lighting changes.

### Future Enhancements
- **Machine Learning Integration**:
  - Analyze patterns in sound and vibration data for nuanced insights.
- **Improved Visual Feedback**:
  - Replace pixel count-based brightness with variable brightness levels.
- **Mobile Interface**:
  - Develop a dashboard for monitoring trends and customizing settings.
- **Expanded Applications**:
  - Integrate additional sensors to capture environmental factors like temperature or CO2 levels.


## Ethical Considerations
- **Privacy**: Ensure no personally identifiable data is collected.
- **Security**: Use encrypted communication to prevent unauthorized access.
- **Over-Simplification**: Avoid reliance on metrics that may misrepresent engagement nuances.

## Conclusion
The Student Engagement Detector bridges the gap between abstract engagement metrics and actionable insights. By addressing feedback and refining its design, the project highlights how IoT can transform learning environments and foster data-driven interventions for improved teaching outcomes.

## Important Note
Make sure to delete your `arduino_secrets.h` file from your GitHub repository to avoid exposing sensitive information.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

