#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include "xstypes/xsstring.h"

class Utils
{
public:
    static QString toQString(const XsString &xsString);
};

#endif // UTILS_H
