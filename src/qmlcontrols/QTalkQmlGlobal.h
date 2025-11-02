#pragma once

#include <QObject>
#include <QtQmlIntegration/QtQmlIntegration>

class QTalkQmlGlobal : public QObject
{
    Q_OBJECT
    QML_NAMED_ELEMENT(QTalk)
    QML_SINGLETON
public:
    explicit QTalkQmlGlobal(QObject* parent = nullptr);
    ~QTalkQmlGlobal();
};
