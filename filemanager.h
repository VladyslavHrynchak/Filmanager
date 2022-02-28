#pragma once
#include <filesystem> 
#include "folder.h"
#include "file.h"
#include "directory.h"

using namespace std;

namespace fs = std::filesystem;

class FileManager
{
public:
	FileManager();
	
	void start();

private:
	
	Directory directory;

	Entity entity;

	std::filesystem::path path = fs::current_path();

	void free_space_on_the_computer();
	
	void go_the_other_path();

	void information_about_file_or_folder();
};
