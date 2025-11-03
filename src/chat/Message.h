#pragma once

#include <QObject>

class Message : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString contents READ contents NOTIFY contentsChanged CONSTANT)
    Q_PROPERTY(QString time READ time CONSTANT)
    Q_PROPERTY(int ID READ ID CONSTANT)
public:
    explicit Message(const QString& contents, int ID, QObject* parent = nullptr);

    void appendToContents(const QString& piece);

    void setFailed(bool failed);

    const QString& contents() const;
    const QString& time() const;
    bool failed() const;
    int ID() const;

signals:
    void contentsChanged();
    void failedChanged();

private:
    QString m_contents;
    QString m_time;
    bool m_failed;
    int m_ID;
};

Q_DECLARE_METATYPE(Message*)
