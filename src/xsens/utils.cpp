#include "utils.h"

QString Utils::toQString(const XsString &xsString)
{
    std::string stdString = xsString.toStdString();
    QString qString = QString::fromStdString(stdString);
    return qString;
}
