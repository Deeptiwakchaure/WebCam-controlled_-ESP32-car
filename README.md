
# Webcam-Controlled ESP32 Robot Car 🚗✋

This project enables real-time control of an ESP32-based robot car using hand gestures detected through a webcam. The system uses computer vision for gesture recognition and WiFi communication to send commands to the robot.

## 📌 Project Overview

The system consists of two main components:

1. **Python Application** (Host PC) - Uses OpenCV and Mediapipe to detect hand gestures from webcam feed
2. **ESP32 Controller** - Receives commands over WiFi and controls the motors accordingly

## 🛠 Hardware Requirements

### For ESP32 Robot Car

- ESP32 development board
- L298N Motor Driver or equivalent
- 2x DC motors with wheels
- Chassis/frame for the robot
- Battery pack (7-12V recommended)
- Jumper wires

### For Host Computer

- Webcam
- Python 3.8+ environment
- WiFi network for communication

## 📋 Software Requirements

### Host Computer

- Python 3.8+
- Required Python packages:
  - OpenCV (`pip install opencv-python`)
  - Mediapipe (`pip install mediapipe`)
  - Requests (`pip install requests`)

### ESP32

- Arduino IDE with ESP32 board support
- WiFi library (included with ESP32 board package)

## 🚀 Setup Instructions

### 1. ESP32 Setup

1. Connect your motors to the ESP32 via the motor driver:
   - Motor A to pins 27 (IN1) and 14 (IN2)
   - Motor B to pins 12 (IN3) and 13 (IN4)
   - Enable pin to pin 22 (EN)
2. Upload `slave_final.ino` to your ESP32
3. Update WiFi credentials in the sketch:
   ```arduino
   const char* ssid = "YOUR_WIFI_SSID";
   const char* password = "YOUR_WIFI_PASSWORD";
   ```
4. Note the IP address shown in Serial Monitor after upload

### 2. Host Computer Setup

1. Install required Python packages:
   ```bash
   pip install opencv-python mediapipe requests
   ```
2. Update the ESP32 IP address in `main.py`:
   ```python
   ESP32_IP = "http://YOUR_ESP32_IP"  # Replace with actual IP
   ```

## ✋ Gesture Controls

| Gesture         | Command | Robot Action  |
| --------------- | ------- | ------------- |
| ✊ Fist         | stop    | Stop motors   |
| 🖐 Open Palm    | 1       | Move Forward  |
| 👍 Thumb Up     | 2       | Move Backward |
| ☝ Index Finger | 3       | Turn Right    |
| 🤙 Pinky Finger | 4       | Turn Left     |

## 🏃‍♂️ Running the System

1. Power on your ESP32 robot car
2. On your host computer, run:
   ```bash
   python main.py
   ```
3. Position your hand in front of the webcam to control the robot
4. Press 'q' to quit the application

## ⚙️ Configuration Options

### Python Script (`main.py`)

- `command_hold_seconds`: Adjust command resend delay (default: 1.5s)
- Camera resolution can be modified by changing `cap = cv2.VideoCapture(0)` parameters

### ESP32 Sketch (`slave_final.ino`)

- `timeoutMs`: Command timeout duration (default: 1500ms)
- Motor pins can be reconfigured as needed
- PWM values can be adjusted in motor control functions

## 🔧 Troubleshooting

1. **Webcam not detected**:

   - Check camera index in `cv2.VideoCapture(0)`
   - Try different USB ports

2. **ESP32 not connecting to WiFi**:

   - Verify SSID and password
   - Check WiFi signal strength

3. **Commands not received**:
   - Verify ESP32 IP address is correct
   - Ensure both devices are on same network
   - Check firewall settings blocking HTTP requests

## 📜 License

This project is open-source under the MIT License.

## 🤝 Contributing

Contributions are welcome! Please open an issue or pull request for any improvements.

---

Enjoy controlling your robot with gestures! 🎮🤖
=======
# WebCam-controlled_-ESP32-car
ESP32 robot car controlled by hand gestures via webcam
>>>>>>> 8edde76f703fa697abe2456c3376760619a6b7c0
