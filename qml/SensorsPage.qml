import QtQuick
import QtQuick.Controls

TabPage {
    id: setupPage
    required property var xsensSensors

    content: Column {
        spacing: 24

        Image {
            id: yBotImage
            source: "qrc:/resources/images/ybotReduced.png"

            SensorsModel {
                id: sensorsModel
            }

            Repeater {
                model: sensorsModel

                delegate: Rectangle {
                    readonly property int size: 16
                    height: size
                    width: size
                    radius: 2
                    anchors.top: parent.top
                    anchors.left: parent.left
                    anchors.leftMargin: (yBotImage.width * leftOffsetPct) - (size / 2)
                    anchors.topMargin: (yBotImage.height * topOffsetPct) - (size / 2)
                    color: "red"
                    border.width: 2
                    border.color: "darkred"
                }
            }
        }
        Rectangle {
            anchors.horizontalCenter: parent.horizontalCenter

            height: 72
            width: 320
            border.width: 1
            border.color: "black"
            radius: 5

            Row {
                readonly property int horizontalPadding: 24
                anchors.fill: parent
                spacing: 24
                leftPadding: horizontalPadding
                rightPadding: horizontalPadding

                Image {
                    source: "qrc:/resources/icons/router.svg"
                    anchors.verticalCenter: parent.verticalCenter

                    Rectangle {
                        readonly property var sensorHub: xsensSensors.sensorHub
                        readonly property int size: 16
                        height: size
                        width: size
                        radius: 2
                        anchors.top: parent.top
                        anchors.left: parent.left
                        color: sensorHub ? "green" : "red"
                        border.width: 2
                        border.color: sensorHub ? "darkgreen" : "darkred"
                    }
                }

                Column {
                    spacing: 4
                    anchors.verticalCenter: parent.verticalCenter

                    Text {
                        readonly property var sensorHub: xsensSensors.sensorHub
                        text: sensorHub ? sensorHub.deviceName : "No sensor hub connected"
                        font.pixelSize: 16
                        font.weight: 500
                    }

                    Text {
                        readonly property var sensorHub: xsensSensors.sensorHub
                        text: sensorHub ? "Channel " + xsensSensors.wirelessChannel + "  |  " + sensorHub.serialNumber : ""
                        font.weight: 300
                    }
                }
            }
        }
    }
}
