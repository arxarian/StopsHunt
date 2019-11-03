import QtQuick 2.9
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
            standardHeight: view.itemHeight
            expandedHeight: view.itemHeight * 2
            width: view.width
        }
    }
}
