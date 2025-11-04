#pragma once

#include <QObject>
#include <QColor>
#include <QMap>
#include <QtQmlIntegration/QtQmlIntegration>

#define DECLARE_QTK_COLOR(name, lightDisabled, lightEnabled, darkDisabled, darkEnabled) \
{ \
        PaletteColorInfo_t colorInfo = { \
            { QColor(lightDisabled), QColor(lightEnabled) }, \
            { QColor(darkDisabled), QColor(darkEnabled) } \
        }; \
        _colorInfoMap[Light][ColorGroupEnabled][QStringLiteral(#name)] = colorInfo[Light][ColorGroupEnabled]; \
        _colorInfoMap[Light][ColorGroupDisabled][QStringLiteral(#name)] = colorInfo[Light][ColorGroupDisabled]; \
        _colorInfoMap[Dark][ColorGroupEnabled][QStringLiteral(#name)] = colorInfo[Dark][ColorGroupEnabled]; \
        _colorInfoMap[Dark][ColorGroupDisabled][QStringLiteral(#name)] = colorInfo[Dark][ColorGroupDisabled]; \
        _colors << #name; \
}

#define DECLARE_QTK_NONTHEMED_COLOR(name, disabledColor, enabledColor) \
{ \
        PaletteColorInfo_t colorInfo = { \
            { QColor(disabledColor), QColor(enabledColor) }, \
            { QColor(disabledColor), QColor(enabledColor) } \
        }; \
        _colorInfoMap[Light][ColorGroupEnabled][QStringLiteral(#name)] = colorInfo[Light][ColorGroupEnabled]; \
        _colorInfoMap[Light][ColorGroupDisabled][QStringLiteral(#name)] = colorInfo[Light][ColorGroupDisabled]; \
        _colorInfoMap[Dark][ColorGroupEnabled][QStringLiteral(#name)] = colorInfo[Dark][ColorGroupEnabled]; \
        _colorInfoMap[Dark][ColorGroupDisabled][QStringLiteral(#name)] = colorInfo[Dark][ColorGroupDisabled]; \
        _colors << #name; \
}

#define DECLARE_QTK_SINGLE_COLOR(name, color) \
{ \
        PaletteColorInfo_t colorInfo = { \
            { QColor(color), QColor(color) }, \
            { QColor(color), QColor(color) } \
        }; \
        _colorInfoMap[Light][ColorGroupEnabled][QStringLiteral(#name)] = colorInfo[Light][ColorGroupEnabled]; \
        _colorInfoMap[Light][ColorGroupDisabled][QStringLiteral(#name)] = colorInfo[Light][ColorGroupDisabled]; \
        _colorInfoMap[Dark][ColorGroupEnabled][QStringLiteral(#name)] = colorInfo[Dark][ColorGroupEnabled]; \
        _colorInfoMap[Dark][ColorGroupDisabled][QStringLiteral(#name)] = colorInfo[Dark][ColorGroupDisabled]; \
        _colors << #name; \
}

#define DEFINE_QTK_COLOR(NAME, SETNAME) \
Q_PROPERTY(QColor NAME READ NAME WRITE SETNAME NOTIFY paletteChanged) \
    Q_PROPERTY(QStringList NAME ## Colors READ NAME ## Colors NOTIFY paletteChanged) \
    QColor NAME() const { return _colorInfoMap[_theme][_colorGroupEnabled  ? ColorGroupEnabled : ColorGroupDisabled][QStringLiteral(#NAME)]; } \
    QStringList NAME ## Colors() const { \
        QStringList c; \
        c << _colorInfoMap[Light][ColorGroupEnabled][QStringLiteral(#NAME)].name(QColor::HexRgb); \
        c << _colorInfoMap[Light][ColorGroupDisabled][QStringLiteral(#NAME)].name(QColor::HexRgb); \
        c << _colorInfoMap[Dark][ColorGroupEnabled][QStringLiteral(#NAME)].name(QColor::HexRgb); \
        c << _colorInfoMap[Dark][ColorGroupDisabled][QStringLiteral(#NAME)].name(QColor::HexRgb); \
        return c; \
} \
    void SETNAME(const QColor& color) { _colorInfoMap[_theme][_colorGroupEnabled  ? ColorGroupEnabled : ColorGroupDisabled][QStringLiteral(#NAME)] = color; signalPaletteChangeToAll(); }


class QTKPalette : public QObject
{
    Q_OBJECT
    QML_ELEMENT

    Q_PROPERTY(Theme        globalTheme        READ globalTheme        WRITE setGlobalTheme        NOTIFY paletteChanged)
    Q_PROPERTY(bool         colorGroupEnabled  READ colorGroupEnabled  WRITE setColorGroupEnabled  NOTIFY paletteChanged)
    Q_PROPERTY(QStringList  colors             READ colors             CONSTANT)
public:
    enum ColorGroup {
        ColorGroupDisabled = 0,
        ColorGroupEnabled,
        cMaxColorGroup
    };

    enum Theme {
        Light = 0,
        Dark,
        cMaxTheme
    };
    Q_ENUM(Theme)

    typedef QColor PaletteColorInfo_t[cMaxTheme][cMaxColorGroup];

    QTKPalette(QObject* parent = nullptr);
    ~QTKPalette();

    QStringList colors() const {return _colors;}
    bool colorGroupEnabled() const {return _colorGroupEnabled;}
    static Theme globalTheme() {return QTKPalette::_theme;}

    void setColorGroupEnabled(bool enabled);
    static void setGlobalTheme(Theme newTheme);

    DEFINE_QTK_COLOR(AppBackground, setAppBackground)
    DEFINE_QTK_COLOR(Text, setText)
    DEFINE_QTK_COLOR(TextSolarized,setTextSolarized)
    DEFINE_QTK_COLOR(ControlsBackground,setControlsBackground)

signals:
    void paletteChanged();

private:
    static void buildMap();
    static void signalPaletteChangeToAll();
    void signalPaletteChanged();

    static Theme        _theme;
    bool                _colorGroupEnabled;
    static QStringList  _colors;

    static QMap<int, QMap<int, QMap<QString, QColor>>> _colorInfoMap;   // theme -> colorGroup -> color name -> color
    static QList<QTKPalette*> _paletteObjects;    ///< List of all active QGCPalette objects
};
