#include <iostream>

class Database {
protected:
    Database() {}

    static Database* instance_;

    std::string test_val_;
public:

    Database(const Database&) = delete;

    Database operator=(const Database&) = delete;

    static Database* getInstance(std::string val);

    std::string getTestValue() {
        return test_val_;
    }

    void query() {
        std::cout << "Query." << std::endl;
    }

    void execute() {
        std::cout << "Execute." << std::endl;
    }
};

Database* Database::instance_ = nullptr;

Database* Database::getInstance(std::string val) {
    if (instance_ == nullptr) {
        instance_ = new Database();
        instance_->test_val_ = val;
    }
    return instance_;
}

class Application {
public:
    void main() {
        Database* database1 = Database::getInstance("A");
        Database* database2 = Database::getInstance("B");
        std::cout << database1->getTestValue() << std::endl;
        std::cout << database2->getTestValue() << std::endl;
    }
};

int main(int argc, char* argv[]) {
    Application* application = new Application();
    application->main();
    delete application;
    return 0;
}
