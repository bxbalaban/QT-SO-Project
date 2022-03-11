#include <assert.h>
#include <dirent.h>
#include <QDebug>
#include <QDirIterator>
#include <QPluginLoader>
#include <iostream>
#include <vector>

#include "../dlib/test-plugin.h"

// constexpr auto ABSOLUTE_PATH_TO_PLUGIN = "/home/pc/Desktop/qt cmake
// dlib/build/dlib2/libdlib2.so";
int readEx();
QStringList soFiles;
QString path="/home/pc/Desktop/qt cmake dlib/Libs";

int main(int argc, char *argv[]) {
    readEx();

    for (int i = 0; i < soFiles.size(); i++) {
        //assert(QLibrary::isLibrary(path));
        if (QLibrary::isLibrary(soFiles.at(i))) {
            QPluginLoader loader(soFiles.at(i));
            if (auto instance = loader.instance()) {
                if (auto plugin = qobject_cast<TestPluginInterface *>(instance)) {
                    plugin->doSomething("sss");

                } else {
                    qDebug() << "qobject_cast<> returned nullptr";
                }
            } else {
                qDebug() << loader.errorString();
            }
        }
    }
}

int readEx() {
    QDirIterator iterator(path, QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        QFile file(iterator.next());
        if (file.open(QIODevice::ReadOnly)) soFiles.append(file.fileName());
                    //std::cout << file.fileName().toStdString() << "|" ;
    }
}