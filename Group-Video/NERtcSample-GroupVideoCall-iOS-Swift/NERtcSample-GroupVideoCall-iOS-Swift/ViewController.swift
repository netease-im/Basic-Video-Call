//
//  ViewController.swift
//  NERtcSample-GroupVideoCall-iOS-Swift
//
//  Created by Think on 2020/8/24.
//  Copyright © 2020 Think. All rights reserved.
//

import UIKit

let kJoinMeetingSegue: String = "Join Meeting"

class ViewController: UIViewController {
    
    @IBOutlet weak var userIDTextField: UITextField!
    @IBOutlet weak var roomIDTextField: UITextField!
    
    var randomUserID: String {
        let uid = 10000 + arc4random() % (99999 - 10000)
        return String(uid)
    }

    override func viewDidLoad() {
        super.viewDidLoad()
        // Do any additional setup after loading the view.
        
        userIDTextField.text = randomUserID
    }

    override func shouldPerformSegue(withIdentifier identifier: String, sender: Any?) -> Bool {
        guard
            identifier == kJoinMeetingSegue,
            let userId = userIDTextField.text, userId.count > 0,
            let roomId = roomIDTextField.text, roomId.count > 0
        else {
                return false
        }
        return true
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        view.endEditing(true)
        
        guard
            segue.identifier == kJoinMeetingSegue,
            let meetVC = segue.destination as? MeetingViewController,
            let userStr = userIDTextField.text,
            let userId = UInt64(userStr),
            let roomId = roomIDTextField.text
        else {
            return
        }
        meetVC.userID = userId
        meetVC.roomID = roomId
    }

}

