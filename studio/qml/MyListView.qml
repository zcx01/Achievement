import QtQuick 2.0

Item{
    ListView{
        id:list
        width: 200
        height: parent.height
        anchors.margins: 30
        model: 5;spacing: 5
        delegate: numberDelegate;snapMode: ListView.SnapToItem
        header: Rectangle{
            width: 50;height: 50;color: "#b4d34e"
            Text{anchors.centerIn: parent;text: "header"}
        }
        footer: Rectangle{
            width: 50;height: 50;color: "#797e65"
            Text{anchors.centerIn: parent;text: "footer"}
        }
        highlight: Rectangle{
            color: "black";radius: 5
            opacity: 0.3
            z:5
        }
        focus: true
        keyNavigationWraps: true
        highlightMoveVelocity: 100
    }
    Component{
        id:numberDelegate
        Rectangle{
            id:wrapper; width: 50;height: 50
            color: ListView.isCurrentItem ? "white" : "lightGreen"
            Text{
                anchors.centerIn: parent
                font.pointSize: 15;text: index
                color: wrapper.ListView.isCurrentItem ? "blue" : "white"
            }
        }
    }

    ListModel{
        id:nameModel
        ListElement{name:"Alice";team:"Crypto"}
        ListElement{name:"Bob";team:"Crypto"}
        ListElement{name:"Jane";team:"QA"}
        ListElement{name:"Victor";team:"QA"}
        ListElement{name:"Wendy";team:"Graphics"}
    }

    ListView{
        anchors.left: list.right
        height: parent.height
//        width: 200
        model: nameModel
        delegate: Text{text: name}
        section.property: "team"
//        section.criteria: ViewSection.FirstCharacter
        section.delegate: sectionHeading
//        section.labelPositioning: ViewSection.CurrentLabelAtStart
    }
    Component{
        id:sectionHeading
        Rectangle{
            width: 300;height: childrenRect.height
            color: "lightsteelblue"
            Text{
                text: section;
                font.bold: true
                font.pixelSize: 20
            }
        }
    }
}
