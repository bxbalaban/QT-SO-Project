#include <QDebug>
#include "test-plugin.h"

void TestPlugin::doSomething(std::string str) const
{
    
    QString qstr = QString::fromStdString(str);
    qDebug()<< "hot dog2!"<< qstr;
}

