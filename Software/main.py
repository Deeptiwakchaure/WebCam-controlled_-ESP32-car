import cv2
import mediapipe as mp
import requests
import time

# Replace with your ESP32 IP address
ESP32_IP = "http://192.168.121.8"  # ← Replace this with actual IP

# Mediapipe setup
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(
    static_image_mode=False,
    max_num_hands=1,
    min_detection_confidence=0.8,
    min_tracking_confidence=0.8
)
mp_draw = mp.solutions.drawing_utils

# Webcam init
cap = cv2.VideoCapture(0)

last_command = ""
last_sent_time = time.time()
command_hold_seconds = 1.5  # Delay before re-sending same command

def send_command(command):
    global last_command, last_sent_time
    current_time = time.time()
    if command != last_command or (current_time - last_sent_time) > command_hold_seconds:
        try:
            print("Sending command:", command)
            requests.get(f"{ESP32_IP}/{command}", timeout=1)
            last_command = command
            last_sent_time = current_time
        except Exception as e:
            print("Failed to send command:", e)

while True:
    success, img = cap.read()
    if not success:
        print("Webcam not detected.")
        break

    img = cv2.flip(img, 1)
    img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    results = hands.process(img_rgb)

    fingers = [0, 0, 0, 0, 0]
    command = "stop"

    if results.multi_hand_landmarks:
        hand = results.multi_hand_landmarks[0]
        lm = hand.landmark

        # Thumb: compare x (for right hand)
        if lm[4].x < lm[3].x:
            fingers[0] = 1

        # Other fingers: compare y (tip vs pip)
        tip_ids = [8, 12, 16, 20]
        for i in range(4):
            if lm[tip_ids[i]].y < lm[tip_ids[i] - 2].y:
                fingers[i + 1] = 1

        print("Fingers:", fingers)

        # Gesture interpretation
        if fingers == [0, 0, 0, 0, 0]:
            command = "stop"       # Fist
        elif fingers == [1, 1, 1, 1, 1]:
            command = "1"          # Palm → Forward
        elif fingers == [1, 0, 0, 0, 0]:
            command = "2"          # Thumb Up → Backward
        elif fingers == [0, 1, 0, 0, 0]:
            command = "3"          # Index Finger → Right
        elif fingers == [0, 0, 0, 0, 1]:
            command = "4"          # Pinky Finger → Left
        else:
            command = "stop"

        send_command(command)
        mp_draw.draw_landmarks(img, hand, mp_hands.HAND_CONNECTIONS)
    else:
        send_command("stop")

    cv2.imshow("Gesture Control", img)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
