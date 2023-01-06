import QtQuick 6.4
import QtQuick.Window 2.2

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    visibility: "FullScreen"

    Item {
        function fibonacci(n){
            var arr = [0, 1];
            for (var i = 2; i < n + 1; i++)
                arr.push(arr[i - 2] + arr[i -1]);

            return arr;
        }

        Component.onCompleted: console.log(fibonacci(5))
    }

    Image {
        id: backgroud
        source: "resources/background.png"
        anchors.fill: parent
        fillMode: Image.Tile
        sourceSize.width: 1024
        sourceSize.height: 1024
        onStatusChanged: console.log(image.status)
        
        Image {
            id: cherry
            width: 1280
            height: 851
            source: "resources/cherry.png"
            fillMode: Image.PreserveAspectFit
        }

        Rectangle {
            color: "#80FAF1D5"
            radius: 25
            border.width: 10
            border.color: "#397066"
            width: 500
            height: 500
            x: 100
            y: 100
        }
    }
}
