//  Created by NetEase on 8/3/2020.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

import QtQuick 2.0

Rectangle {
    id: tool_bar
    width: 960
    height: 54
    radius: 8
    property alias enalbe_video_button: enalbe_video_button
    property alias enable_audio_button: enable_audio_button
    property alias end_call_button: end_call_button

    gradient: Gradient{
        GradientStop{position: 0.0; color: "#292933"}
        GradientStop{position: 0.0; color: "#212129"}
    }

    Rectangle{
        anchors.left: parent.left
        anchors.top: parent.top
        width: 27
        height: 27
        gradient:Gradient {
            GradientStop {position: 0.0; color: "#292933"}
            GradientStop {position: 2.0; color: "#212129"}
        }
    }

    Rectangle{
        anchors.right: parent.right
        anchors.top: parent.top
        width: 27
        height: 27
        gradient:Gradient {
            GradientStop {position: 0.0; color: "#292933"}
            GradientStop {position: 2.0; color: "#212129"}
        }
    }

    Rectangle{
        id: end_call_button_background
        width:125
        height:54
        color: "transparent"
        anchors.centerIn: parent
        Image_button{
            id: end_call_button
            width:68
            height:36
            anchors.centerIn: parent
            defaultImageSrc: "qrc:/G2-Sample-cut/pc-2.1-结束视频-default@2x.png"
            hoveredImageSrc: "qrc:/G2-Sample-cut/pc-2.1-结束视频-hover@2x.png"
            pressedImageSrc: "qrc:/G2-Sample-cut/pc-2.1-结束视频-click@2x.png"
        }
    }
    Rectangle{
        width:125
        height:54
        color: "transparent"
        anchors.right: end_call_button_background.left
        anchors.verticalCenter: parent.verticalCenter
        Image_button{
            id: enable_audio_button
            width:60
            height:54
            anchors.centerIn: parent
            defaultImageSrc: "qrc:/G2-Sample-cut/pc-2.1-静音-default@2x.png"
            hoveredImageSrc: "qrc:/G2-Sample-cut/pc-2.1-静音-hover@2x.png"
            pressedImageSrc: "qrc:/G2-Sample-cut/pc-2.1-静音-click@2x.png"

        }
    }
    Rectangle{
        width:125
        height:54
        color: "transparent"
        anchors.left: end_call_button_background.right
        anchors.verticalCenter: parent.verticalCenter
        Image_button{
            id: enalbe_video_button
            width:60
            height:54
            anchors.centerIn: parent
            defaultImageSrc: "qrc:/G2-Sample-cut/pc-2.1-停止视频-default@2x.png"
            hoveredImageSrc: "qrc:/G2-Sample-cut/pc-2.1-停止视频-hover@2x.png"
            pressedImageSrc: "qrc:/G2-Sample-cut/pc-2.1-停止视频-click@2x.png"

        }
    }

}
