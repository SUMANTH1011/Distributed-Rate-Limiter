#ifndef FILEWATCHER_H
#define FILEWATCHER_H

#include <string>
#include <filesystem>

class FileWatcher
{
private:
    std::string filePath;

    std::filesystem::file_time_type lastModified;

public:
    explicit FileWatcher(
        const std::string& path
    );

    bool hasChanged();
};

#endif