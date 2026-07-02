#include "FileWatcher.h"

FileWatcher::FileWatcher(
    const std::string& path)
    : filePath(path)
{
    lastModified =
        std::filesystem::last_write_time(filePath);
}

bool FileWatcher::hasChanged()
{
    auto current =
        std::filesystem::last_write_time(filePath);

    if(current != lastModified)
    {
        lastModified = current;
        return true;
    }

    return false;
}