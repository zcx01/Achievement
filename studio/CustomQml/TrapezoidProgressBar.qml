import QtQuick 2.0
import QtQuick.Controls 2.2

ProgressBar{
    id:progressBar
    property int triangleWidth: progressBar.height/2
    property string textContent:""
    property string unit: "%"
    property var itemColors:{"20":"#F63636","50":"#FFB22C","100":"#67DECB"}

    Text {
        id: text
        anchors.bottom: progressBar.top
        anchors.horizontalCenter: progressBar.horizontalCenter
        text: (progressBar.textContent.length === 0 ? parseInt(progressBar.visualPosition * 100) : progressBar.textContent) + unit
        color: "#FFFFFF"
        font.pixelSize: 16
        font.bold: true
    }
    background: Rectangle {   //背景项
        id:backgroundRectangle
        property int borderWidth: 2
        implicitWidth: progressBar.width
        implicitHeight: progressBar.height
        color: "transparent"
        radius: 6 //圆滑度
        border.width: borderWidth
        border.color: Qt.rgba(1,1,1,0.6)
    }
    NumberAnimation {
        id:num
        target: progressBar
        property: "value"
        from:1
        to: 0
        duration: 5000
        loops : -1
    }

    Component.onCompleted: {
        num.start()

    }
    function calX()
    {
        for(var itemColor in progressBar.itemColors)
        {
            if(progressBar.visualPosition * 100 <= Number(itemColor))
            {
                return progressBar.itemColors[itemColor]
            }
        }
    }

    contentItem: Item {   //内容项
        Rectangle{
            id:content
            clip:true
            x:backgroundRectangle.borderWidth+2
            y:backgroundRectangle.borderWidth+1
            height: progressBar.height-content.y*2
            width: progressBar.width-content.x*2
            color: "transparent"

            Canvas {
                id: canvasId
                x:-(1-(progressBar.visualPosition))*canvasId.width
                property color triangleColor: calX()
                width: progressBar.triangleWidth+content.width
                height: content.height
                contextType: "2d"

                onPaint: {
                    context.lineWidth = 0
                    context.strokeStyle = "#00000000"
                    context.fillStyle =   triangleColor
                    context.beginPath();
                    context.moveTo(0, 0)
                    context.lineTo(0, canvasId.height);
                    context.lineTo(content.width, canvasId.height);
                    context.lineTo(canvasId.width, 0);
                    context.closePath();
                    context.fill()
                    context.stroke();
                }
                onTriangleColorChanged: {
                    canvasId.requestPaint()
                }
            }
        }
    }
}
