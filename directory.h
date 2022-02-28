#pragma once
#include <vector>
#include "entity.h"

class Directory
{
public:

	void saveDirectoty(const std::filesystem::path& path);

	void saveFile(const std::filesystem::path& path);

	void saveFolder(const std::filesystem::path& path);

	void print_list_of_files_in_the_directory(const std::filesystem::path& path);

	void addFile(const std::filesystem::path& path);

	void addFolder(const std::filesystem::path& path);

	void deleteFile(const std::filesystem::path& path);
	
	void copy_file_or_folder(const std::filesystem::path& path);

	void rename_file_or_folder(const std::filesystem::path& path);

	void clearDirectory();

	std::vector<Entity*> search_file_or_folder(const std::string& name_of_file);

private:
	
	std::vector<Entity> directory;
};




