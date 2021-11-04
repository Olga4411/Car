#include<iostream>
using namespace std;
const unsigned int DEFAULT_TANK_VOLUME = 60;
const unsigned int DEFAULT_ENGINE_CONSUMPTION = 8;

class Tank
{
	//Топливный бак
	const unsigned int VOLUME;// объем бака
	double fuel_level;// уровень топлива
public:
	unsigned int get_volume()const
	{
		return VOLUME;
	}
	double get_fuel_level()const
	{
		return fuel_level;
	}
	void fill(double amount)
	{
		//amount-количество топлива
		if (amount <0)return;
		if (fuel_level + amount < VOLUME)fuel_level += amount;
		else fuel_level = VOLUME;

	}
	double give_fuel(double amount)
	{
		if (fuel_level - amount > 0)fuel_level -= amount;
		else fuel_level = 0;
		return fuel_level;
	}
	Tank(const unsigned int VOLUME):VOLUME(VOLUME>=20 && VOLUME<=80?VOLUME:DEFAULT_TANK_VOLUME),fuel_level(0)
	{
		cout << "Tank is ready:\t"<<this<<endl;
	}
	~Tank()
	{
		cout << "Tank is over:\t" << this << endl;
	}
	void info()const
	{
		cout << "Tank volume:" << VOLUME << " liters\n";
		cout << "Fuel level:" << fuel_level << " liters\n";
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
	Engine( double consumption)
	{
		/*if (consumption >= 4 && consumption <= 25)
			this->consumption = consumption;
		else
			consumption = 8;*/
		this->consumption = consumption >= 4 && consumption <= 25 ? consumption : DEFAULT_ENGINE_CONSUMPTION;
		this->consumption_per_second = consumption * 5e-5;
		cout << "EngineReady:\t" << this << endl;
	}
	~Engine()
	{
		cout << "EngineIsOver:\t" << this << endl;
	}
	void info()
	{
		cout << "Consumption:\t" << consumption << endl;
		cout << "ConsumptionPerSec:\t" << consumption_per_second << endl;
	}
};
//#define TANK_CHECK
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

	Engine engine(20);
	engine.info();

}