import QtQuick 2.9
import QtQuick.Controls 2.4

Item {
    Rectangle {
        anchors.fill: parent
        color: "gold"
    }

    Column {
        anchors.fill: parent
        ProgressBar {
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height / 2

            value: originalModel.progress
        }

        Row {
            anchors.left: parent.left
            anchors.right: parent.right
            height: parent.height / 2

            Text {
                height: parent.height
                width: parent.width * 0.65
                text: "Stop name"
                font.bold: true
            }

            Text {
                height: parent.height
                width: parent.width * 0.35
                text: "Distance"
                font.bold: true
            }
        }
    }

}
