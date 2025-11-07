#include "QTKApplication.h"
#include "CommandLineParser.h"
#include "AppMessages.h"
#include "UnitTestList.h"

int main(int argc, char** argv)
{
    CommandLineParser::Result args;
    {
        const QCoreApplication pre(argc,argv);
        QCoreApplication::setApplicationName(QStringLiteral(QTK_APP_NAME));
        QCoreApplication::setApplicationVersion(QStringLiteral(QTK_APP_VERSION_STR));
        args = CommandLineParser::parseCommandLine();
        if(args.statusCode == CommandLineParser::Result::Status::Error) {
            const QString& errorMessage = args.errorString.value_or(QStringLiteral("Unknown error occured"));
            qCritical() << errorMessage;
            return EXIT_FAILURE;
        }
    }

    AppMessages::installHandler();

    QTKApplication app(argc, argv);

    app.init();

    int exitCode = 0;
    if(args.runningUnitTests) {
#ifdef QTK_UNITTEST_BUILD
        exitCode = QTKUnitTest::runTests(args.unitTests);
#endif
    } else{
        exitCode = app.exec();
    }

    qInfo() << "App closed exit code: " << exitCode;

    return exitCode;
}
