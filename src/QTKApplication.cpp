#include "QTKApplication.h"
#include "QTKApplication_p.h"

QTKApplication::QTKApplication(int argc, char** argv)
    : QApplication(argc,argv)
    , d(new QTKApplicationPrivate)
{

}

QTKApplication::~QTKApplication()
{

}

void QTKApplication::init()
{
    
}

void QTKApplication::initCommon()
{

}

QObject* QTKApplication::rootQmlObject()
{
    return nullptr;
}
