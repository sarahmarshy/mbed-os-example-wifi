/* WiFi Example
 * Copyright (c) 2016 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed.h"
#include "TCPSocket.h"
#include "MXCHIPInterface.h"

MXCHIPInterface wifi(D10,D2,1);
Serial pc(STDIO_UART_TX,STDIO_UART_RX,115200);

void http_demo(NetworkInterface *net)
{
    TCPSocket socket;
    nsapi_error_t response;

    printf("Sending HTTP request to www.arm.com...\r\n");

    // Open a socket on the network interface, and create a TCP connection to www.arm.com
    socket.open(net);
    response = socket.connect("www.arm.com", 80);
    if(0 != response) {
        printf("Error connecting: %d\r\n", response);
        socket.close();
        return;
    }

    // Send a simple http request
    char sbuffer[] = "GET / HTTP/1.1\r\nHost: www.arm.com\r\n\r\n";
    nsapi_size_t size = sizeof sbuffer;
    response = 0;
    while(size)
    {
        response = socket.send(sbuffer+response, size);
        if (response < 0) {
            printf("Error sending data: %d\r\n", response);
            socket.close();
            return;
        } else {
            size -= response;
            // Check if entire message was sent or not
            printf("sent %d [%.*s]\r\n", response, strstr(sbuffer, "\r\n")-sbuffer, sbuffer);
        }
    }

    // Recieve a simple http response and print out the response line
    char rbuffer[64];
    response = socket.recv(rbuffer, sizeof rbuffer);
    if (response < 0) {
        printf("Error receiving data: %d\r\n", response);
    } else {
        printf("recv %d [%.*s]\r\n", response, strstr(rbuffer, "\r\n")-rbuffer, rbuffer);
    }

    // Close the socket to return its memory and bring down the network interface
    socket.close();
}

int main()
{
    printf("WiFi example\r\n\r\n");

    printf("\r\nConnecting...\r\n");
    int ret = wifi.connect(MBED_CONF_APP_WIFI_SSID, MBED_CONF_APP_WIFI_PASSWORD, NSAPI_SECURITY_WPA_WPA2);
    if (ret != 0) {
        printf("\r\nConnection error\r\n");
        return -1;
    }

    printf("Success\r\n\r\n");
    printf("MAC: %s\r\n", wifi.get_mac_address());
    printf("IP: %s\r\n", wifi.get_ip_address());
    printf("Netmask: %s\r\n", wifi.get_netmask());
    printf("Gateway: %s\r\n", wifi.get_gateway());
    printf("RSSI: %d\r\n\r\n", wifi.get_rssi());

    http_demo(&wifi);

    wifi.disconnect();

    printf("\r\nDone\r\n");
}
