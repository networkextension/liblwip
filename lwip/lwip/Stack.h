//
//  test.h
//  lwip
//
//  Created by 孔祥波 on 11/11/16.
//  Copyright © 2016 Kong XiangBo. All rights reserved.
//

#ifndef Stack_h
#define Stack_h

#import <Foundation/Foundation.h>

#include "tcp.h"


@protocol TCPCientDelegate <NSObject>


-(void)client_sent_func:(struct tcp_pcb*)pcb;
-(void)client_handle_freed_client:(struct tcp_pcb*)pcb;
-(void)client_free_client:(struct tcp_pcb*)pcb;
-(void)incomingData:(NSData*)d len:(NSInteger)len pcb:(struct tcp_pcb*)pcb;
-(void)didSendBufferLen:(NSInteger)buf_used;

@end

@protocol TCPStackDelegate <NSObject>

-(void)lwipInitFinish;
//new tcp
-(void)incomingTCP:(struct tcp_pcb*)pcb;
//write data to system
-(void)writeDatagrams:(NSData*)data;
@end

void setupStack(id<TCPStackDelegate> object);

#endif /* test_h */
