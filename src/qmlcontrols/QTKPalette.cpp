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
    DECLARE_QTK_COLOR(AppBackground, "#FFFFFF","#FFFFFF","#303030","#303030")
    DECLARE_QTK_COLOR(Text,"#FFFFFF","#FFFFFF","#FFFFFF","#FFFFFF")
    DECLARE_QTK_COLOR(TextSolarized,"#d0d0d0","#d0d0d0","#d0d0d0","#d0d0d0")
    DECLARE_QTK_COLOR(ControlsBackground,"#404040","#404040","#404040","#404040")
    DECLARE_QTK_COLOR(BubleMainUser,"#FFA657","#FFA657","#FFA657","#FFA657")
    DECLARE_QTK_COLOR(BubleQTalk,"#57a6ff","#57a6ff","#57a6ff","#57a6ff")
    DECLARE_QTK_COLOR(BubleFailed,"#FF0000","#FF0000","#FF0000","#FF0000")
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
