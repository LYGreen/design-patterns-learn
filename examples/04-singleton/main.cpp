#include <iostream>
#include <thread>

class Singleton {
protected:
    Singleton(const std::string value) : value_(value) {}

    static Singleton* singleton_;

    std::string value_;
public:
    Singleton(Singleton& another) = delete;

    void operator=(const Singleton&) = delete;

    static Singleton* GetInstance(const std::string& value);

    void SomeBusinessLogic() {
        // ...
    }

    std::string value() const {
        return value_;
    }
};

Singleton* Singleton::singleton_ = nullptr;

Singleton* Singleton::GetInstance(const std::string& value) {
    if (singleton_ == nullptr) {
        singleton_ = new Singleton(value);
    }
    return singleton_;
}

void ThreadFoo() {
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    Singleton* singleton = Singleton::GetInstance("FOO");
    std::cout << singleton->value() << std::endl;
}

void ThreadBar() {
    std::this_thread::sleep_for(std::chrono::microseconds(1000));
    Singleton* singleton = Singleton::GetInstance("BAR");
    std::cout << singleton->value() << std::endl;
}

int main(int argc, char* argv[]) {
    std::cout <<"If you see the same value, then singleton was reused (yay!\n" <<
    "If you see different values, then 2 singletons were created (booo!!)\n\n" <<
    "RESULT:\n"; 
    std::thread t1(ThreadFoo);
    std::thread t2(ThreadBar);
    t1.join();
    t2.join();

    return 0;
}
