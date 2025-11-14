#pragma once

#include <QCommandLineParser>

namespace CommandLineParser {

struct Result
{
    enum class Status
    {
        Ok,
        Error,
        VersionRequested,
        HelpRequested
    };

    std::unique_ptr<QCommandLineParser> parser;

    QStringList unknownOptions;
    std::optional<QString> errorString;

    Status statusCode = Status::Ok;
    bool runningUnitTests = false;
    QStringList unitTests;
    bool simpleBootTest = false;
};

Result parseCommandLine();

}
