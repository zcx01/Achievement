import QtQuick 2.0

//弹动效果
Item{

    Flickable{
        id:flickable
        width: 200; height: 200
        Image {
            id: image
            source: "qrc:/image/sendpix1.jpg"
        }
        contentWidth: image.width
        contentHeight: image.height
        clip: true
    }

    Rectangle{
        id: scrollbar
        anchors.right: flickable.right
        y:flickable.visibleArea.yPosition * flickable.height
        width: 10
        height: flickable.visibleArea.heightRatio * flickable.height
        color: "black"
    }
}
