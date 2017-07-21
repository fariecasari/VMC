
/*
  FarieCasari 21/07/2017
  Basic ESP8266 MQTT example
  
  This sketch demonstrates the capabilities of the pubsub library in combination
  with the ESP8266 board/library.

  It connects to an MQTT server then:
  - publishes "hello world" to the topic "outTopic" every two seconds
  - subscribes to the topic "inTopic", printing out any messages
    it receives. NB - it assumes the received payloads are strings not binary
  - If the first character of the topic "inTopic" is an 1, switch ON the ESP Led,
    else switch it off

  It will reconnect to the server if the connection is lost using a blocking
  reconnect function. See the 'mqtt_reconnect_nonblocking' example for how to
  achieve the same result without blocking the main loop.

  To install the ESP8266 board, (using Arduino 1.6.4+):
  - Add the following 3rd party board manager under "File -> Preferences -> Additional Boards Manager URLs":
       http://arduino.esp8266.com/stable/package_esp8266com_index.json
  - Open the "Tools -> Board -> Board Manager" and click install for the ESP8266"
  - Select your ESP8266 in "Tools -> Board"

*/

#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_MCP23017.h>
#include <Wire.h>
// Update these with values suitable for your network.

Adafruit_MCP23017 mcp;

const char* ssid = "fariecasari";
const char* password = "fariecasari123";
const char* mqtt_server = "192.168.1.42";

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
  mcp.begin();      // use default address 0
  mcp.pinMode(0, OUTPUT); //on
  mcp.pinMode(1, OUTPUT);  //velocita
  mcp.pinMode(2, OUTPUT);  //velocita
  mcp.pinMode(3, OUTPUT);  //velocita
  mcp.pinMode(4, OUTPUT);  //velocita
  mcp.pinMode(5, OUTPUT);  //velocita
  mcp.pinMode(6, OUTPUT);
  mcp.pinMode(7, OUTPUT);
  mcp.pinMode(8, OUTPUT);
  mcp.pinMode(9, OUTPUT);
  mcp.pinMode(10, OUTPUT);
  mcp.pinMode(11, OUTPUT);
  mcp.pinMode(12, OUTPUT);
  mcp.pinMode(13, OUTPUT);
  mcp.pinMode(14, OUTPUT);
  mcp.pinMode(15, OUTPUT);

}

void setup_wifi() {

  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* payload, unsigned int length) {
  // long value = 0;
  char buffer[10];
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
    // int value = ((char)payload[i]);

  }

  int value;// = 22;
  memcpy((char *)buffer,(char *)payload,length);  //buffer <=== payload
  buffer[length]=0; //chiudo il buffer
  value = atoi(buffer);//converto il buffer ad un intero
  //value = atoi((char *)payload);

  velocita(value);
  Serial.println();

  // Switch on the LED if an 1 was received as first character
  if ((char)payload[0] == '1') {
    digitalWrite(BUILTIN_LED, LOW);   // Turn the LED on (Note that LOW is the voltage level
    // but actually the LED is on; this is because
    // it is acive low on the ESP-01)

  } else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }

}

void velocita(int value) {
  switch (value)
  {
    case 0:
      mcp.digitalWrite(1, LOW);//Ventilatore OFF
      mcp.digitalWrite(2, LOW);//bit1
      mcp.digitalWrite(3, LOW);//bit2
      mcp.digitalWrite(4, LOW);//bit3
      mcp.digitalWrite(5, LOW);//bit4
      mcp.digitalWrite(6, LOW);//bit5
      break;
    case 1:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 0
      mcp.digitalWrite(2, LOW);//bit1
      mcp.digitalWrite(3, LOW);//bit2
      mcp.digitalWrite(4, LOW);//bit3
      mcp.digitalWrite(5, LOW);//bit4
      mcp.digitalWrite(6, LOW);//bit5
      break;
    case 2:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 1
      mcp.digitalWrite(2, HIGH);//bit1
      mcp.digitalWrite(3, LOW);//bit2
      mcp.digitalWrite(4, LOW);//bit3
      mcp.digitalWrite(5, LOW);//bit4
      mcp.digitalWrite(6, LOW);//bit5
      break;
    case 3:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 2
      mcp.digitalWrite(2, LOW);//bit1
      mcp.digitalWrite(3, HIGH);//bit2
      mcp.digitalWrite(4, LOW);//bit3
      mcp.digitalWrite(5, LOW);//bit4
      mcp.digitalWrite(6, LOW);//bit5
      break;
    case 4:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 3
      mcp.digitalWrite(2, HIGH);//bit1
      mcp.digitalWrite(3, HIGH);//bit2
      mcp.digitalWrite(4, LOW);//bit3
      mcp.digitalWrite(5, LOW);//bit4
      mcp.digitalWrite(6, LOW);//bit5
      break;
    case 5:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 4
      mcp.digitalWrite(2, LOW);//bit1
      mcp.digitalWrite(3, LOW);//bit2
      mcp.digitalWrite(4, HIGH);//bit3
      mcp.digitalWrite(5, LOW);//bit4
      mcp.digitalWrite(6, LOW);//bit5
      break;
    case 6:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 5
      mcp.digitalWrite(2, HIGH);//bit1
      mcp.digitalWrite(3, LOW);//bit2
      mcp.digitalWrite(4, HIGH);//bit3
      mcp.digitalWrite(5, LOW);//bit4
      mcp.digitalWrite(6, LOW);//bit5
      break;
    case 7:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 6
      mcp.digitalWrite(2, HIGH);//bit1
      mcp.digitalWrite(3, HIGH);//bit2
      mcp.digitalWrite(4, HIGH);//bit3
      mcp.digitalWrite(5, LOW);//bit4
      mcp.digitalWrite(6, LOW);//bit5
      break;
    case 8:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 7
      mcp.digitalWrite(2, LOW);//bit1
      mcp.digitalWrite(3, LOW);//bit2
      mcp.digitalWrite(4, LOW);//bit3
      mcp.digitalWrite(5, HIGH);//bit4
      mcp.digitalWrite(6, LOW);//bit5
      break;
    case 9:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 8
      mcp.digitalWrite(2, LOW);//bit1
      mcp.digitalWrite(3, LOW);//bit2
      mcp.digitalWrite(4, LOW);//bit3
      mcp.digitalWrite(5, HIGH);//bit4
      mcp.digitalWrite(6, LOW);//bit5
      break;
    case 10:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 9
      mcp.digitalWrite(2, HIGH);//bit1
      mcp.digitalWrite(3, LOW);//bit2
      mcp.digitalWrite(4, LOW);//bit3
      mcp.digitalWrite(5, HIGH);//bit4
      mcp.digitalWrite(6, LOW);//bit5
      break;
    case 11:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 10
      mcp.digitalWrite(2, LOW);//bit1
      mcp.digitalWrite(3, HIGH);//bit2
      mcp.digitalWrite(4, LOW);//bit3
      mcp.digitalWrite(5, HIGH);//bit4
      mcp.digitalWrite(6, LOW);//bit5
      break;
    case 12:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 11
      mcp.digitalWrite(2, HIGH);//bit1
      mcp.digitalWrite(3, HIGH);//bit2
      mcp.digitalWrite(4, LOW);//bit3
      mcp.digitalWrite(5, HIGH);//bit4
      mcp.digitalWrite(6, LOW);//bit5
      break;
    case 13:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 12
      mcp.digitalWrite(2, LOW);//bit1
      mcp.digitalWrite(3, LOW);//bit2
      mcp.digitalWrite(4, HIGH);//bit3
      mcp.digitalWrite(5, HIGH);//bit4
      mcp.digitalWrite(6, LOW);//bit5
      break;
    case 14:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 13
      mcp.digitalWrite(2, HIGH);//bit1
      mcp.digitalWrite(3, LOW);//bit2
      mcp.digitalWrite(4, HIGH);//bit3
      mcp.digitalWrite(5, HIGH);//bit4
      mcp.digitalWrite(6, LOW);//bit5
      break;
    case 15:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 14
      mcp.digitalWrite(2, LOW);//bit1
      mcp.digitalWrite(3, HIGH);//bit2
      mcp.digitalWrite(4, HIGH);//bit3
      mcp.digitalWrite(5, HIGH);//bit4
      mcp.digitalWrite(6, LOW);//bit5
      break;
    case 16:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 15
      mcp.digitalWrite(2, HIGH);//bit1
      mcp.digitalWrite(3, HIGH);//bit2
      mcp.digitalWrite(4, HIGH);//bit3
      mcp.digitalWrite(5, HIGH);//bit4
      mcp.digitalWrite(6, LOW);//bit5
      break;
    case 17:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 16
      mcp.digitalWrite(2, LOW);//bit1
      mcp.digitalWrite(3, LOW);//bit2
      mcp.digitalWrite(4, LOW);//bit3
      mcp.digitalWrite(5, LOW);//bit4
      mcp.digitalWrite(6, HIGH);//bit5
      break;
    case 18:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 17
      mcp.digitalWrite(2, HIGH);//bit1
      mcp.digitalWrite(3, LOW);//bit2
      mcp.digitalWrite(4, LOW);//bit3
      mcp.digitalWrite(5, LOW);//bit4
      mcp.digitalWrite(6, HIGH);//bit5
      break;
    case 19:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 18
      mcp.digitalWrite(2, LOW);//bit1
      mcp.digitalWrite(3, HIGH);//bit2
      mcp.digitalWrite(4, LOW);//bit3
      mcp.digitalWrite(5, LOW);//bit4
      mcp.digitalWrite(6, HIGH);//bit5
      break;
    case 20:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 19
      mcp.digitalWrite(2, HIGH);//bit1
      mcp.digitalWrite(3, HIGH);//bit2
      mcp.digitalWrite(4, LOW);//bit3
      mcp.digitalWrite(5, LOW);//bit4
      mcp.digitalWrite(6, HIGH);//bit5
      break;
    case 21:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 20
      mcp.digitalWrite(2, LOW);//bit1
      mcp.digitalWrite(3, LOW);//bit2
      mcp.digitalWrite(4, HIGH);//bit3
      mcp.digitalWrite(5, LOW);//bit4
      mcp.digitalWrite(6, HIGH);//bit5
      break;
    case 22:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 21
      mcp.digitalWrite(2, HIGH);//bit1
      mcp.digitalWrite(3, LOW);//bit2
      mcp.digitalWrite(4, HIGH);//bit3
      mcp.digitalWrite(5, LOW);//bit4
      mcp.digitalWrite(6, HIGH);//bit5
      break;
    case 23:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 22
      mcp.digitalWrite(2, LOW);//bit1
      mcp.digitalWrite(3, HIGH);//bit2
      mcp.digitalWrite(4, HIGH);//bit3
      mcp.digitalWrite(5, LOW);//bit4
      mcp.digitalWrite(6, HIGH);//bit5
      break;
    case 24:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 23
      mcp.digitalWrite(2, HIGH);//bit1
      mcp.digitalWrite(3, HIGH);//bit2
      mcp.digitalWrite(4, HIGH);//bit3
      mcp.digitalWrite(5, LOW);//bit4
      mcp.digitalWrite(6, HIGH);//bit5
      break;
    case 25:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 24
      mcp.digitalWrite(2, LOW);//bit1
      mcp.digitalWrite(3, LOW);//bit2
      mcp.digitalWrite(4, LOW);//bit3
      mcp.digitalWrite(5, HIGH);//bit4
      mcp.digitalWrite(6, HIGH);//bit5
      break;
    case 26:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 25
      mcp.digitalWrite(2, HIGH);//bit1
      mcp.digitalWrite(3, LOW);//bit2
      mcp.digitalWrite(4, LOW);//bit3
      mcp.digitalWrite(5, HIGH);//bit4
      mcp.digitalWrite(6, HIGH);//bit5
      break;
    case 27:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 26
      mcp.digitalWrite(2, LOW);//bit1
      mcp.digitalWrite(3, HIGH);//bit2
      mcp.digitalWrite(4, LOW);//bit3
      mcp.digitalWrite(5, HIGH);//bit4
      mcp.digitalWrite(6, HIGH);//bit5
      break;
    case 28:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 27
      mcp.digitalWrite(2, HIGH);//bit1
      mcp.digitalWrite(3, HIGH);//bit2
      mcp.digitalWrite(4, LOW);//bit3
      mcp.digitalWrite(5, HIGH);//bit4
      mcp.digitalWrite(6, HIGH);//bit5
      break;
    case 29:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 28
      mcp.digitalWrite(2, LOW);//bit1
      mcp.digitalWrite(3, LOW);//bit2
      mcp.digitalWrite(4, HIGH);//bit3
      mcp.digitalWrite(5, HIGH);//bit4
      mcp.digitalWrite(6, HIGH);//bit5
      break;
    case 30:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 29
      mcp.digitalWrite(2, HIGH);//bit1
      mcp.digitalWrite(3, LOW);//bit2
      mcp.digitalWrite(4, HIGH);//bit3
      mcp.digitalWrite(5, HIGH);//bit4
      mcp.digitalWrite(6, HIGH);//bit5
      break;
    case 31:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 30
      mcp.digitalWrite(2, LOW);//bit1
      mcp.digitalWrite(3, HIGH);//bit2
      mcp.digitalWrite(4, HIGH);//bit3
      mcp.digitalWrite(5, HIGH);//bit4
      mcp.digitalWrite(6, HIGH);//bit5
      break;
    case 32:
      mcp.digitalWrite(1, HIGH);//Ventilatore ON 31
      mcp.digitalWrite(2, HIGH);//bit1
      mcp.digitalWrite(3, HIGH);//bit2
      mcp.digitalWrite(4, HIGH);//bit3
      mcp.digitalWrite(5, HIGH);//bit4
      mcp.digitalWrite(6, HIGH);//bit5
      break;
    default:
      // if nothing else matches, do the default
      // default is optional
      break;
  }
}
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world");
      // ... and resubscribe
      client.subscribe("inTopic");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}
void loop() {
  // int x = 0;
  // velocita(x);
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
  //void velocita();
  long now = millis();
  /*
    if (now - lastMsg > 2000) {
     lastMsg = now;
     ++value;
     snprintf (msg, 75, "hello world #%ld", value);
     Serial.print("Publish message: ");
     Serial.println(msg);
     client.publish("outTopic", msg);



    } */
}
