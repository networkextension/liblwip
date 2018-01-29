//
//  XStack.swift
//  lwip
//
//  Created by yarshure on 07/01/2018.
//  Copyright © 2018 Kong XiangBo. All rights reserved.
//

import Foundation
public typealias Xpcb  = UnsafeMutablePointer<tcp_pcb>!
public protocol  XStackDelegate:class{
    func incomingNewSocket(_ s:LSocket)
    func  writeDatagrams(_ data: Data!,protocols:Int32)
}
public class XStack:NSObject{
    static let stack = XStack()
    public var queue:DispatchQueue!
    public var delegate:XStackDelegate?
    
    var configed:Bool = false
      
    
    //call back inited
    public func configLWIP(_ finish: @escaping (() ->Void)){
        configed = true
        setupStackWithFin(self, finish)
    }
    
}
extension XStack:TCPStackDelegate  {
    public func lwipInitFinish() {
        
    }
    
    public func incomingTCP(_ pcb: Xpcb) {
        let s = LSocket.init(pcb: pcb)
        self.delegate?.incomingNewSocket(s)
    }
    
    public func writeDatagrams(_ data: Data!) {
        self.delegate?.writeDatagrams(data, protocols: AF_INET)
    }
    
    
    
}
