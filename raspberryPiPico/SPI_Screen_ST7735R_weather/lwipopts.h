#ifndef _LWIPOPTS_H
#define _LWIPOPTS_H

// Common settings for Pico Wi-Fi / lwIP
#define NO_SYS                      1
#define LWIP_SOCKET                 0
#define LWIP_NETCONN                0
#define LWIP_DHCP                   1
#define LWIP_ARP                    1
#define LWIP_ETHERNET               1
#define LWIP_ICMP                   1
#define LWIP_RAW                    1
#define LWIP_TCP                    1
#define LWIP_UDP                    1
#define LWIP_DNS                    1
#define LWIP_TCP_KEEPALIVE          1
#define LWIP_NETIF_TX_SINGLE_PBUF   1
#define DHCP_DOES_ARP_CHECK         0
#define LWIP_DHCP_MAX_NTP_SERVERS   1

#define MEM_ALIGNMENT               4
#define MEM_SIZE                    4000
#define MEMP_NUM_PBUF               15
#define MEMP_NUM_TCP_PCB            10
#define MEMP_NUM_TCP_SEG            32
#define MEMP_NUM_ARP_QUEUE          10
#define PBUF_POOL_SIZE              24
#define LWIP_STATS                  0
#define LWIP_PROVIDE_ERRNO          1

#endif