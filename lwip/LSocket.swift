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
    
}


extension LSocket:TCPCientDelegate  {
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
