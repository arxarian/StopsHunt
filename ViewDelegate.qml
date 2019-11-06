import QtQuick 2.9
import Datamodels 1.0

Item {
    id: delegate

    property StopItem stopItem: model.object

    property bool validDistance: stopItem.distance > -1
    property bool gainable: !stopItem.taken && stopItem.distance < 20 && validDistance

    signal collect(var name)

    Loader {
        anchors.fill: parent
        active: stopItem.taken
        sourceComponent: Rectangle {
            color: "#C6A700"
        }
    }

    Loader {
        anchors.fill: parent
        active: delegate.gainable
        sourceComponent: Rectangle {
            color: "#FFE764"

            MouseArea {
                anchors.fill: parent
                onClicked: delegate.collect(stopItem.name)
            }
        }
    }

    Row {
        id: row
        anchors.fill: parent

        Text {
            height: parent.height
            width: parent.width * 0.65
            text: stopItem.name
        }

        Text {
            height: parent.height
            width: parent.width * 0.20
            text: validDistance ? stopItem.distance + " m" : "?"
        }
    }
}
