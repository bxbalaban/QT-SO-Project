#include <assert.h>
#include <gtest/gtest.h>
#include <qdiriterator.h>
#include <QPluginLoader>
#include <QtGlobal>

#include "../dlib/test-plugin.h"
QString path="/home/pc/Desktop/qt cmake dlib/Libs";
QStringList soFiles, controlStr;

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg);

TEST(pluginTest, readLib) {

    QDirIterator iterator(path, QDirIterator::Subdirectories);
    while (iterator.hasNext()) {
        QFile file(iterator.next());
        if (file.open(QIODevice::ReadOnly)) soFiles.append(file.fileName());
    }
    EXPECT_FALSE(soFiles.isEmpty()) << "there is no *.so files in build directory";
}

TEST(pluginTest, useLib) {
    for (int i = 0; i < soFiles.size(); i++) {
        QPluginLoader loader(soFiles.at(i));
        if (auto instance = loader.instance()) {
            if (auto plugin = qobject_cast<TestPluginInterface *>(instance)) {
                qInstallMessageHandler(myMessageOutput);  // Install the handler
                plugin->doSomething("var str");
            } else {
                qInfo() << "qobject_cast<> returned nullptr";
            }
        } else {
            qInfo() << loader.errorString();
        }
    }
    EXPECT_TRUE(controlStr.at(0).compare("hot dog3! \"var str\" "));
    EXPECT_TRUE(controlStr.at(1).compare("hot dog! \"var str\" "));
    EXPECT_TRUE(controlStr.at(2).compare("hot dog2! \"var str\" "));
}

void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg) {
    QByteArray localMsg = msg.toLocal8Bit();
    controlStr.append(localMsg.constData());
    fprintf(stderr, "%s", localMsg.constData());
}