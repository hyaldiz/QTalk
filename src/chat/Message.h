#pragma once

#include <QObject>

class Message : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString contents READ contents CONSTANT)
    Q_PROPERTY(QString time READ time CONSTANT)
    Q_PROPERTY(int ID READ ID CONSTANT)
public:
    explicit Message(const QString& contents, int ID, QObject* parent = nullptr);

    const QString& contents() const;
    const QString& time() const;
    int ID() const;

private:
    QString m_contents;
    QString m_time;
    int m_ID;
};

Q_DECLARE_METATYPE(Message*)
