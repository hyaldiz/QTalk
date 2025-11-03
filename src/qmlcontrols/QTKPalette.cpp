#include "QTKPalette.h"

#include <QDebug>

QTKPalette::Theme QTKPalette::_theme = QTKPalette::Dark;
QStringList QTKPalette::_colors;
QMap<int, QMap<int, QMap<QString, QColor>>> QTKPalette::_colorInfoMap;
QList<QTKPalette*> QTKPalette::_paletteObjects;

QTKPalette::QTKPalette(QObject* parent) : QObject(parent)
    ,_colorGroupEnabled(true)
{
    if(_colorInfoMap.isEmpty()){
        buildMap();
    }

    _paletteObjects += this;
}

QTKPalette::~QTKPalette()
{
    bool fsuccess = _paletteObjects.removeOne(this);
    if(!fsuccess){
        qWarning() << "Internal error!";
    }
}

void QTKPalette::buildMap()
{
    DECLARE_QTK_COLOR(Text,"#FFFFFF","#FFFFFF","#FFFFFF","#FFFFFF")
}

void QTKPalette::setColorGroupEnabled(bool enabled)
{
    _colorGroupEnabled = enabled;
    signalPaletteChanged();
}

void QTKPalette::setGlobalTheme(Theme newTheme)
{
    if(QTKPalette::_theme != newTheme){
        _theme = newTheme;
        signalPaletteChangeToAll();
    }
}

void QTKPalette::signalPaletteChangeToAll()
{
    foreach (QTKPalette* palette, _paletteObjects) {
        palette->signalPaletteChanged();
    }
}

void QTKPalette::signalPaletteChanged()
{
    emit paletteChanged();
}
