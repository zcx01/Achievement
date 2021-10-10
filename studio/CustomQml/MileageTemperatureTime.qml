import QtQuick 2.0

Item {
    id:rootItem
    //里程
    property bool mileageValid: true
    property real mileage: 12800

    //温度
    property bool temperatureValid: true
    property real temperature: 28

    //时间
    property bool timeValid: true
    property real hour: 12
    property real minute: 20

    implicitHeight: childrenRect.height
    implicitWidth: childrenRect.width
    Row
    {
        id:mileageRow
        Image {
            id: mileageImage
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/image/MileageIcon.png"

        }

        DrivingInfoText{
            valid: mileageValid
            value: mileage
            unit: qsTr("km")
            valueFontSize: 26
            unitFontSize: 16
            unitColor: "#80FFFFFF"
            anchors.bottom: mileageImage.bottom
            anchors.top: mileageImage.top
            valueFontBold:false
        }
    }


    Row
    {
        id:temperatureRow
        anchors.left: mileageRow.right
        anchors.top: mileageRow.top
        Image {
            id: temperatureImage
            anchors.verticalCenter: parent.verticalCenter
            source: "qrc:/image/temperatureIcon.png"

        }

        DrivingInfoText{
            valid: temperatureValid
            value: temperature
            unit: qsTr("°C")
            valueFontSize: 26
            unitFontSize: 26
            unitColor: "#FFFFFFFF"
            anchors.bottom: temperatureImage.bottom
            anchors.top: temperatureImage.top
            valueFontBold:false
        }
    }

    DrivingInfoText{
        anchors.left: temperatureRow.right
        anchors.top: temperatureRow.top
        anchors.leftMargin: 24
        valid: timeValid
        value: parseInt(hour)+":"+parseInt(minute)
        unit: ""
        valueFontSize: 26
        unitFontSize: 16
        unitColor: "#80FFFFFF"
    }
}
