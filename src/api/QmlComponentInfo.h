#pragma once

#include <QObject>
#include <QUrl>

class QmlComponentInfo : public QObject
{
    Q_OBJECT
public:
    QmlComponentInfo(const QString& title, 
                      const QUrl& url, 
                      const QUrl& icon, 
                      QObject* parent = nullptr)
    
        : QObject(parent)
        , m_title(title)
        , m_url(url)
        , m_icon(icon)
    {
    
    }

    ~QmlComponentInfo() = default;

    const QString& title() const { return m_title; }
    const QUrl& url() const { return m_url; }
    const QUrl& icon() const { return m_icon; } 

private:
    const QString m_title;
    const QUrl m_url;
    const QUrl m_icon;
};
