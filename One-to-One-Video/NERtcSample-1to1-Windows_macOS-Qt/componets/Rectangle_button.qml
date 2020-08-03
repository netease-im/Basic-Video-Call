//  Created by NetEase on 8/3/2020.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

import QtQuick 2.0

Rectangle {
    id: button
    width: 315
    height: 50
    radius: 25

    signal clicked

    property color defaultColor: "#337EFF"
    property color pressedColor: "#0b64c1"
    property color hoveredColor: "#2787f2"
    Component.onCompleted: button.color = defaultColor

    property alias textColor: txt.color
    property alias text: txt.text
    property alias fontSize: txt.font.pointSize

    MouseArea{
        id: ma
        anchors.fill: parent
        onClicked: button.clicked()
        hoverEnabled: true
        onHoveredChanged: button.color = containsMouse ? hoveredColor : defaultColor
        onPressedChanged: {
            if(containsMouse){
                if(pressed){
                    button.color = pressedColor
                }else{
                    button.color = hoveredColor
                }

            }else{
                button.color = defaultColor
            }
        }
    }
    Text{
        id: txt
        anchors.centerIn: parent
        font.pixelSize:16
        font.weight: Font.DemiBold
        color: "#FFFFFF"
    }
}
