import QtQuick 2.12
import QtQuick.Window 2.12

Window {
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")

    ArcText{
        anchors.fill: parent
        text: "EFFE"
        angle: 90
        textRotation: 90 - angle
    }
}
