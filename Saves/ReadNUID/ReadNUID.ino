#include <WiFi.h>
#include <esp_now.h>

typedef struct struct_message {
  char msg[32];
} struct_message;

void OnDataRecv(const esp_now_recv_info_t *recvInfo, const uint8_t *data, int len) {
  struct_message incomingData;
  memcpy(&incomingData, data, sizeof(incomingData));

  char macStr[18];
  snprintf(macStr, sizeof(macStr), "%02X:%02X:%02X:%02X:%02X:%02X",
           recvInfo->src_addr[0], recvInfo->src_addr[1], recvInfo->src_addr[2],
           recvInfo->src_addr[3], recvInfo->src_addr[4], recvInfo->src_addr[5]);

  Serial.print("From: ");
  Serial.print(macStr);
  Serial.print(" | Message: ");
  Serial.println(incomingData.msg);
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed");
    return;
  }

  esp_now_register_recv_cb(OnDataRecv);
}

void loop() {
  // No loop logic needed
}
