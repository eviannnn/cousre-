#include "Owner.h"
#include "Car.h"

int main()
{
	unsigned num_owners = 0;
	unsigned num_car = 0;
	Owner owner;
	Car car;
	const unsigned Max_Owner = 100;
	const unsigned Max_Car = 100;
	Owner owners[Max_Owner];
	Car cars[Max_Car];
	unsigned choice{0};
	while (true)
	{
		cout << "==================== Menu ===================\n";
		cout << "1.  Create owner\n";
		cout << "2.  Create car\n";
		cout << "3.  Delete owner\n";
		cout << "4.  Delete car\n";
		cout << "5.  print owners\n";
		cout << "6.  print cars\n";
		cout << "7.  Set car to owner\n";
		cout << "8.  Remove car from owner\n";
		cout << "9.  sort owners ascending\n";
		cout << "10. sort owners descending\n";
		cout << "11. sort cars ascending\n";
		cout << "12. sort cars descending\n";
		cout << "13. filter cars by name\n";
		cout << "14. Write to file\n";
		cout << "15. Read from a file\n";
		cout << "16. Exit\n";
		cout << "============================================\n";
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice)
		{
		case 1:
			owner.create_owners(owners, num_owners, Max_Owner);
			break;
		case 2:
			car.create_cars(cars, num_car, Max_Car);
			break;
		case 3:
			if (num_owners == 0)
			{
				cout << "Firstly you should create owner.\n";
				break;
			}
			owner.delete_owners(owners, num_owners, Max_Owner);
			break;
		case 4:
			if (num_car == 0)
			{
				cout << "Firstly you should create car.\n";
				break;
			}
			car.delete_cars(cars, num_car, Max_Car);
			break;
		case 5:
			if (num_owners == 0)
			{
				cout << "Firstly you should create owner.\n";
				break;
			}
			owner.print_owners(owners, num_owners);
			break;
		case 6:
			if (num_car == 0)
			{
				cout << "Firstly you should create car.\n";
				break;
			}
			car.print_cars(cars, num_car);
			break;
		case 7:
		{
			if (num_owners == 0 || num_car == 0)
			{
				cout << "Firstly you should create a owner/car.\n";
				break;
			}
			unsigned _owner_id = owner.choose_Owner_id(owners, num_owners, Max_Owner);
			if (_owner_id == 0)
			{
				continue;
			}
			car.set_car_to_owner(cars, num_car, _owner_id, Max_Car);
			unsigned car_count = car.calculate_car_counts(cars, num_car, _owner_id);
			owner.update_car_count(owners, num_owners, _owner_id, car_count);
			break;
		}
		case 8:
		{
			if (num_owners == 0 || num_car == 0)
			{
				cout << "Firstly, you should create an owner/car.\n";
				break;
			}
			unsigned _owner_id = owner.choose_Owner_id(owners, num_owners, Max_Owner);
			if (_owner_id == 0)
			{
				continue;
			}
			car.remove_car_from_owner(cars, num_car, _owner_id);
			unsigned car_count = car.calculate_car_counts(cars, num_car, _owner_id);
			owner.update_car_count(owners, num_owners, _owner_id, car_count);
			break;
		}
		case 9:
			if (num_owners < 2)
			{
				cout << "You should have at least 2 owners to sort\n";
				break;
			}
			owner.sort_owners_ascend(owners, num_owners);
			break;
		case 10:
			if (num_owners < 2)
			{
				cout << "You should have at least 2 owners to sort\n";
				break;
			}
			owner.sort_owners_descend(owners, num_owners);
			break;
		case 11:
			if (num_car < 2)
			{
				cout << "You should have at least 2 cars to sort\n";
				break;
			}
			car.sort_cars_ascend(cars, num_car);
			break;
		case 12:
			if (num_car < 2)
			{
				cout << "You should have at least 2 cars to sort\n";
				break;
			}
			car.sort_cars_descend(cars, num_car);
			break;
		case 13:
			if (num_car == 0)
			{
				cout << "Firstly you should create car.\n";
				break;
			}
			car.filter_cars_by_name(cars, num_car, "");
			break;
		case 14:
			if (num_owners == 0 && num_car == 0)
			{
				cout << "Firstly you should create owner/car.\n";
				break;
			}
			owner.write_owners_to_file(owners, num_owners);
			car.write_Car_to_file(cars, num_car);
			break;
		case 15:
			owner.read_owners_from_file(owners, num_owners);
			car.read_Car_to_file(cars, num_car);
			break;
		case 16:
			return 0;
		default:
			cout << "You have entered an invalid choice!\n";
			break;
		}
	}
}
