void setupWebServer(){
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp32")) {
    Serial.println("MDNS responder started");
  }

  server.on("/", []() {
    server.send(200, "text/html", "<h1>Hello from the power measure station!</h1><a href=\"/now\">Click here</a> to retrieve the current measures");
  });

  server.on("/now", []() {
    char jsonTxt[100];
    sprintf(jsonTxt, "{intensity:%s,power:%s}", itensityTxt, powerTxt);
    server.send(200, "application/json", jsonTxt); //"{intensity:"+ itensityTxt + ",power:" + powerTxt + "}"
  });

  server.begin();
  Serial.println("HTTP server started");
}
