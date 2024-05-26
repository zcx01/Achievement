#ifndef LOADFONT_HELPER_H
#define LOADFONT_HELPER_H

#include <QString>

class LoadFontHelper
{
public:
    static bool loadFontFiles(QString path="");
    static bool loadFontFromFile(const QString &fontFile);

};

#endif // LOADFONT_HELPER_H
