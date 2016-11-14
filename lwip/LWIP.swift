//
//  Main.swift
//  lwip
//
//  Created by 孔祥波 on 11/11/16.
//  Copyright © 2016 Kong XiangBo. All rights reserved.
//

import Foundation

class LWIP:NSObject,TCPStackDelegate,TCPCientDelegate  {
    public func incomingTCP(_ pcb: UnsafeMutablePointer<tcp_pcb>!) {
        
    }

    public func writeDatagrams(_ data: Data!) {
        
    }

    

    public func lwipInitFinish() {
        
    }

    public func client_sent_func(_ pcb: UnsafeMutablePointer<tcp_pcb>!){
        
    }
    
    public func client_handle_freed_client(_ pcb: UnsafeMutablePointer<tcp_pcb>!){
        
    }
    
    public func client_free_client(_ pcb: UnsafeMutablePointer<tcp_pcb>!){
        
    }
    
    public func incomingData(_ d: Data!, len: Int, pcb: UnsafeMutablePointer<tcp_pcb>!){
        
    }
    
    public func didSendBufferLen(_ buf_used: Int){
        
    }
    
}
