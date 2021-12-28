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
	//fs::path BASE_PATH = "base";


	/*
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
	*/


	bool isPath(fs::path path);

	unsigned long long getDirectorySizeBytes(fs::path basePath);

private:
	unsigned long long _getDirectorySizeBytes(fs::path basePath);
};

