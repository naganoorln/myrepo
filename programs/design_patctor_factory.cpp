#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
using namespace std;

// Abstarct Vehicle base class
class Vehicle
{
public:
	virtual ~Vehicle() = default;
	// Pure virtual functions
	virtual void start() const = 0;
	virtual string getType() const = 0;
	virtual void stop() const = 0;
};
class Car : public Vehicle
{
public:
	void start() const
	{
		cout << "Car is starting." << endl;
	}
	string getType() const
	{
		return "Car";
	}
	void stop() const
	{
		cout << "Car is stopping." << endl;
	}
};
class Bike : public Vehicle
{
public:
	void start() const
	{
		cout << "Bike is starting." << endl;
	}
	string getType() const
	{
		return "Bike";
	}
	void stop() const
	{
		cout << "Bike is stopping." << endl;
	}
};
// Vehicle Factory class
class VehicleFactory
{
public:
	enum VehicleType
	{
		CAR,
		BIKE,
		UNKNOWN
	};
	static unique_ptr<Vehicle> createVehicle(VehicleType type)
	{
		switch(type)
		{
		case CAR:
			return make_unique<Car>();
		case BIKE:
			return make_unique<Bike>();
		default:
			throw
			invalid_argument("Invalid vehicle type.");
		}
	}
};
int main()
{
	try
	{
		int input;
		cout << "Enter Vehicle Type." << endl;
		cout << "0 for Car" << endl;
		cout << "1 for Bike" << endl;
		cin >> input;
		VehicleFactory::VehicleType type = static_cast<VehicleFactory::VehicleType>(input);
		auto vehicle = VehicleFactory::createVehicle(type);
		vehicle->start();
		cout << "Vehicle Type: " << vehicle->getType() << endl;
		vehicle->stop();
	} catch(invalid_argument& e)
	{
		cerr << "Caught Invalid argument: " << e.what() << endl;
	} catch(exception& e)
	{
		cerr << "Caught Exception" << e.what() << endl;
	}
	return 0;
}
