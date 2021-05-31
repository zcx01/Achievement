import QtQuick 2.0

Item {
    id:root
//    color: "red"
    property real angle: 0  //顺时针
    property string text;
    property real textRotation:angle
    function calX(){
        var radius = (root.width - content.width)/ 2;
        var startX = root.x + radius
        return startX + radius * Math.sin(angle * Math.PI / 180)
    }

    function calY(){
        var radius = (root.height- content.height) / 2;
        var startY = root.y + radius
        return startY - radius * Math.cos(angle * Math.PI / 180);
    }

    Text {
        id:content
        x:calX()
        y:calY()
        text: root.text
        rotation: textRotation
    }


    Component.onCompleted: {
        num.start()
    }


//    NumberAnimation {
//        id:num
//        target: root
//        property: "angle"
//        from:0
//        to: 360
//        duration: 2000
//        loops : -1
//        easing.type: Easing.InOutQuad
//    }
}
