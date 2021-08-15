import QtQuick 2.2
import QtQuick.Controls 1.2
import QtQuick.Controls.Styles 1.4

Item {
    ComboBox{
        id:cbx
//        model:["a","b","c"]
        editable:true
        model: ListModel{
            id:model
            ListElement{text:"a"}
            ListElement{text:"b";}
            ListElement{text:"c";}
        }
        style: ComboBoxStyle{
            textColor: "red"
        }
        //接受编辑结束后的添加到下拉框中
        onAccepted: {
            if(cbx.find(currentText) === -1){
                model.append({text:currentText})
                currentIndex = cbx.find(currentText)
            }
        }

    }
}
