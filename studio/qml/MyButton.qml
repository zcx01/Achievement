import QtQuick 2.0
import QtQuick.Controls 1.4

Item {

    property int currentIndex: 0
    function setCheck(v){
        //        currentIndex = v;
        c1.checked = true;
    }

    Row{
        LayoutMirroring.enabled: true
        CheckBox{
            text:"test1"
            checked: currentIndex == 0;
        }
        CheckBox{
            id:c1
            text:"test2"
            checked: currentIndex == 1;
        }
        CheckBox{
            text:"test3"
            checked: currentIndex == 2;
        }
    }

}
