#include "Owner.h"

//func for creating, delelting and printing owners
void Owner::create_owners(Owner* owners, unsigned& num_owners, const unsigned Max_owners)
{
	Owner Owner{};
	if (num_owners >= Max_owners) {
		std::cout << "Maximum number of owners reached." << endl;
		return;
	}
	try {
		cout << "Enter Owner id: ";
		if (cin >> owners[num_owners].owner_id) {}
		else
		{
			throw runtime_error("Error, incorrect id input!\n");

		}
		cout << "Enter Owner name: ";
		cin >> owners[num_owners].owner_name;
		num_owners++;
	}
	catch (exception& e)
	{
		cerr << "Exception caught " << e.what();
		exit(1);
	}
}
void Owner::delete_owners(Owner*owners, unsigned& num_owners, unsigned Max_owners)
{
	unsigned com_num{ 0 };
	com_num = choose_Owner(owners, num_owners, Max_owners);
	if (owners[com_num - 1].num_car != 0)
	{
		cout << "\nFirstly you should remove all cars.\n\n";
	}
	else
	{
		owners[com_num-1].owner_id = 0;
		owners[com_num - 1].owner_name = "";
		owners[com_num - 1].num_car = 0;
		num_owners--;
	}
}
void Owner::print_owners(Owner* owners, unsigned num_owners)
{
	unsigned count{ 0 };
	for (unsigned i{ 0 }; i < num_owners; i++)
	{
		count++;
		cout << endl << count << " Owner\n\n" << "Id:" << owners[i].owner_id << "\nName: " << owners[i].owner_name
			<< "\nNumber of cars: " << owners[i].num_car << endl;
	}
}


//func for choosing one Owner by name and id
unsigned Owner::choose_Owner(Owner* owners, unsigned& num_owners, const unsigned Max_owners)
{
	unsigned com_num;
	print_owners(owners, num_owners);
	cout << "Enter Owner number you wanna choose(Enter \"0\" if you want to return back): ";
	try
	{
		cin >> com_num;
		if (com_num <= num_owners)
		{
			return com_num;
		}
		else if (com_num < 0)
		{
			throw runtime_error("Error, com_num cannot be less than zero!\n");
		}
		else if (com_num == 0)
		{
			cout << "Returning back to a main menu.\n";
			return 0;
		}
		else
		{
			throw runtime_error("Error, com_num cannot exceed the given number of owners!\n");
		}
	}
	catch (exception& e)
	{
		cout << "Exception caught: " << e.what();
		exit(1);
	}
}
unsigned Owner::choose_Owner_id(Owner* owners, unsigned& num_owners, const unsigned Max_owners)
{
	unsigned com_num;
	print_owners(owners, num_owners);
	cout << "Enter Owner number you wanna choose(Enter \"0\" if you want to return back): ";
	try
	{
		cin >> com_num;
		if (com_num > 0 && com_num <= num_owners)
		{
			return owners[com_num - 1].owner_id;
		}
		else if (com_num < 0)
		{
			throw runtime_error("Error, com_num cannot be less than zero!\n");
		}
		else if (com_num == 0)
		{
			return 0;
		}
		else
		{
			throw runtime_error("Error, com_num cannot exceed the given number of owners!\n");
		}
	}
	catch (exception& e)
	{
		cout << "Exception caught: " << e.what();
		exit(1);
	}
}


//func for sorting owners
void Owner::sort_owners_ascend(Owner* owners, unsigned num_owners)
{
	sort(owners, owners + num_owners, [](const Owner& a, const Owner& b)
		{
			return a.owner_name < b.owner_name;
		});
	print_owners(owners, num_owners);
}

void Owner::sort_owners_descend(Owner* owners, unsigned num_owners)
{
	sort(owners, owners + num_owners, [](const Owner& a, const Owner& b)
		{
			return a.owner_name > b.owner_name;
		});
	print_owners(owners, num_owners);
}


//func for setting number of members and cars to Owner
void Owner::update_dep_count(Owner* owners, unsigned num_owners, unsigned _owner_id, unsigned dep_count)
{
	for (unsigned i{ 0 }; i < num_owners; i++)
	{
		if (owners[i].owner_id == _owner_id)
		{
			owners[i].num_car = dep_count;
		}
	}
}


//read and write to file
void Owner::write_Owner_to_file(Owner* owners, unsigned num_owners)
{
	string fn{ "file_owners.bin" };
	ofstream ofs{ fn, ios::binary };
	if (!ofs.is_open())
	{
		cerr << "\nError, cannot write to a file!";
		exit(1);
	}
	for (unsigned i{ 0 }; i < num_owners; i++)
	{
		ofs.write(reinterpret_cast<const char*>(&owners[i].owner_id), sizeof(owners[i].owner_id));
		size_t owner_name_size = owners[i].owner_name.size();
		ofs.write(reinterpret_cast<const char*>(&owner_name_size), sizeof(owner_name_size));
		ofs.write(owners[i].owner_name.c_str(), owner_name_size);
		ofs.write(reinterpret_cast<const char*>(&owners[i].num_car), sizeof(owners[i].num_car));
	}
	ofs.close();
	cout << "\nowners were successfully written to a file.\n";
}

void Owner::read_Owner_to_file(Owner* owners, unsigned& num_owners)
{
	for (unsigned i{ 0 }; i < num_owners; i++)
	{
		owners[i].owner_id = 0;
		owners[i].owner_name = "";
		owners[i].num_car = 0;
	}
	num_owners = 0;
	Owner Owner{};
	string fn{ "file_owners.bin" };
	ifstream ifs{ fn, ios::binary };
	if (!ifs.is_open())
	{
		cerr << "\nError, cannot read a file!";
		exit(1);
	}
	while (ifs.peek() != EOF)
	{
		ifs.read(reinterpret_cast<char*>(&Owner.owner_id), sizeof(Owner.owner_id));
		owners[num_owners].owner_id = Owner.owner_id;
		size_t owner_name_size;
		ifs.read(reinterpret_cast<char*>(&owner_name_size), sizeof(owner_name_size));
		string _owner_name(owner_name_size, '\0');
		ifs.read(&_owner_name[0], owner_name_size);
		Owner.owner_name = move(_owner_name);
		owners[num_owners].owner_name = Owner.owner_name;
		ifs.read(reinterpret_cast<char*>(&Owner.num_car), sizeof(Owner.num_car));
		owners[num_owners].num_car = num_car;
		num_owners++;
	}
	ifs.close();
	cout << "\nowners were successfully read.\n";
}
