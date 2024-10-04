#include <iostream>
#include <vector>
#include <fstream>
#include <string>


struct Icomp
{
	virtual std::string get_path() = 0;
	virtual std::string get_name() = 0;
	virtual void get_info() = 0;
	virtual bool is_not_folder() = 0;
};

struct File :Icomp
{
private:
	std::string data;
	std::string name = "/";
	std::string path = "/";

public:

	std::string get_name()
	{
		return name;
	}

	std::string get_data()
	{
		return data;
	}

	std::string get_path()
	{
		return path;
	}


	bool is_not_folder()
	{
		for (char i : name)
		{
			if (i == '.') return false;
		}
		return true;
	}


	void get_info()
	{
		std::cout << path << "  " << name << " " << data << "\n";
	}
	File(std::string name, std::string path) : name(name), path(path) {}

};


struct Directory :Icomp
{
private:
	std::string path_to_direct;
	std::string name;
public:
	std::vector<Icomp*> list;
	Directory(std::string path) : path_to_direct(path) {}
	Directory(std::string path, std::string n) : path_to_direct(path), name(n) {}
	Directory(std::vector<Icomp*> l, std::string p) : list(l), path_to_direct(p) {}


	bool is_not_folder()
	{
		for (char i : name)
		{
			if (i == '.') return false;
		}
		return true;
	}

	void add_comp(Icomp* el)
	{
		list.push_back(el);
	}

	void get_info()
	{
		std::cout << path_to_direct << " " << name << "\n";
	}

	std::string get_path()
	{
		return path_to_direct;
	}

	std::string get_name()
	{
		return name;
	}
};


class file_system
{
	Directory* first;
	Directory* current;
public:
	file_system()
	{
		first = new Directory("/", "");
		current = first;
	}


	std::string find(std::string name, Directory* dir = nullptr)
	{
		if (dir == nullptr) dir = first;
		auto list = dir->list;
		for (auto i : list)
		{
			if (i->get_name() == name)
				return i->get_path() + name;

			if (i->is_not_folder() == false) //isfolder
			{
				Directory* s = new Directory(i->get_path());
				std::string r = find(name, s);
				if (!r.empty()) return r;
			}
		}
		return "";
	}



	void mkdir(std::string name)
	{
		Directory* el = new Directory(name, current->get_path());
		current->add_comp(el);
	}


	std::string pwd(Directory dir)
	{
		return dir.get_path();
	}

	void touch(std::string nameFile)
	{
		File* el = new File(nameFile, current->get_path());
		current->list.push_back(el);
	}

	void ls()
	{
		for (auto i : current->list)
		{
			i->get_info();
		}
	}



	Directory* cd(std::string path)
	{
		Directory* dir = first;
		std::vector <std::string> list_el;
		std::string el;

		path = path.substr(1);
		for (auto i : path)
		{
			if (i != '/')
			{
				el += i;
			}
			else
			{
				list_el.push_back(el);
				el = "";
			}
		}

		list_el.push_back(el);

		for (auto i : list_el)
		{
			for (auto j : dir->list)
			{
				if (j->get_name() == i and j->is_not_folder())
				{
					Directory s(i);
					dir = &s;
					return dir;
				}
			}
		}
		return dir;
	}


};

int main() {
	file_system console;
	console.touch("ASDFG.txt");
	console.ls();
	console.mkdir("ZXC");
	//console.ls();
	std::cout << console.find("ASDFG.txt") << "\n";


	console.cd("/ZXC");
	console.touch("ZXCASDFG.txt");
	std::cout << console.find("ZXCASDFG.txt");
	return 0;
}
