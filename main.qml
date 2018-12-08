import QtQuick 2.9
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    ListView {
        id: view

        property int itemHeight: height / 20

        anchors.fill: parent
        model: stopsModel

        header: Item {
            z: 1
            height: view.itemHeight
            width: parent.width

            Rectangle {
                anchors.fill: parent
                color: "gold"
            }

            Row {
                anchors.fill: parent

                Text {
                    height: parent.height
                    width: parent.width * 0.75
                    text: "Stop name"
                    font.bold: true
                }

                Text {
                    height: parent.height
                    width: parent.width * 0.25
                    text: "Distance"
                    font.bold: true
                }
            }
        }

        headerPositioning: ListView.PullBackHeader

        delegate: Item {
            height: view.itemHeight
            width: parent.width

            Row {
                anchors.fill: parent

                Text {
                    height: parent.height
                    width: parent.width * 0.75
                    text: model.name
                }

                Text {
                    height: parent.height
                    width: parent.width * 0.25
                    text: model.distance + " m"
                }
            }
        }
    }
}
