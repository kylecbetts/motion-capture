#include "utils.h"

QString Utils::toQString(const XsString &xsString)
{
    std::string stdString = xsString.toStdString();
    QString qString = QString::fromStdString(stdString);
    return qString;
}

XsString Utils::toXsString(const QString &qString)
{
    std::string stdString = qString.toStdString();
    XsString xsString = XsString(stdString);
    return xsString;
}
