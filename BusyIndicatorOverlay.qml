import QtQuick 2.15
import QtQuick.Controls 2.15

Item {
    id: root
    visible: false

    Rectangle {
        anchors.fill: parent
        color: "#ffffff"
        opacity: 0.3

        MouseArea {
            anchors.fill: parent
            preventStealing: true
        }

        BusyIndicator {
            anchors.centerIn: parent
            width: Math.round(0.2 * parent.height)
            height: this.width
            running: root.visible
        }
    }
}
