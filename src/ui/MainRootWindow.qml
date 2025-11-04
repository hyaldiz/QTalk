import QTalk
import QTalk.Controls
import QTalk.UI

ApplicationWindow {
    id: mainWindow

    visible: true
    width: 800
    height: 480
    flags: Qt.FramelessWindowHint
    color: QTalk.palette.AppBackground

    property int resizeMargin: 8

    header: Rectangle {
        id: headerBar
        width: parent.width
        height: 24
        color: QTalk.palette.QTalkBrand

        Text {
            anchors.centerIn: parent
            text: QTalk.appName
            color: QTalk.palette.Text
            font.pixelSize: 15
        }

        MouseArea {
            anchors.fill: parent
            z: 1
            onPressed: (mouse) => {
                if (mouse.button === Qt.LeftButton) {
                    mainWindow.startSystemMove()
                }
            }
        }

        // --- z: 2 (Yeniden Boyutlandırma Alanları) ---
        // Üst Kenar
        MouseArea {
            anchors.top: parent.top
            anchors.left: parent.left
            anchors.right: parent.right
            height: resizeMargin
            // Köşelere ve butonlara girmemek için margin
            anchors.leftMargin: resizeMargin * 2
            anchors.rightMargin: 122 // (40*3 + 2) Butonların genişliği
            z: 2 // Taşıma alanının ÜSTÜNDE
            cursorShape: Qt.SizeVerCursor
            onPressed: (mouse) => {
                if (mouse.button === Qt.LeftButton) {
                    mainWindow.startSystemResize(Qt.TopEdge)
                }
            }
        }

        // Sol-Üst Köşe
        MouseArea {
            anchors.left: parent.left
            anchors.top: parent.top
            width: resizeMargin * 2
            height: resizeMargin * 2
            z: 2 // Taşıma alanının ÜSTÜNDE
            cursorShape: Qt.SizeFDiagCursor // ( \ )
            onPressed: (mouse) => {
                if (mouse.button === Qt.LeftButton) {
                    mainWindow.startSystemResize(Qt.TopEdge | Qt.LeftEdge)
                }
            }
        }

        // Sağ-Üst Köşe
        MouseArea {
            // Butonların hemen solundan başla
            anchors.right: windowControls.left
            anchors.top: parent.top
            width: resizeMargin * 2
            height: resizeMargin * 2
            z: 2 // Taşıma alanının ÜSTÜNDE
            cursorShape: Qt.SizeBDiagCursor//Qt.SizeFDiagCursor // ( / )
            onPressed: (mouse) => {
                if (mouse.button === Qt.LeftButton) {
                    mainWindow.startSystemResize(Qt.TopEdge | Qt.RightEdge)
                }
            }
        }

        // --- z: 3 (Butonlar) ---
        // Pencere Kontrol Butonları (En üstte)
        Row {
            id: windowControls
            anchors.right: parent.right
            anchors.top: parent.top
            anchors.bottom: parent.bottom
            spacing: 1
            z: 3 // Her şeyin üzerinde (resize ve move)

            QTKIconButton {
                id: minimizeBtn
                width: 40; height: parent.height
                radius: 0
                bgColor: QTalk.palette.QTalkBrand

                onClicked: {
                    mainWindow.showMinimized()
                }
            }

            QTKIconButton {
                id: maximizeBtn
                width: 40; height: parent.height
                radius: 0
                bgColor: QTalk.palette.QTalkBrand

                onClicked: {
                    if (mainWindow.visibility === Window.Maximized) {
                        mainWindow.showNormal();
                    } else {
                        mainWindow.showMaximized();
                    }
                }
            }

            QTKIconButton {
                id: closeBtn
                width: 40; height: parent.height
                radius: 0
                bgColor: QTalk.palette.QTalkBrand

                onClicked: {
                    mainWindow.close()
                }
            }

            // // Minimize Butonu
            // Rectangle {
            //     id: minimizeBtn
            //     width: 40; height: parent.height
            //     color: QTalk.palette.QTalkBrand
            //     Text { anchors.centerIn: parent; text: "—"; color: "white"; font.pixelSize: 16 }
            //     MouseArea {
            //         anchors.fill: parent; hoverEnabled: true
            //         onEntered: minimizeBtn.color = QTalk.palette.AppBackground
            //         onExited: minimizeBtn.color = QTalk.palette.QTalkBrand
            //         onClicked: mainWindow.showMinimized()
            //     }
            // }

            // Maximize / Restore Butonu
            // Rectangle {
            //     id: maximizeBtn
            //     width: 40; height: parent.height
            //     color: QTalk.palette.QTalkBrand
            //     Text {
            //         anchors.centerIn: parent
            //         text: mainWindow.visibility === Window.Maximized ? "❐" : "☐"
            //         color: "white"; font.pixelSize: 14
            //     }
            //     MouseArea {
            //         anchors.fill: parent; hoverEnabled: true
            //         onEntered: maximizeBtn.color = QTalk.palette.AppBackground
            //         onExited: maximizeBtn.color = QTalk.palette.QTalkBrand
            //         onClicked: {
            //             if (mainWindow.visibility === Window.Maximized) {
            //                 mainWindow.showNormal();
            //             } else {
            //                 mainWindow.showMaximized();
            //             }
            //         }
            //     }
            // }

            // Kapatma Butonu
            // Rectangle {
            //     id: closeBtn
            //     width: 40; height: parent.height
            //     color: QTalk.palette.QTalkBrand
            //     Text { anchors.centerIn: parent; text: "✕"; color: "white"; font.pixelSize: 16 }
            //     MouseArea {
            //         anchors.fill: parent; hoverEnabled: true
            //         onEntered: closeBtn.color = "#E81123"
            //         onExited: closeBtn.color = QTalk.palette.QTalkBrand
            //         onClicked: mainWindow.close()
            //     }
            // }
        }
    } // Header sonu

    // LOADER
    Loader {
        id: mainLoader

        anchors.fill: parent

        source: "qrc:/qml/QTalk/UI/SplashScreen.qml"
    }

    // --- PENCERENİN GERİ KALANI İÇİN YENİDEN BOYUTLANDIRMA ---
    // (Artık header'ın altından başlıyorlar)
    // Sol Kenar
    MouseArea {
        anchors.left: parent.left
        anchors.top: headerBar.bottom // Header'ın altından başla
        anchors.bottom: parent.bottom
        width: resizeMargin
        cursorShape: Qt.SizeHorCursor
        onPressed: (mouse) => {
            if (mouse.button === Qt.LeftButton) {
                mainWindow.startSystemResize(Qt.LeftEdge)
            }
        }
    }

    // Sağ Kenar
    MouseArea {
        anchors.right: parent.right
        anchors.top: headerBar.bottom // Header'ın altından başla
        anchors.bottom: parent.bottom
        width: resizeMargin
        cursorShape: Qt.SizeHorCursor
        onPressed: (mouse) => {
            if (mouse.button === Qt.LeftButton) {
                mainWindow.startSystemResize(Qt.RightEdge)
            }
        }
    }

    // Alt Kenar
    MouseArea {
        anchors.left: parent.left
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        height: resizeMargin
        cursorShape: Qt.SizeVerCursor
        onPressed: (mouse) => {
            if (mouse.button === Qt.LeftButton) {
                mainWindow.startSystemResize(Qt.BottomEdge)
            }
        }
    }

    // Sol-Alt Köşe
    MouseArea {
        anchors.left: parent.left
        anchors.bottom: parent.bottom
        width: resizeMargin * 2
        height: resizeMargin * 2
        cursorShape: Qt.SizeBDiagCursor
        onPressed: (mouse) => {
            if (mouse.button === Qt.LeftButton) {
                mainWindow.startSystemResize(Qt.BottomEdge | Qt.LeftEdge)
            }
        }
    }

    // Sağ-Alt Köşe
    MouseArea {
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        width: resizeMargin * 2
        height: resizeMargin * 2
        cursorShape: Qt.SizeFDiagCursor
        onPressed: (mouse) => {
            if (mouse.button === Qt.LeftButton) {
                mainWindow.startSystemResize(Qt.BottomEdge | Qt.RightEdge)
            }
        }
    }
}



// import QTalk
// import QTalk.Controls
// import QTalk.UI


// ApplicationWindow {
//     id: mainWindow

//     visible: true
//     width: 800
//     height: 480
//     flags: Qt.FramelessWindowHint
//     color: QTalk.palette.AppBackground

//     header: Rectangle {
//             id: headerBar // Header'a bir id verelim
//             width: parent.width
//             height: 24 // Yüksekliği 30-32 civarı yapmak butonlar için daha iyi olabilir
//             color: "#333333"

//             // Sürükleme mantığı (Tüm alanı kaplamaya devam ediyor)
//             MouseArea {
//                 anchors.fill: parent // Tüm header alanını kapla

//                 onPressed: (mouse) => {
//                     if (mouse.button === Qt.LeftButton) {
//                         mainWindow.startSystemMove()
//                     }
//                 }
//             }

//             // (İsteğe bağlı) Başlık çubuğunda bir yazı
//             Text {
//                 anchors.centerIn: parent
//                 text: "QTalk"
//                 color: "white"
//                 font.pixelSize: 12
//                 // Not: Yazı, butonların altına denk gelirse görünmez
//                 // Bunu engellemek için yazıyı da z: 1 yapabilir veya
//                 // sürükleme MouseArea'sının sağını butonlara göre sınırlayabiliriz.
//                 // Şimdilik böyle bırakmak en basiti.
//             }

//             // --- YENİ EKLENEN BÖLÜM: Pencere Kontrol Butonları ---
//             Row {
//                 id: windowControls
//                 anchors.right: parent.right // Sağa yasla
//                 anchors.top: parent.top
//                 anchors.bottom: parent.bottom
//                 spacing: 1 // Butonlar arası boşluk

//                 // z: 1 -> Bu 'Row'un, anchors.fill olan sürükleme MouseArea'sının
//                 // üzerinde çizilmesini sağlar, böylece butonlar tıklanabilir olur.
//                 z: 1

//                 // Arka Plana Atma Butonu
//                 Rectangle {
//                     id: minimizeBtn
//                     width: 40
//                     height: parent.height
//                     color: "#333333"

//                     Text {
//                         anchors.centerIn: parent
//                         text: "—" // Minimize simgesi
//                         color: "white"
//                         font.pixelSize: 16
//                     }

//                     MouseArea {
//                         anchors.fill: parent
//                         hoverEnabled: true
//                         onEntered: minimizeBtn.color = "#555555" // Hover rengi
//                         onExited: minimizeBtn.color = "#333333"
//                         onClicked: mainWindow.showMinimized() // Arka plana at
//                     }
//                 }

//                 // Tam Ekran / Geri Yükleme Butonu
//                 Rectangle {
//                     id: maximizeBtn
//                     width: 40
//                     height: parent.height
//                     color: "#333333"

//                     Text {
//                         id: maximizeIcon
//                         anchors.centerIn: parent
//                         // Pencere durumuna göre simgeyi değiştir
//                         text: mainWindow.visibility === Window.Maximized ? "❐" : "☐"
//                         color: "white"
//                         font.pixelSize: 14
//                     }

//                     MouseArea {
//                         anchors.fill: parent
//                         hoverEnabled: true
//                         onEntered: maximizeBtn.color = "#555555"
//                         onExited: maximizeBtn.color = "#333333"
//                         onClicked: {
//                             // Durumu kontrol et ve tersini yap
//                             if (mainWindow.visibility === Window.Maximized) {
//                                 mainWindow.showNormal();
//                             } else {
//                                 mainWindow.showMaximized();
//                             }
//                         }
//                     }
//                 }

//                 // Kapatma Butonu
//                 Rectangle {
//                     id: closeBtn
//                     width: 40
//                     height: parent.height
//                     color: "#333333"

//                     Text {
//                         anchors.centerIn: parent
//                         text: "✕" // Kapatma simgesi
//                         color: "white"
//                         font.pixelSize: 16
//                     }

//                     MouseArea {
//                         anchors.fill: parent
//                         hoverEnabled: true
//                         // Windows tarzı hover'da kırmızı yapma
//                         onEntered: closeBtn.color = "#E81123"
//                         onExited: closeBtn.color = "#333333"
//                         onClicked: mainWindow.close() // Uygulamayı kapat
//                     }
//                 }
//             }
//             // --- YENİ BÖLÜM SONU ---
//         }

//     Loader {
//         id: mainLoader

//         anchors.fill: parent

//         source: "qrc:/qml/QTalk/UI/SplashScreen.qml"
//     }
// }
