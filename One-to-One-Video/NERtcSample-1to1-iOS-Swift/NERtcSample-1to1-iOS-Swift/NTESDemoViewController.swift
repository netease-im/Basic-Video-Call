//
//  NTESDemoViewController.swift
//  NERtcSample-1to1-iOS-Swift
//
//  Created by Wenchao Ding on 2020/7/31.
//  Copyright © 2020 Wenchao Ding. All rights reserved.
//

import Foundation
import UIKit

class NTESDemoViewController: UIViewController {
    
    @IBOutlet weak var roomIDTextField: UITextField! // 输入roomID
    @IBOutlet weak var joinButton: UIButton!;  //加入按钮
    
    private lazy var userID: UInt64 = UInt64((10000 + arc4random() % (99999 - 10000)))
    
    // 点击键盘收回空白
    override func touchesBegan(_ touches: Set<UITouch>, with event: UIEvent?) {
        super.touchesBegan(touches, with: event)
        self.roomIDTextField.resignFirstResponder()
    }
    
    override func prepare(for segue: UIStoryboardSegue, sender: Any?) {
        if segue.identifier == "join" {
            self.roomIDTextField.resignFirstResponder()
            
            let destination = segue.destination as! NTES1To1CallViewController
            destination.roomID = self.roomIDTextField.text!
            destination.userID = self.userID
        }
    }
    
    @IBAction func unwind(segue: UIStoryboardSegue) { }
    
}

extension NTESDemoViewController: UITextFieldDelegate {
    
    func textField(_ textField: UITextField, shouldChangeCharactersIn range: NSRange, replacementString string: String) -> Bool {
        guard let text = textField.text else {
            return true
        }
        let roomId = (text as NSString).replacingCharacters(in: range, with: string)
        // 仅限12位以内数字
        return roomId.count <= 12 && roomId.rangeOfCharacter(from: NSCharacterSet.decimalDigits.inverted) == nil
    }
    
    @IBAction func roomIDChanged(_ sender: Any) {
        self.joinButton.isEnabled = self.roomIDTextField.text != nil && self.roomIDTextField.text!.count > 0
    }
    
}
