#ifndef ZXML_GLOBAL_H
#define ZXML_GLOBAL_H
#include <QtCore/qglobal.h>


#if defined(ZXML_LIBRARY)
#  define ZXML_EXPORT Q_DECL_EXPORT
#else
#  define ZXML_EXPORT Q_DECL_IMPORT
#endif

#endif // ZXML_GLOBAL_H
