#pragma once
#include <iostream>
#include <filesystem>
#include <string>
#include<stdarg.h>
#include <fstream>
#include <vector>
#include <chrono>
#include <locale>
#include <thread>
namespace fs = std::filesystem;
using namespace std;

class FolderHelper
{
public:
	

	fs::path BASE_PATH = "base";

	// создаем дерево директорий с вложенностью level
	void createFolder(fs::path basePath, int level) {

		createFiles(basePath, 5);

		if (level == 0)
			return;
		for (int i = 0; i < 5; i++) {

			fs::path newPath = basePath / std::to_string(i);

			fs::create_directories(newPath);
			createFolder(newPath, level - 1 );
		}
	}
	// создаем countFiles файлов по пути basePath
	void createFiles(fs::path basePath, int countFiles) {
		for (int i = 0; i < countFiles; i++) {

			std::filesystem::path path{ basePath }; //creates TestingFolder object on C:
			path /= std::to_string(i) + "_"; //put something into there
			std::filesystem::create_directories(path.parent_path()); //add directories based on the object path (without this line it will not work)

			std::ofstream ofs(path);
			ofs << "this is some text in the new file\n";
			ofs.close();
		}
	}

	bool isPath(fs::path path) {
		return fs::is_directory(path);
	}

	unsigned long long getDirectorySizeBytes(fs::path basePath) {
		// имитация работы, для проверки времени в Х-поточном режимах
		std::this_thread::sleep_for(std::chrono::milliseconds(5000));		
		//return _getDirectorySizeBytes(basePath);
		return 30;
	}

private:
	unsigned long long _getDirectorySizeBytes(fs::path basePath ) {
		unsigned long long allSize = 0L;
		//vector<string> files = {};
		//vector<string> dirs = {};
		for (const auto& entry : fs::directory_iterator(basePath)) {
			if (entry.is_directory()) {
				//std::cout << "[dir]" << entry.path() << std::endl;
				//dirs.push_back(entry.path().u8string());
				allSize += _getDirectorySizeBytes(entry.path());
			}
			else {
				allSize += (long)entry.file_size();
				//std::cout << "[fil]" << entry.path() << " (" << size << ")" << std::endl;
				//files.push_back(entry.path().u8string());
			}
		}
		return allSize;
	}


	//fs::path getPath(string s, ...) {
	//	fs::path result("");
	//	string* argv = &s;
	//	while (!argv->empty()) {
	//		//result = result / (*argv);
	//		std::cout << (*argv) << " ";
	//		//argv += sizeof(string);
	//		argv++;
	//	};
	//	std::cout << endl;
	//	return result;
	//}
	
};

