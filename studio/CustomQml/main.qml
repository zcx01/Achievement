import QtQuick 2.12
import QtQuick.Window 2.12
import IpcTopicDef 1.1

Window {
    width: 640
    height: 480
    visible: true
//    color: Qt.rgba(0,0,0,1)


    title: qsTr("Hello World")

//    ArcText{
//        anchors.fill: parent
//        text: "EFFE"
//        angle: 90
//        textRotation: 90 - angle
//    }

    Text{
        anchors.centerIn: parent
        width: 500
        height:50
        text: IpcTopicDef.t_TOPIC_ASSIST_HU_IACCENABLE
    }
}
