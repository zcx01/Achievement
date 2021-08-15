import QtQuick 2.0

Text {
    default property var someText;
    text: "hello," + someText.text;
}

//MyLabel{
//    id: mylabel
//    anchors.centerIn: parent
//    Text{
//        text: "world";//等价于someText:Text{text:"world!"};Text对象会自动成为MyLabel的默认属性值
//    }
//    Component.onCompleted: {
//        console.log(someText.text);
//    }
//    onClicked: {
//        mylabel.someText.text = "ces";
//    }
//}
