//  Created by NetEase on 8/3/2020.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

import QtQuick 2.4
import "qrc:/ui/"

Inroom_pageForm {
    id: inroom
    Component.onCompleted: {
        NRTCEngine.setupLocalVideo(main_video_frame_provider)
    }
    enable_video_button.onClicked: {
        is_video_enalbed = !is_video_enalbed
        NRTCEngine.enableVideo(is_video_enalbed)
        if(is_video_enalbed){
            enable_video_button.defaultImageSrc = "qrc:/G2-Sample-cut/pc-2.1-停止视频-default@2x.png"
            enable_video_button.hoveredImageSrc = "qrc:/G2-Sample-cut/pc-2.1-停止视频-hover@2x.png"
            enable_video_button.pressedImageSrc = "qrc:/G2-Sample-cut/pc-2.1-停止视频-click@2x.png"
        }else{
            enable_video_button.defaultImageSrc = "qrc:/G2-Sample-cut/pc-2.1-开启视频-default@2x.png"
            enable_video_button.hoveredImageSrc = "qrc:/G2-Sample-cut/pc-2.1-开启视频-hover@2x.png"
            enable_video_button.pressedImageSrc = "qrc:/G2-Sample-cut/pc-2.1-开启视频-click@2x.png"
        }
    }

    enable_audio_button.onClicked:{
        is_audio_enalbed = !is_audio_enalbed
        NRTCEngine.muteLocalAudioStream(!is_audio_enalbed)
        if(is_audio_enalbed){
            enable_audio_button.defaultImageSrc = "qrc:/G2-Sample-cut/pc-2.1-静音-default@2x.png"
            enable_audio_button.hoveredImageSrc = "qrc:/G2-Sample-cut/pc-2.1-静音-hover@2x.png"
            enable_audio_button.pressedImageSrc = "qrc:/G2-Sample-cut/pc-2.1-静音-click@2x.png"
        }else{
            enable_audio_button.defaultImageSrc = "qrc:/G2-Sample-cut/pc-2.1-解除静音-default@2x.png"
            enable_audio_button.hoveredImageSrc = "qrc:/G2-Sample-cut/pc-2.1-解除静音-hover@2x.png"
            enable_audio_button.pressedImageSrc = "qrc:/G2-Sample-cut/pc-2.1-解除静音-click@2x.png"
        }
    }

    end_call_button.onClicked: {
        NRTCEngine.setupLocalVideo(0)
        main.leaveChannel()
    }

    Connections{
        target:NRTCEngine

        onUserJoined: {
            is_remote_user_connected = true
            //console.log("uid :", uid, "online")
            NRTCEngine.setupLocalVideo(sub_video_frame_provider)
            NRTCEngine.setupRemoteVideo(uid, main_video_frame_provider)
        }

        onUserOffline: {
            is_remote_user_connected = false
            //console.log("uid :", uid, "offline")
            NRTCEngine.setupRemoteVideo(uid, 0)
            NRTCEngine.setupLocalVideo(main_video_frame_provider)
        }
    }

}
