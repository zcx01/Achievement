import QtQuick 2.0

Rectangle {
    id:testSig
    signal clicked
    signal hovered
    signal actionPerformed(string action,var actonResult)
    width:  200
    height: 200
    color: Qt.rgba(0,0,0,1);

    MouseArea{
        hoverEnabled: true
        anchors.fill: parent
        onClicked:
        {
            testSig.clicked()
        }
        onEntered: {
            testSig.hovered()
        }
        onPressed: {
            actionPerformed("按下",mouse);
        }
    }
}

//CustomSig{
//    id:sig
//    onClicked: console.log("click")
//    onHovered: console.log("hover")
//    onActionPerformed: {
//        console.log(action,actonResult.x,actonResult.y);
//    }
//}

//在对象的外部使用信号
//Connections{
//    target: sig
//    onClicked : console.log("接受到sig点击")
//}

//连接多个函数
//Component.onCompleted: {
//    sig.clicked.connect(testSig1);
//    sig.clicked.connect(testSig2);
//}
//function testSig1(){
//    console.log("test1")
//}
//function testSig2(){
//    console.log("test2")
//}
