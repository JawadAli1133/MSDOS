#pragma once
#include<iostream>
#include "linkedList.h"
#include "File.h"
#include <vector>
#include<stdlib.h>
#include<queue>
using namespace std;
class Folder {
public:
	string name;
	string path;
	string creationTime;
	string owner;
	bool isHidden;
	int size;
	dLinkedList<Folder*> Folders;
	dLinkedList<File*> Files;
	Folder* parent;
	Folder(string name = "NULL", string path = "/", string owner = "Jawad", Folder* parent = nullptr)
	{
		dLinkedList<Folder*> folders = dLinkedList<Folder*>();
		dLinkedList<File*> files = dLinkedList<File*>();
		Folders = folders;
		Files = files;
		this->name = name;
		this->path = path;
		this->parent = parent;
		this->owner = owner;
		isHidden = false;
		SaveTime();
		saveSize();
	}

	// Saves the size of folder as it is made
	void saveSize()
	{
		this->size = sizeof(*this);
	}

	// Saves the time of folder as it is made
	void SaveTime()
	{
		time_t now = time(0);
		struct tm timeinfo;
		if (localtime_s(&timeinfo, &now) == 0) {
			char dt[25];
			strftime(dt, sizeof(dt), "%m/%d/%Y   %I:%M %p", &timeinfo);
			creationTime = dt;
		}
		else {
			creationTime = "error";
		}
	}

	// Function to insert a folder in a list of folders
	void InsertFolder(Folder* F)
	{
		Folders.InsertAtTail(F);
	}

	// Function to insert a file in a list of files
	void InsertFile(File* F)
	{
		Files.InsertAtTail(F);
	}

	// Function to remove a file from a list of fiels
	void removeFile(File* F)
	{
		Files.RemoveAt(F);
	}

	// Function to remove a folder from a list of folders
	void removeFolder(Folder* F)
	{
		Folders.RemoveAt(F);
	}

	// Function to format a folder
	void formatFolder()
	{
		dLinkedList<Folder*> Fs = dLinkedList<Folder*>();
		dLinkedList<File*> fs = dLinkedList<File*>();
		Folders = Fs;
		Files = fs;
	}

	// Function to print current directory
	void PrintDirectory()
	{
		int foldersize = 0;
		int filesize = 0;
		cout << " Directory of " << path << "\n\n";
		for (int i = 0;i < Folders.getSize();i++)
		{
			cout << Folders[i]->creationTime << "\t\t" << "<DIR>\t\t" << Folders[i]->name << endl;
			foldersize += Folders[i]->size;
		}
		for (int i = 0;i < Files.getSize();i++)
		{
			cout << Files[i]->creationTime << "\t\t     \t\t" << Files[i]->name << Files[i]->extension << endl;
			filesize += Files[i]->size;
		}
		cout << "\t\t" << Files.getSize() << " File(s)\t\t" << filesize << " bytes\n";
		cout << "\t\t" << Folders.getSize() << " Dir(s)\t\t" << foldersize << " bytes\n";
	}
	
	// Function to cehck if given folder name is valid
	bool checkFolderName(string name)
	{
		for (int i = 0;i < Folders.getSize();i++)
		{
			if (name == Folders[i]->name)
			{
				return false;
			}
		}
		return true;
	}

	// Function to check if given file name is valid
	bool checkFileName(string name,string extension)
	{
		for (int i = 0;i < Files.getSize();i++)
		{
			if (name == Files[i]->name and extension == Files[i]->extension)
			{
				return false;
			}
		}
		return true;
	}

	// Function to find a folder with name
	Folder* findFolderInGiveDirectory(string name)
	{
		for (int i = 0;i < Folders.getSize();i++)
		{
			if (name == Folders[i]->name)
			{
				return Folders[i];
			}
		}
		return nullptr;
	}

	// Function to find file with name
	File* getFileInGivenDirectory(string name,string extension)
	{
		for (int i = 0;i < Files.getSize();i++)
		{
			if (name == Files[i]->name and extension == Files[i]->extension)
			{
				return Files[i];
			}
		}
		return nullptr;
	}

	// Function to print attributes a given file
	void PrintFileData(File *F)
	{
		cout << getAttribute(F->extension) << "\t\t\t" << F->path << endl;
	}

	// Function to print attributes all files in current directory
	void PrintFiles()
	{
		for (int i = 0;i < Files.getSize();i++)
		{
			PrintFileData(Files[i]);
		}
	}
	
	// Function to get attribute based on the file extension
	string getAttribute(string ext)
	{
		vector<string> extension = { ".cpp",".txt",".exe"};
		vector<string> attribute = { "A","A","R" };
		for (int i=0;i<extension.size() ;i++)
		{
			if (extension[i] == ext)
			{
				return attribute[i];
			}
		}
		return "NULL";
	}

	// Function to change the extension of all files
	void changeExtension(string firstExtension, string secondExtension)
	{
		for (int i = 0;i < Files.getSize();i++)
		{
			if (firstExtension == Files[i]->extension)
			{
				changeFile_attributes(Files[i], secondExtension);
			}
		}
	}

	//Function to find a string in all files
	void findString(string data)
	{
		for (int i = 0;i < Files.getSize();i++)
		{
			if (Files[i]->extension != ".exe")
			{
				bool isPresent = isSubstring(Files[i]->data, data);
				cout << "---------- " << Files[i]->name << Files[i]->extension << endl;
				if (isPresent)
				{
					cout << Files[i]->data << endl;
				}
				cout << endl;
			}
		}
	}
	void changeFile_attributes(File* F,string extension)
	{
		F->extension = extension;
		string newpath = F->path.substr(0,F->path.length()-4);
		F->path = newpath + extension;
	}

	// Function to check if given substring is actually a substring of main string
	bool isSubstring(string mainstring, string substring)
	{
		int index = -1;
		index = mainstring.find(substring);
		if (index != -1) return true;
		return false;
	}

	Folder* findFolderRecursively(const string& targetPath)
	{
		if (path == targetPath)
		{
			return this;
		}

		for (int i = 0; i < Folders.getSize(); i++)
		{
			Folder* foundFolder = Folders[i]->findFolderRecursively(targetPath);
			if (foundFolder != nullptr)
			{
				return foundFolder;
			}
		}
		return nullptr;
	}
	void printDirectoryTree(Folder* currentFolder, int level = 0, bool last = true)
	{
		if (currentFolder == nullptr)
		{
			return;
		}
		if (level > 1)
		{
			cout << "|" << string(level * 4, ' ');
		}
		if (currentFolder->parent == nullptr)
		{
			cout << "V:.\n";
		}
		else
		{
			cout << (last ? "|________" : "|--------") << currentFolder->name << endl;
		}
		//currentFolder->PrintFile(level + 1);
		for (int i = 0;i < Folders.getSize();i++)
		{
			bool isLast = (i == currentFolder->Folders.getSize() - 1);
			printDirectoryTree(currentFolder->Folders[i], level + 1, isLast);
		}

	}
	void PrintFile(int level = 0)
	{
		if (Files.isEmpty())
		{
			return;
		}
		for (int i = 0;i < Files.getSize();i++)
		{
			cout << string(level * 4, ' ') << "   " << Files[i]->name << Files[i]->extension << endl;
		}
	}
};
