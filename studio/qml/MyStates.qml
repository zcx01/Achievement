import QtQuick 2.0

Item {
    width: 300;
    height: 300
    Rectangle{
        id:signals
        anchors.fill: parent
        color: "green"
        states: [
            State {
                name: "WARNING"
                PropertyChanges {
                    target: signals
                    color:"red"
                }
            },
            State {
                name: "CRITICAL"
                PropertyChanges {
                    target: signals
                    color:"yellow"
                }
            }
        ]
        MouseArea{
            anchors.fill: parent
            onClicked:{
            signals.state = "CRITICAL"
            }
        }
    }
}
