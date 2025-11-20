#include "CommandLineParser.h"

#include <QCoreApplication>

static const QString kOptUnitTest = QStringLiteral("unittest");
static const QString kOptSimpleBootTest = QStringLiteral("simple-boot-test");

namespace CommandLineParser
{

static QStringList normalizeArgs(const QStringList &args)
{
    QStringList out;
    out.reserve(args.size() + 4);
    for (const QString &arg : args) {
        if (arg == QStringLiteral("--unittest")) {
            out << arg << QString();
            continue;
        }

        if (arg.startsWith("--") && arg.contains(':')) {
            const int idx = arg.indexOf(':');
            const QString opt = arg.left(idx);
            const QString val = arg.mid(idx + 1);
            out << opt;
            if (!val.isEmpty()) {
                out << val;
            } else if (opt == QStringLiteral("--unittest")) {
                out << QString();
            }
        } else {
            out << arg;
        }
    }
    return out;
}

Result parseCommandLine()
{
    Result out{};
    out.parser = std::make_unique<QCommandLineParser>();

    QCommandLineParser& parser = *out.parser;
    parser.setSingleDashWordOptionMode(QCommandLineParser::ParseAsLongOptions);
    parser.setOptionsAfterPositionalArgumentsMode(QCommandLineParser::ParseAsOptions);
    parser.setApplicationDescription(QStringLiteral(QTK_APP_NAME));

    const QCommandLineOption helpOption = parser.addHelpOption();
    const QCommandLineOption versionOption = parser.addVersionOption();

#ifdef QTK_UNITTEST_BUILD
    const QCommandLineOption unittestOpt(
        kOptUnitTest,
        QCoreApplication::translate("main", "Run unit tests (optional filter value)."),
        QCoreApplication::translate("main", "test"));
    (void)parser.addOption(unittestOpt);
#endif

    const QCommandLineOption simpleBooTestOpt(
            kOptSimpleBootTest,
            QCoreApplication::translate("main","Run a simple startup test and exit (used for CI)."),
            QCoreApplication::translate("main",""));
    (void)parser.addOption(simpleBooTestOpt);

    const QStringList normalizedArgs = normalizeArgs(QCoreApplication::arguments());
    parser.process(normalizedArgs);

    out.unknownOptions = parser.unknownOptionNames();

#if !defined(QTK_UNITTEST_BUILD)
    if (out.unknownOptions.contains(kOptUnitTest)) {
        out.statusCode = Result::Status::Error;
        out.errorString = QCoreApplication::translate("main", "--%1 option are only available in unittest builds.").arg(kOptUnitTest);
        return out;
    }
#endif

#ifdef QTK_UNITTEST_BUILD
    if(parser.isSet(unittestOpt)) {
        out.runningUnitTests = true;
        const QStringList vals = parser.values(unittestOpt);
        if(vals.isEmpty()) {
            out.unitTests.clear();
        } else {
            out.unitTests = vals;
        }
    }
#endif

    out.simpleBootTest = parser.isSet(simpleBooTestOpt);

    out.statusCode = Result::Status::Ok;

    return out;
}

}
