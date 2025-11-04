import QtQuick
import QtQuick.Controls
import QtQuick.Dialogs

Item {
    id: homePage

    anchors.fill: parent

    Button {
        anchors.centerIn: parent

        text: qsTr("Select LLM model")

        onClicked: fileDialog.open()
    }

    FileDialog {
        id: fileDialog
        title: "Bir dosya seçin"
        // Dosya filtreleri: sadece txt ve json göster
        nameFilters: ["Text files (*.txt)", "JSON files (*.json)", "All files (*)"]

        onAccepted: {
            console.log("Seçilen dosya:", fileDialog.file)
            // Burada dosya path'i ile işlemi başlatabilirsin
        }

        onRejected: {
            console.log("Dosya seçimi iptal edildi")
        }
    }
}
