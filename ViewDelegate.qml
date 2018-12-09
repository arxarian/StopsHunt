import QtQuick 2.9
import QtQuick.Window 2.2

Item {
    id: delegate

    property real standardHeight: 0
    property real expandedHeight: 0
    property bool gainable: !model.taken && model.distance < 20

    height: gainable ? expandedHeight : standardHeight

    Behavior on height { NumberAnimation { duration: 250 } }

    Loader {
        anchors.fill: parent
        active: model.taken
        sourceComponent: Rectangle {
            color: "lightgreen"
        }
    }

    Row {
        id: row
        anchors.fill: parent

        Text {
            height: parent.height
            width: parent.width * 0.65
            text: model.name
        }

        Text {
            height: parent.height
            width: parent.width * 0.20
            text: model.distance + " m"
        }

        Loader {
            active: gainable
            height: parent.height
            width: parent.width * 0.15
            sourceComponent: MouseArea {
                anchors.fill: parent
                anchors.margins: 5
                opacity: 0

                onClicked: animator.start()

                Component.onCompleted: opacity = 1

                OpacityAnimator {
                    id: animator
                    duration: 500
                    target: image
                    from: 1
                    to: 0

                    onStopped: {
                        if (image.opacity === 0) {
                            model.taken = true
                        }
                    }
                }

                Image {
                    id: image

                    property real size: Math.min(parent.height, parent.width)

                    anchors.horizontalCenter: parent.horizontalCenter
                    height: size
                    width: size
                    source: "qrc:/tram_collect.png"
                    fillMode: Image.PreserveAspectFit
                }
            }
        }

    }
}
