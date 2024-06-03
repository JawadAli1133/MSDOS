#pragma once
#include"list"
#include <string>
#include <iostream>
#include <fstream>
#include<stack>
#include <conio.h>
#include<deque>
#include<Windows.h>
using namespace std;
void gotoRowCol(int curRow, int curCol) {
	COORD coord;
	coord.X = curCol;
	coord.Y = curRow;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

list<string >Files;
struct state
{
	list<list <char>>text;
	list<list <char>>::iterator riter;
	list <char > ::iterator citer;
	int r, c;



};


class Editor
{
public:
	int curRow, curCol;
	list<list <char>>text;
	list<list <char>>::iterator riter;
	list <char > ::iterator citer;
	deque<state> undo;
	stack<state> redo;



	Editor() {
		text.push_back(list<char>());
		riter = text.begin();
		(*riter).push_back(' ');
		citer = (*riter).begin();
		curRow, curCol = 0;

	}

	state saveState() {
		state* s = new state;
		s->text.push_back(list<char>());
		auto r_itr = s->text.begin();
		for (auto row = text.begin(); row != text.end(); row++, r_itr++)
		{
			s->text.push_back(list<char>());
			for (auto col = (*row).begin(); col != (*row).end(); col++)
			{
				char ch = *col;
				(*r_itr).push_back(ch);
			}
		}
		s->riter = s->text.begin();
		s->citer = (*s->riter).begin();
		s->c = curCol;
		s->r = curRow;
		return *s;
	}
	void loadState(state s)
	{
		text = s.text;
		riter = text.begin();
		curCol = s.c;
		curRow = s.r;
		for (int r = 0; r < s.r; r++)
		{
			riter++;
		}
		citer = (*riter).begin();
		for (int c = 0; c < s.c; c++)
		{
			citer++;
		}
	}


	void closing(ifstream& rdr)
	{
		rdr.close();
		ofstream wtr;
		wtr.open("SaveFile.txt");
		for (auto i = Files.begin(); i != Files.end(); i++)
		{
			wtr << (*i) << endl;
		}
		wtr.close();
	}

	void createFile()
	{
		system("cls");
		string fileName;
		cout << "Enter File Name: ";
		cin >> fileName;
		if (find(Files.begin(), Files.end(), fileName) != Files.end())
		{
			cout << "File already exists";
			return;
		}
		Files.push_back(fileName);
		ofstream wrt(fileName.c_str());
		system("cls");
		editFile(wrt);
		//////// Here you have to  write a line missing
		system("cls");
		system("color f0");
		wrt.close();
	}
	void handleEnter(ofstream& wrt)
	{
		// Update undo and clear redo stack
		state currentState = saveState();

		undo.push_back(currentState);
		while (!redo.empty()) {
			redo.pop();
		}

		updateUndo();

		riter = text.begin();
		advance(riter, curRow);

		citer = (*riter).begin();
		advance(citer, curCol);

		// Insert a newline character
		auto newRowItr = text.insert(++riter, list<char>(citer, (*riter).end()));

		// Erase the content after the cursor in the current line using iterators from newRowItr
		if (newRowItr != text.end()) {
			(*newRowItr).erase((*newRowItr).begin(), (*newRowItr).end());
		}

		// Move to the next line
		riter = newRowItr;
		curRow++;
		citer = (*riter).begin();
		curCol = 0;

		system("cls");
		print();

	}

	void editFile(ofstream& wrt)
	{
		system("color f0");

		char c;
		c = _getch();
		gotoRowCol(curRow, curCol);
		cout << c;
		(*citer) = c;
		curCol++;
		while (true)
		{
			//if (curRow == 0 or curCol == 0) {
			gotoRowCol(curRow, curCol);
			//}
			//else gotoRowCol(curRow, curCol + 1);

			c = _getch();

			if (c == -32)
			{
			A:
				c = _getch();
				if (c == 72)
				{
					if (curRow == 0)
					{
						continue;
					}
					riter--;
					citer = (*riter).begin();
					curRow--; curCol = 0;
				}
				else if (c == 80)
				{
					//if (curRow <= text.size())



					riter++;
					citer = (*riter).begin();
					curRow++; curCol = 0;
				}
				else if (c == 75)
				{
					if (curCol - 1 > 0)
					{
						citer--;
						curCol--;
					}
				}
				else if (c == 77)
				{
					if (curCol == 159)
					{
						continue;
					}
					if (curCol < (*riter).size() - 1)
					{

						citer++;
						curCol++;
					}
				}
				else if (c == 83)
				{
					auto temp = citer;
					(*riter).erase(citer);
					citer = temp;
					system("cls");
					print();
					updateUndo();
				}
				if (curCol == 0)
				{
					gotoRowCol(curRow, 0);
					c = _getch();
					if (c == -32)
					{
						goto A;
					}
					(*riter).push_front(c);
					citer = (*riter).begin();
					curCol = 1;
					system("cls");
					print();
					updateUndo();
				}
				continue;
			}
			else if (c == 13)
			{
				//auto temp = riter;
				//riter++;
				//text.insert(riter, list<char>());
				//riter = ++temp;
				//curRow++; curCol = 0;
				//gotoRowCol(curRow, curCol);
				///*c = _getch();
				//if (c == -32)
				//{
				//	goto A;
				//}
				//(*riter).push_back(c);
				//citer = (*riter).begin();*/
				//system("cls");
				//print();
				//updateUndo();
				//continue;
				handleEnter(wrt);
			}
			else if (c == 8)
			{
				if (curCol == 0)
				{
					/*gotoRowCol(curRow, 0);
					c = _getch();
					if (c == -32)
					{
						goto A;
					}
					if (c == 8)
					{
						continue;
					}
					(*citer) = c;
					citer = (*riter).begin();
					curCol = 1;*/
					continue;
				}

				if (citer != (*riter).begin())
				{
					auto temp = --citer;
					citer++;
					(*riter).erase(citer);
					citer = temp;
					curCol--;
					system("cls");
					print();
					updateUndo();
					continue;

				}
				(*riter).erase(citer);
				curCol--;
				system("cls");
				print();
				updateUndo();
				continue;
			}
			else if (c == 26)
			{
				if (!undo.empty())
				{
					state s = undo.back();
					loadState(s);
					redo.push(undo.back());
					undo.pop_back();
					system("cls");
					print();
				}
				continue;
			}
			else if (c == 25)
			{
				if (!redo.empty())
				{
					undo.push_back(redo.top());
					state s = redo.top();
					redo.pop();
					loadState(s);
					system("cls");
					print();
				}
				continue;
			}
			else if (c == 27)
			{
				writeTextToFile(wrt);
				break;
			}

			if (curCol == 100)
			{
				text.push_back(list<char>());
				riter++;
				curCol = 0;
				curRow++;
			}
			else
			{
				if (curCol == 0)
				{
					(*riter).push_back(c);
					citer = (*riter).begin();
					curCol++;

				}
				else {

					auto temp = citer;
					citer++;
					(*riter).insert(citer, c);
					citer = ++temp;
					curCol++;
				}
			}
			system("cls");
			print();
			updateUndo();

		}

	}



	void writeTextToFile(ofstream& wrt)
	{
		for (auto r = text.begin(); r != text.end(); r++)

		{
			for (auto c = (*r).begin(); c != (*r).end(); c++)
			{
				wrt << *c;
			}
			wrt << '\n';
		}
	}
	void updateUndo()
	{
		if (undo.size() > 5)
		{
			undo.erase(undo.begin());
		}
		state s;
		s = saveState();
		undo.push_back(s);
	}
	void openSaveFile(ifstream& rdr)
	{
		char ch;
		while (!rdr.eof()) {
			rdr.get(ch);
			if ((*riter).size() == 1 && (*citer) == ' ') {
				break;
			}


			if (ch != '\n')
			{
				(*riter).push_back((ch));
			}
			else {
				text.push_back(list<char>());
				riter++;
			}
		}
		riter = text.begin();
		citer = (*riter).begin();
		curRow = 0; curCol = 0;
		gotoRowCol(curRow, curCol);
	}

	void open_File() {
		system("cls");
		string fileName;
		cout << "Enter File Name: ";
		cin >> fileName;
		if (find(Files.begin(), Files.end(), fileName) == Files.end()) {
			cout << "File Doesnot exists ";
			return;
		}
		ifstream Rdr(fileName.c_str());
		openSaveFile(Rdr);
		Rdr.close();
		ofstream wrt(fileName.c_str());
		system("cls");
		print();
		gotoRowCol(curRow, curCol);
		editFile(wrt);
		system("cls");
		wrt.close();
	}


	void print()
	{
		for (auto r = text.begin(); r != text.end(); r++)
		{
			for (auto c = (*r).begin(); c != (*r).end(); c++)
			{
				cout << *c;
			}
			cout << endl;
		}
	}

};