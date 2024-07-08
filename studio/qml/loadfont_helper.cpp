#include <QDir>
#include <QFont>
#include <QFile>
#include <QDebug>
#include <QFontDatabase>
#include "loadfont_helper.h"

bool LoadFontHelper::loadFontFiles(QString path)
{
    bool result = false;
    QString dir_name = "";

    if(path == "")
    {
#if defined (Q_OS_QNX)
        dir_name = "/data/qt/resources/fonts";
#else
        dir_name = "resources/fonts";
#endif
    }
    else
    {
        dir_name = path;
    }


    QDir dir(dir_name);
    if (dir.exists()){
        dir.setFilter(QDir::Files);
        QStringList fontFiles = dir.entryList();
        for(const QString &fontFile : qAsConst(fontFiles)) {
            loadFontFromFile(dir.absoluteFilePath(fontFile));
        }
    }
    return result;
}

bool LoadFontHelper::loadFontFromFile(const QString &fontFile)
{
    QStringList _fonts;
    QFile file(fontFile);
    if(!file.open(QIODevice::ReadOnly)){
        qDebug()<<"Open font file error";
        return false;
    } else {
        int loadedFontID = QFontDatabase::addApplicationFontFromData(file.readAll());
        _fonts = QFontDatabase::applicationFontFamilies(loadedFontID);
        file.close();
    }
    return true;
}
