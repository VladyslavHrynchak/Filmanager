#include "filemanager.h"
#include <iostream>

using namespace std;

FileManager::FileManager()
{
	directory.saveDirectoty(path);
}

void FileManager::start()
{
	int num;
	cout << "File manager started..." << endl << endl;
	while (true)
	{
		cout << endl;
		cout << "1 - See current path" << endl;
		cout << "2 - Add file to current path" << endl;
		cout << "3 - Add folder to current path" << endl;
		cout << "4 - Set a new path" << endl;
		cout << "5 - See size of file" << endl;
		cout << "6 - See free space on computer" << endl;
		cout << "7 - Information about folder" << endl;
		cout << "8 - Information about file" << endl;
		cout << "9 - Delete file or folder" << endl;
		cout << "10 - Copy file or folder" << endl;
		cout << "11 - Rename file or folder" << endl;
		cout << "12 - Search file or folder" << endl;
		try
		{
			cin >> num;
			if (num < 1 || num > 12)
			{
				throw exception("You enter wrong num");
			}
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}

		switch (num)
		{
		case 1:
			cout << "Path:" << path << endl << endl;
			directory.print_list_of_files_in_the_directory(path);
			cout << endl;
			break;

		case 2:
			directory.addFile(path);
			break;

		case 3:
			directory.addFolder(path);
			break;

		case 4:
			go_the_other_path();
			break;

		case 5:
			cout << Entity::calculate_file_size(path) << endl;
			break;

		case 6:
			free_space_on_the_computer();
			break;
		case 7:
			information_about_file_or_folder();
			break;
		case 8:
			information_about_file_or_folder();
			break;
		case 9:
			directory.deleteFile(path);
			break;
		case 10:
			directory.copy_file_or_folder(path);
			break;
		case 11:
			directory.rename_file_or_folder(path);
			break;
		case 12:
			string name_of_file;
			cout << "Enter name of file: ";
			cin >> name_of_file;
		    vector<Entity*> search = directory.search_file_or_folder(name_of_file);
			for (size_t i = 0; i < search.size(); i++)
			{
				cout << search[i]->name << endl;
			}
			break;
		}
	}
}

void  FileManager::free_space_on_the_computer()
{
	const auto& root_c = fs::path("C:/");
	const auto& root_d = fs::path("D:/");
	const auto& space_c = fs::space(root_c);
	const auto& space_d = fs::space(root_d);
	cout << "Disk C" << endl;
	cout << "Total: " << space_c.capacity / 1024 / 1024 / 1024 << " GB" << endl;
	cout << "Free: " << space_c.free / 1024 / 1024 / 1024 << " GB" << endl;
	cout << "Aviable: " << space_c.available / 1024 / 1024 / 1024 << " GB" << endl << endl;
	cout << "Disk D" << endl;
	cout << "Total: " << space_d.capacity / 1024 / 1024 / 1024 << " GB" << endl;
	cout << "Free: " << space_d.free / 1024 / 1024 / 1024 << " GB" << endl;
	cout << "Aviable: " << space_d.available / 1024 / 1024 / 1024 << " GB" << endl;
}

void FileManager::go_the_other_path()
{
	bool isAddPath = false;
	while (!isAddPath)
	{
		try
		{
			cout << "Enter new path ";
			cin >> path;
			directory.clearDirectory();
			directory.saveDirectoty(path);
			isAddPath = true;
		}
		catch (const std::exception& ex)
		{
			cout << "You enter wrong path " << endl;
		}
	}
	cout << endl;
	directory.print_list_of_files_in_the_directory(path);
}

void FileManager::information_about_file_or_folder()
{
	std::filesystem::path filepath = path;
	string name;
	bool isAddPath = false;
	while (!isAddPath)
	{
		try
		{
			filepath = path;
			cout << "Enter name: ";
			cin >> name;
			filepath /= name;
			if (!fs::exists(filepath))
			{
				throw exception("You enter wrong name ");
			}
			std::cout << "Name: " << filepath.filename() << endl;
			cout << "Size: " << fs::file_size(filepath) << " bytes" << endl;
			cout << "Path: " << filepath << endl;
			isAddPath = true;
		}
		catch (const std::exception& ex)
		{
			cout << ex.what() << endl;
		}

	}
}