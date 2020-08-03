//  Created by NetEase on 8/3/2020.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

import QtQuick 2.0
import QtQuick.Controls 2.12
import QtGraphicalEffects 1.0
import QtQuick.Layouts 1.12

Rectangle {
    id: root
    width: background.width
    height: 40
    radius: 2
    opacity: 0
    color: "#FFFFFF"
    property real time: defaultTime
    readonly property real defaultTime: 3000
    readonly property real fadeTime: 300

    function show(text) {
        txt.text = text
        anim.start();
    }

    Rectangle{
        id: background
        width: content.width + 32
        height: 40
        anchors.centerIn: parent
        radius: parent.radius
        RowLayout {
            id: content
            anchors.verticalCenter: parent.verticalCenter
            anchors.horizontalCenter: parent.horizontalCenter
            spacing: 10

            Image{
                id: icon
                width: 14
                height: 14
                source: "qrc:/G2-Sample-cut/toast_icon.PNG"
            }
            Text{
                id: txt
                text: ""
                font.pixelSize: 14
                color: "#333333"
                verticalAlignment: Text.AlignVCenter
                horizontalAlignment: Text.AlignLeft
            }
        }
    }

    SequentialAnimation on opacity {
        id: anim
        running: false

        NumberAnimation {
            to: 1
            duration: fadeTime
        }
        PauseAnimation {
            duration: time - 2*fadeTime
        }
        NumberAnimation {
            to: 0
            duration: fadeTime
        }
    }

    DropShadow {
        anchors.fill: parent
        horizontalOffset: 0
        verticalOffset: 2
        radius: 6.0
        source: background
        samples: 13
        color: Qt.rgba(23/255,23/255,26/255, 0.1)
        Behavior on radius { PropertyAnimation { duration: 100 } }
    }
}
