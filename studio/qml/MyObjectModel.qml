import QtQuick 2.0
import QtQuick.Controls 1.2
import QtQml.Models 2.3

Item {
    height: 90
    //不需要委托，可以显示可视项目
    ObjectModel{
        id:itemModel
        Rectangle{width: 80;height: 30; color: "red"}
        Rectangle{width: 80;height: 30; color: "green"}
        Rectangle{width: 80;height: 30; color: "blue"}
    }

    ListView{
        anchors.fill: parent
        model: itemModel
    }
}
