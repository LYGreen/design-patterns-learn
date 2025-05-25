#include <iostream>
#include <list>

class Graphics {
protected:
public:
    Graphics() {}
    virtual ~Graphics() {}

    virtual void move(int x, int y) {}
    virtual void draw() {}
};

class Dot : public Graphics {
protected:
    int _x, _y;
public:
    Dot() {}
    Dot(int x, int y) : _x(x), _y(y) {}
    virtual ~Dot() {}

    virtual void move(int x, int y) override {
        _x += x;
        _y += y;
    }

    virtual void draw() override {
        std::cout << "Dot" << std::endl;
    }
};

class Circle : public Dot {
    protected:
    int _radius;
    public:
    Circle() {}
    Circle(int radius) : _radius(radius), Dot(0, 0) {}
    Circle(int radius, int x, int y) : _radius(radius), Dot(x, y) {}
    virtual ~Circle() {}

    virtual void draw() override {
        std::cout << "Circle" << std::endl;
    }
};

class CompoundGraphic : public Graphics {
protected:
    std::list<Graphics*> _children;
public:
    virtual ~CompoundGraphic() {
        for (Graphics* g : _children) {
            delete g;
        }
    }

    void add(Graphics* graphics) {
        _children.push_back(graphics);
    }

    void remove(Graphics* graphics) {
        _children.remove(graphics);
    }

    void move(int x, int y) {
        for (Graphics* g : _children) {
            g->move(x, y);
        }
    }

    void draw() override {
        for (Graphics* g : _children) {
            g->draw();
        }
    }
};

class ImageEditor {
protected:
    CompoundGraphic* _all;
public:
    ~ImageEditor() {
        delete _all;
    }

    void load() {
        _all = new CompoundGraphic;
        _all->add(new Dot(1, 2));
        _all->add(new Circle(5, 3, 10));
    }

    void groupSelected(std::list<Graphics*> components) {
        CompoundGraphic* group = new CompoundGraphic;
        for (Graphics* g : components) {
            group->add(g);
            _all->remove(g);
        }
        _all->add(group);
        _all->draw();
    }
};

int main(int argc, char* argv[]) {
    ImageEditor* ie = new ImageEditor;
    std::list<Graphics*> components = {
        new Dot(4, 9),
        new Circle(5, 8, 3),
        new Circle(6, 1, 5)
    };
    ie->load();
    ie->groupSelected(components);
    
    delete ie;

    return 0;
}
