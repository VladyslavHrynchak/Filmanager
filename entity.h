#pragma once
#include <filesystem>

namespace fs = std::filesystem;

class Entity
{
	
	
public:
	static int calculate_file_size(const std::filesystem::path& path);
	std::filesystem::path path;
	std::string name;
	int size;
	std::string extension;
};

