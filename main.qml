// Main.qml
import QtQuick
import QtQuick.Controls
import QtQuick.Layouts

ApplicationWindow {
    width: 800
    height: 560
    visible: true
    title: "Qt + llama.cpp"

    ColumnLayout {
        anchors.fill: parent
        spacing: 8
        anchors.margins: 12

        RowLayout {
            spacing: 8
            Layout.fillWidth: true

            TextField {
                id: modelPath
                placeholderText: "model.gguf yolu"
                Layout.fillWidth: true
            }

            SpinBox { id: nctx; from: 256; to: 32768; value: 2048; stepSize: 256 }
            SpinBox { id: ngl;  from: 0;   to: 99;     value: 0 }

            Button {
                text: "Yükle"
                onClicked: llamaChat.load(modelPath.text, nctx.value, ngl.value)
            }

            Label {
                text: llamaChat && llamaChat.ready ? "✅ Hazır" : "⏳ Bekleniyor"
                // opsiyonel: renk
                // color: llamaChat.ready ? "green" : "orange"
            }
        }

        ScrollView {
            Layout.fillWidth: true
            Layout.fillHeight: true

            TextArea {
                id: chat
                readOnly: true
                wrapMode: TextArea.Wrap
                textFormat: TextEdit.PlainText
            }
        }

        RowLayout {
            spacing: 8
            Layout.fillWidth: true

            TextField {
                id: input
                placeholderText: "Mesaj yaz..."
                Layout.fillWidth: true
                focus: true
                onAccepted: sendBtn.clicked() // Enter ile gönder
            }

            Button {
                id: sendBtn
                text: "Gönder"
                // enabled: llamaChat && llamaChat.ready
                onClicked: {
                    if (input.text.length === 0) return;
                    chat.append("🧑: " + input.text + "\n")
                    llamaChat.send(input.text)
                    input.text = ""
                }
            }

            Button {
                text: "Durdur"
                onClicked: llamaChat.stop()
            }
        }
    }

    // Sinyal köprüleri
    Connections {
        target: llamaChat
        function onTokenArrived(piece) { chat.append(piece) }
        function onResponseDone() { chat.append("\n\n") }
        function onInfo(msg) { chat.append("ℹ️ " + msg + "\n") }
        function onReadyChanged(ready) { chat.append(ready ? "✅ Model hazır\n" : "⏳ Yükleniyor...\n") }
    }
}
