#include <ESP8266WiFi.h>
#include<WiFiUDP.h>

#define UDP_PORT 4201
 
// Replace with your network credentials
const char* ssid     = "Soft spot";   //wifi name
const char* password = "rotex.rotimipro8088";      //wifi password

// Set your Static IP address
IPAddress local_IP(192, 168, 65, 157);
// Set your Gateway IP address
IPAddress gateway(192, 168, 25, 61);

IPAddress subnet(255, 255, 0, 0);
IPAddress primaryDNS(8, 8, 8, 8); // optional
IPAddress secondaryDNS(8, 8, 4, 4); // optional

// Set web server port number to 80
WiFiServer server(UDP_PORT);

char str[128];

int spark1 = 0;
int spark2 = 0;
int spark3 = 0;
int spark4 = 0;

String string;


// UDP
WiFiUDP UDP;
char packet[255];

void setup() {
  Serial.begin(115200);
  // Initialize the INPUT variables as INPUTs

  // Configures static IP address
//  if (!WiFi.config(local_IP, gateway, subnet, primaryDNS, secondaryDNS)) {
//    Serial.println("STA Failed to configure");
//  }

 
  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  // Print local IP address and start web server
  Serial.println("");
  Serial.println("WiFi connected.");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  server.begin();

  // Begin listening to UDP port
  UDP.begin(UDP_PORT);
  Serial.print("Listening on UDP port ");
  Serial.println(UDP_PORT);

  sprintf(str, "%u,%u,%u,%u", spark1,spark2,spark3,spark4);
}

 
void loop() 
{
  if (Serial.available()){
      string = Serial.readString();
      string.toCharArray(str, 128);
      Serial.print(str);
    }
  
    int packetSize = UDP.parsePacket();
    if(packetSize)
    {   
      Serial.print("Received packet of size ");
      Serial.println(packetSize);
      Serial.print("From ");
      IPAddress remoteIp = UDP.remoteIP();
      Serial.print(remoteIp);
      Serial.print(", port ");
      Serial.println(UDP.remotePort());
  
      // read the packet into packetBufffer
      int len = UDP.read(packet,255);
      if (len >0) packet[len]=0;
      Serial.println("Contents:");
      Serial.println(packet);
      
      // send a reply, to the IP address and port that sent us the packet we received
      UDP.beginPacket(UDP.remoteIP(), UDP.remotePort());
      Serial.println("sending :");
      Serial.println(str);
      UDP.write(str);
      UDP.endPacket();
     }

}
