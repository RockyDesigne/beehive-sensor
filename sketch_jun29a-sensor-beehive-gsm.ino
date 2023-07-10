#include <SoftwareSerial.h>
#include <dht.h>
#include <string.h>

SoftwareSerial SIM900A(10, 11); // RX | TX

dht DHT {};

const uint8_t DHT_PIN {7};

void sendDataToThingSpeak();

void setup() {
  Serial.begin(9600);
  SIM900A.begin(9600);

  delay(1000);
  SIM900A.println("AT");
  delay(1000);
  SIM900A.println("AT+CPIN?");
  delay(3000);
  SIM900A.println("AT+CREG?");
  delay(3000);
  SIM900A.println("AT+CGATT?");
  delay(3000);
  SIM900A.println("AT+CIPSHUT");
  delay(1000);
  SIM900A.println("AT+CIPSTATUS");
  delay(2000);
  SIM900A.println("AT+CIPMUX=0");
  delay(2000);
  SIM900A.println("AT+CSTT=\"internet\",\"Digi Mobil\",\"\"");
  delay(3000);
  SIM900A.println("AT+CIICR");
  delay(3000);
  SIM900A.println("AT+CIFSR");
  delay(2000);
}

unsigned long previousSendTime = 0;
const unsigned long sendInterval = 8UL * 60UL * 60UL * 1000UL; // 8 hours

void loop() {
  unsigned long currentMillis = millis();

  // Check if the specified interval has passed, taking overflow into account
  if ((currentMillis - previousSendTime >= sendInterval) || (currentMillis < previousSendTime)) {
    DHT.read11(DHT_PIN);

    sendDataToThingSpeak(String(DHT.temperature), String(DHT.humidity));

    previousSendTime = currentMillis; // Update the previous send time
  }

}


void sendDataToThingSpeak(String temperature, String humidity) {
  // API endpoint URL
  String url = "https://api.thingspeak.com/update";

  // Data to be sent in the request
  String data = "api_key=DO6M82KWFNDZKOOB&field1=" + temperature + "&field2=" + humidity;

  // Construct the request
  String request = "POST /update HTTP/1.1\r\n";
  request += "Host: api.thingspeak.com\r\n";
  request += "Content-Type: application/x-www-form-urlencoded\r\n";
  request += "Content-Length: " + String(data.length()) + "\r\n\r\n";
  request += data;

  // Connect to the server
  SIM900A.println("AT+CIPSTART=\"TCP\",\"api.thingspeak.com\",80");
  delay(2000);
  SIM900A.println("AT+CIPSEND");
  delay(1000);

  // Send the request
  SIM900A.println(request);
  delay(2000);

  // Close the connection
  SIM900A.println((char)26);
  delay(5000);
  SIM900A.println("AT+CIPCLOSE");
}
