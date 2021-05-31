pragma Singleton

import QtQuick 2.0

Item {
    Rectangle{
        color: "red"
        width: 100
        height: 100
        opacity: 0.5//会应用到子项目上
        Rectangle{
            opacity:1
            color: Qt.rgba(255,0,0)
            x:238;y:86;width: 100;height: 100
            border.width: 1
            border.color: "blue"
            radius: 9
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
