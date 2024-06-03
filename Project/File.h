#pragma once
class File {
public:
	string name;
	string extension;
	string data;
	string path;
	string creationTime;
	bool isHidden;
	int size;
	int randomAttribute;
	File(string name = "NULL", string path = "NULL", string data = "NULL",string extension = ".txt")
	{
		this->name = name;
		this->data = data;
		this->path = path;
		isHidden = false;
		this->extension = extension;
		extension = ".txt";
		SaveTime();
		saveSize();
		saveRandomAttribute();
	}

	// Saves the size of file as it is made
	void saveSize()
	{
		this->size = sizeof(*this);
	}

	void saveRandomAttribute()
	{
		randomAttribute = rand() % 1000;
	}
	// Saves the time of file as it is made
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

	
};
