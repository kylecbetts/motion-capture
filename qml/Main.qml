import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

import MotionCapture

ApplicationWindow {
    width: 1280
    height: 720
    visible: true

    title: qsTr("Motion Capture")

    FontLoader {
        id: exo2
        source: "qrc:/resources/fonts/Exo2.ttf"
    }

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

        XsensController {
            id: xsens
        }

        ColumnLayout {
            id: setupView

            ColumnLayout {
                Layout.alignment: Qt.AlignHCenter
                Text {
                    text: "Xsens System"
                    font.weight: 600
                    font.pixelSize: 24
                    Layout.alignment: Qt.AlignHCenter
                }
                Text {
                    text: xsens.version + " " + xsens.licenseName + " License"
                    font.weight: 100
                    font.pixelSize: 14
                    Layout.alignment: Qt.AlignHCenter
                }
            }
        }

        ColumnLayout {
            id: analyzeView
        }
    }
}
