import QtQuick 2.0

Rectangle {
    id:win
    width: 120;height: 120
    color:"black"
    Rectangle{id:myRect;width: 50;height: 50;color: "red"}
    states: State {
        name: "reanchored"
        AnchorChanges{
            target: myRect
            anchors.top: win.top
            anchors.bottom: win.bottom
        }

        PropertyChanges {
            target: myRect
            anchors.topMargin: 10
            anchors.bottomMargin: 10
        }
    }

    MouseArea{
        anchors.fill:parent
        onClicked:{
            win.state="reanchored";
        }
        onWheel: {
        }
        drag:{
        }
    }
}
