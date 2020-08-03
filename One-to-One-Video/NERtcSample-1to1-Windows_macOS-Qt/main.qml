//  Created by NetEase on 8/3/2020.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

import QtQuick 2.14
import QtQuick.Window 2.12
import QtGraphicalEffects 1.0

Window {
    visible: true
    width: 720
    height: 490
    flags: Qt.FramelessWindowHint | Qt.Window
    color: "transparent"

    property string roomId: ""
    signal toastShow(var text)

    id: main

    DropShadow {
        anchors.fill: loader
        horizontalOffset: 0
        verticalOffset: 10
        radius: 10
        source: loader
        samples: 11
        color: Qt.rgba(0/255,0/255,0/255, 0.2)
    }


    Loader{
        id: loader
        focus: true
        anchors.fill: parent
        anchors.leftMargin: 20
        anchors.rightMargin: 20
        anchors.bottomMargin: 20
    }

    Component.onCompleted: {
        joinRoomPage()
    }

    Connections{
        target: NRTCEngine
        onLeavingChannel:{
            joinRoomPage()
        }

    }

    function joinRoomPage(){
        width = 720
        height = 490
        loader.setSource(Qt.resolvedUrl("qrc:/ui/Joinroom_page.qml"))
    }
    function inRoomPage(){
        width = 1000
        height = 664
        loader.setSource(Qt.resolvedUrl("qrc:/ui/Inroom_page.qml"))
    }

    function joinChannel(room_id){
        if(room_id.length === 0){
            toastShow(qsTr("请填写房间号"))
            return
        }

        var ret = NRTCEngine.joinChannel(room_id);

        if(ret === 0){
            roomId = room_id
            inRoomPage()
        }else if(ret === -1){
            toastShow(qsTr("房间号应为12位以内数字"))
        }
    }
    function leaveChannel(){
        if (NRTCEngine.leaveChannel() === 0) {
            roomId = ""
            loader.setSource(Qt.resolvedUrl("qrc:/ui/Joinroom_page.qml"))
        }
    }

    function minimizeWindow(){
        showMinimized()
    }
    function maximizeWindow(){
        showMaximized()
    }
    function closeWindow(){
        close()
    }
    function normalizeWindow(){
        showNormal()
    }
}
