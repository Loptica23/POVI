#pragma once

#include <QtCore/qglobal.h>
#include <memory>

#if defined(DBCONNECTION_LIBRARY)
#  define DBCONNECTIONSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DBCONNECTIONSHARED_EXPORT Q_DECL_IMPORT
#endif
