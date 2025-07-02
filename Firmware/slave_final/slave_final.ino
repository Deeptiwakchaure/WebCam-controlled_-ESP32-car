#include <WiFi.h>

const char* ssid = "Heretics";
const char* password = "24466678";

#define MOTOR_EN 22
#define MOTOR_A1 27
#define MOTOR_A2 14
#define MOTOR_B1 12
#define MOTOR_B2 13

WiFiServer server(80);
String currentCommand = "stop";
unsigned long lastCommandTime = 0;
unsigned long timeoutMs = 1500;

void setup() {
  Serial.begin(115200);
  WiFi.begin(ssid, password);

  pinMode(MOTOR_EN, OUTPUT);
  pinMode(MOTOR_A1, OUTPUT);
  pinMode(MOTOR_A2, OUTPUT);
  pinMode(MOTOR_B1, OUTPUT);
  pinMode(MOTOR_B2, OUTPUT);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected. IP address:");
  Serial.println(WiFi.localIP());
  server.begin();
}

void loop() {
  WiFiClient client = server.available();
  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();
    Serial.println("Received: " + request);

    if (request.startsWith("GET /1 ")) {
      currentCommand = "forward";
    } else if (request.startsWith("GET /2 ")) {
      currentCommand = "backward";
    } else if (request.startsWith("GET /3 ")) {
      currentCommand = "right";
    } else if (request.startsWith("GET /4 ")) {
      currentCommand = "left";
    } else if (request.startsWith("GET /stop")) {
      currentCommand = "stop";
    }

    lastCommandTime = millis();
    client.println("HTTP/1.1 200 OK\r\nContent-Type: text/plain\r\n\r\nOK");
    client.stop();
  }

  if (millis() - lastCommandTime > timeoutMs) {
    stopMotors();
    return;
  }

  if (currentCommand == "forward") moveForward();
  else if (currentCommand == "backward") moveBackward();
  else if (currentCommand == "right") turnRight();
  else if (currentCommand == "left") turnLeft();
  else stopMotors();
}

void moveForward() {
  Serial.println("Moving forward");
  digitalWrite(MOTOR_A1, HIGH); digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, LOW);  digitalWrite(MOTOR_B2, HIGH);
  analogWrite(MOTOR_EN, 255);
}

void moveBackward() {
  Serial.println("Moving backward");
  digitalWrite(MOTOR_A1, LOW);  digitalWrite(MOTOR_A2, HIGH);
  digitalWrite(MOTOR_B1, HIGH); digitalWrite(MOTOR_B2, LOW);
  analogWrite(MOTOR_EN, 255);
}

void turnRight() {
  Serial.println("Turning right");
  digitalWrite(MOTOR_A1, HIGH); digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, LOW);  digitalWrite(MOTOR_B2, LOW);
  analogWrite(MOTOR_EN, 255);
}

void turnLeft() {
  Serial.println("Turning left");
  digitalWrite(MOTOR_A1, LOW);  digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, LOW);  digitalWrite(MOTOR_B2, HIGH);
  analogWrite(MOTOR_EN, 255);
}

void stopMotors() {
  Serial.println("Stopping");
  digitalWrite(MOTOR_A1, LOW);
  digitalWrite(MOTOR_A2, LOW);
  digitalWrite(MOTOR_B1, LOW);
  digitalWrite(MOTOR_B2, LOW);
  analogWrite(MOTOR_EN, 0);
}
