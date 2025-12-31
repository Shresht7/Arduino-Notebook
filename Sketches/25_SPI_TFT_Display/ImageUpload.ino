#include <WiFi.h>
#include <WebServer.h>
#include <TFT_eSPI.h>

const char *ssid = "YOUR_SSID";
const char *password = "YOUR_PASSWORD";

TFT_eSPI tft = TFT_eSPI();
WebServer server(80);

// The HTML page (stored as a string for simplicity)
extern const char index_html[];

void setup()
{
  Serial.begin(115200);
  tft.init();
  tft.setRotation(1); // Landscape
  tft.fillScreen(TFT_BLACK);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());

  // Root page
  server.on("/", HTTP_GET, []()
            { server.send(200, "text/html", index_html); });

  // Binary Image Receiver
  server.on("/upload", HTTP_POST, []()
            { server.send(200, "text/plain", "OK"); }, []()
            {
    HTTPUpload& upload = server.upload();
    if (upload.status == UPLOAD_FILE_START) {
      tft.setAddrWindow(0, 0, 160, 128); // Start from top-left
    } else if (upload.status == UPLOAD_FILE_WRITE) {
      // Stream bytes directly to the TFT
      tft.pushColors(upload.buf, upload.currentSize);
    } });

  server.begin();
}

void loop()
{
  server.handleClient();
}

// Minimal HTML/JS stored in a separate variable
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html>
<body>
  <h3>ESP32 Photo Frame</h3>
  <input type="file" id="picker" accept="image/*">
  <canvas id="c" width="160" height="128" style="display:none"></canvas>
  <script>
    document.getElementById('picker').onchange = function(e) {
      let img = new Image();
      img.onload = function() {
        let canvas = document.getElementById('c');
        let ctx = canvas.getContext('2d');
        ctx.drawImage(img, 0, 0, 160, 128); // Resize to TFT resolution
        
        let pixels = ctx.getImageData(0, 0, 160, 128).data;
        let rgb565 = new Uint8Array(160 * 128 * 2);
        
        for (let i = 0, j = 0; i < pixels.length; i += 4) {
          let r = pixels[i], g = pixels[i+1], b = pixels[i+2];
          // RGB888 to RGB565 conversion
          let val = ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
          // Big Endian Byte Swap for TFT
          rgb565[j++] = (val >> 8) & 0xFF;
          rgb565[j++] = val & 0xFF;
        }
        
        let blob = new Blob([rgb565], {type: 'application/octet-stream'});
        let formData = new FormData();
        formData.append("file", blob);
        fetch('/upload', {method: 'POST', body: formData});
      };
      img.src = URL.createObjectURL(e.target.files[0]);
    };
  </script>
</body>
</html>
)rawliteral";
