import QtQuick 2.9
import QtQuick.Window 2.2
import QtPositioning 5.12

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
                    property int distance: positionSource.position.coordinate.distanceTo(model.coordinate)

                    height: parent.height
                    width: parent.width * 0.25
                    text: positionSource.sourceError === PositionSource.NoError ? distance + " m" : "?"
                }
            }
        }
    }

    PositionSource {
        id: positionSource

        active: true
        updateInterval: 1000

        onPositionChanged: {
            var coord = positionSource.position.coordinate;
            console.log("coordinate:", coord.longitude, coord.latitude, valid)
        }

        onSourceErrorChanged: {
            if (sourceError == PositionSource.NoError)
                return

            console.log("sourceError", sourceError, valid)
        }
    }
}
