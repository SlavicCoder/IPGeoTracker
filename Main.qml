import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

ApplicationWindow {
    id: root
    visible: true
    title: "Geolocation Data App"

    height: 800
    width: 600

    Material.theme: Material.Dark
    Material.accent: Material.Purple

    Component.onCompleted: {
        root.showMaximized()
    }

    Connections {
        target: geoDataManager
        function onActionFinished(response) {
            busyOverlay.visible = false
            outputArea.text = JSON.stringify(response, null, 2)
        }

        function onAdded(success) {
            if (success) {
                showSuccess("Geolocation data added to database")
            } else {
                showFailure("Failed to add geolocation data to database. See Output for details.")
            }
        }

        function onDeleted(success) {
            if (success) {
                showSuccess("Geolocation data deleted from database")
            } else {
                showFailure("Failed to delete geolocation data from database. See Output for details.")
            }
        }

        function onPreviewed(response) {
            if (response.ip === undefined) {
                showFailure("Failed to retrieve geolocation data from database. See Output for details.")
            } else {
                showSuccess("Geolocation data retrieved from database")

                geoDataPopup.setDataSource(response)
                geoDataPopup.open()
            }
        }
    }

    function showSuccess(message) {
        resultText.text = message
        resultText.color = "green"
        resultAnimation.restart()
    }

    function showFailure(message) {
        resultText.text = message
        resultText.color = "red"
        resultAnimation.restart()
    }

    function showError(message) {
        errorText.text = message
        errorAnimation.restart()
    }

    function hideError() {
        errorAnimation.stop()
    }

    function validateInput() {
        if (inputField.text.trim() === "") {
            showError("IP address/URL cannot be empty!")
            return false
        } else {
            hideError()
            return true
        }
    }

    BusyIndicatorOverlay {
        id: busyOverlay
        anchors.fill: parent
        z: 9999
    }

    PreviewPopup {
        id: geoDataPopup
    }

    RowLayout {
        anchors.fill: parent
        anchors.margins: 20
        spacing: 20

        ColumnLayout {
            Layout.fillWidth: true
            Layout.preferredWidth: Math.round(parent.width * 0.5)
            spacing: 10

            Label {
                text: "Output:"
                font.pixelSize: 18
                Layout.alignment: Qt.AlignLeft | Qt.AlignVCenter
            }

            TextArea {
                id: outputArea
                wrapMode: Text.Wrap
                Layout.fillWidth: true
                Layout.fillHeight: true
                readOnly: true
                visible: true
            }
        }

        ColumnLayout {
            Layout.fillWidth: true
            Layout.preferredWidth: Math.round(parent.width * 0.5)
            spacing: 10

            Text {
                id: errorText
                color: "red"
                Layout.fillWidth: true
                visible: false

                SequentialAnimation {
                    id: errorAnimation
                    loops: 1
                    PauseAnimation {
                        duration: 5000
                    }
                    PropertyAnimation {
                        target: errorText
                        property: "opacity"
                        from: 1.0
                        to: 0.0
                        duration: 250
                    }
                    onStarted: {
                        errorText.visible = true
                        errorText.opacity = 1.0
                    }

                    onStopped: {
                        errorText.visible = false
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true

                TextField {
                    id: inputField
                    placeholderText: "Enter IP address or URL"
                    Layout.fillWidth: true
                }

                Button {
                    text: "Clear"
                    onClicked: {
                        inputField.text = ""
                    }
                }
            }

            RowLayout {
                Layout.fillWidth: true
                spacing: 10

                Button {
                    text: "Add/Update"
                    Layout.fillWidth: true
                    onClicked: {
                        if (!validateInput()) {
                            return
                        }
                        busyOverlay.visible = true
                        errorText.visible = false
                        geoDataManager.addEntry(inputField.text)
                    }
                }

                Button {
                    text: "Delete"
                    Layout.fillWidth: true
                    onClicked: {
                        if (!validateInput()) {
                            return
                        }
                        busyOverlay.visible = true
                        errorText.visible = false
                        geoDataManager.deleteEntry(inputField.text)
                    }
                }

                Button {
                    text: "Retrieve"
                    Layout.fillWidth: true
                    onClicked: {
                        if (!validateInput()) {
                            return
                        }
                        busyOverlay.visible = true
                        errorText.visible = false
                        geoDataManager.previewEntry(inputField.text)
                    }
                }
            }

            Text {
                id: resultText
                font.pixelSize: 18
                Layout.fillWidth: true
                visible: false

                SequentialAnimation {
                    id: resultAnimation
                    loops: 1
                    PauseAnimation {
                        duration: 10000
                    }
                    PropertyAnimation {
                        target: resultText
                        property: "opacity"
                        from: 1.0
                        to: 0.0
                        duration: 250
                    }
                    onStarted: {
                        resultText.visible = true
                        resultText.opacity = 1.0
                    }

                    onStopped: {
                        resultText.visible = false
                    }
                }
            }
        }
    }
}
