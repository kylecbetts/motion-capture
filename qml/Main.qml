import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 1280
    height: 720
    visible: true

    title: qsTr("Motion Capture")
    color: colors.slate300

    FontLoader {
        id: exo2
        source: "qrc:/resources/fonts/Exo2.ttf"
    }

    QtObject {
        id: colors

        property color slate50: "#f8fafc"
        property color slate100: "#f1f5f9"
        property color slate200: "#e2e8f0"
        property color slate300: "#cbd5e1"
        property color slate400: "#94a3b8"
        property color slate500: "#64748b"
        property color slate600: "#475569"
        property color slate700: "#334155"
        property color slate800: "#1e293b"
        property color slate900: "#0f172a"
        property color slate950: "#020617"
    }

    ColumnLayout {
        width: parent.width
        Text {
            text: "Xsens System"

            font.family: exo2.name
            font.weight: 300
            font.pixelSize: 24
            color: colors.slate600

            Layout.alignment: Qt.AlignHCenter
        }
    }
}
