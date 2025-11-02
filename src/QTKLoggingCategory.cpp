#include "QTKLoggingCategory.h"
#include <QSettings>

QTKLoggingCategoryRegister* _instance = nullptr;
const char* QTKLoggingCategoryRegister::_filterRulesSettingsGroup = "LoggingFilters";

QTKLoggingCategoryRegister* QTKLoggingCategoryRegister::instance()
{
    if(!_instance){
        _instance = new QTKLoggingCategoryRegister;
        Q_CHECK_PTR(_instance);
    }

    return _instance;
}

QStringList QTKLoggingCategoryRegister::registeredCategories()
{
    _registeredCategories.sort();
    return _registeredCategories;
}

void QTKLoggingCategoryRegister::setCategoryLoggingOn(const QString& category, bool enable)
{
    QSettings settings;

    settings.beginGroup(QTKLoggingCategoryRegister::_filterRulesSettingsGroup);
    settings.setValue(category,enable);
}

bool QTKLoggingCategoryRegister::categoryLoggingOn(const QString& category)
{
    QSettings settings;

    settings.beginGroup(QTKLoggingCategoryRegister::_filterRulesSettingsGroup);
    return settings.value(category,false).toBool();
}

void QTKLoggingCategoryRegister::setFilterRulesFromSettings(const QString& commandLineLoggingOptions)
{
    QString filterRules;
    QString filterRuleFormat{"%1.debug=true\n"};

    if(!commandLineLoggingOptions.isEmpty()){
        _commandLineLoggingOptions = commandLineLoggingOptions;
    }

    filterRules += "*Log.debug=false\n";

    foreach(QString category,_registeredCategories){
        if(categoryLoggingOn(category)){
            filterRules += filterRuleFormat.arg(category);
        }
    }

    if(!_commandLineLoggingOptions.isEmpty()){
        QStringList logList = _commandLineLoggingOptions.split(",");

        if(logList[0] == "full"){
            filterRules += "*Log.debug=true\n";
            for(int i=1; i<logList.count(); i++){
                filterRules += filterRuleFormat.arg(logList[i]);
            }
        }
        else{
            for(auto& category:logList){
                filterRules += filterRuleFormat.arg(category);
            }
        }
    }

    filterRules += "qt.qml.connections=false";

    qDebug() << "Filter rules" << filterRules;
    QLoggingCategory::setFilterRules(filterRules);
}
