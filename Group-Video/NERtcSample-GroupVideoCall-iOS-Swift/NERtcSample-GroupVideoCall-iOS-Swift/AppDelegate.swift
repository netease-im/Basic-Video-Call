//
//  AppDelegate.swift
//  NERtcSample-GroupVideoCall-iOS-Swift
//
//  Created by Think on 2020/8/24.
//  Copyright © 2020 Think. All rights reserved.
//

import UIKit

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {

    var window: UIWindow?

    func application(_ application: UIApplication, didFinishLaunchingWithOptions launchOptions: [UIApplication.LaunchOptionsKey: Any]?) -> Bool {
        // Override point for customization after application launch.
        
        // 首次安装提示获取网络权限
        if let url = URL(string: "https://www.baidu.com") {
            let request = URLRequest(url: url)
            URLSession.shared.dataTask(with: request).resume()
        }
        
        return true
    }


}

