import QtQuick
import Qt5Compat.GraphicalEffects

Image {
    id: icon

    property string color: ""
    property string path: ""

    fillMode: Image.PreserveAspectFit
    source: path

    layer{
        enabled: color != ""
        effect: ColorOverlay {
            color: icon.color
        }
    }
}
