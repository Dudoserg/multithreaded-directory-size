#include "FolderHelper.h"

bool FolderHelper::isPath(fs::path path)
{
	return fs::is_directory(path);
}

unsigned long long FolderHelper::getDirectorySizeBytes(fs::path basePath) {
	return _getDirectorySizeBytes(basePath);
	return 30;
}

unsigned long long FolderHelper::_getDirectorySizeBytes(fs::path basePath)
{
	unsigned long long allSize = 0L;
	for (const auto& entry : fs::directory_iterator(basePath)) {
		if (entry.is_directory()) {
			allSize += _getDirectorySizeBytes(entry.path());
		}
		else {
			allSize += (long)entry.file_size();
		}
	}
	return allSize;
}
