
/*https communication requires certificates to be known ahead of time so each entity will trust one another.
   This is a cert for google's generic servers below, allowing us to connect over https with their resources
*/
#include <WiFiClientSecure.h>
#include <WiFiClient.h>

WiFiClientSecure client;   //global WiFiClient Secure object use this one for localization

//const char NETWORK[] = "MIT";
//const char PASSWORD[] = "";
//const char POST_TEMP_CURR_URL[] = "/";
//const char SERVER_HOST[] = "http://608dev-2.net/sandbox/sc/team73/Server/server.py";
//const char POST_REQ_NO_BODY_NO_LEN[] = "POST / HTTP/1.1\r\nHost: http://608dev-2.net/sandbox/sc/team73/Server/server.py\r\nContent-Type: aplication/xxx-url-form-encoded\r\nContent-Length: ";
//char REQUEST_BUFFER[1000];

void wifiSetup(char* network, char* password) {
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.print(n);
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      Serial.printf("%d: %s, Ch:%d (%ddBm) %s ", i + 1, WiFi.SSID(i).c_str(), WiFi.channel(i), WiFi.RSSI(i), WiFi.encryptionType(i) == WIFI_AUTH_OPEN ? "open" : "");
      uint8_t* cc = WiFi.BSSID(i);
      for (int k = 0; k < 6; k++) {
        Serial.print(*cc, HEX);
        if (k != 5) Serial.print(":");
        cc++;
      }
      Serial.println("");
    }
  }
  delay(100);  //wait a bit (100 ms)

  //if using regular connection use line below:
  WiFi.begin(network, password);
  //if using channel/mac specification for crowded bands use the following:
  //WiFi.begin(network, password, channel, bssid);

  uint8_t count = 0;  //count used for Wifi check times
  Serial.print("Attempting to connect to ");
  Serial.println(network);
  while (WiFi.status() != WL_CONNECTED && count < 12) {
    delay(500);
    Serial.print(".");
    count++;
  }
  delay(2000);
  if (WiFi.isConnected()) {  //if we connected then print our IP, Mac, and SSID we're on
    Serial.println("CONNECTED!");
    Serial.printf("%d:%d:%d:%d (%s) (%s)\n", WiFi.localIP()[3], WiFi.localIP()[2],
                  WiFi.localIP()[1], WiFi.localIP()[0],
                  WiFi.macAddress().c_str(), WiFi.SSID().c_str());
    delay(500);
  } else {  //if we failed to connect just Try again.
    Serial.println("Failed to Connect :/  Going to restart");
    Serial.println(WiFi.status());
    ESP.restart();  // restart the ESP (proper way)
  }
}

/*----------------------------------
   char_append Function:
   Arguments:
      char* buff: pointer to character array which we will append a
      char c:
      uint16_t buff_size: size of buffer buff

   Return value:
      boolean: True if character appended, False if not appended (indicating buffer full)
*/
uint8_t char_append(char* buff, char c, uint16_t buff_size) {
  int len = strlen(buff);
  if (len > buff_size) return false;
  buff[len] = c;
  buff[len + 1] = '\0';
  return true;
}



/*----------------------------------
 * do_http_request Function:
 * Arguments:
 *    char* host: null-terminated char-array containing host to connect to
 *    char* request: null-terminated char-arry containing properly formatted HTTP request
 *    char* response: char-array used as output for function to contain response
 *    uint16_t response_size: size of response buffer (in bytes)
 *    uint16_t response_timeout: duration we'll wait (in ms) for a response from server
 *    uint8_t serial: used for printing debug information to terminal (true prints, false doesn't)
 * Return value:
 *    void (none)
 */
//void do_http_request(char* host, char* request, char* response, uint16_t response_size, uint16_t response_timeout, uint8_t serial){
//  if (client.connect(host, 80)) { //try to connect to host on port 80
//    if (serial) Serial.print(request);//Can do one-line if statements in C without curly braces
//    client.print(request);
//    memset(response, 0, response_size); //Null out (0 is the value of the null terminator '\0') entire buffer
//    uint32_t count = millis();
//    while (client.connected()) { //while we remain connected read out data coming back
//      client.readBytesUntil('\n',response,response_size);
//      if (serial) Serial.println(response);
//      if (strcmp(response,"\r")==0) { //found a blank line!
//        break;
//      }
//      memset(response, 0, response_size);
//      if (millis()-count>response_timeout) break;
//    }
//    memset(response, 0, response_size);  
//    count = millis();
//    while (client.available()) { //read out remaining text (body of response)
//      char_append(response,client.read(),response_size);
//    }
//    if (serial) Serial.println(response);
//    client.stop();
//    if (serial) Serial.println("-----------");  
//  }else{
//    if (serial) Serial.println("connection failed :/");
//    if (serial) Serial.println("wait 0.5 sec...");
//    client.stop();
//  }
//}  
void do_http_request(const char* host, char* request, char* response, uint16_t response_size, uint16_t response_timeout, uint8_t serial) {
  WiFiClient client; //instantiate a client object
  if (client.connect(host, 80)) { //try to connect to host on port 80
    if (serial) Serial.print(request);//Can do one-line if statements in C without curly braces
    client.print(request);
    memset(response, 0, response_size); //Null out (0 is the value of the null terminator '\0') entire buffer
    uint32_t count = millis();
    while (client.connected()) { //while we remain connected read out data coming back
      client.readBytesUntil('\n', response, response_size);
      if (serial) Serial.println(response);
      if (strcmp(response, "\r") == 0) { //found a blank line!
        break;
      }
      memset(response, 0, response_size);
      if (millis() - count > response_timeout) break;
    }
    memset(response, 0, response_size);
    count = millis();
    while (client.available()) { //read out remaining text (body of response)
      char_append(response, client.read(), OUT_BUFFER_SIZE);
    }
    if (serial) Serial.println(response);
    client.stop();
    if (serial) Serial.println("-----------");
  } else {
    if (serial) Serial.println("connection failed :/");
    if (serial) Serial.println("wait 0.5 sec...");
    client.stop();
  }
}
/*----------------------------------
   do_https_request Function. Similar to do_http_request, but supports https requests
   Arguments:
      char* host: null-terminated char-array containing host to connect to
      char* request: null-terminated char-arry containing properly formatted HTTP request
      char* response: char-array used as output for function to contain response
      uint16_t response_size: size of response buffer (in bytes)
      uint16_t response_timeout: duration we'll wait (in ms) for a response from server
      uint8_t serial: used for printing debug information to terminal (true prints, false doesn't)
   Return value:
      void (none)
*/
void do_https_request(char* host, char* request, char* response, uint16_t response_size, uint16_t response_timeout, uint8_t serial, const char* cert) {
  client.setHandshakeTimeout(30);
  client.setCACert(cert); //set cert for https
  if (client.connect(host,443,4000)) { //try to connect to host on port 443
    if (serial) Serial.print(request);//Can do one-line if statements in C without curly braces
    delay(10);
    Serial.println("there");
    client.print(request);
    response[0] = '\0';
    //memset(response, 0, response_size); //Null out (0 is the value of the null terminator '\0') entire buffer
    uint32_t count = millis();
    while (client.connected()) { //while we remain connected read out data coming back
      client.readBytesUntil('\n', response, response_size);
      if (serial) Serial.println(response);
      if (strcmp(response, "\r") == 0) { //found a blank line!
        break;
      }
      memset(response, 0, response_size);
      if (millis() - count > response_timeout) break;
    }
    memset(response, 0, response_size);
    count = millis();
    while (client.available()) { //read out remaining text (body of response)
      char_append(response, client.read(), response_size);
    }
    if (serial) Serial.println(response);
    client.stop();
    if (serial) Serial.println("-----------");
  } else {
    if (serial) Serial.println("connection failed :/");
    if (serial) Serial.println("wait 0.5 sec...");
    client.stop();
  }
}


//void post_temp_curr_to_host(float current, float temperature, char* response_buffer, int response_len) {
//  strcpy(REQUEST_BUFFER, POST_REQ_NO_BODY_NO_LEN);
//  int request_offset = strlen(REQUEST_BUFFER);
//
//  char body_buffer[100];
//  sprintf(body_buffer, "temperature=%f.5&current=%f.5", temperature, current);
//  int content_length = strlen(body_buffer);
//
//  request_offset += sprintf(REQUEST_BUFFER[request_offset], " %i\r\n\r\n", content_length);
//  request_offset += sprintf(REQUEST_BUFFER[request_offset], "%s\r\n", body_buffer);
//
//  do_https_request(SERVER_HOST, REQUEST_BUFFER, response_buffer, response_len, 10000);
//}
