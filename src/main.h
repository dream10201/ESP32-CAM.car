//
// Created by xl on 2020/4/15.
//

#ifndef CARESP32CAM_MAIN_H
#define CARESP32CAM_MAIN_H

#define PWDN_GPIO_NUM     32
#define RESET_GPIO_NUM    -1
#define XCLK_GPIO_NUM      0
#define SIOD_GPIO_NUM     26
#define SIOC_GPIO_NUM     27

#define Y9_GPIO_NUM       35
#define Y8_GPIO_NUM       34
#define Y7_GPIO_NUM       39
#define Y6_GPIO_NUM       36
#define Y5_GPIO_NUM       21
#define Y4_GPIO_NUM       19
#define Y3_GPIO_NUM       18
#define Y2_GPIO_NUM        5
#define VSYNC_GPIO_NUM    25
#define HREF_GPIO_NUM     23
#define PCLK_GPIO_NUM     22

#define TCP_PORT 80
#define UDP_PORT 1314
#define CAR_TICKER_TIME  50
#define COMMAND_LENGTH  6
//毫秒每帧
#define MSEC_PER_FRAME  60


const char *go_command = "ccccgo";
const char *back_command = "ccback";
const char *left_command = "ccleft";
const char *right_command = "cright";
const char *stop_command = "ccstop";

static const char *ssid = "TP-LINK_10bs";
static const char *pwd = "lhj362526*";
//static camera_fb_t *fb = NULL;
static void udpHandler(AsyncUDPPacket packet);
static void car_timeout_call_back();

#endif //CARESP32CAM_MAIN_H
