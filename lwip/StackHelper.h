//
//  StackHelper.h
//  lwip
//
//  Created by 孔祥波 on 11/11/16.
//  Copyright © 2016 Kong XiangBo. All rights reserved.
//

#ifndef StackHelper_h
#define StackHelper_h

#include <stdio.h>
#include "ipaddr.h"
#import <lwip/tcp.h>
#import  <Foundation/Foundation.h>
#define BADDR_TYPE_NONE 0
#define BADDR_TYPE_IPV4 1
#define BADDR_TYPE_IPV6 2
#ifdef BADVPN_Darwin
#define BADDR_TYPE_PACKET 5
#endif

#define BADDR_MAX_ADDR_LEN 128

#define BIPADDR_MAX_PRINT_LEN 40
#define BADDR_MAX_PRINT_LEN 120

#define BADDR_PACKET_HEADER_TYPE_ETHERNET 1

#define BADDR_PACKET_PACKET_TYPE_HOST 1
#define BADDR_PACKET_PACKET_TYPE_BROADCAST 2
#define BADDR_PACKET_PACKET_TYPE_MULTICAST 3
#define BADDR_PACKET_PACKET_TYPE_OTHERHOST 4
#define BADDR_PACKET_PACKET_TYPE_OUTGOING 5

typedef struct {
    int type;
    union {
        struct {
            uint32_t ip;
            uint16_t port;
        } ipv4;
        struct {
            uint8_t ip[16];
            uint16_t port;
        } ipv6;
        struct {
            uint16_t phys_proto;
            int interface_index;
            int header_type;
            int packet_type;
            uint8_t phys_addr[8];
        } packet;
    };
} BAddr;
typedef struct {
    int type;
    union {
        uint32_t ipv4;
        uint8_t ipv6[16];
    };
} BIPAddr;

void logLWIPParams(void);
void init_lwip(void);


typedef  struct netif  *SFNetIF;

typedef  struct pbuf  *SFPbuf;
typedef  struct tcp_pcb  *SFPcb;
typedef  struct udp_pcb  *SFUPcb;
typedef  struct ip_pcb  SFIP;



@protocol TCPStackDelegate <NSObject>

//new tcp
-(void)incomingTCP:(struct tcp_pcb*)pcb;
//write data to system
-(void)writeDatagrams:(NSData*)data;
//raw tcp socket callback api
//socket-->TCPStackDelegate->Swift Class
-(void)client_sent_func:(void *)client;
-(void)client_handle_freed_client:(void *)client error:(int)err;
-(void)client_free_client:(void *)client;
-(void)incomingData:(NSData*)d len:(NSInteger)len client:(void *)client;
-(void)client_poll:(void*)client;
@end
    //block style
typedef void (^lwipInitComplete)(void);
void setupStackWithFin(id<TCPStackDelegate> object,lwipInitComplete complete);

const  char* pcbStatus(struct tcp_pcb* pcb);
enum tcp_state pcbStat(struct tcp_pcb*pcb);
void setupStack(id<TCPStackDelegate> object);

void nagle_disable(struct tcp_pcb*pcb);
err_t input(struct pbuf *p);
void pcbinfo(SFPcb pcb, uint32_t *srcip,uint32_t *dstip, uint16_t *sport , uint16_t *dport);
void inputData(NSData *data,NSInteger len);
BAddr baddr_from_lwip (int is_ipv6, const ipX_addr_t *ipx_addr, uint16_t port_hostorder);
void tcp_accepted_c(struct tcp_pcb *pcb);
ipX_addr_t local_ip(struct tcp_pcb *pcb);
BOOL isHTTP(struct tcp_pcb *pcb, uint32_t ip);
void config_netif(struct netif *netif);
err_t client_sent_func (void *arg, struct tcp_pcb *tpcb, u16_t len);
void configClient_sent_func(struct tcp_pcb *tpcb);
void config_tcppcb(struct tcp_pcb *pcb, void *client);
uint16_t snd_buf(struct tcp_pcb *pcb);
static void tcp_remove(struct tcp_pcb* pcb_list);
void pcbinfo(struct tcp_pcb *pcb, uint32_t *srcip,uint32_t *dstip, uint16_t *sport , uint16_t *dport);
void upcbinfo(struct tcp_pcb *pcb, uint32_t *srcip,uint32_t *dstip, uint16_t *sport , uint16_t *dport);
int tcp_write_check(struct tcp_pcb *pcb);
void closeLWIP(void);
void closeTW(void);
#endif /* StackHelper_h */
