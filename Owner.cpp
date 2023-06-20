#include "Owner.h"
#include <algorithm>
#include <fstream>

// func for creating, deleting and printing owners
void Owner::create_owners(Owner *owners, unsigned &num_owners, const unsigned Max_owners)
{
	if (num_owners >= Max_owners)
	{
		std::cout << "Maximum number of owners reached." << std::endl;
		return;
	}
	try
	{
		std::cout << "Enter Owner id: ";
		if (std::cin >> owners[num_owners].owner_id)
		{
		}
		else
		{
			throw std::runtime_error("Error, incorrect id input!\n");
		}
		std::cout << "Enter Owner name: ";
		std::cin >> owners[num_owners].owner_name;
		owners[num_owners].num_cars = 0;
		num_owners++;
	}
	catch (std::exception &e)
	{
		std::cerr << "Exception caught " << e.what();
		exit(1);
	}
}

void Owner::delete_owners(Owner *owners, unsigned &num_owners, unsigned Max_owners)
{
	unsigned com_num{0};
	com_num = choose_Owner(owners, num_owners, Max_owners);
	if (owners[com_num - 1].num_cars != 0)
	{
		std::cout << "\nFirstly you should remove all cars.\n\n";
	}
	else
	{
		owners[com_num - 1].owner_id = 0;
		owners[com_num - 1].owner_name = "";
		owners[com_num - 1].num_cars = 0;
		num_owners--;
	}
}

void Owner::print_owners(const Owner *owners, unsigned num_owners) const
{
	unsigned count{0};
	for (unsigned i{0}; i < num_owners; i++)
	{
		count++;
		std::cout << std::endl
				  << count << " Owner\n\n"
				  << "Id: " << owners[i].owner_id << "\nName: " << owners[i].owner_name
				  << "\nNumber of cars: " << owners[i].num_cars << std::endl;
	}
}

// func for choosing one Owner by name and id
unsigned Owner::choose_Owner(Owner *owners, unsigned &num_owners, const unsigned Max_owners)
{
	unsigned com_num;
	print_owners(owners, num_owners);
	std::cout << "Enter Owner number you wanna choose(Enter \"0\" if you want to return back): ";
	try
	{
		std::cin >> com_num;
		if (com_num <= num_owners)
		{
			return com_num;
		}
		else if (com_num == 0)
		{
			std::cout << "Returning back to a main menu.\n";
			return 0;
		}
		else
		{
			throw std::runtime_error("Error, com_num cannot exceed the given number of owners!\n");
		}
	}
	catch (std::exception &e)
	{
		std::cout << "Exception caught: " << e.what();
		exit(1);
	}
}

unsigned Owner::choose_Owner_id(Owner *owners, unsigned &num_owners, const unsigned Max_owners)
{
	unsigned com_num;
	print_owners(owners, num_owners);
	std::cout << "Enter Owner number you wanna choose(Enter \"0\" if you want to return back): ";
	try
	{
		std::cin >> com_num;
		if (com_num > 0 && com_num <= num_owners)
		{
			return owners[com_num - 1].owner_id;
		}
		else if (com_num == 0)
		{
			return 0;
		}
		else
		{
			throw std::runtime_error("Error, com_num cannot exceed the given number of owners!\n");
		}
	}
	catch (std::exception &e)
	{
		std::cout << "Exception caught: " << e.what();
		exit(1);
	}
}

// func for sorting owners ascend
void Owner::sort_owners_ascend(Owner *owners, unsigned num_owners)
{
	std::sort(owners, owners + num_owners, [](const Owner &a, const Owner &b)
			  { return a.owner_name < b.owner_name; });
	print_owners(owners, num_owners);
}

// func for sorting owners descend
void Owner::sort_owners_descend(Owner *owners, unsigned num_owners)
{
	std::sort(owners, owners + num_owners, [](const Owner &a, const Owner &b)
			  { return a.owner_name > b.owner_name; });
	print_owners(owners, num_owners);
}

void Owner::update_car_count(Owner *owners, unsigned num_owners, unsigned _owner_id, unsigned car_count)
{
	for (unsigned i{0}; i < num_owners; i++)
	{
		if (owners[i].owner_id == _owner_id)
		{
			owners[i].num_cars = car_count;
		}
	}
}

// read and write to file
void Owner::write_owners_to_file(Owner *owners, unsigned num_owners)
{
	std::string fn{"file_owners.bin"};
	std::ofstream ofs{fn, std::ios::binary};
	if (!ofs.is_open())
	{
		std::cerr << "\nError, cannot write to a file!";
		exit(1);
	}
	for (unsigned i{0}; i < num_owners; i++)
	{
		ofs.write(reinterpret_cast<const char *>(&owners[i].owner_id), sizeof(owners[i].owner_id));
		size_t owner_name_size = owners[i].owner_name.size();
		ofs.write(reinterpret_cast<const char *>(&owner_name_size), sizeof(owner_name_size));
		ofs.write(owners[i].owner_name.c_str(), owner_name_size);
		ofs.write(reinterpret_cast<const char *>(&owners[i].num_cars), sizeof(owners[i].num_cars));
	}
	ofs.close();
	std::cout << "\nOwners were successfully written to a file.\n";
}

void Owner::read_owners_from_file(Owner *owners, unsigned &num_owners)
{
	for (unsigned i{0}; i < num_owners; i++)
	{
		owners[i].owner_id = 0;
		owners[i].owner_name = "";
		owners[i].num_cars = 0;
	}
	num_owners = 0;
	std::string fn{"file_owners.bin"};
	std::ifstream ifs{fn, std::ios::binary};
	if (!ifs.is_open())
	{
		std::cerr << "\nError, cannot read a file!";
		exit(1);
	}
	while (ifs.peek() != EOF)
	{
		ifs.read(reinterpret_cast<char *>(&owners[num_owners].owner_id), sizeof(owners[num_owners].owner_id));
		size_t owner_name_size;
		ifs.read(reinterpret_cast<char *>(&owner_name_size), sizeof(owner_name_size));
		std::string _owner_name(owner_name_size, '\0');
		ifs.read(&_owner_name[0], owner_name_size);
		owners[num_owners].owner_name = std::move(_owner_name);
		ifs.read(reinterpret_cast<char *>(&owners[num_owners].num_cars), sizeof(owners[num_owners].num_cars));
		num_owners++;
	}
	ifs.close();
	std::cout << "\nOwners were successfully read.\n";
}
