//
//  MeetingViewController.swift
//  NERtcSample-GroupVideoCall-iOS-Swift
//
//  Created by Think on 2020/8/24.
//  Copyright © 2020 Think. All rights reserved.
//

import UIKit
import NERtcSDK

class MeetingViewController: UIViewController {
    
    var userID: UInt64?
    var roomID: String?
    
    @IBOutlet weak var localUserView: UIView!
    @IBOutlet var remoteUserViews: [UIView]!
    
    override func viewDidLoad() {
        super.viewDidLoad()

        // Do any additional setup after loading the view.
        
        title = "Room \(roomID ?? "--")"
        setupRTCEngine()
        joinCurrentRoom()
    }
    
    deinit {
        NERtcEngine.shared().leaveChannel()
        NERtcEngine.destroy()
    }
    
    func setupRTCEngine() {
        let context = NERtcEngineContext()
        context.engineDelegate = self
        context.appKey = kAppKey
        let engine = NERtcEngine.shared()
        engine.setupEngine(with: context)
        engine.enableLocalAudio(true)
        engine.enableLocalVideo(true)
    }
    
    func joinCurrentRoom() {
        guard let userId = userID else {
            return
        }
        NERtcEngine.shared().joinChannel(
            withToken: "",
            channelName: roomID,
            myUid: userId) { [weak self] (error, channelId, elapesd) in
                guard let self = self else { return }
                if let error = error {
                    // 加入失败
                    print(error.localizedDescription)
                } else {
                    // 加入成功，建立本地canvas，准备渲染本地视图
                    let canvas = NERtcVideoCanvas()
                    canvas.container = self.localUserView
                    NERtcEngine.shared().setupLocalVideoCanvas(canvas)
                }
            }
    }
    
}

extension MeetingViewController: NERtcEngineDelegateEx {
    func onNERtcEngineUserDidJoin(withUserID userID: UInt64, userName: String) {
        let canvas = NERtcVideoCanvas()
        for view in remoteUserViews {
            if view.tag == 0 {
                canvas.container = view
                NERtcEngine.shared().setupRemoteVideoCanvas(canvas, forUserID: userID)
                view.tag = NSInteger(userID)
                break
            }
        }
    }
    
    func onNERtcEngineUserVideoDidStart(withUserID userID: UInt64, videoProfile profile: NERtcVideoProfileType) {
        NERtcEngine.shared().subscribeRemoteVideo(true, forUserID: userID, streamType: .high)
    }
    
    func onNERtcEngineUserDidLeave(withUserID userID: UInt64, reason: NERtcSessionLeaveReason) {
        let tag = Int(userID)
        view.viewWithTag(tag)?.tag = 0
    }
}
