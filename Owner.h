#pragma once
#include <iostream>
#include <string>

struct Owner
{
	unsigned int owner_id;
	std::string owner_name;
	unsigned int num_cars;

	Owner() : owner_id(0), owner_name(""), num_cars(0) {}

	Owner(unsigned int id, std::string name, unsigned int cars)
		: owner_id(id), owner_name(name), num_cars(cars) {}

	void create_owners(Owner *owners, unsigned &num_owners, const unsigned Max_owners);
	void delete_owners(Owner *owners, unsigned &num_owners, unsigned Max_owners);
	void print_owners(const Owner *owners, unsigned num_owners) const;
	unsigned choose_Owner(Owner *owners, unsigned &num_owners, const unsigned Max_owners);
	unsigned choose_Owner_id(Owner *owners, unsigned &num_owners, const unsigned Max_owners);
	void sort_owners_ascend(Owner *owners, unsigned num_owners);
	void sort_owners_descend(Owner *owners, unsigned num_owners);
	void update_car_count(Owner *owners, unsigned num_owners, unsigned _owner_id, unsigned car_count);
	void write_owners_to_file(Owner *owners, unsigned num_owners);
	void read_owners_from_file(Owner *owners, unsigned &num_owners);
};
