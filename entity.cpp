#include "entity.h"
#include <iostream>

using namespace std;

int Entity::calculate_file_size(const std::filesystem::path& path) 
{
	bool isAddPath = false;
	while (!isAddPath)
	{
		try
		{
			std::filesystem::path newpath = path;
			return fs::file_size(newpath);
			isAddPath = true;
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
	}
}



