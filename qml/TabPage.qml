import QtQuick
import QtQuick.Controls

Page {
    required property Item content

    Pane {
        anchors.centerIn: parent
        contentItem: content
    }
}
