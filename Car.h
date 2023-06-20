#pragma once
#include "Libraries.h"

struct Car
{
private:
	unsigned car_id = 0, owner_id = 0;
	string car_name;
	static const unsigned Max_cars = 100;
public:
	//getters
	unsigned get_car_id();

	//func for creating deleting and printing deps
	void create_cars(Car* cars, unsigned& num_car, const unsigned Max_cars);
	void delete_cars(Car* cars, unsigned& num_car, unsigned Max_cars);
	void print_cars(Car* cars, unsigned num_car);

	//func for choosing a dep
	unsigned choose_Car(Car* cars, unsigned& num_car, const unsigned Max_cars);
	unsigned choose_Car_id(Car* cars, unsigned& num_car, const unsigned Max_cars);

	//func for setting and removing deps
	void set_car_to_owner(Car* cars, unsigned num_car, unsigned owner_id, unsigned Max_cars);
	void remove_car_from_owner(Car* cars, unsigned num_car, unsigned owner_id);

	void filter_cars_by_name(Car* cars, unsigned num_car, string _car_name);

	//func for sort 
	void sort_cars_ascend(Car* cars, unsigned num_car);
	void sort_cars_descend(Car* cars, unsigned num_car);

	//functiuons to calculate Car count for Owner
	unsigned calculate_car_counts(Car* cars,unsigned num_car, unsigned _owner_id);
	
	//read and write to file
	void write_Car_to_file(Car* cars, unsigned num_car);
	void read_Car_to_file(Car* cars, unsigned& num_car);
};

