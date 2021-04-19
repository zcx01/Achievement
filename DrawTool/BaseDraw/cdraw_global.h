#ifndef CDRAW_GLOBAL_H
#define CDRAW_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(CDRAW_LIBRARY)
#  define CDRAW_EXPORT Q_DECL_EXPORT
#else
#  define CDRAW_EXPORT Q_DECL_IMPORT
#endif

#endif // CDRAW_GLOBAL_H
