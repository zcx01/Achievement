import QtQuick 2.0
import QtQuick.Controls 1.3
import QtQml.Models 2.2
import QtQuick.Controls.Styles 1.2
Item {
    //    width: 200; height: 100
    Column{
        ScrollView{
            Image{
                source: "qrc:/image/cal.png"
            }
        }
        TabView{
            Tab{
                title:" Home";
                Rectangle{color: "red"}
            }
            Tab{
                title:" Home1";
                Rectangle{color: "blue"}
            }
        }
        ListModel{
            id:lib
            ListElement{title:"a";author:"s"}
            ListElement{title:"b";author:"d"}
            ListElement{title:"c";author:"w"}//定义的字段必须以小写字母开头
        }



        TableView{
            model:lib
            TableViewColumn{role:"title";title:"Title"}//指定列的属性 role:显示的文本 title:行上的标题
            TableViewColumn{role:"author";title:"Author"}

            //委托，如果放在TableViewColumn中，是指定单列的
            itemDelegate: Item{
                Text {
                    text: styleData.value
                }
            }

        }
    }
}
