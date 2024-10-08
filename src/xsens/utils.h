#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include "xstypes/xsstring.h"

class Utils
{
public:
    static QString toQString(const XsString &xsString);
    static XsString toXsString(const QString &qString);
};

#endif // UTILS_H
