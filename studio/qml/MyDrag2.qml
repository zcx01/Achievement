import QtQuick 2.0

Item {

    Component{
        id:rect
        Rectangle{
            id:rect1
            color: customColor
            width: 20
            height:20
            Drag.active:dragArea.drag.active
            Drag.hotSpot.x: 10
            Drag.hotSpot.y: 10
            Drag.source: rect1
            MouseArea{
                id:dragArea
                anchors.fill: parent
                drag.target: parent
            }

        }
    }

    width: 400; height: 150
    DropArea {
        x : 175; y:75
        width: 50; height: 50
        Rectangle{
            id:area;
            anchors.fill: parent
            border.color: "black"
        }
        onEntered: {
            area.color = drag.source.color
        }
    }

    Loader{property var customColor:"blue";sourceComponent: rect; x:110}
    Loader{property var customColor:"red";sourceComponent: rect; x:140}
    Loader{property var customColor:"yellow";sourceComponent: rect; x:170}
    Loader{property var customColor:"black";sourceComponent: rect; x:200}
    Loader{property var customColor:"steelblue";sourceComponent: rect; x:230}
    Loader{property var customColor:"green";sourceComponent: rect; x:260}
}
