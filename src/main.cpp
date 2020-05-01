#include <Arduino.h>
#include <WiFi.h>
#include <AsyncUDP.h>
#include <Ticker.h>
#include <CStreamer.h>
#include <CRtspSession.h>
#include <OV2640Streamer.h>
#include "main.h"
#include "car.h"
#include "util.h"
#include "UltrasonicRanging.h"

WiFiServer ser;
AsyncUDP udp;
Car car;
UltrasonicRanging ur;
CStreamer *streamer;
CRtspSession *session;
WiFiClient client;
OV2640 cam;

Ticker car_timeout_ticker;

void setup() {
    Serial.begin(115200);
    camera_config_t config;
    config.ledc_channel = LEDC_CHANNEL_0;
    config.ledc_timer = LEDC_TIMER_0;
    config.pin_d0 = Y2_GPIO_NUM;
    config.pin_d1 = Y3_GPIO_NUM;
    config.pin_d2 = Y4_GPIO_NUM;
    config.pin_d3 = Y5_GPIO_NUM;
    config.pin_d4 = Y6_GPIO_NUM;
    config.pin_d5 = Y7_GPIO_NUM;
    config.pin_d6 = Y8_GPIO_NUM;
    config.pin_d7 = Y9_GPIO_NUM;
    config.pin_xclk = XCLK_GPIO_NUM;
    config.pin_pclk = PCLK_GPIO_NUM;
    config.pin_vsync = VSYNC_GPIO_NUM;
    config.pin_href = HREF_GPIO_NUM;
    config.pin_sscb_sda = SIOD_GPIO_NUM;
    config.pin_sscb_scl = SIOC_GPIO_NUM;
    config.pin_pwdn = PWDN_GPIO_NUM;
    config.pin_reset = RESET_GPIO_NUM;
    config.xclk_freq_hz = 20000000;
    config.pixel_format = PIXFORMAT_JPEG;
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
//    Serial.setDebugOutput(true);
    WiFi.mode(WIFI_STA);
    WiFi.setAutoReconnect(true);
    WiFi.setAutoConnect(true);
    WiFi.setHostname("car");
    WiFi.setSleep(false);
    //连接wifi
    WiFi.begin(ssid, pwd);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }
    //初始化udp服务器
    if (!udp.listen(UDP_PORT)) {
        Serial.println("udo listen fail");
    }
    udp.onPacket(udpHandler);
    Serial.println(WiFi.localIP());
    cam.init(config);
    //初始化tcp服务器
    ser.begin(TCP_PORT);
    //定时任务
    car_timeout_ticker.attach_ms(CAR_TICKER_TIME, car_timeout_call_back);
    cam.setFrameSize(FRAMESIZE_VGA);
    cam.setPixelFormat(PIXFORMAT_YUV422);
}

void loop() {
    if (session) {
        session->handleRequests(0); // we don't use a timeout here,
        session->broadcastCurrentFrame(millis());
        if (session->m_stopped) {
            delete session;
            delete streamer;
            session = NULL;
            streamer = NULL;
        }
    } else {
        client = ser.accept();
        if (client) {
            // rtsp://ip:port/mjpeg/1
            //streamer = new SimStreamer(&client, true);             // our streamer for UDP/TCP based RTP transport
            streamer = new OV2640Streamer(&client, cam);             // our streamer for UDP/TCP based RTP transport
            session = new CRtspSession(&client, streamer); // our threads RTSP session and state
        }
    }
    delay(MSEC_PER_FRAME);
}

static void car_timeout_call_back() {
    //如果运行命令超时则停车
    if (millis()- car.run_time > car.timeout) {
        car.stop();
    }
}


static void udpHandler(AsyncUDPPacket packet) {
    switch (packet.length()) {
        case COMMAND_LENGTH: {
            if (ccieq(go_command, strlen(go_command), packet.data(), packet.length())) {
                car.go();
            } else if (ccieq(back_command, strlen(back_command), packet.data(), packet.length())) {
                //判断距离是否过近
                if (ur.getDistance() > car.getMinBack()) {
                    car.back();
                } else { car.stop(); }
            } else if (ccieq(left_command, strlen(left_command), packet.data(), packet.length())) {
                car.left();
            } else if (ccieq(right_command, strlen(right_command), packet.data(), packet.length())) {
                car.right();
            } else if (ccieq(stop_command, strlen(stop_command), packet.data(), packet.length())) {
                car.stop();
            }
            break;
        }
    }
}