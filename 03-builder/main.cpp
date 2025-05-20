#include <iostream>
#include <vector>

class CarManual {
public:
    std::string seats_;
    std::string engine_;
    std::string trip_computer_;
    std::string gps_;
};

class Car {
public:
    std::vector<std::string> seats_;
    std::string engine_;
    std::string trip_computer_;
    std::string gps_;
};

class Builder {
public:
    virtual ~Builder() {}
    virtual void reset() = 0;
    virtual void setSeats(int number) const = 0;
    virtual void setEngine(std::string engine) const = 0;
    virtual void setTripComputer(std::string trip_computer) const = 0;
    virtual void setGPS(std::string gps) const = 0;
};

class CarBuilder : public Builder {
private:
    Car* car;
public:
    void reset() override {
        car = new Car();
    }

    void setSeats(int number) const override {
        for (int i = 0; i < number; i++) {
            car->seats_.push_back("seat");
        }
    }
    
    void setEngine(std::string engine) const override {
        car->engine_ = engine;
    }

    void setTripComputer(std::string trip_computer) const override {
        car->trip_computer_ = trip_computer;
    }

    void setGPS(std::string gps) const override {
        car->gps_ = gps;
    }

    Car* getResult() {
        Car* r = car;
        car = nullptr;
        return r;
    }
};

class CarManualBuilder : public Builder {
private:
    CarManual* manual;
public:
    void reset() override {
        manual = new CarManual();
    }

    void setSeats(int number) const override {
        manual->seats_ = "Seats count: " + number;
    }

    void setEngine(std::string engine) const override {
        manual->engine_ = "Engine usage: " + engine;
    }

    void setTripComputer(std::string trip_computer) const override {
        manual->trip_computer_ = "Trip computer usage: " + trip_computer;
    }

    void setGPS(std::string gps) const override {
        manual->gps_ = "GPS usage: " + gps;
    }

    CarManual* getResult() {
        CarManual* r = manual;
        manual = nullptr;
        return r;
    }
};

class Director {
private:
    Builder* car_builder_;
    Builder* manual_builder_;
public:
    Director(Builder* car_builder, Builder* manual_builder) {
        car_builder_ = car_builder;
        manual_builder_ = manual_builder;
    }

    void BuildMinimal() {
        car_builder_->reset();
        car_builder_->setEngine("my_engine");
        car_builder_->setSeats(5);
        
        manual_builder_->reset();
        manual_builder_->setEngine("my_engine");
        manual_builder_->setSeats(5);
    }

    void BuildFull() {
        car_builder_->reset();
        car_builder_->setEngine("my_engine");
        car_builder_->setSeats(5);
        car_builder_->setTripComputer("my_trip_computer");
        car_builder_->setGPS("my_gps");

        manual_builder_->reset();
        manual_builder_->setEngine("my_engine");
        manual_builder_->setSeats(5);
        manual_builder_->setTripComputer("my_trip_computer");
        manual_builder_->setGPS("my_gps");
    }
};

void client() {
    Builder* car = new CarBuilder();
    Builder* manual = new CarManualBuilder();
    Director* director = new Director(car, manual);
    director->BuildMinimal();

    // TODO:

    delete director;
    delete manual;
    delete car;
}

int main(int argc, char* argv[]) {
    client();

    return 0;
}
