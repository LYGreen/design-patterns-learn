#include <iostream>

std::string readApplicationConfigFile();

class Button {
public:
    virtual ~Button() {};
    virtual void render() const = 0;
    virtual void onClick() const {};
};

class Dialog {
public:
    virtual ~Dialog() {};
    virtual Button* createButton() const = 0;
};

class WindowsButton : public Button {
public:
    void render() const override {
        std::cout << "Windows button rendered." << std::endl;
    }

    void onClick() const override {
        std::cout << "Windows button was clicked." << std::endl;
    }
};

class HTMLButton : public Button {
public:
    void render() const override {
        std::cout << "HTML button rendered." << std::endl;
    }

    void onClick() const override {
        std::cout << "HTML button was clicked." << std::endl;
    }
};

class WindowsDialog : public Dialog {
public:
    Button* createButton() const override {
        return new WindowsButton();
    }
};

class HTMLDialog : public Dialog {
public:
    Button* createButton() const override {
        return new HTMLButton();
    }
};

class Application {
private:
    Dialog* dialog;
public:
    void initialize() {
        std::string os = readApplicationConfigFile();

        if (os == "Windows") {
            dialog = new WindowsDialog();
        } else if (os == "Web") {
            dialog = new HTMLDialog();
        } else {
            throw "Unknown system";
        }
    }
};

std::string readApplicationConfigFile() {
    return "Windows";
    // return "Web";
}
