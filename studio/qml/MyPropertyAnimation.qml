import QtQuick 2.0
//Image {
//    id:fengcheg
//    width: 300;height: 300
//    source: "qrc:/image/sendpix0.jpg"
//    opacity: 0.1
//    MouseArea{
//        anchors.fill: parent
//        onClicked: {
//            animateOpacity.start()
//            animateRotation.start()
//        }
//    }
//    PropertyAnimation{
//        id:animateOpacity
//        target: fengcheg
//        properties: "opacity"
//        to: 1.0
//        duration: 2000
//    }

//    NumberAnimation{
//        id:animateRotation
//        target: fengcheg
//        loops: Animation.Infinite
//        properties: "rotation"
//        from: 0
//        to:360
//        duration: 3000
//        easing {type: Easing.OutBack}
//    }
//}
//组合动画
//Rectangle{
//    id:rect
//    width: 100 ; height: 100
//    color: "red"
//    SequentialAnimation on color {
//        ColorAnimation{to:"yellow";duration: 1000}
//        ColorAnimation{to:"blue";duration: 1000}
//    }
//}

//过渡动画
//Item{
//    width: 100; height: 100
//    Rectangle{
//        width: 75; height: 75
//        anchors.centerIn: parent
//        id:button
//        state: "RELEASED"
//        MouseArea{
//            anchors.fill: parent
//            onPressed: button.state = "PRESSED"
//            onReleased: button.state = "RELEASED"
//        }


//        states: [
//            State {
//                name: "PRESSED"
//                PropertyChanges {
//                    target: button
//                    color:"lightblue"
//                }
//            },
//            State {
//                name: "RELEASED"
//                PropertyChanges {
//                    target: button
//                    color:"lightsteelblue"
//                }
//            }
//        ]

//        transitions:[
//            Transition {
//                from: "PRESSED"
//                to: "RELEASED"
//                ColorAnimation{target: button;duration: 100}
//            },
//            Transition {
//                from: "RELEASED"
//                to: "PRESSED"
//                ColorAnimation{target: button;duration: 100}
//            }
//        ]
//    }
//}
Rectangle{
    width: 75;height: 75;radius: width
    
}
