#include <iostream>
#include <cmath>

class RoundPeg {
private:
    int _radius;
public:
    RoundPeg() {}
    RoundPeg(int radius) : _radius(radius) {}

    virtual int getRadius() {
        return _radius;
    }
};

class SquarePeg {
private:
    int _width;
public:
    SquarePeg() {}
    SquarePeg(int width) : _width(width) {}

    virtual int getWidth() {
        return _width;
    }
};

class RoundHole {
private:
    int _radius;
public:
    RoundHole() {}
    RoundHole(int radius) : _radius(radius) {}

    virtual int getRadius() {
        return _radius;
    }

    bool fits(RoundPeg* roundPeg) {
        return getRadius() >= roundPeg->getRadius();
    }
};

class SquarePegAdapter : public RoundPeg {
private:
    SquarePeg* _square_peg;
public:
    SquarePegAdapter(SquarePeg* squarePeg) : _square_peg(squarePeg) {}

    int getRadius() {
        return _square_peg->getWidth() * sqrt(2) / 2;
    }
};

int main(int argc, char* argv[]) {
    RoundHole* rh = new RoundHole(10);
    RoundPeg* rp1 = new RoundPeg(5);
    RoundPeg* rp2 = new RoundPeg(20);
    
    std::cout << rh->fits(rp1) << std::endl;
    std::cout << rh->fits(rp2) << std::endl;

    SquarePeg* sp = new SquarePeg(5);
    SquarePegAdapter* spa = new SquarePegAdapter(sp);
    std::cout << rh->fits(spa) << std::endl;

    return 0;
}
