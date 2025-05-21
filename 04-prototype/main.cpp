#include <iostream>

class Shape {
protected:
    int x = 0, y = 0;
public:
    Shape() {}
    Shape(int x, int y) : x(x), y(y) {}

    void setX(int x) {
        this->x = x;
    }

    void setY(int y) {
        this->y = y;
    }

    virtual Shape* clone() const = 0;
    virtual std::string toString() const = 0;
};

class Rectangle : public Shape {
protected:
    int width = 0, height = 0;
public:
    Rectangle() {}
    Rectangle(int width, int height) : width(width), height(height) {}
    Rectangle(int x, int y, int width, int height) : Shape(x, y), width(width), height(height) {}

    void setWidth(int width) {
        this->width = width;
    }

    void setHeight(int height) {
        this->height = height;
    }

    Shape* clone() const override {
        return new Rectangle(this->x, this->y, this->width, this->height);
    }

    std::string toString() const override {
        return "Rectangle: " + std::to_string(x) +
                " " + std::to_string(y) +
                " " + std::to_string(width) + 
                " " + std::to_string(height);
    }
};

class Circle : public Shape {
protected:
    int radius = 0;
public:
    Circle() {}
    Circle(int radius) : radius(radius) {}
    Circle(int x, int y, int radius) : Shape(x, y), radius(radius) {}

    void setRadius(int radius) {
        this->radius = radius;
    }

    Shape* clone() const override {
        return new Circle(this->x, this->y, this->radius);
    }

    std::string toString() const override {
        return "Circle: " + std::to_string(x) +
                " " + std::to_string(y) +
                " " + std::to_string(radius);
    }
};

class Application {
public:
    void main() {
        Rectangle* rect1 = new Rectangle(64, 20);
        Circle* circle1 = new Circle(5);
        std::cout << rect1->toString() << std::endl;
        std::cout << circle1->toString() << std::endl;
        std::cout << std::endl;

        Rectangle* rect2 = (Rectangle*) rect1->clone();
        Circle* circle2 = (Circle*) circle1->clone();
        std::cout << rect2->toString() << std::endl;
        std::cout << circle2->toString() << std::endl;
        std::cout << std::endl;

        rect2->setWidth(12);
        rect2->setHeight(6);
        circle2->setRadius(3);
        std::cout << rect1->toString() << std::endl;
        std::cout << circle1->toString() << std::endl;
        std::cout << rect2->toString() << std::endl;
        std::cout << circle2->toString() << std::endl;
        std::cout << std::endl;
    }
};

int main(int argc, char* argv[]) {
    Application* application = new Application();
    application->main();

    delete application;
    return 0;
}
