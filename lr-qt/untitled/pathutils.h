#include <QString>

#ifndef PATHUTILS_H
#define PATHUTILS_H

#define APP_TMP_DIR "mintaka"

class PathUtils
{
public:
    PathUtils();
    static QString getAppTmpDir();
};

#endif // PATHUTILS_H
