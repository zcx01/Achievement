import QtQuick 2.0
// 附加属性和附加信号处理器

ListView {
    id:rootView
    width: 240; height: 320;model: 3; focus: true
    delegate: Rectangle{
        width: 240 ;height:30
        color: ListView.isCurrentItem ? "red" : "yellow";
    }

    MouseArea{
        anchors.fill: parent
        onClicked: {
        }
    }
}
