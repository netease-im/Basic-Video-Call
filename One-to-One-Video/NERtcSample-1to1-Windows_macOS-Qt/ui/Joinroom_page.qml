//  Created by NetEase on 8/3/2020.
//  Copyright (c) 2014-2020 NetEase, Inc. All rights reserved.
//

import QtQuick 2.4
import "qrc:/ui/"

Joinroom_pageForm {
    anchors.fill: parent

    join_room_button.onClicked: {
//        console.log("room_id:"+room_id)
        main.joinChannel(room_id)
    }

    Connections{
        target: main
        onToastShow:{
            toast.show(text)
        }
    }

}
