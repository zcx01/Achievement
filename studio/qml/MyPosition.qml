import QtQuick 2.0

Grid {
    Repeater{
        model: 16
        Rectangle{
            id:rect
            width: 50;height: 30
            border.width: 1
            color: Positioner.isFirstItem ? "yellow" : "lightgreen"
            Text {

                text: rect.Positioner.index
                anchors.centerIn: parent
            }
        }
    }
}
