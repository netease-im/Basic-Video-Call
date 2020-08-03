//  Created by NetEase on 8/3/2020.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

import QtQuick 2.0
/**
*定义了一个Image_button，可以显示自定义的图片并触发clicked信号
*/
Rectangle {
    id: image_button
    color: "transparent"

    signal clicked

    //Image_button无鼠标事件时显示defaultImage
    property url defaultImageSrc: image.source
    //当鼠标在Image_button区域内时显示hoveredImage
    property url hoveredImageSrc: image.source
    //当鼠标在Image_button区域内并按下时显示pressedImage
    property url pressedImageSrc: image.source


    Component.onCompleted: {
        image.source = defaultImageSrc
    }

    Image{
        id: image
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.verticalCenter: parent.verticalCenter
        fillMode: Image.PreserveAspectFit
        width: parent.width
        height: parent.height
//        onSourceSizeChanged: {
//            image.width = sourceSize.width
//            image.height = sourceSize.height
//        }
    }

    MouseArea{
        id: ma
        anchors.fill: parent
        //当单击本区域时，触发上面自定义的clicked信号
        onClicked: image_button.clicked()
        hoverEnabled: true
        //当鼠标移入区域时，将背景图片换为 hoveredImage
        onHoveredChanged: image.source = containsMouse ? hoveredImageSrc : defaultImageSrc
        onPressedChanged: {
            if(containsMouse){
                if(pressed){
                    image.source = pressedImageSrc  //如果鼠标在区域内并按下
                }else{
                    image.source = hoveredImageSrc  //如果鼠标在区域内但没有按下
                }

            }else{
                image.source = defaultImageSrc      //如果鼠标不在区域内
            }
        }
    }
}
