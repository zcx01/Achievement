import QtQuick 2.0

Rectangle{
    id:container
    width: 600;height: 200
    Rectangle{
        id:rect
        width: 50;height: 50
        color: "red"
        opacity: (600.0 - x)/600
        MouseArea{
            anchors.fill: parent
            drag{
                target: rect
                axis: Drag.XAxis
                minimumX: 0
                maximumX: container.width - rect.width
            }
        }
    }
}
