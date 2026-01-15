/*
  Example:  Wi-Fi Server Demo
  Boards: CodeCell C3 / CodeCell C3 Light / CodeCell C6 / CodeCell C6 Drive

  Overview:
  - Connects CodeCell to your Wi-Fi network (station mode).
  - Starts an HTTP server on port 80.
  - The root path (/) returns a simple web page showing the live proximity value.
  - Serial Monitor prints the assigned IP address so you can visit the page.

  How to Use:
  - Update ssid/password below with your Wi-Fi credentials.
  - Open the Serial Monitor at 115200 baud to see the IP address.
  - Visit http://<printed-ip>/ to view the proximity reading.

*/

#include <WiFi.h>
#include <WebServer.h>
#include <CodeCell.h>

CodeCell myCodeCell;

// IMPOTANT: Replace with your Wi-Fi credentials
const char* ssid     = "DIN_SSID";
const char* password = "Passord_til_wifi";

WebServer server(80);

// Serve a simple HTML page with the current proximity value
void handleRoot() {
  String html = R"rawliteral(
<!DOCTYPE html>
<html>
<head><title>CodeCell Live Data</title></head>
<body>
  <h1>Live Proximity with CodeCell C3</h1>
  <p>Proximity: <span id="proximity">Loading...</span></p>
  <script>
    function updateData() {
      fetch('/data')
        .then(response => response.json())
        .then(data => {
          document.getElementById('proximity').textContent = data.proximity;
        })
        .catch(error => console.error('Error:', error));
    }
    updateData(); // Initial load
    setInterval(updateData, 1000); // Refresh every 1 second
  </script>
</body>
</html>
  )rawliteral";
  server.send(200, "text/html", html);
}

void setup() {
  Serial.begin(115200);                                     // Start USB serial at 115200 baud

  myCodeCell.Init(LIGHT);                                   // Enable light + proximity sensing

  WiFi.begin(ssid, password);                               // Connect to existing Wi-Fi network
  Serial.print("Connecting to Wi-Fi");
  while (WiFi.status() != WL_CONNECTED) {                   // Wait for connection
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConnected to Wi-Fi");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());                           // Print the IP to visit

  server.on("/", handleRoot);
  server.on("/data", []() {
  int proximityValue = myCodeCell.Light_ProximityRead();
  String json = "{\"proximity\":" + String(proximityValue) + "}";
  server.send(200, "application/json", json);
});                               // Register the root handler
  server.begin();                                           // Start HTTP server
  Serial.println("HTTP server started");
}

void loop() {
  if (myCodeCell.Run(10)) {                                 // Run the CodeCell service loop at 10 Hz
    server.handleClient();                                  // Handle incoming HTTP requests
  }
}
