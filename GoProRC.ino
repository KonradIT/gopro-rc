#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>

extern "C" {
#include <user_interface.h>
}

//Constants
const char *ssid = "HERO-RC-000000"; // HERO-RC-[last 3 octets of Mac addr]
const char *password = ""; 

const uint8_t mac[6] {0xD8, 0x96, 0x85, 0x00, 0x00, 0x00}; //D8:96:85:00:00:00

String GOPRO_IP = "127.0.0.1";
const String SHUTTER_URI = "http://" + GOPRO_IP + "/gp/gpControl/command/shutter?p=1";


HTTPClient http; 
void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println('\n');
  Serial.print("OLD ESP8266 MAC: ");
  Serial.println(WiFi.macAddress());

  wifi_set_macaddr(0, const_cast<uint8*>(mac)); 
  Serial.print("NEW ESP8266 MAC: ");
  Serial.println(WiFi.macAddress());

  /* DCHP settings */
  IPAddress ip(10, 71, 79, 1);
  IPAddress gateway(192, 168, 43, 1);
  IPAddress subnet(255, 255, 255, 0);
  WiFi.softAPConfig(ip, gateway, subnet);
  
  WiFi.softAP(ssid, password); 

  Serial.println('\n');
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" started");

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());
}

void loop() {
  delay(5000);
  client_status();
  delay(4000);
}
void makeReq(String addr) {

  http.begin("http://" + addr + "/gp/gpControl/command/shutter?p=1");
  int httpCode = http.GET();
  Serial.print("HTTPCODE" + httpCode);
  if (httpCode > 0) { 
    String payload = http.getString();
    Serial.println(payload);
  }
  http.end();
}
String IpAddress2String(const IPAddress& ipAddress){
  return String(ipAddress[0]) + String(".") + \
         String(ipAddress[1]) + String(".") + \
         String(ipAddress[2]) + String(".") + \
         String(ipAddress[3])  ;
}
void client_status() {
  unsigned char number_client;
  struct station_info *stat_info;

  struct ip4_addr *IPaddress;
  IPAddress address;
  int i = 1;

  number_client = wifi_softap_get_station_num();
  stat_info = wifi_softap_get_station_info();

  Serial.print(" Total Connected Clients are = ");
  Serial.println(number_client);

  while (stat_info != NULL) {
    http.begin(SHUTTER_URI);
    int httpCode = http.GET();
    Serial.print(" HttpCode ");
    Serial.print(httpCode);

    IPaddress = &stat_info->ip;
    address = IPaddress->addr;

    String strAddr = IpAddress2String(address);
    Serial.print("Trying... ");
    Serial.println(address);
    makeReq(strAddr);

    Serial.print("Trying... ");
    Serial.println("127.0.0.1");
    makeReq("127.0.0.1");
    
    stat_info = STAILQ_NEXT(stat_info, next);
    i++;
    Serial.println();
  }
}
