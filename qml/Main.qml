import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import MotionCapture

ApplicationWindow {
    width: 1280
    height: 720
    visible: true

    title: qsTr("Motion Capture")

    header: TabBar {
        id: tabBar
        width: parent.width
        Material.elevation: 4

        TabButton {
            text: "Setup"
            display: AbstractButton.TextUnderIcon
            icon.source: "qrc:/resources/icons/settings.svg"
        }

        TabButton {
            text: "Analyze"
            display: AbstractButton.TextUnderIcon
            icon.source: "qrc:/resources/icons/query.svg"
        }
    }

    SwipeView {
        id: swipeView
        currentIndex: tabBar.currentIndex
        anchors.fill: parent

        XsensSystem {
            id: xsens
        }

        Page {
            id: setupPage
            Column {
                spacing: 32
                width: parent.width

                Column {
                    spacing: 4
                    anchors.horizontalCenter: parent.horizontalCenter
                    Text {
                        text: "Xsens System"
                        font.weight: 600
                        font.pixelSize: 24
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                    Text {
                        text: xsens.version + " | " + xsens.license.type + " License"
                        font.weight: 200
                        font.pixelSize: 14
                        anchors.horizontalCenter: parent.horizontalCenter
                    }
                }

                Row {
                    spacing: 32
                    anchors.horizontalCenter: parent.horizontalCenter

                    Image {
                        source: "qrc:/resources/icons/router.svg"

                        Rectangle {
                            property int size: 16
                            property int half: size / 2
                            radius: half
                            width: size
                            height: size
                            anchors.top: parent.top
                            anchors.left: parent.left
                            color: xsens.hardware.sensorHub.isConnected ? "green" : "red"
                        }
                    }

                    Column {
                        anchors.verticalCenter: parent.verticalCenter

                        Text {
                            text: xsens.hardware.sensorHub.isConnected ? xsens.hardware.sensorHub.modelName : "No Device Found"
                            font.pixelSize: 16
                            font.weight: 400
                        }
                        Text {
                            text: xsens.hardware.sensorHub.isConnected ? "Channel " + xsens.hardware.sensorHub.channel + " | " + xsens.hardware.sensorHub.modelId : "Required"
                            font.pixelSize: 12
                            font.weight: 200
                        }
                    }


                }
            }


        }

        Page {
            id: analyzePage
        }
    }
}
