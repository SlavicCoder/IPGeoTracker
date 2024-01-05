import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

ApplicationWindow {
    property var jsonData: {
        "ip": "185.54.101.72",
        "type": "ipv4",
        "continent_code": "EU",
        "continent_name": "Europe",
        "country_code": "PL",
        "country_name": "Poland",
        "region_code": "MZ",
        "region_name": "Mazovia",
        "city": "Warsaw",
        "zip": "00-025",
        "latitude": 52.2317008972168,
        "longitude": 21.018339157104492,
        "location": {
            "geoname_id": 756135,
            "capital": "Warsaw",
            "languages": [{"code": "pl", "name": "Polish", "native": "Polski"}],
            "country_flag": "https://assets.ipstack.com/flags/pl.svg",
            "country_flag_emoji": "\ud83c\uddf5\ud83c\uddf1",
            "country_flag_emoji_unicode": "U+1F1F5 U+1F1F1",
            "calling_code": "48",
            "is_eu": true
        }
    };

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
        } else {
            hideError()
        }
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
                        validateInput()
                        // Handle the "Add" action
                        errorText.visible = false // Hide the error message if input is not empty
                        // Here, you can display the sample JSON data in a TextArea or Text element
                        outputArea.text = JSON.stringify(jsonData, null, 2) // JSON.stringify with formatting
                    }
                }

                Button {
                    text: "Delete"
                    Layout.fillWidth: true
                    onClicked: {
                        validateInput()
                        showSuccess("Delete action successful!")
                    }
                }

                Button {
                    text: "Retrieve"
                    Layout.fillWidth: true
                    onClicked: {
                        validateInput()
                        showFailure("Retrieval action failed!")
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
