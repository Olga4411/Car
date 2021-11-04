#include<iostream>
#include<conio.h>
using namespace std;
const unsigned int DEFAULT_TANK_VOLUME = 60;
const unsigned int MIN_FUEL_LEVEL = 5;
const unsigned int DEFAULT_ENGINE_CONSUMPTION = 8;

class Tank
{
	//Топливный бак
	const unsigned int VOLUME;// объем бака
	double fuel_level;// уровень топлива
	unsigned int min_level;
public:
	unsigned int get_volume()const
	{
		return VOLUME;
	}
	double get_fuel_level()const
	{
		return fuel_level;
	}
	unsigned int get_min_level()const
	{
		return min_level;
	}
	void set_fuel_level(double fuel)
	{
		if (fuel < 0)return;
		if (this->fuel_level + fuel < VOLUME)
			fuel_level += fuel;
		else
			fuel_level = VOLUME;
	}
	//void fill(double amount)
	//{
	//	//amount-количество топлива
	//	if (amount <0)return;
	//	if (fuel_level + amount < VOLUME)fuel_level += amount;
	//	else fuel_level = VOLUME;

	//}
	//double give_fuel(double amount)
	//{
	//	if (fuel_level - amount > 0)fuel_level -= amount;
	//	else fuel_level = 0;
	//	return fuel_level;
	//}
	/*Tank(const unsigned int VOLUME):VOLUME(VOLUME>=20 && VOLUME<=80?VOLUME:DEFAULT_TANK_VOLUME),fuel_level(0)
	{
		cout << "Tank is ready:\t"<<this<<endl;
	}*/
	explicit Tank(int volume) :VOLUME(volume >= 40 && volume <= 120 ? volume : DEFAULT_TANK_VOLUME)
	{
		/*if (volume >= 40 && volume <= 120)
			this->volume = volume;
		else
			this->volume = 60;*/
			//this->VOLUME = volume >= 40 && volume <= 120 ? volume : DEFAULT_TANK_VOLUME;
		fuel_level = 0;
		min_level = MIN_FUEL_LEVEL;
		cout << "TankReady:\t" << this << endl;
	}
	~Tank()
	{
		cout << "Tank is over:\t" << this << endl;
	}
	double give_fuel(double amount)
	{
		fuel_level -= amount;
		if (fuel_level < 0)fuel_level = 0;
		return fuel_level;
	}
	/*void info()const
	{
		cout << "Tank volume:" << VOLUME << " liters\n";
		cout << "Fuel level:" << fuel_level << " liters\n";
	}*/
	void info()const
	{
		cout << "Volume:\t" << VOLUME << endl;
		cout << "Fuel:\t";
		if (fuel_level < 10)cout << 0;
		cout << fuel_level << endl;
		cout << "MinFuel:";
		if (min_level < 10)cout << 0;
		cout << min_level << endl;
	}
};

class Engine//двигатель
{
	//engine properties
	unsigned int VOLUME;
	unsigned int POWER;// мощность
	double consumption;// расход топлива liters per 100 km
	double consumption_per_second;//liters per seccond

	//Engine state:
	bool started;
public:
	double get_consumption()const
	{
		return consumption;
	}
	double get_consumption_per_second()const
	{
		return consumption_per_second;
	}
	explicit Engine(double consumption)
	{
		/*if (consumption >= 4 && consumption <= 25)
			this->consumption = consumption;
		else
			consumption = 8;*/
		this->consumption = consumption >= 4 && consumption <= 25 ? consumption : DEFAULT_ENGINE_CONSUMPTION;
		this->consumption_per_second = consumption * 5e-5;
		started = false;
		cout << "EngineReady:\t" << this << endl;
	}
	~Engine()
	{
		cout << "EngineIsOver:\t" << this << endl;
	}


	bool is_started()
	{
		return started;
	}
	void start()
	{
		started = true;
	}
	void stop()
	{
		started = false;
	}
	void info()
	{
		cout << "Consumption:\t" << consumption << endl;
		cout << "ConsumptionPerSec:\t" << consumption_per_second << endl;
	}
};

class Car
{
	Engine engine;
	Tank tank;
	const unsigned int MAX_SPEED;
	unsigned int speed;
	bool driver;
public:
	/*Car(const Engine& engine,const Tank& tank):engine(engine),tank(tank)
	{
		cout << "CarISReady:\t" << this << endl;
	}*/
	Car(double consumption, unsigned int volume,unsigned int MAX_SPEED):
		engine(consumption),tank(volume),MAX_SPEED(MAX_SPEED>=90 && MAX_SPEED<=400?MAX_SPEED:250),speed(0)
	{
		driver = false;
		cout << "CarISReady:\t" << this << endl;
	}
	~Car()
	{
		cout << "CarIsOver:\t" << this << endl;
	}
	void get_in()
	{
		driver = true;
	}
	void get_out()
	{
		driver = false;
	}
	bool is_driver_inside()const
	{
		return driver;
	}
	void fill(unsigned int fuel)
	{
		tank.set_fuel_level(fuel);
	}
	void display()
	{
		cout<<"Engine is" << (engine.is_started() ? "Started" : "Stopped") << endl;
		cout << "Fuel_level:\t" << tank.get_fuel_level() << endl;
		if (tank.get_fuel_level() < tank.get_min_level())cout << "LOW FUEL" << endl;
		cout << "Speed:" << speed << "\t";
		cout << "MAX_SPEED:" << endl;
	}
	void info()
	{
		cout << "Engine:\n"; engine.info();
		cout << "Tank:\n"; tank.info();
		cout << "Engine is:" << (engine.is_started() ? "Started" : "Stopped") << endl;
		cout << "Speed:\t" << speed << "km/h\n";
		cout << "MAX_SPEED:\t" << MAX_SPEED << "km/h\n";
	}
};

//#define TANK_CHECK
//#define ENGINE_CHECK
#define Escape 27
#define Enter 13
void main()
{
	setlocale(LC_ALL, "Russian");
#ifdef TANK_CHECK
	Tank tank(11);
	tank.info();
	tank.fill(3);
	tank.info();
	tank.fill(30);
	tank.info();
	tank.fill(30);
	tank.info();
#endif // TANK_CHECK

#ifdef ENGINE_CHECK
	Engine engine(20);
	engine.info();

#endif // ENGINE_CHECK

	//Car car(Engine(10),Tank(80));
	Car car(10, 50,250);
	//car.info();

	cout << "Press Enter to get in" << endl;
	cout << "Press F to fill the car" << endl;
	char key;
	do
	{
		key=_getch();
		switch (key)
		{
		case'F':
		case'f':
			unsigned int fuel;
			cout << "Введите объем топлива:"; cin >> fuel; cout << endl;
			car.fill(fuel);
			break;
		case Enter:car.get_in(); break;
		case Escape:cout << "Get out" << endl; break;
		}
		if(car.is_driver_inside())car.display();
	} while (key != 27);
}