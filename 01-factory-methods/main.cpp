#include <iostream>
#include "interface.cpp"

int main(int argc, char* argv[]) {
    Application* application = new Application();
    application->initialize();

    delete application;

    return 0;
}
