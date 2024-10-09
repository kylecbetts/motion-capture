import QtQuick
import QtQuick.Controls

Page {
    id: sensorsPage
    required property var sensors

    Pane {
        anchors.centerIn: parent

        Column {
            spacing: 8

            Rectangle {
                id: statusCard

                width: 196
                height: 64
                color: sensors.allConnected ? "lightGreen" : "lightpink"

                anchors.horizontalCenter: parent.horizontalCenter

                Text {
                    text: "Sensors " + (sensors.allConnected ? "Ready" : "Not Ready")
                    color: sensors.allConnected ? "darkGreen" : "darkred"
                    font.pixelSize: 16
                    font.weight: 600

                    anchors.centerIn: parent
                }
            }

            Image {
                id: yBotImage
                source: "qrc:/resources/images/yBot.png"

                SensorCoordinates {
                    id: sensorCoordinates
                }

                Repeater {
                    model: sensorCoordinates

                    delegate: Rectangle {
                        readonly property var sensor: sensors.requiredSensors[bodyPartIndex]
                        readonly property int size: 14

                        width: size
                        height: size
                        radius: 2

                        color: sensor ? "lightgreen" : "lightpink"
                        border.color: sensor ? "darkgreen" : "darkred"
                        border.width: 2

                        visible: bodyPartIndex in sensors.requiredSensors
                        anchors.top: parent.top
                        anchors.left: parent.left
                        anchors.leftMargin: (yBotImage.width * leftOffsetPct) - (size / 2)
                        anchors.topMargin: (yBotImage.height * topOffsetPct) - (size / 2)

                        MouseArea {
                            anchors.fill: parent

                            onClicked: {
                                sensorStatusCard.bodyPartName = bodyPartName
                                sensorStatusCard.bodyPartIndex = bodyPartIndex
                            }
                        }
                    }
                }

                Pane {
                    id: sensorHubStatusCard

                    width: 240
                    height: 240
                    Material.elevation: 8

                    anchors.right: yBotImage.left
                    anchors.rightMargin: -128
                    anchors.verticalCenter: yBotImage.verticalCenter

                    Column {
                        topPadding: 16
                        leftPadding: 8
                        spacing: 8

                        Row {
                            spacing: 8
                            Image {
                                source: "qrc:/resources/icons/router.svg"
                            }
                            Text {
                                text: "Sensor Hub"
                                font.pixelSize: 14
                                font.weight: 500
                                anchors.verticalCenter: parent.verticalCenter
                                color: sensors.sensorHub ? "darkgreen" : "darkred"
                            }
                        }

                        Column {
                            spacing: 4

                            Text {
                                text: sensors.sensorHub ? sensors.sensorHub.deviceName : "Not Connected"
                                font.weight: 300
                            }
                            Text {
                                text: sensors.sensorHub ? sensors.sensorHub.deviceId : ""
                                font.weight: 300
                            }
                            Text {
                                text: sensors.sensorHub ? "Channel " + sensors.wirelessChannel : ""
                                font.weight: 300
                            }
                        }
                    }
                }

                Pane {
                    id: sensorStatusCard
                    property string bodyPartName: sensorCoordinates.get(0).bodyPartName
                    property int bodyPartIndex: sensorCoordinates.get(0).bodyPartIndex
                    property var sensor: sensors.requiredSensors[bodyPartIndex]

                    width: 240
                    height: 240
                    Material.elevation: 8

                    anchors.left: yBotImage.right
                    anchors.leftMargin: -128
                    anchors.verticalCenter: yBotImage.verticalCenter

                    Column {
                        topPadding: 16
                        leftPadding: 8
                        spacing: 8

                        Row {
                            spacing: 8
                            Image {
                                source: getSignalStrengthImage(sensorStatusCard.sensor)

                                function getSignalStrengthImage(sensor) {
                                    if (!sensor) {
                                        return "qrc:/resources/icons/signal0.svg"
                                    }
                                    let strength = sensor.signalStrength
                                    if (strength < 25) {
                                        return "qrc:/resources/icons/signal1.svg"
                                    }
                                    if (strength < 50) {
                                        return "qrc:/resources/icons/signal2.svg"
                                    }
                                    if (strength < 75) {
                                        return "qrc:/resources/icons/signal3.svg"
                                    }
                                    return "qrc:/resources/icons/signal4.svg"
                                }
                            }
                            Text {
                                text: sensorStatusCard.bodyPartName + " Sensor"
                                font.pixelSize: 14
                                font.weight: 500
                                anchors.verticalCenter: parent.verticalCenter
                                color: sensorStatusCard.sensor ? "darkgreen" : "darkred"
                            }
                        }

                        Column {
                            spacing: 4

                            Text {
                                text: sensorStatusCard.sensor ? sensorStatusCard.sensor.deviceName : "Not Connected"
                                font.weight: 300
                            }
                            Text {
                                text: sensorStatusCard.sensor ? sensorStatusCard.sensor.serialNumber : ""
                                font.weight: 300
                            }
                            Text {
                                text: sensorStatusCard.sensor ? "Signal Strength: " + sensorStatusCard.sensor.signalStrength : ""
                                font.weight: 300
                            }
                        }
                    }
                }
            }

            Button {
                text: "Power Off Devices"
                icon.source: "qrc:/resources/icons/power.svg"
                display: AbstractButton.TextBesideIcon
                enabled: sensors.allConnected

                anchors.horizontalCenter: parent.horizontalCenter

                onClicked: {
                    sensors.requestPowerOffDevices()
                }
            }

        }
    }
}
