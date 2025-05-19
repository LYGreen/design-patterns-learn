#include <iostream>

std::string readApplicationConfigFile() {
    return "Windows";
    // return "Mac";
}

class Button {
public:
    virtual void paint() const = 0;
};

class CheckBox {
public:
    virtual void paint() const = 0;
    virtual void check() const = 0;
};

class GUIFactory {
public:
    virtual Button* createButton() const = 0;
    virtual CheckBox* createCheckBox() const = 0;
};

class WinButton : public Button {
public:
    void paint() const override {
        std::cout << "WinButton painted." << std::endl;
    }
};

class MacButton : public Button {
public:
    void paint() const override {
        std::cout << "MacButton painted." << std::endl;
    }
};

class WinCheckBox : public CheckBox {
public:
    void paint() const override {
        std::cout << "WinCheckBox painted." << std::endl;
    }

    void check() const override {
        std::cout << "WinCheckBox checked." << std::endl;
    }
};

class MacCheckBox : public CheckBox {
public:
    void paint() const override {
        std::cout << "MacCheckBox painted." << std::endl;
    }

    void check() const override {
        std::cout << "MacCheckBox checked." << std::endl;
    }
};

class WinFactory : public GUIFactory {
public:
    Button* createButton() const override {
        return new WinButton();
    }

    CheckBox* createCheckBox() const override {
        return new WinCheckBox();
    }
};

class MacFactory : public GUIFactory {
public:
    Button* createButton() const override {
        return new MacButton();
    }

    CheckBox* createCheckBox() const override {
        return new MacCheckBox();
    }
};

class Application {
private:
    GUIFactory* factory;
    Button* button;
public:
    Application(GUIFactory* factory) : factory(factory) {}

    void createUI() {
        button = factory->createButton();
    }

    void paint() {
        button->paint();
    }
};

class ApplicationConfigurator {
private:
    Application* application;
public:
    void main() {
        std::string config = readApplicationConfigFile();

        GUIFactory* factory;

        if (config == "Windows") {
            factory = new WinFactory();
        } else if (config == "Mac") {
            factory = new MacFactory();
        } else {
            throw "Unknown system.";
        }

        application = new Application(factory);

        application->createUI();
        application->paint();
    }
};
