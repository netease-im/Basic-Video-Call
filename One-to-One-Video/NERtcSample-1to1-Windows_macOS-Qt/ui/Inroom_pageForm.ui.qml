//  Created by NetEase on 8/3/2020.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

import QtQuick 2.4
import QtQuick.Window 2.14
import QtMultimedia 5.14
import FrameProvider 1.0
import "qrc:/componets/"

Rectangle {
    width: 960
    height: 644
    radius: 8
    property alias main_video: main_video
    property alias sub_video: sub_video
    property bool is_remote_user_connected: false
    property bool is_video_enalbed: true
    property bool is_audio_enalbed: true
    property alias enable_video_button: tool_bar.enalbe_video_button
    property alias enable_audio_button: tool_bar.enable_audio_button
    property alias end_call_button: tool_bar.end_call_button
    property alias main_video_frame_provider: main_video_frame_provider
    property alias sub_video_frame_provider: sub_video_frame_provider

    Titlebar {
        id: title_bar
        has_maximize_button: true
        anchors.top: parent.top
        anchors.left: parent.left
        anchors.right: parent.right
    }

    Rectangle {
        id: background
        anchors.top: title_bar.bottom
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.right: parent.right
        radius: 8
        Rectangle{
            width: 8
            height: 8
            anchors.left: parent.left
            anchors.top: parent.top
            color:"#141417"
        }

        Rectangle{
            width: 8
            height: 8
            anchors.right: parent.right
            anchors.top: parent.top
            color:"#141417"
        }

        gradient: Gradient {
            GradientStop {
                position: 0.0
                color: "#141417"
            }
            GradientStop {
                position: 1.0
                color: "#181824"
            }
        }

        Toolbar {
            id: tool_bar
            anchors.left: parent.left
            anchors.right: parent.right
            anchors.bottom: parent.bottom
        }

        Rectangle {
            id: main_video_background
            anchors.bottom: tool_bar.top
            anchors.top: parent.top
            anchors.horizontalCenter: parent.horizontalCenter
            width: height / 9 * 16
            color: "transparent"

            FrameProvider {
                id: main_video_frame_provider
            }

            VideoOutput {
                property bool is_remote_user_video_enabled: false
                id: main_video
                anchors.fill: parent
                source: main_video_frame_provider
                fillMode: VideoOutput.PreserveAspectFit
                visible: is_remote_user_connected ? is_remote_user_video_enabled : is_video_enalbed
                Connections{
                    target: NRTCEngine
                    onUserVideoEnabled:{
                        //console.log("main_video enabled: ", enabled)
                        main_video.is_remote_user_video_enabled = enabled
                    }
                }
            }
        }

        Rectangle {
            id: sub_video_background
            anchors.margins: parent.width / 60
            anchors.top: parent.top
            anchors.right: parent.right
            width: 160
            height: 90
            color: is_remote_user_connected ? "transparent" : "#292933"

            Text {
                visible: !is_remote_user_connected
                id: sub_video_text
                anchors.centerIn: parent
                text: qsTr("等待加入...")
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignHCenter
                font.pixelSize: 16
                color: "#FFFFFF"
            }

            FrameProvider {
                id: sub_video_frame_provider
            }

            VideoOutput {
                id: sub_video
                anchors.fill: parent
                source: sub_video_frame_provider
                fillMode: VideoOutput.PreserveAspectFit
                visible: is_remote_user_connected ? is_video_enalbed : false
            }
        }
    }
}
