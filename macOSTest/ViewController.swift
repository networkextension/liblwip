//
//  ViewController.swift
//  macOSTest
//
//  Created by yarshure on 2016/11/20.
//  Copyright © 2016年 Kong XiangBo. All rights reserved.
//

import Cocoa
import lwip
class ViewController: NSViewController {

    override func viewDidLoad() {
        super.viewDidLoad()
        logLWIPParams()
        // Do any additional setup after loading the view.
    }

    override var representedObject: Any? {
        didSet {
        // Update the view, if already loaded.
        }
    }


}

