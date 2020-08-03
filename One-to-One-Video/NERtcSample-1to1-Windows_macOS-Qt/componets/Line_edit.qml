//  Created by NetEase on 8/3/2020.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

import QtQuick 2.0

Rectangle {
    width:315
    height: 44
    border.color: "transparent"
    color: "transparent"
    property alias text: input.text //
    property alias hint: hint.text //
    property int font_size: 17 //定义字体大小

    signal accepted

    Text {
        id: hint  //水印层文字显示
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter //垂直对齐
        text: "请输入房间号"
        font.pixelSize: font_size //字体大小
        color: "#B0B6BE"
        opacity: input.length ? 0 : 1 //不透明度
    }

    TextInput {
        id: input
        focus: true
        anchors.fill: parent
        verticalAlignment: Text.AlignVCenter  //垂直对齐
        font.pixelSize: font_size
        color: "#337EFF"
        onAccepted: wrapper.accepted()  //链接到信号
    }

    Rectangle{
        id: under_line
        border.color: input.length ? "#337EFF" : "#B0B6BE"
        height: 2
        width: parent.width
        anchors.bottom: parent.bottom
    }

    Image_button{
        id: clear_button
        defaultImageSrc: "qrc:/G2-Sample-cut/clear_button.PNG"
        hoveredImageSrc: defaultImageSrc
        pressedImageSrc: defaultImageSrc
        width:20
        height: 20
        visible: !(input.text === "")
        anchors.leftMargin: 298
        anchors.left: parent.left
        anchors.verticalCenter:parent.verticalCenter
        onClicked: {
            input.text = ""
        }
    }
}

