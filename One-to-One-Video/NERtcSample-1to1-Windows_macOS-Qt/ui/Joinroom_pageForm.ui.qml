//  Created by NetEase on 8/3/2020.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

import QtQuick 2.4
import "qrc:/componets/"

Rectangle {
    id: join_room
    width: 680
    height: 470
    radius: 8
    property alias join_room_button: join_room_button
    property alias room_id: room_id_line_edit.text
    property alias toast: toast

    Titlebar {
        id: title_bar
        x: 0
        y: 0
        has_maximize_button: false
    }

    Toast {
        id: toast
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 8
        anchors.top: box.top
    }

    Rectangle {
        id: box
        width: 400
        height: 400
        color: "transparent"
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.topMargin: 10
        anchors.top: title_bar.bottom
        Image {
            id: icon
            width: 220
            height: 55
            source: "qrc:/G2-Sample-cut/icon.PNG"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 60
            anchors.top: parent.top
        }
        Line_edit {
            id: room_id_line_edit
            text: ""
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 166
            anchors.top: parent.top
        }

        Rectangle_button {
            id: join_room_button
            text: "加入房间"
            anchors.horizontalCenter: parent.horizontalCenter
            anchors.topMargin: 250
            anchors.top: parent.top
        }
    }
}
