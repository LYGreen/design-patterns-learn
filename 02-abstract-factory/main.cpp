#include <iostream>
#include "interface.cpp"

int main(int argc, char* argv[]) {
    ApplicationConfigurator* ac = new ApplicationConfigurator();
    ac->main();

    delete ac;

    return 0;
}
