import QtQuick 2.9
import QtQuick.Controls 2.13
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480

    ListView {
        id: view

        property int itemHeight: height / 20

        anchors.fill: parent
        model: stopsModel

        header: ViewHeader {
            height: view.itemHeight * 2
            width: parent.width
        }

        headerPositioning: ListView.PullBackHeader

        delegate: ViewDelegate {
            height: view.itemHeight
            width: view.width

            onGainableChanged: {
                if (!gainable) {
                    collectDialog.close()
                }
            }

            onCollect: {
                collectDialog.name = stopItem.name
                collectDialog.open()
            }

            Connections {
                enabled: collectDialog.name === stopItem.name
                target: collectDialog
                onAccepted: taken = true
            }
        }
    }

    Dialog {
        id: collectDialog

        property string name

        anchors.centerIn: parent
        title: "Collect " + name
        standardButtons: Dialog.Ok | Dialog.Cancel
    }
}
