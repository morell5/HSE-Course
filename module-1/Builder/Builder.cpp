#include <iostream>
#include <string>

class Car {

friend class Builder;

private:
	int platformType; 
	int engineType;
	int doorType;

public:

	Car(int _platformType, int _engineType, int _doorType): platformType(_platformType), engineType(_engineType), doorType(_doorType) {};

	Car(const Car& car): platformType(car.platformType), engineType(car.engineType), doorType(car.doorType) {}; 

	Car(): platformType(0), engineType(0), doorType(0) {};

	std::string getParameters() {
		return std::to_string(platformType) + " " + std::to_string(engineType) + " " + std::to_string(doorType);
	}
};

class Builder {
private:
	Car* car;
public:
	Builder(): car(new Car()) {};

	void reset() {
		car = new Car();
	}

	void setPlatformType(int platformType) {
		car->platformType = platformType;
	}

	void setEngineType(int engineType) {
		car->engineType = engineType;
	}

	void setDoorType(int doorType) {
		car->doorType = doorType;
	}

	Car* getResult() {
		return car;
	}
};

int main() {
	Builder builder;

	int a, b, c;
	std::cin >> a >> b >> c;

	builder.setDoorType(a);
	builder.setEngineType(b);
	builder.setPlatformType(c);

	Car car = *builder.getResult();
	std::cout << car.getParameters() << std::endl;
	return 0;
}