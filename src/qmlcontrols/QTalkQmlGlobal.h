#pragma once

#include <QObject>
#include <QtQmlIntegration/QtQmlIntegration>

class QTKCorePlugin;
class QTKPalette;
class ChatManager;

Q_MOC_INCLUDE("QTKPalette.h")
Q_MOC_INCLUDE("ChatManager.h")

class QTalkQmlGlobal : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(QTalk)
    QML_SINGLETON

    Q_PROPERTY(QString appName READ appName CONSTANT)
    Q_PROPERTY(QString appVersion READ appVersion CONSTANT)

    Q_PROPERTY(qreal zOrderTopMost READ zOrderTopMost CONSTANT)
    Q_PROPERTY(qreal zOrderWidgets READ zOrderWidgets CONSTANT)
    Q_PROPERTY(qreal zOrderHighlights READ zOrderHighlights CONSTANT)

    Q_PROPERTY(QTKCorePlugin* corePlugin READ corePlugin CONSTANT)
    Q_PROPERTY(QTKPalette* palette READ palette CONSTANT)
    Q_PROPERTY(ChatManager* chatManager READ chatManager CONSTANT)
public:
    explicit QTalkQmlGlobal(QObject* parent = nullptr);
    ~QTalkQmlGlobal();

    static QString appName();
    static QString appVersion();

    qreal zOrderTopMost() const { return 1000; }
    qreal zOrderWidgets() const { return 100; }
    qreal zOrderHighlights() const { return 3; }

    QTKCorePlugin* corePlugin() const { return m_corePlugin; }
    QTKPalette* palette() const { return m_palette; }
    ChatManager* chatManager() const { return m_chatManager; }

private:
    QTKCorePlugin* m_corePlugin;
    QTKPalette* m_palette;
    ChatManager* m_chatManager;
};
