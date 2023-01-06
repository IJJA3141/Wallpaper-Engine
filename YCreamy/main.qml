import QtQuick 6.4
import QtQuick.Window 2.2
import QtQuick.Controls 2.14
import Method 1.0

Window {
    visible: true
    width: 2560
    height: 1440
    title: qsTr("Hello World")
    visibility: "FullScreen"

    Method {
        id: method
        Component.onCompleted: {
            method.Test()
    }}

    Image {
        id: backgroud
        source: "resources/background.png"
        anchors.fill: parent
        fillMode: Image.Tile
        sourceSize.width: 1024
        sourceSize.height: 1024
        onStatusChanged: console.log(image.status)
    }
}
