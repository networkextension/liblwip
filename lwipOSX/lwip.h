//
//  lwipOSX.h
//  lwipOSX
//
//  Created by 孔祥波 on 19/11/2016.
//  Copyright © 2016 Kong XiangBo. All rights reserved.
//

#import <Cocoa/Cocoa.h>

//! Project version number for lwipOSX.
FOUNDATION_EXPORT double lwipOSXVersionNumber;

//! Project version string for lwipOSX.
FOUNDATION_EXPORT const unsigned char lwipOSXVersionString[];

// In this header, you should import all the public headers of your framework using statements like #import <lwipOSX/PublicHeader.h>

/* Modules initialization */
/* Define generic types used in lwIP */
#ifdef TCP_MSS
#undef TCP_MSS
#define TCP_MSS 1460
#endif
typedef unsigned   char    u8_t;
typedef signed     char    s8_t;
typedef unsigned   short   u16_t;
typedef signed     short   s16_t;
typedef unsigned   int     u32_t;
typedef signed     int     s32_t;

typedef unsigned long mem_ptr_t;


typedef s8_t err_t;
typedef struct ip_addr ip_addr_t;
typedef struct ip_addr_packed ip_addr_p_t;
#define ERR_OK          0    /* No error, everything OK. */
#define ERR_MEM        -1    /* Out of memory error.     */
#define ERR_BUF        -2    /* Buffer error.            */
#define ERR_TIMEOUT    -3    /* Timeout.                 */
#define ERR_RTE        -4    /* Routing problem.         */
#define ERR_INPROGRESS -5    /* Operation in progress    */
#define ERR_VAL        -6    /* Illegal value.           */
#define ERR_WOULDBLOCK -7    /* Operation would block.   */
#define ERR_USE        -8    /* Address in use.          */
#define ERR_ISCONN     -9    /* Already connected.       */

#define ERR_IS_FATAL(e) ((e) < ERR_ISCONN)

#define ERR_ABRT       -10   /* Connection aborted.      */
#define ERR_RST        -11   /* Connection reset.        */
#define ERR_CLSD       -12   /* Connection closed.       */
#define ERR_CONN       -13   /* Not connected.           */

#define ERR_ARG        -14   /* Illegal argument.        */

#define ERR_IF         -15   /* Low-level netif error    */


struct tcp_pcb;

/** Function prototype for tcp accept callback functions. Called when a new
 * connection can be accepted on a listening pcb.
 *
 * @param arg Additional argument to pass to the callback function (@see tcp_arg())
 * @param newpcb The new connection pcb
 * @param err An error code if there has been an error accepting.
 *            Only return ERR_ABRT if you have called tcp_abort from within the
 *            callback function!
 */
typedef err_t (*tcp_accept_fn)(void *arg, struct tcp_pcb *newpcb, err_t err);


/** Function prototype for tcp sent callback functions. Called when sent data has
 * been acknowledged by the remote side. Use it to free corresponding resources.
 * This also means that the pcb has now space available to send new data.
 *
 * @param arg Additional argument to pass to the callback function (@see tcp_arg())
 * @param tpcb The connection pcb for which data has been acknowledged
 * @param len The amount of bytes acknowledged
 * @return ERR_OK: try to send some data by calling tcp_output
 *            Only return ERR_ABRT if you have called tcp_abort from within the
 *            callback function!
 */
typedef err_t (*tcp_sent_fn)(void *arg, struct tcp_pcb *tpcb,
u16_t len);

/** Function prototype for tcp poll callback functions. Called periodically as
 * specified by @see tcp_poll.
 *
 * @param arg Additional argument to pass to the callback function (@see tcp_arg())
 * @param tpcb tcp pcb
 * @return ERR_OK: try to send some data by calling tcp_output
 *            Only return ERR_ABRT if you have called tcp_abort from within the
 *            callback function!
 */
typedef err_t (*tcp_poll_fn)(void *arg, struct tcp_pcb *tpcb);

/** Function prototype for tcp error callback functions. Called when the pcb
 * receives a RST or is unexpectedly closed for any other reason.
 *
 * @note The corresponding pcb is already freed when this callback is called!
 *
 * @param arg Additional argument to pass to the callback function (@see tcp_arg())
 * @param err Error code to indicate why the pcb has been closed
 *            ERR_ABRT: aborted through tcp_abort or by a TCP timer
 *            ERR_RST: the connection was reset by the remote host
 */
typedef void  (*tcp_err_fn)(void *arg, err_t err);

/** Function prototype for tcp connected callback functions. Called when a pcb
 * is connected to the remote side after initiating a connection attempt by
 * calling tcp_connect().
 *
 * @param arg Additional argument to pass to the callback function (@see tcp_arg())
 * @param tpcb The connection pcb which is connected
 * @param err An unused error code, always ERR_OK currently ;-) TODO!
 *            Only return ERR_ABRT if you have called tcp_abort from within the
 *            callback function!
 *
 * @note When a connection attempt fails, the error callback is currently called!
 */
typedef err_t (*tcp_connected_fn)(void *arg, struct tcp_pcb *tpcb, err_t err);

enum tcp_state {
    CLOSED      = 0,
    LISTEN      = 1,
    SYN_SENT    = 2,
    SYN_RCVD    = 3,
    ESTABLISHED = 4,
    FIN_WAIT_1  = 5,
    FIN_WAIT_2  = 6,
    CLOSE_WAIT  = 7,
    CLOSING     = 8,
    LAST_ACK    = 9,
    TIME_WAIT   = 10
};

#if LWIP_CALLBACK_API
/* Function to call when a listener has been connected.
 * @param arg user-supplied argument (tcp_pcb.callback_arg)
 * @param pcb a new tcp_pcb that now is connected
 * @param err an error argument (TODO: that is current always ERR_OK?)
 * @return ERR_OK: accept the new connection,
 *                 any other err_t abortsthe new connection
 */
#define DEF_ACCEPT_CALLBACK  tcp_accept_fn accept;
#else /* LWIP_CALLBACK_API */
#define DEF_ACCEPT_CALLBACK
#endif /* LWIP_CALLBACK_API */

/**
 * members common to struct tcp_pcb and struct tcp_listen_pcb
 */
#define TCP_PCB_COMMON(type) \
type *next; /* for the linked list */ \
void *callback_arg; \
/* the accept callback for listen- and normal pcbs, if LWIP_CALLBACK_API */ \
DEF_ACCEPT_CALLBACK \
enum tcp_state state; /* TCP state */ \
u8_t prio; \
/* ports are in host byte order */ \
int bound_to_netif; \
u16_t local_port; \
char local_netif[3]

/* This is the aligned version of ip_addr_t,
 used as local variable, on the stack, etc. */
struct ip_addr {
    u32_t addr;
};
typedef struct ip6_addr ip6_addr_t;
struct ip6_addr {
    u32_t addr[4];
};
typedef struct ip_addr ip_addr_t;

typedef union {
    ip_addr_t ip4;
    ip6_addr_t ip6;
} ipX_addr_t;

#if LWIP_NETIF_HWADDRHINT
#define IP_PCB_ADDRHINT ;u8_t addr_hint
#else
#define IP_PCB_ADDRHINT
#endif /* LWIP_NETIF_HWADDRHINT */

#if LWIP_IPV6
#define IP_PCB_ISIPV6_MEMBER  u8_t isipv6;
#define IP_PCB_IPVER_EQ(pcb1, pcb2)   ((pcb1)->isipv6 == (pcb2)->isipv6)
#define IP_PCB_IPVER_INPUT_MATCH(pcb) (ip_current_is_v6() ? \
((pcb)->isipv6 != 0) : \
((pcb)->isipv6 == 0))
#define PCB_ISIPV6(pcb) ((pcb)->isipv6)
#else
#define IP_PCB_ISIPV6_MEMBER
#define IP_PCB_IPVER_EQ(pcb1, pcb2)   1
#define IP_PCB_IPVER_INPUT_MATCH(pcb) 1
#define PCB_ISIPV6(pcb)            0
#endif /* LWIP_IPV6 */

/* This is the common part of all PCB types. It needs to be at the
 beginning of a PCB type definition. It is located here so that
 changes to this common part are made in one location instead of
 having to change all PCB structs. */
#define IP_PCB \
IP_PCB_ISIPV6_MEMBER \
/* ip addresses in network byte order */ \
ipX_addr_t local_ip; \
ipX_addr_t remote_ip; \
/* Socket options */  \
u8_t so_options;      \
/* Type Of Service */ \
u8_t tos;              \
/* Time To Live */     \
u8_t ttl               \
/* link layer address resolution hint */ \
IP_PCB_ADDRHINT

struct ip_pcb {
    /* Common members of all PCB types */
    IP_PCB;
};

/* the TCP protocol control block */
struct tcp_pcb {
    /** common PCB members */
    IP_PCB;
    /** protocol specific PCB members */
    TCP_PCB_COMMON(struct tcp_pcb);
    
    /* ports are in host byte order */
    u16_t remote_port;
    
    u8_t flags;
#define TF_ACK_DELAY   ((u8_t)0x01U)   /* Delayed ACK. */
#define TF_ACK_NOW     ((u8_t)0x02U)   /* Immediate ACK. */
#define TF_INFR        ((u8_t)0x04U)   /* In fast recovery. */
#define TF_TIMESTAMP   ((u8_t)0x08U)   /* Timestamp option enabled */
#define TF_RXCLOSED    ((u8_t)0x10U)   /* rx closed by tcp_shutdown */
#define TF_FIN         ((u8_t)0x20U)   /* Connection was closed locally (FIN segment enqueued). */
#define TF_NODELAY     ((u8_t)0x40U)   /* Disable Nagle algorithm */
#define TF_NAGLEMEMERR ((u8_t)0x80U)   /* nagle enabled, memerr, try to output to prevent delayed ACK to happen */
    
    /* the rest of the fields are in host byte order
     as we have to do some math with them */
    
    /* Timers */
    u8_t polltmr, pollinterval;
    u8_t last_timer;
    u32_t tmr;
    
    /* receiver variables */
    u32_t rcv_nxt;   /* next seqno expected */
    u16_t rcv_wnd;   /* receiver window available */
    u16_t rcv_ann_wnd; /* receiver window to announce */
    u32_t rcv_ann_right_edge; /* announced right edge of window */
    
    /* Retransmission timer. */
    s16_t rtime;
    
    u16_t mss;   /* maximum segment size */
    
    /* RTT (round trip time) estimation variables */
    u32_t rttest; /* RTT estimate in 500ms ticks */
    u32_t rtseq;  /* sequence number being timed */
    s16_t sa, sv; /* @todo document this */
    
    s16_t rto;    /* retransmission time-out */
    u8_t nrtx;    /* number of retransmissions */
    
    /* fast retransmit/recovery */
    u8_t dupacks;
    u32_t lastack; /* Highest acknowledged seqno. */
    
    /* congestion avoidance/control variables */
    u16_t cwnd;
    u16_t ssthresh;
    
    /* sender variables */
    u32_t snd_nxt;   /* next new seqno to be sent */
    u32_t snd_wl1, snd_wl2; /* Sequence and acknowledgement numbers of last
                             window update. */
    u32_t snd_lbb;       /* Sequence number of next byte to be buffered. */
    u16_t snd_wnd;   /* sender window */
    u16_t snd_wnd_max; /* the maximum sender window announced by the remote host */
    
    u16_t acked;
    
    u16_t snd_buf;   /* Available buffer space for sending (in bytes). */
#define TCP_SNDQUEUELEN_OVERFLOW (0xffffU-3)
    u16_t snd_queuelen; /* Available buffer space for sending (in tcp_segs). */
    
#if TCP_OVERSIZE
    /* Extra bytes available at the end of the last pbuf in unsent. */
    u16_t unsent_oversize;
#endif /* TCP_OVERSIZE */
    
    /* These are ordered by sequence number: */
    struct tcp_seg *unsent;   /* Unsent (queued) segments. */
    struct tcp_seg *unacked;  /* Sent but unacknowledged segments. */
#if TCP_QUEUE_OOSEQ
    struct tcp_seg *ooseq;    /* Received out of sequence segments. */
#endif /* TCP_QUEUE_OOSEQ */
    
    struct pbuf *refused_data; /* Data previously received but not yet taken by upper layer */
    
#if LWIP_CALLBACK_API
    /* Function to be called when more send buffer space is available. */
    tcp_sent_fn sent;
    /* Function to be called when (in-sequence) data has arrived. */
    tcp_recv_fn recv;
    /* Function to be called when a connection has been set up. */
    tcp_connected_fn connected;
    /* Function which is called periodically. */
    tcp_poll_fn poll;
    /* Function to be called whenever a fatal error occurs. */
    tcp_err_fn errf;
#endif /* LWIP_CALLBACK_API */
    
#if LWIP_TCP_TIMESTAMPS
    u32_t ts_lastacksent;
    u32_t ts_recent;
#endif /* LWIP_TCP_TIMESTAMPS */
    
    /* idle time before KEEPALIVE is sent */
    u32_t keep_idle;
#if LWIP_TCP_KEEPALIVE
    u32_t keep_intvl;
    u32_t keep_cnt;
#endif /* LWIP_TCP_KEEPALIVE */
    
    /* Persist timer counter */
    u8_t persist_cnt;
    /* Persist timer back-off */
    u8_t persist_backoff;
    
    /* KEEPALIVE counter */
    u8_t keep_cnt_sent;
};


struct tcp_pcb_listen {
    /* Common members of all PCB types */
    IP_PCB;
    /* Protocol specific PCB members */
    TCP_PCB_COMMON(struct tcp_pcb_listen);
    
#if TCP_LISTEN_BACKLOG
    u8_t backlog;
    u8_t accepts_pending;
#endif /* TCP_LISTEN_BACKLOG */
#if LWIP_IPV6
    u8_t accept_any_ip_version;
#endif /* LWIP_IPV6 */
};

#if LWIP_EVENT_API

enum lwip_event {
    LWIP_EVENT_ACCEPT,
    LWIP_EVENT_SENT,
    LWIP_EVENT_RECV,
    LWIP_EVENT_CONNECTED,
    LWIP_EVENT_POLL,
    LWIP_EVENT_ERR
};

err_t lwip_tcp_event(void *arg, struct tcp_pcb *pcb,
                     enum lwip_event,
                     struct pbuf *p,
                     u16_t size,
                     err_t err);

#endif /* LWIP_EVENT_API */

/* Application program's interface: */
struct tcp_pcb * tcp_new     (void);
/** Function prototype for tcp receive callback functions. Called when data has
 * been received.
 *
 * @param arg Additional argument to pass to the callback function (@see tcp_arg())
 * @param tpcb The connection pcb which received data
 * @param p The received data (or NULL when the connection has been closed!)
 * @param err An error code if there has been an error receiving
 *            Only return ERR_ABRT if you have called tcp_abort from within the
 *            callback function!
 */
typedef err_t (*tcp_recv_fn)(void *arg, struct tcp_pcb *tpcb,struct pbuf *p, err_t err);

void             tcp_arg     (struct tcp_pcb *pcb, void *arg);
void             tcp_accept  (struct tcp_pcb *pcb, tcp_accept_fn accept);
void             tcp_recv    (struct tcp_pcb *pcb, tcp_recv_fn recv);
void             tcp_sent    (struct tcp_pcb *pcb, tcp_sent_fn sent);
void             tcp_poll    (struct tcp_pcb *pcb, tcp_poll_fn poll, u8_t interval);
void             tcp_err     (struct tcp_pcb *pcb, tcp_err_fn err);

#define          tcp_mss(pcb)             (((pcb)->flags & TF_TIMESTAMP) ? ((pcb)->mss - 12)  : (pcb)->mss)
#define          tcp_sndbuf(pcb)          ((pcb)->snd_buf)
#define          tcp_sndqueuelen(pcb)     ((pcb)->snd_queuelen)
#define          tcp_nagle_disable(pcb)   ((pcb)->flags |= TF_NODELAY)
#define          tcp_nagle_enable(pcb)    ((pcb)->flags &= ~TF_NODELAY)
#define          tcp_nagle_disabled(pcb)  (((pcb)->flags & TF_NODELAY) != 0)

#if TCP_LISTEN_BACKLOG
#define          tcp_accepted(pcb) do { \
LWIP_ASSERT("pcb->state == LISTEN (called for wrong pcb?)", pcb->state == LISTEN); \
(((struct tcp_pcb_listen *)(pcb))->accepts_pending--); } while(0)
#else  /* TCP_LISTEN_BACKLOG */
#define          tcp_accepted(pcb) LWIP_ASSERT("pcb->state == LISTEN (called for wrong pcb?)", \
(pcb)->state == LISTEN)
#endif /* TCP_LISTEN_BACKLOG */

void             tcp_recved  (struct tcp_pcb *pcb, u16_t len);
err_t            tcp_bind    (struct tcp_pcb *pcb, ip_addr_t *ipaddr,
                              u16_t port);
err_t            tcp_bind_to_netif (struct tcp_pcb *pcb, const char ifname[3]);
err_t            tcp_connect (struct tcp_pcb *pcb, ip_addr_t *ipaddr,
                              u16_t port, tcp_connected_fn connected);

struct tcp_pcb * tcp_listen_with_backlog(struct tcp_pcb *pcb, u8_t backlog);
#define          tcp_listen(pcb) tcp_listen_with_backlog(pcb, TCP_DEFAULT_LISTEN_BACKLOG)

void             tcp_abort (struct tcp_pcb *pcb);
err_t            tcp_close   (struct tcp_pcb *pcb);
err_t            tcp_shutdown(struct tcp_pcb *pcb, int shut_rx, int shut_tx);

/* Flags for "apiflags" parameter in tcp_write */
#define TCP_WRITE_FLAG_COPY 0x01
#define TCP_WRITE_FLAG_MORE 0x02

err_t            tcp_write   (struct tcp_pcb *pcb, const void *dataptr, u16_t len,
                              u8_t apiflags);

void             tcp_setprio (struct tcp_pcb *pcb, u8_t prio);

#define TCP_PRIO_MIN    1
#define TCP_PRIO_NORMAL 64
#define TCP_PRIO_MAX    127

err_t            tcp_output  (struct tcp_pcb *pcb);


const char* tcp_debug_state_str(enum tcp_state s);

#if LWIP_IPV6
struct tcp_pcb * tcp_new_ip6 (void);
#define          tcp_bind_ip6(pcb, ip6addr, port) \
tcp_bind(pcb, ip6_2_ip(ip6addr), port)
#define          tcp_connect_ip6(pcb, ip6addr, port, connected) \
tcp_connect(pcb, ip6_2_ip(ip6addr), port, connected)
struct tcp_pcb * tcp_listen_dual_with_backlog(struct tcp_pcb *pcb, u8_t backlog);
#define          tcp_listen_dual(pcb) tcp_listen_dual_with_backlog(pcb, TCP_DEFAULT_LISTEN_BACKLOG)
#else /* LWIP_IPV6 */
#define          tcp_listen_dual_with_backlog(pcb, backlog) tcp_listen_with_backlog(pcb, backlog)
#define          tcp_listen_dual(pcb) tcp_listen(pcb)
#endif /* LWIP_IPV6 */

struct pbuf {
    /** next pbuf in singly linked pbuf chain */
    struct pbuf *next;
    
    /** pointer to the actual data in the buffer */
    void *payload;
    
    /**
     * total length of this buffer and all next buffers in chain
     * belonging to the same packet.
     *
     * For non-queue packet chains this is the invariant:
     * p->tot_len == p->len + (p->next? p->next->tot_len: 0)
     */
    u16_t tot_len;
    
    /** length of this buffer */
    u16_t len;
    
    /** pbuf_type as u8_t instead of enum to save space */
    u8_t /*pbuf_type*/ type;
    
    /** misc flags */
    u8_t flags;
    
    /**
     * the reference count always equals the number of pointers
     * that refer to this pbuf. This can be pointers from an application,
     * the stack itself, or pbuf->next pointers from a chain.
     */
    u16_t ref;
};


struct netif;
/** Function prototype for netif init functions. Set up flags and output/linkoutput
 * callback functions in this function.
 *
 * @param netif The netif to initialize
 */
typedef err_t (*netif_init_fn)(struct netif *netif);
/** Function prototype for netif->input functions. This function is saved as 'input'
 * callback function in the netif struct. Call it when a packet has been received.
 *
 * @param p The received packet, copied into a pbuf
 * @param inp The netif which received the packet
 */
typedef err_t (*netif_input_fn)(struct pbuf *p, struct netif *inp);
/** Function prototype for netif->output functions. Called by lwIP when a packet
 * shall be sent. For ethernet netif, set this to 'etharp_output' and set
 * 'linkoutput'.
 *
 * @param netif The netif which shall send a packet
 * @param p The packet to send (p->payload points to IP header)
 * @param ipaddr The IP address to which the packet shall be sent
 */
typedef err_t (*netif_output_fn)(struct netif *netif, struct pbuf *p,
ip_addr_t *ipaddr);

typedef err_t (*netif_linkoutput_fn)(struct netif *netif, struct pbuf *p);
#define NETIF_MAX_HWADDR_LEN 6U
struct netif *netif_list;

void
sys_restart_timeouts(void);
void
sys_check_timeouts(void);
typedef enum {
    PBUF_TRANSPORT,
    PBUF_IP,
    PBUF_LINK,
    PBUF_RAW
} pbuf_layer;
#ifndef TCP_DEFAULT_LISTEN_BACKLOG
#define TCP_DEFAULT_LISTEN_BACKLOG      0xff
#endif
#define IPADDR_ANY          ((u32_t)0x00000000UL)
#define IP_ADDR_BROADCAST   ((ip_addr_t *)&ip_addr_broadcast)
extern const ip_addr_t ip_addr_any;
extern const ip_addr_t ip_addr_broadcast;
typedef enum {
    PBUF_RAM, /* pbuf data is stored in RAM */
    PBUF_ROM, /* pbuf data is stored in ROM */
    PBUF_REF, /* pbuf comes from the pbuf pool */
    PBUF_POOL /* pbuf payload refers to RAM */
} pbuf_type;
struct pbuf *
pbuf_alloc(pbuf_layer layer, u16_t length, pbuf_type type);
void tcp_accepted_c(struct tcp_pcb *pcb);
void
lwip_init(void);
/** Generic data structure used for all lwIP network interfaces.
 *  The following fields should be filled in by the initialization
 *  function for the device driver: hwaddr_len, hwaddr[], mtu, flags */
struct netif {
    /** pointer to next in linked list */
    struct netif *next;
    
    /** IP address configuration in network byte order */
    ip_addr_t ip_addr;
    ip_addr_t netmask;
    ip_addr_t gw;
    
#if LWIP_IPV6
    /** Array of IPv6 addresses for this netif. */
    ip6_addr_t ip6_addr[LWIP_IPV6_NUM_ADDRESSES];
    /** The state of each IPv6 address (Tentative, Preferred, etc).
     * @see ip6_addr.h */
    u8_t ip6_addr_state[LWIP_IPV6_NUM_ADDRESSES];
#endif /* LWIP_IPV6 */
    /** This function is called by the network device driver
     *  to pass a packet up the TCP/IP stack. */
    netif_input_fn input;
    /** This function is called by the IP module when it wants
     *  to send a packet on the interface. This function typically
     *  first resolves the hardware address, then sends the packet. */
    netif_output_fn output;
    /** This function is called by the ARP module when it wants
     *  to send a packet on the interface. This function outputs
     *  the pbuf as-is on the link medium. */
    netif_linkoutput_fn linkoutput;
#if LWIP_IPV6
    /** This function is called by the IPv6 module when it wants
     *  to send a packet on the interface. This function typically
     *  first resolves the hardware address, then sends the packet. */
    netif_output_ip6_fn output_ip6;
#endif /* LWIP_IPV6 */
#if LWIP_NETIF_STATUS_CALLBACK
    /** This function is called when the netif state is set to up or down
     */
    netif_status_callback_fn status_callback;
#endif /* LWIP_NETIF_STATUS_CALLBACK */
#if LWIP_NETIF_LINK_CALLBACK
    /** This function is called when the netif link is set to up or down
     */
    netif_status_callback_fn link_callback;
#endif /* LWIP_NETIF_LINK_CALLBACK */
#if LWIP_NETIF_REMOVE_CALLBACK
    /** This function is called when the netif has been removed */
    netif_status_callback_fn remove_callback;
#endif /* LWIP_NETIF_REMOVE_CALLBACK */
    /** This field can be set by the device driver and could point
     *  to state information for the device. */
    void *state;
#if LWIP_DHCP
    /** the DHCP client state information for this netif */
    struct dhcp *dhcp;
#endif /* LWIP_DHCP */
#if LWIP_AUTOIP
    /** the AutoIP client state information for this netif */
    struct autoip *autoip;
#endif
#if LWIP_IPV6_AUTOCONFIG
    /** is this netif enabled for IPv6 autoconfiguration */
    u8_t ip6_autoconfig_enabled;
#endif /* LWIP_IPV6_AUTOCONFIG */
#if LWIP_IPV6_SEND_ROUTER_SOLICIT
    /** Number of Router Solicitation messages that remain to be sent. */
    u8_t rs_count;
#endif /* LWIP_IPV6_SEND_ROUTER_SOLICIT */
#if LWIP_IPV6_DHCP6
    /** the DHCPv6 client state information for this netif */
    struct dhcp6 *dhcp6;
#endif /* LWIP_IPV6_DHCP6 */
#if LWIP_NETIF_HOSTNAME
    /* the hostname for this netif, NULL is a valid value */
    char*  hostname;
#endif /* LWIP_NETIF_HOSTNAME */
    /** maximum transfer unit (in bytes) */
    u16_t mtu;
    /** number of bytes used in hwaddr */
    u8_t hwaddr_len;
    /** link level hardware address of this interface */
    u8_t hwaddr[NETIF_MAX_HWADDR_LEN];
    /** flags (see NETIF_FLAG_ above) */
    u16_t flags;
    /** descriptive abbreviation */
    char name[2];
    /** number of this interface */
    u8_t num;
#if LWIP_SNMP
    /** link type (from "snmp_ifType" enum from snmp.h) */
    u8_t link_type;
    /** (estimate) link speed */
    u32_t link_speed;
    /** timestamp at last change made (up/down) */
    u32_t ts;
    /** counters */
    u32_t ifinoctets;
    u32_t ifinucastpkts;
    u32_t ifinnucastpkts;
    u32_t ifindiscards;
    u32_t ifoutoctets;
    u32_t ifoutucastpkts;
    u32_t ifoutnucastpkts;
    u32_t ifoutdiscards;
#endif /* LWIP_SNMP */
#if LWIP_IGMP
    /** This function could be called to add or delete an entry in the multicast
     filter table of the ethernet MAC.*/
    netif_igmp_mac_filter_fn igmp_mac_filter;
#endif /* LWIP_IGMP */
#if LWIP_IPV6 && LWIP_IPV6_MLD
    /** This function could be called to add or delete an entry in the IPv6 multicast
     filter table of the ethernet MAC. */
    netif_mld_mac_filter_fn mld_mac_filter;
#endif /* LWIP_IPV6 && LWIP_IPV6_MLD */
#if LWIP_NETIF_HWADDRHINT
    u8_t *addr_hint;
#endif /* LWIP_NETIF_HWADDRHINT */
#if ENABLE_LOOPBACK
    /* List of packets to be queued for ourselves. */
    struct pbuf *loop_first;
    struct pbuf *loop_last;
#if LWIP_LOOPBACK_MAX_PBUFS
    u16_t loop_cnt_current;
#endif /* LWIP_LOOPBACK_MAX_PBUFS */
#endif /* ENABLE_LOOPBACK */
};



u8_t pbuf_free(struct pbuf *p);
u16_t pbuf_copy_partial(struct pbuf *buf, void *dataptr, u16_t len, u16_t offset);

void tcp_recv(struct tcp_pcb *pcb, tcp_recv_fn recv);
typedef  struct netif  *SFNetIF;

typedef  struct pbuf  *SFPbuf;
typedef  struct tcp_pcb  *SFPcb;
typedef  struct udp_pcb  *SFUPcb;
typedef  struct ip_pcb  SFIP;
err_t input(struct pbuf *p);
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
void inputData(NSData *data,NSInteger len);
BAddr baddr_from_lwip (int is_ipv6, const ipX_addr_t *ipx_addr, uint16_t port_hostorder);
void tcp_accepted_c(struct tcp_pcb *pcb);
ipX_addr_t local_ip(struct tcp_pcb *pcb);
BOOL isHTTP(struct tcp_pcb *pcb, uint32_t ip);
void config_netif(struct netif *netif);
err_t client_sent_func (void *arg, struct tcp_pcb *tpcb, u16_t len);
void configClient_sent_func(struct tcp_pcb *tpcb);

uint16_t snd_buf(struct tcp_pcb *pcb);
static void tcp_remove(struct tcp_pcb* pcb_list);
void pcbinfo(struct tcp_pcb *pcb, uint32_t *srcip,uint32_t *dstip, uint16_t *sport , uint16_t *dport);
void upcbinfo(struct tcp_pcb *pcb, uint32_t *srcip,uint32_t *dstip, uint16_t *sport , uint16_t *dport);
int tcp_write_check(struct tcp_pcb *pcb);
void closeLWIP();
void closeTW();


@protocol TCPStackDelegate <NSObject>

-(void)lwipInitFinish;
//new tcp
-(void)incomingTCP:(struct tcp_pcb*)pcb;
//write data to system
-(void)writeDatagrams:(NSData*)data;


-(void)client_sent_func;
-(void)client_handle_freed_client;
-(void)client_free_client;
-(void)incomingData:(NSData*)d len:(NSInteger)len;
-(void)client_poll:(void*)client;
@end
extern void tcp_tmr();
void config_tcppcb(struct tcp_pcb *pcb, void *c);
const  char* pcbStatus(struct tcp_pcb* pcb);
void setupStack(id<TCPStackDelegate> object);
enum tcp_state pcbStat(struct tcp_pcb*pcb);
