#pragma once
#include "Libraries.h"

struct Owner
{
private:
	unsigned owner_id = 0, num_car = 0;
	string owner_name = "";
public:
	//func for creating, deleting and printing owners
	void create_owners(Owner* owners, unsigned& num_owners, const unsigned Max_owners);
	void delete_owners(Owner* owners, unsigned& num_owners, unsigned Max_owners);
	void print_owners(Owner* owners, unsigned num_owners);

	//func for choosing one Owner by name and id
	unsigned choose_Owner(Owner* owners, unsigned& num_owners, const unsigned Max_owners);
	unsigned choose_Owner_id(Owner* owners, unsigned& num_owners, const unsigned Max_owners);

	//func for sorting
	void sort_owners_ascend(Owner*owners, unsigned num_owners);
	void sort_owners_descend(Owner* owners, unsigned num_owners);

	//func for setting number of cars to Owner
	void update_car_count(Owner* owners, unsigned num_owners, unsigned _owner_id, unsigned car_count);

	//read and write to file
	void write_Owner_to_file(Owner* owners, unsigned num_owners);
	void read_Owner_to_file(Owner* owners, unsigned &num_owners);
};
