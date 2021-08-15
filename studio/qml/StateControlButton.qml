import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQuick.Layouts 1.2

Item{
    id:root
    property var images
    signal buttonClick(int index)

    function setStateButton(index,state){
        repeater.itemAt(index).buttonCheck = state
    }

    RowLayout{
        anchors.fill: parent
        Repeater{
            id:repeater
            model: images
            Column{
                id:col
                //属性不能定义在Repeater中
                property bool buttonCheck:false
                spacing: 2
                Image{
                    id:_image
                    source: images[index]
                    MouseArea{
                        anchors.fill: _image
                        onClicked: {
                            buttonCheck = !buttonCheck
                        }
                    }
                }
                Rectangle{
                    id:rect
                    x:(_image.width-width)/2
                    width: 50
                    height: 20
                    radius: 10
                    color:buttonCheck ? "yellow": Qt.rgba(0,0,0,1)
                    MouseArea{
                        anchors.fill: rect
                        onClicked: {
                            buttonCheck = !buttonCheck
                            buttonClick(index)
                        }
                    }
                }
            }
        }
    }
}
