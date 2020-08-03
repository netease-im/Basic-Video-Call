//  Created by NetEase on 8/3/2020.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

import QtQuick 2.0

Rectangle {
    id: titleBar
    width: 680
    height: 50
    radius: 8
    transformOrigin: Item.Center
//    color: "transparent"
    //渐变色
    gradient: Gradient {
        GradientStop {position: 0.0; color: "#292933"}
        GradientStop {position: 1.0; color: "#212129"}
    }
    border.color: "transparent"
    property bool has_maximize_button: false
    property alias minimize_button: minimize_button
    property alias maximize_button: maximize_button
    property alias close_button: close_button
    property bool isMaximized: false

    MouseArea{
        //当拖拽title_bar时，改变主窗体的位置
        property var window: main
        anchors.fill: parent
        property point clickPos: "1,1"
        onPressed: {
            clickPos = Qt.point(mouse.x,mouse.y)
        }
        onPositionChanged: {
            var delta = Qt.point(mouse.x-clickPos.x, mouse.y-clickPos.y)
            window.x = window.x+delta.x
            window.y = window.y+delta.y
        }
    }

    Rectangle{
        id: bottomLeft
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: 25
        height: 25
        gradient:Gradient {
            GradientStop {position: -1.0; color: "#292933"}
            GradientStop {position: 1.0; color: "#212129"}
        }
    }

    Rectangle{
        id: bottomRight
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: 25
        height: 25
        gradient:Gradient {
            GradientStop {position: -1.0; color: "#292933"}
            GradientStop {position: 1.0; color: "#212129"}
        }
    }

    Image_button{
        id: minimize_button
        x: 560
        y: 10
        visible: true
        defaultImageSrc: "qrc:/G2-Sample-cut/pc-4.1-最小化-default@2x.png"
        hoveredImageSrc: "qrc:/G2-Sample-cut/pc-4.1-最小化-hover@2x.png"
        pressedImageSrc: "qrc:/G2-Sample-cut/pc-4.1-最小化-click@2x.png"
        width: 30
        height: 30
        anchors.bottomMargin: 10
        anchors.margins: 10
        anchors.bottom: parent.bottom
        anchors.right: maximize_button.left
        onClicked: {
            main.minimizeWindow()
        }
    }

    Image_button{
        id: maximize_button
        visible: parent.has_maximize_button
        defaultImageSrc: "qrc:/G2-Sample-cut/pc-4.1-最大化-default@2x.png"
        hoveredImageSrc: "qrc:/G2-Sample-cut/pc-4.1-最大化-hover@2x.png"
        pressedImageSrc: "qrc:/G2-Sample-cut/pc-4.1-最大化-click@2x.png"
        width: 30
        height: 30
        anchors.bottomMargin: 10
        anchors.margins: 10
        anchors.bottom: parent.bottom
        anchors.right: close_button.left
        onClicked: {
            isMaximized = !isMaximized
            if(isMaximized){
                main.maximizeWindow()
                defaultImageSrc = "qrc:/G2-Sample-cut/pc-4.1-还原-default@2x.png"
                hoveredImageSrc = "qrc:/G2-Sample-cut/pc-4.1-还原-hover@2x.png"
                pressedImageSrc = "qrc:/G2-Sample-cut/pc-4.1-还原-click@2x.png"
            }else{
                main.normalizeWindow()
                defaultImageSrc = "qrc:/G2-Sample-cut/pc-4.1-最大化-default@2x.png"
                hoveredImageSrc = "qrc:/G2-Sample-cut/pc-4.1-最大化-hover@2x.png"
                pressedImageSrc = "qrc:/G2-Sample-cut/pc-4.1-最大化-click@2x.png"
            }
        }
    }

    Image_button{
        id: close_button
        visible: true
        defaultImageSrc: "qrc:/G2-Sample-cut/pc-4.1-关闭-default@2x.png"
        hoveredImageSrc: "qrc:/G2-Sample-cut/pc-4.1-关闭-hover@2x.png"
        pressedImageSrc: "qrc:/G2-Sample-cut/pc-4.1-关闭-click@2x.png"

        width: 30
        height: 30
        anchors.margins: 10
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        onClicked: {
            main.closeWindow()
        }
    }

    Image{
        id: icon
        source: "qrc:/G2-Sample-cut/title_icon.PNG"
        anchors.leftMargin: 16
        anchors.left: parent.left
        anchors.verticalCenter: parent.verticalCenter
        height:30
        fillMode: Image.PreserveAspectFit
    }

}
