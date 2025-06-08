#include <WiFi.h>
#include <esp_now.h>

uint8_t receiverAddress[] = {0x78, 0x42, 0x1C, 0x6C, 0x76, 0xEC}; // Replace with receiver MAC

typedef struct struct_message {
  char msg[32];
} struct_message;

struct_message myData;

void OnDataSent(const uint8_t *mac_addr, esp_now_send_status_t status) {
  Serial.print("Delivery Status: ");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Success" : "Fail");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);
  
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_send_cb(OnDataSent);

  esp_now_peer_info_t peerInfo = {};
  memcpy(peerInfo.peer_addr, receiverAddress, 6);
  peerInfo.channel = 0;
  peerInfo.encrypt = false;

  if (!esp_now_add_peer(&peerInfo)) {
    Serial.println("Peer added successfully");
  }

  strcpy(myData.msg, "Hello ESP32!");

  esp_now_send(receiverAddress, (uint8_t *)&myData, sizeof(myData));
}

void loop() {
  delay(2000);
  strcpy(myData.msg, "Ping!");
  esp_now_send(receiverAddress, (uint8_t *)&myData, sizeof(myData));
}
