#include "QTKApplication.h"
#include "AppMessages.h"

int main(int argc, char** argv)
{
    QTKApplication app(argc,argv);

    app.init();

    AppMessages::installHandler();

    int exitCode = app.exec();

    qInfo() << "App closed exit code: " << exitCode;

    return exitCode;
}
