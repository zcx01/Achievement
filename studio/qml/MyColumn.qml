import QtQuick 2.0

Column {
    spacing: 2
    id:root
    Rectangle{id:r1;color:"red"; width: 50;height: 50;}
    Rectangle{id:r2;color:"red"; width: 50;height: 50;}
    Rectangle{id:r3;color:"red"; width: 50;height: 50;}
    populate : Transition {
        NumberAnimation{properties: "x,y";duration: 1000}
    }
    Keys.onSpacePressed: r1.visible = !r1.visible
    focus: true

}
