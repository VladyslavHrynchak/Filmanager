#include <filesystem> 
#include "directory.h"
#include "file.h"
#include "folder.h"
#include <iostream>
#include <fstream>

namespace fs = std::filesystem;

using namespace std;

void Directory::clearDirectory()
{
	directory.clear();
}

void Directory::addFile(const std::filesystem::path& path)
{
	std::filesystem::path newpath = path;
	string name_of_file;
	cout << "Enter name of file: ";
	cin >> name_of_file;
	newpath /= name_of_file;
	fs::create_directories(newpath.parent_path());
	std::ofstream ofs(newpath);
	ofs << "Craate";
	ofs.close();
	saveFile(newpath);
}

void Directory::addFolder(const std::filesystem::path& path)
{
	std::filesystem::path newpath = path;
	string folder;
	cout << "Enter name of folder: ";
	cin >> folder;
	newpath /= folder;
	fs::create_directories(newpath);
	saveFolder(newpath);
}

void Directory::saveDirectoty(const std::filesystem::path& path)
{
	for (const auto& entry : fs::directory_iterator(path))
	{
		if (fs::is_regular_file(entry))
		{
			File newfile;
			newfile.path = entry.path();
			newfile.name = entry.path().stem().string();
			newfile.size = fs::file_size(entry.path());
			newfile.extension = entry.path().filename().string();;
			directory.push_back(newfile);
		}
		else
		{
			Folder newfolder;
			newfolder.path = entry.path();
			newfolder.name = entry.path().stem().string();
			newfolder.size = fs::file_size(entry.path());
			directory.push_back(newfolder);
		}
	}
}

void Directory::saveFile(const std::filesystem::path& path)
{
	File newfile;
	newfile.path = path;
	newfile.name = path.stem().string();
	newfile.size = fs::file_size(path);
	newfile.extension = path.filename().string();;
	directory.push_back(newfile);
}

void Directory::saveFolder(const std::filesystem::path& path)
{
	Folder newfolder;
	newfolder.path = path;
	newfolder.name = path.stem().string();
	newfolder.size = fs::file_size(path);
	directory.push_back(newfolder);
}

void Directory::print_list_of_files_in_the_directory(const std::filesystem::path& path)
{
	for (const auto& entry : fs::directory_iterator(path))
	{
		cout << entry.path().stem() << endl;
	}
}

void Directory::deleteFile(const std::filesystem::path& path) 
{
	bool isAddPath = false;
	while (!isAddPath)
	{
		try
		{
			std::filesystem::path newpath = path;
			string name_of_file;
			cout << "Enter name of file: ";
			cin >> name_of_file;
			newpath /= name_of_file;
			if (!fs::exists(newpath))
			{
				throw exception("You enter wrong name ");
			}
			for (size_t i = 0; i < directory.size(); i++)
			{
				if (directory[i].path == newpath)
				{
					directory[i].path = " ";
					directory[i].name = " ";
					directory[i].size = 0;
					directory[i].extension = " ";
				}
			}
			fs::remove(newpath);
			isAddPath = true;
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
	}
}

void Directory::copy_file_or_folder(const std::filesystem::path& path)
{
	bool isAddPath = false;
	while (!isAddPath)
	{
		try
		{
			string name_of_file;
			std::filesystem::path newpath;
		    std::filesystem::path curr_path = path;
			cout << "Enter name of file: ";
			cin >> name_of_file;
			curr_path /= name_of_file;
			if (!fs::exists(curr_path))
			{
				throw exception("You enter wrong name ");
			}
			cout << "Enter path: ";
			cin >> newpath;
			newpath /= name_of_file;
			fs::copy(curr_path, newpath, fs::copy_options::overwrite_existing);
			isAddPath = true;
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
	}
}

void Directory::rename_file_or_folder(const std::filesystem::path& path) 
{
	bool isAddPath = false;
	while (!isAddPath)
	{
		try
		{
			string name_of_file;
			std::filesystem::path curr_path = path;
			std::filesystem::path newpath = path;
			cout << "Enter name of file: ";
			cin >> name_of_file;
			curr_path /= name_of_file;
			if (!fs::exists(curr_path))
			{
				throw exception("You enter name ");
			}
			cout << "Enter new name: ";
			cin >> name_of_file;
			newpath /= name_of_file;
			fs::rename(curr_path, newpath);
			isAddPath = true;
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}
	}
}

vector<Entity*> Directory::search_file_or_folder(const string& name_of_file)
{
	vector<Entity*> search;
	size_t pos; 
	 for (size_t i = 0; i < directory.size(); i++)
	 {
		 pos = directory[i].name.find(name_of_file);
		  if (pos != std::string::npos)
		  {
			 search.push_back(&(directory[i]));
		  }
	 }
	 if (search.empty())
	 {
		 cout << "No file in directory" << endl;
	 }
	 return search;
}
