#pragma once

#include <QObject>
#include <QLoggingCategory>
#include <QStringList>

#define QTK_LOGGING_CATEGORY(name, ...) \
static QTKLoggingCategory qtkCategory ## name (__VA_ARGS__); \
    Q_LOGGING_CATEGORY(name, __VA_ARGS__)

class QTKLoggingCategoryRegister : public QObject
{
    Q_OBJECT
    Q_DISABLE_COPY_MOVE(QTKLoggingCategoryRegister)
public:
    static QTKLoggingCategoryRegister* instance();

    void registerCategory(const char* category) { _registeredCategories << category; }

    Q_INVOKABLE QStringList registeredCategories();

    Q_INVOKABLE void setCategoryLoggingOn(const QString& category, bool enable);

    Q_INVOKABLE bool categoryLoggingOn(const QString& category);

    void setFilterRulesFromSettings(const QString& commandLineLoggingOptions);

private:
    QTKLoggingCategoryRegister() = default;

    QStringList _registeredCategories;
    QString     _commandLineLoggingOptions;

    static const char* _filterRulesSettingsGroup;
};

class QTKLoggingCategory
{
public:
    QTKLoggingCategory(const char* category) {QTKLoggingCategoryRegister::instance()->registerCategory(category);}
};
