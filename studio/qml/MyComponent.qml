import QtQuick 2.0
import QtQuick.Controls 1.2

Item {

    Column{
        //滑动条
        Slider{
            orientation : Qt.Vertical
        }
        //数值选择框
        SpinBox{
//            prefix: "p"//前缀
//            suffix: "s"//后缀

        }

        GroupBox{
            title: qsTr("box")
            checkable: true //内部的子控件是否可以选择
            flat: false //是否最简化
            Column{
                CheckBox{text: "update"}
                CheckBox{text: "add"}
                CheckBox{text: "remove"}
            }
        }

        //忙等 属性running为false自动消失
        BusyIndicator{
        }

    }
}
