import QtQuick 2.0

Item {
    id:rootItem
    property string value: "17.6"
    property bool valid:false
    property string inValidStr: "--"
    property string unit: ""
    property string comment: ""
    property string unitColor: "#FFFFFF"
    property int valueFontSize: 24
    property int unitFontSize: 24
    property bool valueFontBold: true
    implicitHeight: childrenRect.height
    implicitWidth: childrenRect.width
    Row
    {
        id:col
        anchors.left: rootItem.left
        spacing: 4
        Text {
            id: valueItem
            text: valid ? value : inValidStr
            color: "#FFFFFF"
            font.bold: valueFontBold
            font.pixelSize: valueFontSize

        }
        Text {
            id: unitItem
            text: unit
            color:unitColor
            font.pixelSize: unitFontSize
            anchors.bottom : valueItem.bottom
        }
    }

    Text {
        anchors.top: col.bottom
        anchors.topMargin: 2
        anchors.horizontalCenter: col.horizontalCenter
        id: commentItem
        visible: comment.length !== 0
        text: comment
        color: "#80FFFFFF"
        font.pixelSize: 12
    }
}
