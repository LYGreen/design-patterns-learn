#include <iostream>
#include "interface.cpp"

void ClientCode(Director& director) {
    ConcreteBuilder1* builder = new ConcreteBuilder1();
    director.set_builder(builder);
    std::cout << "Standard basic product:" << std::endl;
    director.BuildMinimalViableProduct();

    Product1* p = builder->GetProduce();
    p->ListParts();
    delete p;

    std::cout << "Standard full featured product:" << std::endl;
    director.BuildFullFeaturedProduct();

    p = builder->GetProduce();
    p->ListParts();
    delete p;

    std::cout << "Custom product:" << std::endl;
    builder->ProducePartA();
    builder->ProducePartC();
    p = builder->GetProduce();
    p->ListParts();
    delete p;

    delete builder;
}

int main(int argc, char* argv[]) {
    Director* director = new Director();
    ClientCode(*director);
    delete director;

    return 0;
}
