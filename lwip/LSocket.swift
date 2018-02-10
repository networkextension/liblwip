//
//  Main.swift
//  lwip
//
//  Created by 孔祥波 on 11/11/16.
//  Copyright © 2016 Kong XiangBo. All rights reserved.
//

import Foundation


public class LSocket:NSObject{
  
    var pcb :Xpcb
    init(pcb:Xpcb) {
        self.pcb = pcb
        //autocall?
        super.init()
    }
    func configCallBack(){
        let client = Unmanaged.passUnretained(self).toOpaque()
        
        tcp_arg(pcb, client)
        tcp_err(pcb, errorFunc())
        tcp_recv(pcb, recvFunc())
        tcp_poll(pcb, pollFunc(), 1)
    }
    func test(){
        
    }
    
    func sendFunc() ->tcp_sent_fn{
        return { arg,pcb ,len in
            guard let arg = arg else {return Int8(ERR_ARG) }
            let unmanaged:Unmanaged<LSocket>  =   Unmanaged.fromOpaque(arg)
            
            let client:LSocket = unmanaged.takeUnretainedValue()
            client.test()
            return Int8(ERR_OK)
        }
    }
    func errorFunc() ->tcp_err_fn {
        return { arg,err in
            guard let arg = arg else {return  }
            let unmanaged:Unmanaged<LSocket>  =   Unmanaged.fromOpaque(arg)
            let client:LSocket = unmanaged.takeUnretainedValue()
            client.test()
            
        }
    }
    func recvFunc() ->tcp_recv_fn {
        return { arg,pcb,buffer,err  in
            guard let arg = arg else {return Int8(ERR_ARG) }
            let unmanaged:Unmanaged<LSocket>  =   Unmanaged.fromOpaque(arg)
            let client:LSocket = unmanaged.takeUnretainedValue()
            client.test()
            return Int8(ERR_OK)
        }
    }
    func pollFunc() -> tcp_poll_fn {
        return { arg ,pcb in
            guard let arg = arg else {return Int8(ERR_ARG)}
            let unmanaged:Unmanaged<LSocket>  =   Unmanaged.fromOpaque(arg)
            let client:LSocket = unmanaged.takeUnretainedValue()
            client.test()
            return Int8(ERR_OK)
        }
    }
}


extension LSocket  {
    public func client_sent_func() {
        
    }
    
    public func client_handle_freed_client() {
        
    }
    
    public func client_free_client() {
        
    }
    
    public func incomingData(_ d: Data!, len: Int) {
        
    }
    
    public func didSendBufferLen(_ buf_used: Int) {
        
    }
    
    
    
}
