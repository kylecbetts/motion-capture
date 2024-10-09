import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import MotionCapture

ApplicationWindow {
    id: application
    title: qsTr("Motion Capture")

    visible: true
    width: 1280
    height: 720

    XsensSystem {
        id: xsensSystem
    }

    header: TabBar {
        id: tabBar
        width: application.width
        Material.elevation: 4

        TabButton {
            id: sensorsTab

            text: "Sensors"
            icon.source: "qrc:/resources/icons/sensor.svg"
            display: AbstractButton.TextUnderIcon
        }

        TabButton {
            id: calibrationTab

            text: "Calibration"
            icon.source: "qrc:/resources/icons/compass.svg"
            display: AbstractButton.TextUnderIcon

            enabled: xsensSystem.sensors.allConnected
        }

        TabButton {
            id: analyzeTab

            text: "Analyze"
            icon.source: "qrc:/resources/icons/query.svg"
            display: AbstractButton.TextUnderIcon

            enabled: false
        }
    }

    SwipeView {
        id: swipeView

        currentIndex: tabBar.currentIndex
        anchors.fill: parent

        SensorsPage {
            sensors: xsensSystem.sensors
        }

        Page {
            id: calibrationPage

            Text {
                text: "Calibration"
            }
        }

        Page {
            id: analyzePage
            Text {
                text: "Analyze"
            }
        }
    }

    footer: Rectangle {
        id: footer

        width: application.width
        height: 48

        Rectangle {
            height: 2
            color: "lightgray"

            anchors.top: footer.top
            anchors.left: footer.left
            anchors.right: footer.right
        }

        Text {
            text: xsensSystem.licenseName + " License  |  SDK v" + xsensSystem.sdkVersion
            color: "gray"
            font.weight: 300

            anchors.centerIn: footer
        }
    }
}
