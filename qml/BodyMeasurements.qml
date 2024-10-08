import QtQuick
import QtQuick.Controls

Column {
    required property var measurements
    spacing: 8

    function toLabel(id) {
        let result = '';
        result += id[0].toUpperCase();
        for (let i = 1; i < id.length; i++) {
            if (id[i] === id[i].toUpperCase()) {
                result += ' ';
            }
            result += id[i];
        }
        return result
    }

    Repeater {
        model: measurements

        delegate: Row {
            spacing: 12

            TextField {
                width: 60
                height: 24
                horizontalAlignment: Text.AlignHCenter
                font.weight: 700
            }

            Label {
                text: toLabel(modelData.id)
                anchors.verticalCenter: parent.verticalCenter
                font.weight: 500
                font.pixelSize: 14
            }
        }
    }
}
