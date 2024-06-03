#pragma once
#include "Folder.h"
class Tree {
public:
	Folder* CF;
	Folder* root;
	bool prompt = true;
	Tree()
	{
		root = CF = new Folder("V","V:");
	}

	void print(string promt = ">")
	{
		if (CF->name == "V")
		{
			cout << "V:\\" << setprompt();
		}
		else
		{
			cout << "V:" << CF->path.substr(2, CF->path.length()) << setprompt();
		}
	}

	string setprompt()
	{
		if (prompt)
		{
			return ">";
		}
		return "$";
	}
};