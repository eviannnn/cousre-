#include "Car.h"


//getters
unsigned Car::get_car_id() { return car_id; }

//func for creating deleting and printing deps
void Car::print_cars(Car* cars, unsigned num_car)
{
	unsigned count{ 0 };
	for (unsigned i{ 0 }; i < num_car; i++)
	{
		count++;
		cout << endl << count << " Car\n\n" << "Name: " << cars[i].car_name << "\nId: " << cars[i].car_id << "\nOwner id: "
			<< cars[i].owner_id << endl;
	}
}
void Car::create_cars(Car* cars, unsigned& num_car, const unsigned Max_cars)
{
	Car Car{};
	if (num_car >= Max_cars) {
		cout << "Maximum number of cars reached." << endl;
		return;
	}
	try
	{
		cout << "Enter Car ID: ";
		if (cin >> cars[num_car].car_id) {}
		else
		{
			throw runtime_error("Error, incorrect id input!\n");
		}
		cout << "Enter Car name: ";
		cin >> cars[num_car].car_name;
		num_car++;
	}
	catch (exception& e)
	{
		cerr << "Exception caught " << e.what();
		exit(1);
	}
}
void Car::delete_cars(Car* cars, unsigned& num_car, unsigned Max_cars)
{
	unsigned dep_num{ 0 };
	dep_num = choose_Car(cars, num_car, Max_cars);
	if (cars[dep_num - 1].owner_id != 0)
	{
		cout << "\nFirstly you should remove Car from Owner.\n\n";
	}
	else
	{
		cars[dep_num - 1].owner_id = 0;
		cars[dep_num - 1].car_name = "";
		cars[dep_num - 1].car_id = 0;
		num_car--;
	}
}


//func for choosing a dep
unsigned Car::choose_Car(Car* cars, unsigned& num_car, const unsigned Max_cars)
{
	unsigned dep_num;
	print_cars(cars, num_car);
	cout << "Enter Car number you wanna choose(Enter \"0\" if you want to return back): ";
	try
	{
		cin >> dep_num;
		if (dep_num <= num_car)
		{
			return dep_num;
		}
		else if (dep_num < 0)
		{
			throw runtime_error("Error, dep_num cannot be less than zero!\n");
		}
		else if (dep_num == 0)
		{
			cout << "Returning back to a main menu.\n";
			return 0;
		}
		else
		{
			throw runtime_error("Error, dep_num cannot exceed the given number of cars!\n");
		}
	}
	catch (exception& e)
	{
		cout << "Exception caught: " << e.what();
		exit(1);
	}
}
unsigned Car::choose_Car_id(Car* cars, unsigned& num_car, const unsigned Max_cars)
{
	unsigned dep_num;
	print_cars(cars, num_car);
	cout << "Enter Car number you wanna choose(Enter \"0\" if you want to return back): ";
	try
	{
		cin >> dep_num;
		if (dep_num > 0 && dep_num <= num_car)
		{
			return cars[dep_num - 1].owner_id;
		}
		else if (dep_num < 0)
		{
			throw runtime_error("Error, dep_num cannot be less than zero!\n");
		}
		else if (dep_num == 0)
		{
			return 0;
		}
		else
		{
			throw runtime_error("Error, dep_num cannot exceed the given number of cars!\n");
		}
	}
	catch (exception& e)
	{
		cout << "Exception caught: " << e.what();
		exit(1);
	}
}


//func for setting and removing deps
void Car::set_car_to_owner(Car* cars, unsigned num_car, unsigned _owner_id, unsigned Max_cars)
{
	unsigned long car_num = choose_Car(cars, num_car, Max_cars);
	if (car_num != 0)
	{
		cars[car_num - 1].owner_id = _owner_id;
	}
}
void Car::remove_car_from_owner(Car* cars, unsigned num_car, unsigned _owner_id)
{
	unsigned num_filt_car = 0;
	//filter function
	Car filtered_cars[Max_cars];
	for (unsigned i{ 0 }; i < num_car; i++)
	{
		if (cars[i].owner_id == _owner_id)
		{
			filtered_cars[num_filt_car].car_id = cars[i].car_id;
			filtered_cars[num_filt_car].owner_id = cars[i].owner_id;
			filtered_cars[num_filt_car].car_name = cars[i].car_name;
			num_filt_car++;
		}
	}
	if (num_filt_car == 0)
	{
		cout << "\nNo cars to remove\n\n";
	}
	else
	{
		unsigned dep_num = choose_Car(filtered_cars,num_car, Max_cars);
		if (dep_num != 0)
		{
			unsigned car_id_to_remove = filtered_cars[dep_num - 1].car_id;
			for (unsigned i{ 0 }; i < num_car; i++)
			{
				if (cars[i].car_id == car_id_to_remove)
				{
					cars[i].owner_id = 0;
				}
			}
		}
	}
}


void Car::filter_cars_by_name(Car* cars, unsigned num_car, string _car_name)
{
	unsigned num_filt_car = 0;
	Car filtered_cars[Max_cars];
	for (unsigned i{ 0 }; i < num_car; i++)
	{
		if (cars[i].car_name == _car_name)
		{
			filtered_cars[num_filt_car].car_id = cars[i].car_id;
			filtered_cars[num_filt_car].owner_id = cars[i].owner_id;
			filtered_cars[num_filt_car].car_name = cars[i].car_name;
			num_filt_car++;
		}
	}
	if (num_filt_car == 0)
	{
		cout << "\nNo such cars exist\n\n";
		}
	else
	{
		cout << "Filtered cars are: ";
		print_cars(filtered_cars, num_filt_car);
	}
}


//func for sort
void Car::sort_cars_ascend(Car* cars, unsigned num_car)
{
	sort(cars, cars + num_car, [](const Car& a, const Car& b)
		{
			return a.car_name < b.car_name;
		});
	print_cars(cars, num_car);
}
void Car::sort_cars_descend(Car* cars, unsigned num_car)
{
	sort(cars, cars + num_car, [](const Car& a, const Car& b)
		{
			return a.car_name > b.car_name;
		});
	print_cars(cars, num_car);
}


//functiuons to calculate Car count for Owner
unsigned Car::calculate_car_counts(Car* cars, unsigned num_car, unsigned _owner_id)
{
	unsigned car_count = 0;
	for (unsigned i{ 0 }; i < num_car; i++)
	{
		if (cars[i].owner_id == _owner_id)
		{
			car_count++;
		}
	}
	return car_count;
}


//read and write to file
void Car::write_Car_to_file(Car* cars, unsigned num_car)
{
	string fn{ "file_cars.bin" };
	ofstream ofs{ fn, ios::binary };
	if (!ofs.is_open())
	{
		cerr << "\nError, cannot write to a file!";
		exit(1);
	}
	for (unsigned i{ 0 }; i < num_car; i++)
	{
		ofs.write(reinterpret_cast<const char*>(&cars[i].car_id), sizeof(cars[i].car_id));
		size_t car_name_size = cars[i].car_name.size();
		ofs.write(reinterpret_cast<const char*>(&car_name_size), sizeof(car_name_size));
		ofs.write(cars[i].car_name.c_str(), car_name_size);
		ofs.write(reinterpret_cast<const char*>(&cars[i].owner_id), sizeof(cars[i].owner_id));
	}
	ofs.close();
	cout << "\ncars were successfully written to a file.\n";
}
void Car::read_Car_to_file(Car* cars, unsigned& num_car)
{
	for (unsigned i{ 0 }; i < num_car; i++)
	{
		cars[i].owner_id = 0;
		cars[i].car_name = "";
		cars[i].car_id = 0;
	}
	num_car = 0;
	Car car{};
	string fn{ "file_cars.bin" };
	ifstream ifs{ fn, ios::binary };
	if (!ifs.is_open())
	{
		cerr << "\nError, cannot read a file!";
		exit(1);
	}
	while (ifs.peek() != EOF)
	{
		ifs.read(reinterpret_cast<char*>(&car.car_id), sizeof(car.car_id));
		cars[num_car].car_id = car.car_id;
		size_t car_name_size;
		ifs.read(reinterpret_cast<char*>(&car_name_size), sizeof(car_name_size));
		string _car_name(car_name_size, '\0');
		ifs.read(&_car_name[0], car_name_size);
		car.car_name = move(_car_name);
		cars[num_car].car_name = car.car_name;
		ifs.read(reinterpret_cast<char*>(&car.owner_id), sizeof(car.owner_id));
		cars[num_car].owner_id = car.owner_id;
		num_car++;
	}
	ifs.close();
	cout << "\ncars were successfully read.\n";
}