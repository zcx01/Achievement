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

    Text {
        id: name
        text: qsTr("text")
    }
}
