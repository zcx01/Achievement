import QtQuick 2.0

Item {
    property string title
    TitleText{
        id:text
        size:22
        anchors.top: parent.top
    }
    TitleText{
        size:64
        anchors.top: text.bottom
    }
}
