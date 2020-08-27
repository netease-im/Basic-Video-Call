//
//  NTESAppDelegate.swift
//  NERtcSample-1to1-iOS-Swift
//
//  Created by Wenchao Ding on 2020/7/31.
//  Copyright © 2020 Wenchao Ding. All rights reserved.
//

import UIKit

@UIApplicationMain
class NTESAppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?
    
    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        URLSession.shared.dataTask(with: URL(string: "https://www.baidu.com")!).resume()
        return true
    }


}

