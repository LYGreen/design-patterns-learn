#include <iostream>
#include <list>
#include <algorithm>

class TreeType {
protected:
    std::string _name;
    std::string _color;
    std::string _texture;
public:
    TreeType(std::string name, std::string color, std::string texture) 
        : _name(name), _color(color), _texture(texture)
    {}

    virtual void draw(void* canvas, int x, int y) {
        std::cout << "Draw." << std::endl;
    }

    virtual std::string getName() {
        return _name;
    }

    virtual std::string getColor() {
        return _color;
    }

    virtual std::string getTexture() {
        return _texture;
    }
};

class TreeFactory {
protected:
    static std::list<TreeType*> _treeTypes;
public:
    static TreeType* getTreeType(std::string name, std::string color, std::string texture) {
        TreeType* type = nullptr;
        for (TreeType* tt : _treeTypes) {
            if (
                tt->getName() == name &&
                tt->getColor() == color &&
                tt->getTexture() == texture
            ) {
                type = tt;
                break;
            }
        }

        if (type == nullptr) {
            type = new TreeType(name, color, texture);
            _treeTypes.push_back(type);
            std::cout << "Created a new type." << std::endl;
        }
        return type;
    }
};

std::list<TreeType*> TreeFactory::_treeTypes;

class Tree {
protected:
    int _x, _y;
    TreeType* _tree_type;
public:
    Tree(int x, int y, TreeType* treeType) : _x(x), _y(y), _tree_type(treeType) {}

    void draw(void* canvas) {
        _tree_type->draw(canvas, _x, _y);
    }
};

class Forest {
protected:
    std::list<Tree*> _trees;
public:
    void plantTree(int x, int y, std::string name, std::string color, std::string texture) {
        TreeType* type = TreeFactory::getTreeType(name, color, texture);
        Tree* tree = new Tree(x, y, type);
        _trees.push_back(tree);
    }

    void draw(void* canvas) {
        for (Tree* tree : _trees) {
            tree->draw(canvas);
        }
    }
};

int main(int argc, char* argv[]) {
    Forest* forest = new Forest;
    forest->plantTree(0, 0, "a", "red", "i don't know");
    forest->draw(nullptr);
    forest->plantTree(15, 31, "a", "red", "i don't know");
    forest->plantTree(34, 27, "a", "green", "i don't know");
    forest->draw(nullptr);

    // 释放内存
    
    return 0;
}
