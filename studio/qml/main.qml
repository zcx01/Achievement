import QtQuick 2.12
import QtQuick.Window 2.12
import TEST.messging 1.0
import QtQuick.Dialogs 1.0
import qml.Singleton 1.0
import QtQuick.Controls 2.0

Window {
    id:win
    width: 640
    height: 480
    visible: true
    title: qsTr("Hello World")
    signal qmlSignal(var msg)

    function text(msg){
        //        Array a;
        //        a.splice(i);
        console.log(msg)
        return "some retrun value";
    }


    MouseArea{
        anchors.fill: parent
        onClicked: {
            win.qmlSignal(win)
            loader.item.text="OnClick"
        }
    }

    function myFunction(total, value, index, array){
        console.log(total)
        return total+value;
    }

    Component{
        id:test
        Text {
            //            property var jsObject;
            width:jsObject.w
            height:jsObject.h
            text:jsObject.text
        }
    }


    function creatTest(){
        var tmp = {};
        tmp.w = 300
        tmp.h = 300
        tmp.text = "TEST"
        return tmp;
    }
    property var add : (function () {
        var counter = 0;
        return function () {return counter += 1;}
    })();

    Loader{
        id:loader
        property var jsObject : creatTest()
        sourceComponent: test
        Component.onCompleted: {
            console.log(JSON.stringify(jsObject))
        }
    }
}
