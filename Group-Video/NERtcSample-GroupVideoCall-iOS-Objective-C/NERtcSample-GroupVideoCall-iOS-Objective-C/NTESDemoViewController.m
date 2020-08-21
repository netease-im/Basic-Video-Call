//
//  NTESDemoViewController.m
//  NERtcGroupMeetingSample
//
//  Created by 丁文超 on 2020/3/23.
//  Copyright © 2020 丁文超. All rights reserved.
//

#import "NTESDemoViewController.h"
#import "NTESMeetingViewController.h"

#define JoinMeetingSegue @"Join Meeting"

@interface NTESDemoViewController ()

@property (strong, nonatomic) IBOutlet UITextField *userIDTextField;
@property (strong, nonatomic) IBOutlet UITextField *roomIDTextField;

@end

@implementation NTESDemoViewController

- (void)viewDidLoad
{
    [super viewDidLoad];
    self.userIDTextField.text = [self randomUserID];
}

- (NSString *)randomUserID
{
    uint64_t uid = 10000 + arc4random() % (99999 - 10000);
    return @(uid).stringValue;
}

- (BOOL)shouldPerformSegueWithIdentifier:(NSString *)identifier sender:(id)sender
{
    if ([identifier isEqualToString:JoinMeetingSegue]) {
        return self.userIDTextField.text.length > 0 && self.roomIDTextField.text.length > 0;
    }
    return NO;
}

- (void)prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    [self.view endEditing:YES];
    if ([segue.identifier isEqualToString:JoinMeetingSegue]) {
        NTESMeetingViewController *meetingViewController = segue.destinationViewController;
        meetingViewController.userID = self.userIDTextField.text.longLongValue;
        meetingViewController.roomID = self.roomIDTextField.text;
    }
}

@end
