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
        id: xsens
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
        }

        TabButton {
            id: analyzeTab
            text: "Analyze"
            icon.source: "qrc:/resources/icons/query.svg"
            display: AbstractButton.TextUnderIcon
        }
    }

    SwipeView {
        id: swipeView
        currentIndex: tabBar.currentIndex
        anchors.fill: parent

        SensorsPage {
            xsensSensors: xsens.sensors()
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

    footer: Pane {
        id: footer
        contentWidth: application.width
            Text {
                readonly property var license: xsens.license()
                text: "Xsens Version " + xsens.version + " (" + license.type + " License)"
                anchors.horizontalCenter: parent.horizontalCenter
            }
    }
}
