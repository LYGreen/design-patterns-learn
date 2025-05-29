#include <iostream>
#include <list>

class ComponentWithContextualHelp {
public:
    ComponentWithContextualHelp() {}
    virtual ~ComponentWithContextualHelp() {}

    virtual void showHelp() const = 0;
};

class Component : public ComponentWithContextualHelp {
protected:
    std::string tooltipText;
    ComponentWithContextualHelp* container;
public:
    virtual void showHelp() const override {
        if (tooltipText != "") {
            std::cout << "Show tooltip: " << tooltipText << std::endl;
        } else {
            container->showHelp();
        }
    }

    void setContainer(ComponentWithContextualHelp* container) {
        this->container = container;
    }

    void setTooltipText(std::string_view sw) {
        tooltipText = sw;
    }
};

class Container : public Component {
protected:
    std::list<Component*> children;
public:
    void add(Component* child) {
        children.push_back(child);
        child->setContainer(this);
    }

    void remove(Component* child) {
        children.remove(child);
    }
};

class Button : public Component {
protected:
    int x, y, width, height;
    std::string text;
public:
    Button(int x = 0, int y = 0, int width = 20, int height = 16, std::string_view text = "")
        : x(x), y(y), width(width), height(height), text(text) {}

    void setText(std::string_view sw) {
        text = sw;
    }

    void click() {
        std::cout << "Button clicked." << std::endl;
    }
};

class Panel : public Container {
protected:
    std::string modalHelpText;
    int x, y, width, height;
public:
    Panel(int x = 0, int y = 0, int width = 240, int height = 120)
        : x(x), y(y), width(width), height(height) {}

    void setModalHelpText(std::string_view sw) {
        modalHelpText = sw;
    }
    
    void showHelp() const override {
        if (modalHelpText != "") {
            std::cout << "Show modalHelpText: " << modalHelpText << std::endl;
        } else {
            Container::showHelp();
        }
    }
};

class Dialog : public Container {
protected:
    std::string wikiPageURL;
    std::string title;
public:
    Dialog(std::string title) : title(title) {}

    void setWikiPageURL(std::string_view sw) {
        wikiPageURL = sw;
    }

    void showHelp() const override {
        if (wikiPageURL != "") {
            std::cout << "Show wikiPageURL: " << wikiPageURL << std::endl;
        } else {
            Container::showHelp();
        }
    }
};

class Application {
protected:
    Component* component;
public:
    void createUI() {
        Dialog* dialog = new Dialog("Budget Reports");
        dialog->setWikiPageURL("http://...");
        Panel* panel = new Panel(0, 0, 400, 800);
        panel->setModalHelpText("This panel does...");
        Button* ok = new Button(250, 760, 50, 20, "OK");
        ok->setTooltipText("This is an OK button that...");
        Button* cancel = new Button(320, 760, 50, 20, "Cancel");
        panel->add(ok);
        panel->add(cancel);
        dialog->add(panel);

        // 测试代码
        component = panel;
        component->showHelp();
    }

};

int main(int argc, char* argv[]) {
    Application* application = new Application;
    application->createUI();
    
    return 0;
}
