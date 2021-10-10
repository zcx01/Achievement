import QtQuick 2.0
import QtQuick.Layouts 1.2

Item {
    id:rootItem
    property string title: "title"
    implicitHeight: childrenRect.height
    implicitWidth: childrenRect.width
    //油距离
    property bool oilDistanceValid: false
    property real oilDistance: 0

    //油时间
    property bool oilTimeValid: false
    property real oilTime: 0

    //油平均
    property bool oilAveragelid: false
    property real oilAverage: 0

    //电距离
    property bool electricDistanceValid: false
    property real electricDistance: 0

    //电时间
    property bool electricTimeValid: false
    property real electricTime: 0

    //电平均
    property bool electricAveragelid: false
    property real electricAverage: 0

    Row
    {
        id:oilItem
        anchors.top: oiltitle.bottom
        anchors.topMargin: 12
        spacing: 41
        DrivingInfoText
        {
            valid: oilDistanceValid
            value: oilDistance
            unit: qsTr("km")
            comment: qsTr("Distance")
        }
        DrivingInfoText
        {
            valid: oilTimeValid
            value: oilTime
            unit: qsTr("min")
            comment: qsTr("Time")
        }
        DrivingInfoText
        {
            valid: oilAveragelid
            value: oilAverage
            inValidStr: "--.-"
            unit: qsTr("kmh")
            comment: qsTr("AverageEnergy/100km")
        }
    }

    Row
    {
        id:electricItem
        anchors.top: electricTitle.bottom
        anchors.topMargin: 12
        spacing: 41
        DrivingInfoText
        {
            valid: electricDistanceValid
            value: electricDistance
            unit: qsTr("km")
            comment: qsTr("Distance")
        }
        DrivingInfoText
        {
            valid: electricTimeValid
            value: electricTime
            unit: qsTr("min")
            comment: qsTr("Time")
        }
        DrivingInfoText
        {
            valid: electricAveragelid
            value: electricAverage
            inValidStr: "--.-"
            unit: qsTr("kmh")
            comment: qsTr("AverageElectric/100km")
        }
    }

    Text {
        id: titleItem
        text: title
        color: "#80FFFFFF"
        font.pixelSize: 24
        anchors.horizontalCenter: oilItem.horizontalCenter
    }

    Text {
        anchors.top: titleItem.bottom
        anchors.topMargin: 27
        id:oiltitle
        text: qsTr("Drive oil consumption")
        anchors.horizontalCenter: oilItem.horizontalCenter
        color: "#80FFFFFF"
        font.pixelSize: 16
    }

    Text {
        anchors.top: oilItem.bottom
        anchors.topMargin: 27
        id:electricTitle
        text: qsTr("Driving power consumption")
        anchors.horizontalCenter: oilItem.horizontalCenter
        color: "#80FFFFFF"
        font.pixelSize: 16
    }
}
