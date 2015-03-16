import QtQuick 2.0
import Sailfish.Silica 1.0
import Test 1.0

ApplicationWindow {
    cover: null

    onWindowChanged: webView.chromeWindow = window


    initialPage: Page {
        id: chrome

        property bool popupActive

        Component.onCompleted: console.log("-------------- ", webView.contentItem, "-- " , webView.contentItem.verticalScrollDecorator)

        Rectangle {
            id: verticalScrollDecorator

            width: 5
            height: webView.contentItem ? webView.contentItem.verticalScrollDecorator.size : 0
            y: webView.contentItem ? webView.contentItem.verticalScrollDecorator.position : 0
            x: parent.width - width

            color: "black"
            smooth: true
            radius: 2.5
            visible: opacity > 0.0
            opacity: webView.contentItem && webView.contentItem.verticalScrollDecorator.moving ? 1.0 : 0.0
            Behavior on opacity { NumberAnimation { properties: "opacity"; duration: 400 } }
        }

        Rectangle {
            id: horizontalScrollDecorator

            width: webView.contentItem ? webView.contentItem.horizontalScrollDecorator.size : 0
            height: 5
            x: webView.contentItem ? webView.contentItem.horizontalScrollDecorator.position : 0
            y: parent.height - height - 100
            color: "black"
            smooth: true
            radius: 2.5
            visible: opacity > 0.0
            opacity: webView.contentItem && webView.contentItem.horizontalScrollDecorator.moving ? 1.0 : 0.0
            Behavior on opacity { NumberAnimation { properties: "opacity"; duration: 400 } }
        }

        Rectangle {
            anchors.bottom: parent.bottom
            width: parent.width
            height: 100
            color: Theme.highlightDimmerColor
            opacity: 0.7

            Label {
                anchors.centerIn: parent
                text: "Toolbar"
            }

            MouseArea {
                anchors.fill: parent
                onClicked: console.log("Terve terve")
            }
        }

        WebView {
            id: webView

            width: 1536
            height: 2048
//            active: true
//            clip: true
        }

    }
}



//Item {


//        id: browserPage
//        width: 1536
//        height: 2048

//        Rectangle {
//            color: "blue"
//            width: 100
//            height: 100
//        }

//    }

