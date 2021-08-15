import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQml.Models 2.1

Rectangle {
    width: 120
    height: 120
    //自由定义的模型
    ListModel{
        id:fruitmodel
        ListElement{
            name:"Apple"
            cost:2.45
            attributes:[
                ListElement{description:"C"},
                ListElement{description:"D"}
            ]
        }
        ListElement{
            name:"Orange"
            cost:3.25
            attributes:[
                ListElement{description:"C"}
            ]
        }
        ListElement{
            name:"Banana"
            cost:1.95
            attributes:[
                ListElement{description:"T"},
                ListElement{description:"S"}
            ]
        }
    }

    Component{
        id:fruitDelegate
        Item{
            width: 200;height: 50
            Text{id:nameField; text:name}
            Text{text:"￥"+cost;anchors.left: nameField.right}
            Row{
                anchors.top: nameField.bottom
                spacing: 5
                Row{
                    Repeater{
                        model: attributes
                        Text {text: description}
                    }
                }
            }
            MouseArea{
                anchors.fill: parent
                onClicked: fruitmodel.setProperty(index,"cost",cost * 2)
            }
        }
    }

    ListView{
        anchors.fill: parent
        model: fruitmodel
        delegate: fruitDelegate
    }
}
