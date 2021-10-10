import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.2

Item {
    id: rootItem
    //值无效字符
    property string inValidStr: "---"
    property string unit: qsTr("km")

    //动力电池百分比是否有效
    property bool batteryPercentValid:false

    //动力电池百分比
    property real batteryPercent: 0

    //油量百分比是否有效
    property bool oilPercentValid:false

    //油量百分比
    property real oilPercent: 0

    //电续航剩余里程是否有效
    property bool eleRemainRangeValid:false

    //电续航剩余里程 km
    property real eleRemainRange: 0

    //油续航剩余里程 km
    property bool oilRemainRangeValid:false

    //油续航剩余里程 km
    property real oilRemainRange: 0

    property int energyConsumptionModel:0x1

    Row
    {
        spacing: 5
        Row
        {
            Text {
                id: tolalRemainRange
                text: ((eleRemainRangeValid === false || oilRemainRangeValid ===false) ? inValidStr : parseInt(eleRemainRange+oilRemainRange))+unit
                color: "#FFFFFF"
                font.bold: true
                font.pixelSize: 20
                anchors.verticalCenter: parent.verticalCenter
            }
            Image {
                id: oilIamge
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/image/OilIcon.png"
            }

            TrapezoidProgressBar{
                id:oilItem
                value: rootItem.batteryPercentValid ? rootItem.batteryPercent : 0
                height: 14
                width: 60
                textContent:  (rootItem.oilRemainRangeValid ? rootItem.oilRemainRange.toFixed(0) : inValidStr)
                unit: rootItem.unit
                anchors.verticalCenter: parent.verticalCenter
            }

            Image {
                id: eleIamge
                anchors.verticalCenter: parent.verticalCenter
                source: "qrc:/image/BatteryIcon.png"
            }

            TrapezoidProgressBar{
                id:eleItem
                value: rootItem.batteryPercentValid ? rootItem.batteryPercent : 0
                textContent: (rootItem.eleRemainRangeValid ? rootItem.eleRemainRange.toFixed(0) : inValidStr)
                unit: rootItem.unit
                height:oilItem.height
                width: oilItem.width
                anchors.verticalCenter: parent.verticalCenter
            }
        }


        Image {
            id: energyConsumptionModelItem
            anchors.verticalCenter: parent.verticalCenter
            source: rootItem.energyConsumptionModel === 0x1  ? "qrc:/image/WLTC.png" : "qrc:/image/CLTC.png"
        }
    }

}
