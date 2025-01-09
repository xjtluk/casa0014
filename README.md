# Chrono Lumina - Light Control with Vibration and Sound Sensors
<img src="https://github.com/xjtluk/casa0014/blob/main/ce_work/Doc/pic1.jpg" alt="Example Image" width="300"/>
<img src="https://github.com/xjtluk/casa0014/blob/main/ce_work/Doc/result1.jpg" alt="Example Image" width="300"/>

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
## Hardware Components
- **Arduino MKR WiFi 1010**: Microcontroller with built-in WiFi support.
- **Vibration Sensor (Analog)**: Detects vibrations to trigger color changes.
<img src="https://github.com/xjtluk/casa0014/blob/main/ce_work/Doc/sensor1.jpg" alt="Example Image" width="300"/>

- **Sound Sensor (Analog)**: Measures sound levels to control pixel activation.
<img src="https://github.com/xjtluk/casa0014/blob/main/ce_work/Doc/sensor2.jpg" alt="Example Image" width="300"/>

- **Lighting System**: 12 individually addressable pixels.
- **WiFi Connectivity**: Connects to the network to send MQTT messages.

## Software Components
- **Arduino IDE**: Development environment for writing and uploading code.
- **MQTT Protocol**: Used for communication between the Arduino board and the lighting system.
- **Libraries**:
  - `WiFiNINA.h`: Manages WiFi connectivity.
  - `PubSubClient.h`: Enables MQTT communication.
 
## Enclosure Design
- Custom 3D-Printed Shell: Protects components while ensuring accurate sensor readings with features like perforations for sound detection and open areas for vibration sensing
<img src="https://github.com/xjtluk/casa0014/blob/main/ce_work/Doc/pic3.jpg" alt="Example Image" width="300"/>

## Functional Workflow

### Setup Phase:
<img src="https://github.com/xjtluk/casa0014/blob/main/ce_work/Doc/pic2.png" alt="Example Image" width="300"/>

- Establishes WiFi and MQTT connections.
- Initializes sensors and sets up system variables.

### Vibration Sensor Logic:
- Reads the analog value from the vibration sensor.
- If the value exceeds the threshold, the system cycles to the next predefined color and updates all pixels.

### Sound Sensor Logic:
- Reads the analog value from the sound sensor.
- Based on the sound intensity, determines the number of active pixels:
  - Low Sound (0-340): Activates 4 pixels.
  - Medium Sound (341-681): Activates 8 pixels.
  - High Sound (682-1023): Activates all 12 pixels.
- Updates pixel colors and deactivates unused pixels.

### MQTT Communication:
- Constructs and publishes MQTT messages to update pixel states remotely.

## Code Overview

### WiFi and MQTT Configuration:
- Credentials are stored securely in a separate `arduino_secrets.h` file for safety.
- The system reconnects to WiFi or MQTT automatically if the connection is lost.

### Vibration Handling:
- Uses a debounce interval to prevent rapid state changes.
- Cycles through four colors and applies them to all pixels.
![Code Example](https://github.com/xjtluk/casa0014/blob/main/ce_work/Doc/code2.png)
### Sound Handling:
- Dynamically calculates the number of active pixels based on sound intensity.
- Turns off inactive pixels to save energy.
  
![Code Example](https://github.com/xjtluk/casa0014/blob/main/ce_work/Doc/code3.png)
### MQTT Messaging:
- Constructs JSON messages with pixel ID and RGB values.
- Publishes messages to a pre-defined topic.
  ![Code Example](https://github.com/xjtluk/casa0014/blob/main/ce_work/Doc/code1.png)
  
## Results and Reflection
<img src="https://github.com/xjtluk/casa0014/blob/main/ce_work/Doc/result2.jpg" alt="Example Image" width="300"/>
<img src="https://github.com/xjtluk/casa0014/blob/main/ce_work/Doc/result3.png" alt="Example Image" width="300"/>

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



