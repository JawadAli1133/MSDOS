#pragma once
#include<string>
#include "Tree.h"
#include "notepad.h"

class CompareFiles {
public:
	bool operator()(const File* f1, const File* f2) const {
		return f1->randomAttribute > f2->randomAttribute;
	}
};
class DOS {
private:
	string lower(string str)
	{
		string lower = "";
		for (char c : str)
		{
			lower += tolower(c);
		}
		return lower;
	}
	vector<string> commands = { "mkdir","exit","cls","create","cd","cd..","attrib","pwd","cd\\","prompt","ver","find","findf","del","convert","rmdir","format","findstr" };
	vector<string> helps = { "Creates a virtual directory.","Quits the CMD.EXE program (command interpreter).","Clears the screen.","Creates a virtual file.","Changes the current virtual directory.","Changes the current virtual directory to its parent.","Displays the file attributes.","Displays the working virtual directory.","Changes to the virtual root directory.","Changes the MS DOS command prompt.","Displays the MS DOS version.","Searches for a file in current virtual directory.","Searches for a text string in a file.","Deletes a virtual file.","Convert the extension of all files with given extension.","Deletes a virtual directory.","Formats the current virtual directory.","Searches for a text string in all files of current virtual directory." };
	vector<string> methods = { "MKDIR [drive:]path","EXIT","CLS","CREATE [drive:]path[extension]\n\n\t\tthe extension should be .txt,.cpp or .exe.","CD [drive:][path]","CD..","ATTRIB [drive:][path][filename]","PWD","CD\\","PROMPT","VER","FIND [[drive:][path]filename[...]]","FINDF 'string' [[drive:][path]filename[...]]","convert [extension] [extension]","RMDIR [drive:]path","FORMAT","FIND 'string'","DEL [drive:]path[extension]" };
public:
	Tree t;
	queue<File*> Queue;
	priority_queue<File*, vector<File*>, CompareFiles> priorityPrintQueue;
	void Header()
	{
		cout << "Asad Ali [2022-CS-185]\n(c) Mini Operating System Project\n\n";
		t.print();
	}
	void Run()
	{
		Header();
		bool exit = false;
		while (!exit)
		{
			exit = input();
		}
	}

	bool input()
	{
		string command;
		getline(cin, command);
		string op = command.substr(0, command.find(' '));
		op = lower(op);
		if (op == "exit")
		{
			return true;
		}
		else if (op == "cls")
		{
			system("cls");
			t.print();
			return false;
		}
		else if (op == "mkdir")
		{
			if ((command.length() == op.length()))
			{
				commandSyntaxError();
			}
			else
			{
				string substring = command.substr(6, command.length());
				string name = removeSpace(substring);
				if (name != "")
				{
					bool checkName = t.CF->checkFolderName(name);
					if (checkName)
					{
						Folder* F = new Folder(name, t.CF->path + "\\" + name, "Jawad", t.CF);
						t.CF->InsertFolder(F);
						t.CF->size += F->size;
					}
					else
					{
						dirExistError();
					}
				}
				else
				{
					commandSyntaxError();
				}
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "dir")
		{
			string com = "";
			//command.erase(remove((command.begin() + 4), command.end(), ' '), command.end());
			if (op.length() != command.length())
			{
				string substring = command.substr(4, command.length());
				com = removeSpace(substring);
			}
			if (com == "")
			{
				t.CF->PrintDirectory();
				cout << endl;
				t.print();
				return false;
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "cd.")
		{
			string com = "";
			if (op.length() != command.length())
			{
				string substring = command.substr(4, command.length());
				com = removeSpace(substring);
			}
			if (com != "")
			{
				pathError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "cd..")
		{
			string com = "";
			if (op.length() != command.length())
			{
				string substring = command.substr(5, command.length());
				com = removeSpace(substring);
			}
			if (com == "")
			{
				if (t.CF->parent != nullptr)
				{
					t.CF = t.CF->parent;
				}
			}
			else
			{
				pathError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "cd")
		{
			string name = "";
			if (op.length() != command.length())
			{
				string substring = command.substr(3, command.length());
				name = removeSpace(substring);
			}
			if (name != "")
			{
				Folder* F = t.CF->findFolderInGiveDirectory(name);
				if (F != nullptr)
				{
					t.CF = F;
				}
				else
				{
					pathError();
				}
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "create")
		{
			if ((command.length() == op.length()))
			{
				commandSyntaxError();
			}
			else
			{
				int index = -1;
				int dotIndex = -1;
				string data = "NULL";
				string fileextension = ".txt";
				string filename;
				string substring = command.substr(7, command.length());
				string name = removeSpace(substring);
				if (name != "")
				{
					index = substring.find(',');
					dotIndex = substring.find('.');
					if (index != -1)
					{
						string tempName = substring.substr(0, index);
						string tempData = substring.substr(index + 1, substring.length());
						tempName = removeSpace(tempName);
						if (tempName != "")
						{
							if (dotIndex != -1)
							{
								string a = tempName.substr(tempName.find('.'), tempName.length());
								fileextension = getExtension(a);
								filename = tempName.substr(0, tempName.find('.'));
							}
							else
							{
								filename = tempName.substr(0, tempName.length());
							}
							data = substring.substr(substring.find(',') + 1, substring.length());
						}
					}
					else
					{
						string name = removeSpace(substring);
						if (dotIndex != -1)
						{
							fileextension = getExtension(name.substr(name.find('.'), name.length()));
							filename = name.substr(0, name.find('.'));
						}
						else
						{
							filename = removeSpace(substring);
						}
					}
					bool checkFileName = t.CF->checkFileName(filename,fileextension);
					if (checkFileName)
					{
						if (fileextension != "NULL")
						{
							if (fileextension != ".exe")
							{
								File* F = new File(filename, t.CF->path + "\\" + filename + fileextension, data, fileextension);
								t.CF->InsertFile(F);
								t.CF->size += F->size;
							}
							else
							{
								cout << "Cannot enter data in a readable file\n";
							}
						}
						else
						{
							extensionError();
						}
					}
					else
					{
						dirExistError();
					}
				}
				else
				{
					commandSyntaxError();
				}
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "attrib")
		{
			string com = "";
			if (op.length() != command.length())
			{
				string substring = command.substr(7, command.length());
				com = removeSpace(substring);
			}
			if (com == "")
			{
				t.CF->PrintFiles();
			}
			else
			{
				string name = com;
				string extension = ".txt";
				int index = -1;
				index = com.find('.');
				if (index != -1)
				{
					extension = getExtension(com.substr(index,com.length()));
					name = com.substr(0, index);
				}
				if (extension != "NULL")
				{
					File* F = t.CF->getFileInGivenDirectory(name,extension);
					if (F != nullptr)
					{
						t.CF->PrintFileData(F);
					}
					else
					{
						pathError();
					}
				}
				else
				{
					extensionError();
				}
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "pwd")
		{
			string name = "";
			if (op.length() != command.length())
			{
				string substring = command.substr(4, command.length());
				name = removeSpace(substring);
			}
			if (name == "")
			{
				cout <<"\t\t\t" << t.CF->path;
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "cd\\")
		{
			string name = "";
			if (op.length() != command.length())
			{
				string substring = command.substr(4, command.length());
				name = removeSpace(substring);
			}
			if (name == "")
			{
				t.CF = t.root;
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "ver")
		{
			string name = "";
			if (op.length() != command.length())
			{
				string substring = command.substr(4, command.length());
				name = removeSpace(substring);
			}
			if (name == "")
			{
				cout << "DSA Project MS DOS [Version 10.0.19045.3570]\n";
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "prompt")
		{
			string name = "";
			if (op.length() != command.length())
			{
				string substring = command.substr(7, command.length());
				name = removeSpace(substring);
			}
			if (name == "")
			{
				t.prompt = !t.prompt;
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "find")
		{
			string com = "";
			if (op.length() != command.length())
			{
				string substring = command.substr(5, command.length());
				com = removeSpace(substring);
			}
			if (com == "")
			{
				commandSyntaxError();
			}
			else
			{
				string name = com;
				string extension = ".txt";
				int index = -1;
				index = com.find('.');
				if (index != -1)
				{
					extension = getExtension(com.substr(index, com.length()));
					name = com.substr(0, index);
				}
				if (extension != "NULL")
				{
					File* F = t.CF->getFileInGivenDirectory(name,extension);
					if (F != nullptr)
					{
						cout << F->creationTime<<"\t\t\t" << F->path << endl;
					}
					else
					{
						pathError();
					}
				}
				else
				{
					extensionError();
				}
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "findf")
		{
			string data = "NULL";
			string name = "";
			string name_withextension = "";
;			string filename = "";
			string extension = ".txt";
			if (op.length() != command.length())
			{
				string substring = command.substr(6, command.length());
				name = removeSpace(substring);
			}
			if (name != "")
			{
				int index = -1;
				int commaFind = -1;
				index = name.find('"');
				if (index == 0)
				{
					string datawithcomma = name.substr(index + 1, name.length());
					commaFind = datawithcomma.find('"');
					if (commaFind != -1)
					{
						string tempData1 = command.substr(command.find('"')+1,command.length());
						data = tempData1.substr(0, tempData1.find('"'));
						name_withextension = tempData1.substr(tempData1.find('"') + 1, tempData1.length());
						if (name_withextension != "")
						{
							filename = removeSpace(name_withextension);
							int dotIndex = -1;
							dotIndex = filename.find('.');
							if (dotIndex != -1)
							{
								extension = getExtension(filename.substr(dotIndex, filename.length()));
								filename = filename.substr(0, dotIndex);
							}
							if (extension != "NULL")
							{
								File* F = t.CF->getFileInGivenDirectory(filename,extension);
								bool is_substring = t.CF->isSubstring(F->data, data);
								cout << "---------- " << F->name << F->extension << endl;
								if (is_substring)
								{
									cout << F->data;
								}
							}
							else
							{
								extensionError();
							}
						}
						else
						{
							pathError();
						}
					}
					else
					{
						commandSyntaxError();
					}
				}
				else
				{
					commandSyntaxError();
				}
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "del")
		{
			string com = "";
			string name;
			string extension = ".txt";
			int dotIndex = -1;
			if (op.length() != command.length())
			{
				string substring = command.substr(4, command.length());
				com = removeSpace(substring);
			}
			if (com != "")
			{
				name = com;
				dotIndex = name.find('.');
				if (dotIndex != -1)
				{
					extension = getExtension(com.substr(dotIndex, com.length()));
					name = name.substr(0, dotIndex);
				}
				if (extension != "NULL")
				{
					File* F = t.CF->getFileInGivenDirectory(name,extension);
					if (F != nullptr)
					{
						t.CF->removeFile(F);
						t.CF->size -= F->size;
					}
					else
					{
						pathError();
					}
				}
				else
				{
					extensionError();
				}
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "convert")
		{
			string name = "";
			string substring;
			string first_extension = "";
			string second_extension = "";
			if (op.length() != command.length())
			{
				substring = command.substr(8, command.length());
				name = removeSpace(substring);
			}
			if (name != "")
			{
				int dotIndex1 = -1;
				int dotIndex2 = -1;
				dotIndex1 = name.find('.'); 
				if (dotIndex1 == 0)
				{
					string substring_withoutdot = name.substr(1, name.length());
					dotIndex2 = substring_withoutdot.find('.');
					if (dotIndex2 != -1)
					{
						first_extension = name.substr(0, dotIndex2 + 1);
						second_extension = name.substr(dotIndex2 + 1, name.length());
						first_extension = getExtension(first_extension);
						second_extension = getExtension(second_extension);
						if (first_extension != "NULL" && second_extension != "NULL")
						{
							t.CF->changeExtension(first_extension, second_extension);
						}
						else
						{
							extensionError();
						}
					}
					else
					{
						commandSyntaxError();
					}

				}
				else
				{
					commandSyntaxError();
				}
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "rmdir")
		{
			string com = "";
			if (op.length() != command.length())
			{
				string substring = command.substr(6, command.length());
				com = removeSpace(substring);
			}
			if (com != "")
			{
				Folder* F = t.CF->findFolderInGiveDirectory(com);
				if (F != nullptr)
				{
					t.CF->removeFolder(F);
				}
				else
				{
					pathError();
				}
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
			}
		else if (op == "format")
		{
			string com = "";
			if (op.length() != command.length())
			{
				string substring = command.substr(7, command.length());
				com = removeSpace(substring);
			}
			if (com == "")
			{
				t.CF->formatFolder();
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "findstr")
		{
			int commaIndex1;
			int commaIndex2;
			string str = "";
			if (op.length() != command.length())
			{
				string substring = command.substr(8, command.length());
				str = removeSpace(substring);
			}
			if (str != "")
			{
				commaIndex1 = str.find('"');
				if (commaIndex1 == 0)
				{

					string substring_from_str = str.substr(1, str.length());
					commaIndex2 = substring_from_str.find('"');
					if (commaIndex2 == substring_from_str.length() - 1)
					{
						string tempData = command.substr(command.find('"') + 1,command.length());
						string data = tempData.substr(0, tempData.find('"'));
						t.CF->findString(data);
					}
					else
					{
						commandSyntaxError();
					}
				}
				else
				{
					commandSyntaxError();
				}
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "help")
		{
			string name = "";
			if (op.length() != command.length())
			{
				string substring = command.substr(5,command.length());
				name = removeSpace(substring);
			}
			if (name == "")
			{
				cout << "For more information on a specific command, type HELP command-name\n";
				for (int i = 0;i < commands.size();i++)
				{
					cout << commands[i] << "\t\t" << helps[i] << endl;
				}
			}
			else
			{
				int comIndex = checkHelpCommand(name, commands);
				if (comIndex != -1)
				{
					cout <<helps[comIndex] << "\n\n" << methods[comIndex] << endl;
				}
				else
				{
					cout << "This command is not supported by the help utility.";
				}
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "rename")
		{
			string name = "";
			string substring = "";
			string firstName, secondName = "";
			string firstExtension = ".txt", secondExtension = ".txt";
			if (op.length() != command.length())
			{
				substring = command.substr(7, command.length());
				name = removeSpace(substring);
			}
			if (name != "")
			{
				string first_tempString = substring.substr(substring.find_first_not_of(' '), substring.find(' '));
				string second_tempString = substring.substr(first_tempString.length(), substring.length());
				string firstNameTemp = removeSpace(first_tempString);
				string secondNameTemp = removeSpace(second_tempString);
				if (firstNameTemp != "" && secondNameTemp != "")
				{
					int dotIndex1 = -1, dotIndex2 = -1;
					dotIndex1 = firstNameTemp.find('.');
					dotIndex2 = secondNameTemp.find('.');
					firstName = firstNameTemp;
					secondName = secondNameTemp;
					if (dotIndex1 != -1)
					{
						firstExtension = getExtension(firstNameTemp.substr(dotIndex1, firstNameTemp.length()));
						firstName = firstNameTemp.substr(0, dotIndex1);
					}
					if (dotIndex2 != -1)
					{
						string str = secondNameTemp.substr(dotIndex2, secondNameTemp.length());
						secondExtension = getExtension(str);
						secondName = secondNameTemp.substr(0, dotIndex2);
					}
					if (firstExtension != "NULL" && secondExtension != "NULL")
					{
						if (firstExtension == secondExtension)
						{
							File* F = t.CF->getFileInGivenDirectory(firstName, firstExtension);
							if (F != nullptr)
							{
								bool checkFile = t.CF->checkFileName(secondName, secondExtension);
								if (checkFile)
								{
									F->name = secondName;
								}
							}
							else
							{
								pathError();
							}
						}
						else
						{
							cout << "Cannot change the extension of file during rename\n";
						}
						
					}
					else
					{
						extensionError();
					}

				}
				else
				{
					commandSyntaxError();
				}
			}
			else
			{
				commandSyntaxError();
			}
			
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "copy")
		{
			string str = "";
			int rootFind1 = -1;
			int rootFind2 = -1;
			string name = "";
			string extension = ".txt";
			int dotIndex = -1;
			if (op.length() != command.length())
			{
				string substring = command.substr(5, command.length());
				str = removeSpace(substring);
			}
			if (str != "")
			{
				rootFind1 = str.find("V:");
				if (rootFind1 != -1)
				{
					string nameofFile = str.substr(0, rootFind1);
					if (nameofFile != "")
					{
						string tempSubString = str.substr(rootFind1 + 1, str.length());
						rootFind2 = tempSubString.find("V:");
						if (rootFind2 != -1)
						{
							string firstpath = str.substr(rootFind1, rootFind2+1);
							string secondpath = str.substr(nameofFile.length() + rootFind2 + 1, str.length());
							if (firstpath != "" && secondpath != "")
							{
								Folder* F1 = t.root->findFolderRecursively(firstpath);
								Folder* F2 = t.root->findFolderRecursively(secondpath);
								if (F1 != nullptr && F2 != nullptr)
								{
									name = nameofFile;
									dotIndex = str.find('.');
									if (dotIndex != -1)
									{
										extension = getExtension(nameofFile.substr(dotIndex, nameofFile.length()));
										name = nameofFile.substr(0, dotIndex);
									}
									if (extension != "NULL")
									{
										File* f = F1->getFileInGivenDirectory(name,extension);
										if (f != nullptr)
										{
											F2->InsertFile(f);
										}
									}
									else
									{
										extensionError();
									}
								}
								else
								{
									pathError();
								}
							}
						}
						else
						{
							commandSyntaxError();
						}
					}
					else
					{
						commandSyntaxError();
					}
					
				}
				else
				{
					commandSyntaxError();
				}
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "move")
		{
			string str = "";
			int rootFind1 = -1;
			int rootFind2 = -1;
			string name = "";
			string extension = ".txt";
			int dotIndex = -1;
			if (op.length() != command.length())
			{
				string substring = command.substr(5, command.length());
				str = removeSpace(substring);
			}
			if (str != "")
			{
				rootFind1 = str.find("V:");
				if (rootFind1 != -1)
				{
					string nameofFile = str.substr(0, rootFind1);
					if (nameofFile != "")
					{
						string tempSubString = str.substr(rootFind1 + 1, str.length());
						rootFind2 = tempSubString.find("V:");
						if (rootFind2 != -1)
						{
							string firstpath = str.substr(rootFind1, rootFind2 + 1);
							string secondpath = str.substr(nameofFile.length() + rootFind2 + 1, str.length());
							if (firstpath != "" && secondpath != "")
							{
								Folder* F1 = t.root->findFolderRecursively(firstpath);
								Folder* F2 = t.root->findFolderRecursively(secondpath);
								if (F1 != nullptr && F2 != nullptr)
								{
									name = nameofFile;
									dotIndex = str.find('.');
									if (dotIndex != -1)
									{
										extension = getExtension(nameofFile.substr(dotIndex, nameofFile.length()));
										name = nameofFile.substr(0, dotIndex);
									}
									if (extension != "NULL")
									{
										File* f = F1->getFileInGivenDirectory(name,extension);
										if (f != nullptr)
										{
											F1->removeFile(f);
											F2->InsertFile(f);
										}
									}
									else
									{
										extensionError();
									}
								}
								else
								{
									pathError();
								}
							}
						}
						else
						{
							commandSyntaxError();
						}
					}
					else
					{
						commandSyntaxError();
					}

				}
				else
				{
					commandSyntaxError();
				}
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "tree")
		{
			string com = "";
			if (op.length() != command.length())
			{
				string substring = command.substr(7, command.length());
				com = removeSpace(substring);
			}
			if (com == "")
			{
				cout << "Folder PATH listing\n";
				cout << "Volume serial number is EAFF-7FBA\n";
				t.CF->printDirectoryTree(t.CF);
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "print")
		{
			string name = "";
			int dotIndex = -1;
			string fileName = "";
			string fileExtension = ".txt";
			if (op.length() != command.length())
			{
				string substring = command.substr(6,command.length());
				name = removeSpace(substring);
			}
			if (name != "")
			{
				fileName = name;
				dotIndex = name.find('.');
				if (dotIndex != -1)
				{
					fileExtension = name.substr(dotIndex, name.length());
					fileName = name.substr(0, dotIndex);
				}
				if (fileName != "" and fileExtension != "NULL")
				{
					File* F = t.CF->getFileInGivenDirectory(fileName, fileExtension);
					if (F != nullptr)
					{
						Queue.push(F);
						cout << "'" << F->name << "' has been added to queue successfully.\n";
					}
					else
					{
						pathError();
					}
				}
				else
				{
					commandSyntaxError();
				}
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "pprint")
		{
			string name = "";
			int dotIndex = -1;
			string fileName = "";
			string fileExtension = ".txt";
			if (op.length() != command.length())
			{
				string substring = command.substr(7, command.length());
				name = removeSpace(substring);
			}
			if (name != "")
			{
				fileName = name;
				dotIndex = name.find('.');
				if (dotIndex != -1)
				{
					fileExtension = name.substr(dotIndex, name.length());
					fileName = name.substr(0, dotIndex);
				}
				if (fileName != "" and fileExtension != "NULL")
				{
					File* F = t.CF->getFileInGivenDirectory(fileName, fileExtension);
					if (F != nullptr)
					{
						priorityPrintQueue.push(F);
						cout << "'" << F->name << "' has been added to priority queue successfully.\n";
					}
					else
					{
						pathError();
					}
				}
				else
				{
					commandSyntaxError();
				}
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "queue")
		{
			string name = "";
			if (op.length() != command.length())
			{
				string substring = command.substr(6, command.length());
				name = removeSpace(substring);
			}
			if (name == "")
			{
				PrintQueue();
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "pqueue")
		{
			string name = "";
			if (op.length() != command.length())
			{
				string substring = command.substr(6, command.length());
				name = removeSpace(substring);
			}
			if (name == "")
			{
				PrintPriorityQueue();
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "edit")
		{
			string name = "";
			int dotIndex = -1;
			string fileName = "";
			string fileExtension = ".txt";
			if (op.length() != command.length())
			{
				string substring = command.substr(5, command.length());
				name = removeSpace(substring);
			}
			if (name != "")
			{
				fileName = name;
				dotIndex = name.find('.');
				if (dotIndex != -1)
				{
					fileExtension = name.substr(dotIndex, name.length());
					fileName = name.substr(0, dotIndex);
				}
				if (fileName != "" and fileExtension != "NULL")
				{
					if (fileExtension != ".exe")
					{
						File* F = t.CF->getFileInGivenDirectory(fileName, fileExtension);
						if (F != nullptr)
						{
							ifstream read;
							string filename = F->name + "." + F->extension;
							read.open(filename);
							Editor e;
							e.openSaveFile(read);
							read.close();
							ofstream write;
							write.open(filename);
							system("cls");
							e.editFile(write);
							system("cls");
							write.close();
							system("Color 07");
							Header();
						}
						else
						{
							pathError();
						}
					}
					else
					{
						cout << "Error! Cannot edit a readable file.\n";
					}
				}
				else
				{
					commandSyntaxError();
				}
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "save")
		{
			string name = "";
			int dotIndex = -1;
			string fileName = "";
			string fileExtension = ".txt";
			if (op.length() != command.length())
			{
				string substring = command.substr(5, command.length());
				name = removeSpace(substring);
			}
			if (name != "")
			{
				fileName = name;
				dotIndex = name.find('.');
				if (dotIndex != -1)
				{
					fileExtension = name.substr(dotIndex, name.length());
					fileName = name.substr(0, dotIndex);
				}
				if (fileName != "" and fileExtension != "NULL")
				{
					File* F = t.CF->getFileInGivenDirectory(fileName, fileExtension);
					if (F != nullptr)
					{
						saveFile(F);
					}
					else
					{
						pathError();
					}
				}
				else
				{
					commandSyntaxError();
				}
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "loadtree")
		{
			string com = "";
			if (op.length() != command.length())
			{
				string substring = command.substr(7, command.length());
				com = removeSpace(substring);
			}
			if (com == "")
			{
				
			}
			else
			{
				commandSyntaxError();
			}
			cout << endl;
			t.print();
			return false;
		}
		else if (op == "")
		{
			t.print();
			return false;
		}
		else
		{
			commandError(op);
			cout << endl;
			t.print();
			return false;
		}
		return false;
	}

	//Function to remove space characters from a given string
	string removeSpace(string str)
	{
		string name = "";
		for (char c : str)
		{
			if (c != ' ')
			{
				name += c;
			}
		}
		return name;
	}
	void extensionError()
	{
		cout << "The extension of the file in invalid.\n";
	}
	void pathError()
	{
		cout << "The system cannot find the path specified.\n";
	}

	void commandSyntaxError()
	{
		cout << "The syntax of the command is incorrect.\n";
	}

	void commandError(string command)
	{
		cout << "'" << command << "'" << "is not recognized as an internal or external command,\noperable program or batch file.\n";
	}

	void dirExistError()
	{
		cout << "A subdirectory or a file already exists.\n";
	}

	// Function to check extension of a file
	string getExtension(string name)
	{
		string ext = "NULL";
		vector<string> vect{ ".cpp",".txt",".exe" };
		int index = -1;
		index = name.find('.');
		if (index != -1)
		{
			string nameExtension = name.substr(index, name.length());
			for (string a : vect)
			{
				if (nameExtension == a)
				{
					ext = a;
				}
			}
			return ext;
		}
	}

	int checkHelpCommand(string com,vector<string> commands)
	{
		for (int i = 0;i < commands.size();i++)
		{
			if (com == commands[i])
			{
				return i;
			}
		}
		return -1;
	}

	void PrintQueue()
	{
		if (Queue.empty())
		{
			cout << "Queue is empty.\n";
		}
		else
		{
			cout << "Print queue:" << endl;
			int i = 1;
			queue<File*> tempQueue = Queue;
			while (!tempQueue.empty()) {
				File* file = tempQueue.front();
				int timeLeft = rand() % 60;
				cout << i << ". " << file->name << " - Time Left: " << timeLeft << " seconds" << endl;
				tempQueue.pop();
				i++;
			}
		}
	}

	void PrintPriorityQueue()
	{
		if (priorityPrintQueue.empty())
		{
			cout << "Queue is empty.\n";
		}
		else
		{
			cout << "Print priority queue:" << endl;
			int i = 1;
			priority_queue<File*, vector<File*>, CompareFiles> tempQueue = priorityPrintQueue;
			while (!tempQueue.empty()) {
				File* file = tempQueue.top();
				int timeLeft = rand() % 60;
				cout << i << ". " << file->name << " - Time Left: " << timeLeft << " seconds" << endl;
				tempQueue.pop();
				i++;
			}
		}
	}

	void saveFile(File* currentFile)
	{
		if (currentFile != nullptr) {
			string filePath = currentFile->path + "\\" + currentFile->name + currentFile->extension;

			ofstream outputFile(filePath);

			if (outputFile.is_open()) {
				outputFile << currentFile->data;

				outputFile.close();

				cout << "File saved successfully." << endl;
			}
			else {
				cerr << "Error: Unable to save the file." << endl;
			}
		}
		else {
			cerr << "Error: No file is currently open." << endl;
		}
	}
};

