//
//  NTES1To1CallViewController.swift
//  NERtcSample-1to1-iOS-Swift
//
//  Created by Wenchao Ding on 2020/7/31.
//  Copyright © 2020 Wenchao Ding. All rights reserved.
//

import UIKit
import NERtcSDK

class NTES1To1CallViewController: UIViewController {

    var roomID: String!
    var userID: UInt64!
    var remoteUserID: UInt64?
    
    @IBOutlet weak var localContainer: UIView!;  // 本地渲染视图
    @IBOutlet weak var remoteContainer: UIView!;  // 对方渲染视图
    @IBOutlet weak var waitingLabel: UILabel!  // 等待中
    
    
    override func viewDidLoad() {
        super.viewDidLoad()
        self.setupNERtcEngine()
        self.joinRoom(roomID: self.roomID, userID: self.userID)
    }
    
    deinit {
        NERtcEngine.shared().leaveChannel()
        NERtcEngine.destroy()
    }
    
    private func setupNERtcEngine() {        
        let engine = NERtcEngine.shared()
        let context = NERtcEngineContext()
        context.engineDelegate = self;
        context.appKey = kAppKey;
        engine.setupEngine(with: context)
        engine.enableLocalAudio(true)
        engine.enableLocalVideo(true)
        
        let config = NERtcVideoEncodeConfiguration()
        config.maxProfile = .HD720P
        engine.setLocalVideoConfig(config)
    }
    
    private func joinRoom(roomID: String, userID: UInt64) {
        NERtcEngine.shared().joinChannel(withToken: "", channelName: self.roomID, myUid: self.userID) { [weak self](error, channelId, elapesd) in
            guard let self = self else {
                return
            }
            guard error == nil else {
                print(error!.localizedDescription)
                return
            }
            let canvas = NERtcVideoCanvas()
            canvas.container = self.localContainer
            canvas.renderMode = .cropFill;
            NERtcEngine.shared().setupLocalVideoCanvas(canvas)
        }
    }
    
    @IBAction func onAudioToggleAction(sender: UIButton) {
        let enabled = !sender.isSelected
        NERtcEngine.shared().enableLocalAudio(enabled)
        sender.isSelected = enabled
    }
    
    @IBAction func onVideoToggleAction(sender: UIButton) {
        let enabled = !sender.isSelected
        NERtcEngine.shared().enableLocalVideo(enabled)
        sender.isSelected = enabled
    }

}

// MARK: - NERtcEngineDelegateEx
extension NTES1To1CallViewController: NERtcEngineDelegateEx {
    
    func onNERtcEngineUserDidJoin(withUserID userID: UInt64, userName: String) {
        if self.remoteUserID != nil {
            return
        }
        self.remoteUserID = userID
        let canvas = NERtcVideoCanvas()
        canvas.container = self.remoteContainer
        NERtcEngine.shared().setupRemoteVideoCanvas(canvas, forUserID: userID)
        self.waitingLabel.isHidden = true
    }
    
    func onNERtcEngineUserDidLeave(withUserID userID: UInt64, reason: NERtcSessionLeaveReason) {
        self.remoteUserID = nil
        self.waitingLabel.isHidden = false
    }
    
    func onNERtcEngineUserVideoDidStart(withUserID userID: UInt64, videoProfile profile: NERtcVideoProfileType) {
        if userID == self.remoteUserID {
            NERtcEngine.shared().subscribeRemoteVideo(true, forUserID: userID, streamType: .high)
        }
    }
    
}
