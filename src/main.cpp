#include "QTKApplication.h"
#include "AppMessages.h"

int main(int argc, char** argv)
{
    AppMessages::installHandler();

    QTKApplication app(argc,argv);

    app.init();

    int exitCode = app.exec();

    qInfo() << "App closed exit code: " << exitCode;

    return exitCode;
}

// #include <QGuiApplication>
// #include <QQmlApplicationEngine>
// #include <QQmlContext>

// #include "llama/ChatEngine.h"

// #define MODEL_PATH "/home/umbrella/Desktop/models/mistral-7b-instruct-v0.2.Q4_K_M.gguf"

// int main(int argc, char *argv[])
// {
//     QGuiApplication app(argc, argv);

//     QQmlApplicationEngine engine;

//     engine.addImportPath(QStringLiteral("qrc:/qml"));

//     const QUrl url(QStringLiteral("qrc:/qml/QTalk/MainRootWindow.qml"));
//     QObject::connect(
//         &engine,
//         &QQmlApplicationEngine::objectCreated,
//         &app,
//         [url](QObject *obj, const QUrl &objUrl) {
//             if (!obj && url == objUrl)
//                 QCoreApplication::exit(-1);
//         },
//         Qt::QueuedConnection);


//     ChatEngine chatEngine;
//     engine.rootContext()->setContextProperty("llamaChat", &chatEngine);

//     engine.load(url);

//     //chatEngine.load(MODEL_PATH,2048,0);

//     return app.exec();
// }
