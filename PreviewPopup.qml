import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

Popup {
    id: root
    modal: true
    anchors.centerIn: parent
    visible: false

    Material.theme: Material.Dark
    Material.accent: Material.Purple

    property var geoData: ({})

    function setDataSource(dataSource) {
        geoData = dataSource
    }

    ColumnLayout {
        anchors.centerIn: parent
        spacing: 10

        Label {
            text: "<b>IP:</b> " + geoData.ip
            font.pixelSize: 18
        }
        Label {
            text: "<b>Latitude:</b> " + geoData.latitude
            font.pixelSize: 18
        }
        Label {
            text: "<b>Longitude:</b> " + geoData.longitude
            font.pixelSize: 18
        }
        Label {
            text: "<b>City:</b> " + geoData.city
            font.pixelSize: 18
        }
        Label {
            text: "<b>Zip:</b> " + geoData.zip
            font.pixelSize: 18
        }
        Label {
            text: "<b>Region Name:</b> " + geoData.region_name
            font.pixelSize: 18
        }
        Label {
            text: "<b>Country Name:</b> " + geoData.country_name
            font.pixelSize: 18
        }
        Label {
            text: "<b>Continent:</b> " + geoData.continent_name
            font.pixelSize: 18
        }

        Button {
            text: "Close"
            Layout.alignment: Qt.AlignHCenter
            onClicked: {
                root.close();
            }
        }
    }
}
