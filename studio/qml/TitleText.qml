import QtQuick 2.0

Text {
    property int size
    text:"<b>"+title+"</b>"//title能够声明在其他的文件
    font.pixelSize: size
}
