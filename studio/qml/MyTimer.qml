import QtQuick 2.0

Item {
    Timer{
        interval: 500;repeat: true;running: true
        onTriggered: {
            time.text = Date().toString();
        }
    }

    Text {
        id: time
    }
}
