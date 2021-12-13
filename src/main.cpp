#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#define gpio4LEDPin 4 /* One LED connected to GPIO4 - D2 */
#define gpio5LEDPin 5 /* One LED connected to GPIO5 - D1 */

// Define de  functions to handle HTTP get requests
  void PrintMensage(String Mensage);
  void handle_NoFound(void);
  void handle_OnConnect(void);
  void handle_OnRed(void);
  void handle_OnGreen(void);
  void handle_OnBlue(void);
  void handle_OnRGBRed(void);
  void handle_OnRGBGreen(void);
  void handle_OnRGBBlue(void);
  void handle_OnRGBridness(void);
  void handle_OnPowerOn(void);
  void handle_OnPowerOff(void);



const char* ssid = "FIBRA-170E"; /* Add your router's SSID */
const char* password = "0Z17005124"; /*Add the password */

ESP8266WebServer WebServer(80);
int gpio4Value; 
int gpio5Value;

void setup() 
{
  Serial.begin(9600); /* Begin Serial Communication with 115200 Baud Rate */
  /* Configure GPIO4 and GPIO5 Pins as OUTPUTs */

// Setup HTTP requests funtions

WebServer.on("/",handle_OnConnect);
WebServer.onNotFound(handle_NoFound);
WebServer.on("/red",handle_OnRed);
WebServer.on("/green",handle_OnRGBGreen);
WebServer.on("/blue",handle_OnBlue);
WebServer.on("/rbgred",handle_OnRGBRed);
WebServer.on("/rgbgree",handle_OnRGBGreen);
WebServer.on("/rgbblue",handle_OnRGBBlue);
WebServer.on("/rgbbritness",handle_OnRGBridness);
WebServer.on("/on",handle_OnPowerOn);
WebServer.on("/off",handle_OnPowerOn);

WebServer.begin(); // Start webserver to listen to requests



  pinMode(gpio4LEDPin, OUTPUT);
  pinMode(gpio5LEDPin, OUTPUT);
  /* Set the initial values of GPIO4 and GPIO5 as LOW*/
  /* Both the LEDs are initially OFF */
  digitalWrite(gpio4LEDPin, LOW);
  digitalWrite(gpio5LEDPin, LOW);
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.print("\n");
  Serial.print("Connecting to: ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA); /* Configure ESP8266 in STA Mode */
  WiFi.begin(ssid, password); /* Connect to Wi-Fi based on above SSID and Password */
  while(WiFi.status() != WL_CONNECTED)
  {
    Serial.print("*");
    digitalWrite(LED_BUILTIN, HIGH);
    delay(2500);
    digitalWrite(LED_BUILTIN,LOW);
    delay(250);
  }

  digitalWrite(LED_BUILTIN,LOW);
  Serial.print("\n");
  Serial.print("Connected to Wi-Fi: ");
  Serial.println(WiFi.SSID());
  delay(100);
  Serial.print("\n");
  Serial.println("Starting ESP8266 Web Server...");
 
  Serial.println("ESP8266 Web Server Started");
  Serial.print("\n");
  Serial.print("The URL of ESP8266 Web Server is: ");
  Serial.print("http://");
  Serial.println(WiFi.localIP());
  Serial.print("\n");
  Serial.println("Use the above URL in your Browser to access ESP8266 Web Server\n");

  }

void loop()
{
  
  /* HTTP Response in the form of HTML Web Page */
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(); //  IMPORTANT
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.println("<head>");
  client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  client.println("<link rel=\"icon\" href=\"data:,\">");
  /* CSS Styling for Buttons and Web Page */
  client.println("<style>");
  client.println("html { font-family: Courier New; display: inline-block; margin: 0px auto; text-align: center;}");
  client.println(".button {border: none; color: white; padding: 10px 20px; text-align: center;");
  client.println("text-decoration: none; font-size: 25px; margin: 2px; cursor: pointer;}");
  client.println(".button1 {background-color: #13B3F0;}");
  client.println(".button2 {background-color: #3342FF;}");
  client.println("</style>");
  client.println("</head>");
  
  /* The main body of the Web Page */
  client.println("<body>");
  client.println("<h2>ESP8266 Web Server</h2>");
  
  if(gpio4Value == LOW) 
  {
    client.println("<p>GPIO4 LED Status: OFF</p>");
    client.print("<p><a href=\"/GPIO4ON\"><button class=\"button button1\">Click to turn ON</button></a></p>");  
  } 
  else 
  {
    client.println("<p>GPIO4 LED Status: ON</p>");
    client.print("<p><a href=\"/GPIO4OFF\"><button class=\"button button2\">Click to turn OFF</button></a></p>"); 
  }
  
  if(gpio5Value == LOW) 
  {
    client.println("<p>GPIO5 LED Status: OFF</p>");
    client.print("<p><a href=\"/GPIO5ON\"><button class=\"button button1\">Click to turn ON</button></a></p>");  
  } 
  else 
  {
    client.println("<p>GPIO5 LED Status: ON</p>");
    client.print("<p><a href=\"/GPIO5OFF\"><button class=\"button button2\">Click to turn OFF</button></a></p>");  
  }
  
  client.println("</body>");
  client.println("</html>");
  client.print("\n");
  
  delay(1);
  /* Close the connection */
  client.stop();
  Serial.println("Client disconnected");
  Serial.print("\n");
}

  void PrintMensage(String Mensage){

    Serial.println("------------------------------------------------------------");

    Serial.println(Mensage);

    Serial.println("------------------------------------------------------------");

  }

  void handle_NoFound(void) {
    PrintMensage(" Page not foound ");
  }

  void handle_OnConnect(void){
    PrintMensage(" Client Connected ");

  }

  void handle_OnRed(void){
    PrintMensage("Turn on Red");
  }

  void handle_OnGreen(void){
         PrintMensage("Turn on Green");
  }

  void handle_OnBlue(void){
        PrintMensage("Turn on Blue");
  }

  void handle_OnRGBRed(void){

       PrintMensage("Received RGBRed Value");
  }

  void handle_OnRGBGreen(void){

              PrintMensage("Received RGBGreen Value");
  }

  void handle_OnRGBBlue(void){
                PrintMensage("Received RGRBlue Value");
  }

  void handle_OnRGBridness(void){
              PrintMensage("Received RGRBrigth Value");
  }

  void handle_OnPowerOn(void){
     PrintMensage("Turn Lights On");
  }

  void handle_OnPowerOff(void){
     PrintMensage("Turn Lights On");
  }