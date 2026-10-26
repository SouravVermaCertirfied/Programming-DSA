// this not a weather  app, rather a racing game that can be played via phone pico hotspot on phone at http://192.168.4.1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "pico/cyw43_arch.h"
#include "lwip/tcp.h"

// Pin definitions
#define PIN_SCK   18
#define PIN_MOSI  19
#define PIN_CS    17
#define PIN_DC    16
#define PIN_RST   21

// ST7735 Commands
#define ST7735_SWRESET 0x01
#define ST7735_SLPOUT  0x11
#define ST7735_DISPON  0x29
#define ST7735_CASET   0x2A
#define ST7735_RASET   0x2B
#define ST7735_RAMWR   0x2C
#define ST7735_MADCTL  0x36
#define ST7735_COLMOD  0x3A

// Colors (RGB565)
#define COLOR_BG      0x1002 
#define COLOR_ROAD    0x18E3 
#define COLOR_CYAN    0x07EF 
#define COLOR_MAGENTA 0xF81F 
#define COLOR_PURPLE  0x4010 
#define COLOR_YELLOW  0xFFE0 
#define COLOR_RED     0xF800 
#define COLOR_WHITE   0xFFFF

// RAM Framebuffer (40 KB)
static uint16_t fb[160][128];

// Road layout & Player
#define ROAD_LEFT   24
#define ROAD_RIGHT  104
int road_scroll = 0;
int player_lane = 1; // 0: Left, 1: Center, 2: Right
int lane_centers[3] = {40, 64, 88};

// Traffic Cars
typedef struct {
    int lane;
    float y;
    uint16_t color;
} TrafficCar;

TrafficCar traffic[3];

void tft_write_command(uint8_t cmd) {
    gpio_put(PIN_DC, 0); gpio_put(PIN_CS, 0); 
    spi_write_blocking(spi0, &cmd, 1);
    gpio_put(PIN_CS, 1); 
}

void tft_write_data(const uint8_t *data, size_t len) {
    gpio_put(PIN_DC, 1); gpio_put(PIN_CS, 0); 
    spi_write_blocking(spi0, data, len);
    gpio_put(PIN_CS, 1); 
}

void tft_init() {
    spi_init(spi0, 20 * 1000 * 1000); // 20 MHz
    spi_set_format(spi0, 8, SPI_CPOL_0, SPI_CPHA_0, SPI_MSB_FIRST);
    gpio_set_function(PIN_SCK, GPIO_FUNC_SPI);
    gpio_set_function(PIN_MOSI, GPIO_FUNC_SPI);

    gpio_init(PIN_CS);  gpio_set_dir(PIN_CS, GPIO_OUT);   gpio_put(PIN_CS, 1);
    gpio_init(PIN_DC);  gpio_set_dir(PIN_DC, GPIO_OUT);   gpio_put(PIN_DC, 1);
    gpio_init(PIN_RST); gpio_set_dir(PIN_RST, GPIO_OUT);  gpio_put(PIN_RST, 1);

    gpio_put(PIN_RST, 1); sleep_ms(50);
    gpio_put(PIN_RST, 0); sleep_ms(50);
    gpio_put(PIN_RST, 1); sleep_ms(150);

    tft_write_command(ST7735_SWRESET); sleep_ms(150);
    tft_write_command(ST7735_SLPOUT);  sleep_ms(255);

    tft_write_command(ST7735_COLMOD);
    uint8_t color_mode = 0x05; 
    tft_write_data(&color_mode, 1);

    tft_write_command(ST7735_MADCTL);
    uint8_t madctl = 0xC0;
    tft_write_data(&madctl, 1);

    tft_write_command(ST7735_DISPON);
    sleep_ms(100);
}

void fb_fill_rect(int x0, int y0, int w, int h, uint16_t color) {
    if (x0 >= 128 || y0 >= 160) return;
    if (x0 + w > 128) w = 128 - x0;
    if (y0 + h > 160) h = 160 - y0;
    if (x0 < 0) { w += x0; x0 = 0; }
    if (y0 < 0) { h += y0; y0 = 0; }

    for (int y = y0; y < y0 + h; y++) {
        for (int x = x0; x < x0 + w; x++) {
            fb[y][x] = color;
        }
    }
}

void tft_flush() {
    tft_write_command(ST7735_CASET);
    uint8_t x_data[] = {0x00, 0x00, 0x00, 127};
    tft_write_data(x_data, 4);

    tft_write_command(ST7735_RASET);
    uint8_t y_data[] = {0x00, 0x00, 0x00, 159};
    tft_write_data(y_data, 4);

    tft_write_command(ST7735_RAMWR);

    gpio_put(PIN_DC, 1);
    gpio_put(PIN_CS, 0);
    spi_write_blocking(spi0, (const uint8_t *)fb, sizeof(fb));
    gpio_put(PIN_CS, 1);
}

void reset_traffic() {
    for (int i = 0; i < 3; i++) {
        traffic[i].lane = rand() % 3;
        traffic[i].y = -40.0f - (i * 60);
        traffic[i].color = (i == 0) ? COLOR_RED : COLOR_MAGENTA;
    }
}

// HTTP Server Callback for Mobile Controls
static err_t http_recv(void *arg, struct tcp_pcb *tpcb, struct pbuf *p, err_t err) {
    if (!p) {
        tcp_close(tpcb);
        return ERR_OK;
    }

    char *req = (char *)p->payload;
    if (strstr(req, "GET /L") != NULL) {
        if (player_lane > 0) player_lane--;
    } else if (strstr(req, "GET /R") != NULL) {
        if (player_lane < 2) player_lane++;
    }

    const char *html = 
        "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n"
        "<!DOCTYPE html><html><head><meta name='viewport' content='width=device-width, initial-scale=1.0'>"
        "<style>"
        "body{background:#0a0a16;color:#00ffff;text-align:center;font-family:sans-serif;margin:0;padding-top:40px;}"
        "h1{letter-spacing:2px;text-shadow:0 0 10px #ff00ff;}"
        ".btn-container{display:flex;justify-content:center;gap:20px;margin-top:60px;}"
        "button{font-size:32px;padding:40px 30px;width:130px;background:#181830;border:3px solid #00ffff;"
        "color:#00ffff;border-radius:20px;font-weight:bold;box-shadow:0 0 15px #00ffff55;outline:none;}"
        "button:active{background:#ff00ff;border-color:#ff00ff;color:#ffffff;box-shadow:0 0 20px #ff00ff;}"
        "</style></head><body>"
        "<h1>CYBER RACER</h1><p>Steer Your Supercar</p>"
        "<div class='btn-container'>"
        "<button onclick=\"fetch('/L')\">LEFT</button>"
        "<button onclick=\"fetch('/R')\">RIGHT</button>"
        "</div></body></html>";

    tcp_write(tpcb, html, strlen(html), TCP_WRITE_FLAG_COPY);
    tcp_output(tpcb);

    tcp_recved(tpcb, p->tot_len);
    pbuf_free(p);
    tcp_close(tpcb);
    return ERR_OK;
}

static err_t http_accept(void *arg, struct tcp_pcb *newpcb, err_t err) {
    tcp_recv(newpcb, http_recv);
    return ERR_OK;
}

int main() {
    stdio_init_all();
    tft_init();
    reset_traffic();

    // 1. Initialize Wi-Fi in AP Mode (Built-in network handler manages IP assignment)
    if (cyw43_arch_init()) {
        return 1;
    }
    cyw43_arch_enable_ap_mode("PicoRacer", "12345678", CYW43_AUTH_WPA2_MIXED_PSK);

    // 2. Start TCP Web Server on Port 80
    struct tcp_pcb *server_pcb = tcp_new();
    tcp_bind(server_pcb, IP_ADDR_ANY, 80);
    server_pcb = tcp_listen(server_pcb);
    tcp_accept(server_pcb, http_accept);

    while (true) {
        cyw43_arch_poll();

        // Clear Framebuffer
        fb_fill_rect(0, 0, 128, 160, COLOR_BG);

        // Cityscape
        fb_fill_rect(0, 40, 20, 120, COLOR_PURPLE);
        fb_fill_rect(4, 50, 3, 6, COLOR_CYAN);
        fb_fill_rect(12, 70, 3, 6, COLOR_MAGENTA);
        fb_fill_rect(6, 110, 3, 6, COLOR_CYAN);

        fb_fill_rect(108, 20, 20, 140, COLOR_PURPLE);
        fb_fill_rect(112, 30, 3, 6, COLOR_MAGENTA);
        fb_fill_rect(118, 80, 3, 6, COLOR_CYAN);
        fb_fill_rect(114, 120, 3, 6, COLOR_MAGENTA);

        // Road
        fb_fill_rect(ROAD_LEFT, 0, ROAD_RIGHT - ROAD_LEFT, 160, COLOR_ROAD);
        fb_fill_rect(ROAD_LEFT, 0, 2, 160, COLOR_CYAN);
        fb_fill_rect(ROAD_RIGHT - 2, 0, 2, 160, COLOR_CYAN);

        road_scroll = (road_scroll + 4) % 16;
        for (int y = -16 + road_scroll; y < 160; y += 16) {
            fb_fill_rect(63, y, 2, 8, COLOR_WHITE);
        }

        // Traffic
        for (int i = 0; i < 3; i++) {
            traffic[i].y += 3.5f;
            if (traffic[i].y > 160) {
                traffic[i].y = -30.0f;
                traffic[i].lane = rand() % 3;
            }

            int tx = lane_centers[traffic[i].lane] - 5;
            int ty = (int)traffic[i].y;

            fb_fill_rect(tx, ty, 10, 16, traffic[i].color);
            fb_fill_rect(tx + 1, ty + 14, 2, 2, COLOR_RED);
            fb_fill_rect(tx + 7, ty + 14, 2, 2, COLOR_RED);

            if (abs(lane_centers[player_lane] - lane_centers[traffic[i].lane]) < 4 && 
                abs(125 - ty) < 14) {
                reset_traffic();
            }
        }

        // Player
        int px = lane_centers[player_lane] - 5;
        int py = 125;

        fb_fill_rect(px, py, 10, 16, COLOR_CYAN);       
        fb_fill_rect(px + 2, py + 4, 6, 6, COLOR_BG);   
        fb_fill_rect(px, py, 2, 3, COLOR_YELLOW);       
        fb_fill_rect(px + 8, py, 2, 3, COLOR_YELLOW);
        fb_fill_rect(px + 1, py + 14, 2, 2, COLOR_MAGENTA); 
        fb_fill_rect(px + 7, py + 14, 2, 2, COLOR_MAGENTA);

        tft_flush();
        sleep_ms(22);
    }
}