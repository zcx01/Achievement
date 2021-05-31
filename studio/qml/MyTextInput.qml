import QtQuick 2.2

Rectangle{
    width: 100
    height: 50
    TextInput{//相等于QLineEdit--(一般不使用单独使用)
//        validator: IntValidator{bottom:11; top:31}
        focus: true
        echoMode: TextInput.PasswordEchoOnEdit
        anchors.fill: parent
    }
    border.color: "red"
}
