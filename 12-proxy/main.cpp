#include <iostream>
#include <list>
#include <algorithm>

class ThirdPartyTVLib {
public:
    virtual std::string listVideos() = 0;
    
    virtual std::string getVideoInfo(int id) = 0;

    virtual void downloadVideo(int id) = 0;
};

class ThirdPartyTVClass : public ThirdPartyTVLib {
public:
    std::string listVideos() override {
        return "Videos";
    }

    std::string getVideoInfo(int id) override {
        return "Video id: " + std::to_string(id);
    }

    void downloadVideo(int id) override {
        std::cout << "Downloaded video id: " + std::to_string(id) << std::endl;
    }
};

class CachedTVClass : public ThirdPartyTVLib {
private:
    ThirdPartyTVLib* _service;
    std::string _list_cache;
    std::list<std::string> _video_cache;
    bool _need_reset;

    bool downloadExists(int id) {
        return false;
    }
public:
    CachedTVClass(ThirdPartyTVLib* service) : _service(service) {}

    std::string listVideos() override {
        if (_list_cache == "" || _need_reset) {
            _list_cache = _service->listVideos();
        }
        return _list_cache;
    }

    std::string getVideoInfo(int id) override {
        auto iter = std::find(_video_cache.begin(), _video_cache.end(), "Video id: " + std::to_string(id));
        if (iter == _video_cache.end() || _need_reset) {
            _video_cache.push_back(_service->getVideoInfo(id));
            iter = (--_video_cache.end());
        }
        return *iter;
    }

    void downloadVideo(int id) override {
        if (!downloadExists(id) || _need_reset) {
            _service->downloadVideo(id);
        }
    }
};

class TVManager {
protected:
    ThirdPartyTVLib* _service;
public:
    TVManager(ThirdPartyTVLib* service) : _service(service) {}

    void renderVideoPage(int id) {
        std::string info = _service->getVideoInfo(id);
        std::cout << "Render video page: " + info << std::endl;
    }

    void renderListPanel() {
        std::string list = _service->listVideos();
        std::cout << "Render list panel: " + list << std::endl;
    }
};

class Application {
public:
    void main() {
        ThirdPartyTVClass* aTVService = new ThirdPartyTVClass;
        CachedTVClass* aTVProxy = new CachedTVClass(aTVService);
        TVManager* manager = new TVManager(aTVProxy);
        manager->renderListPanel();
        manager->renderVideoPage(0);
    }
};

int main(int argc, char* argv[]) {
    Application* application = new Application;
    application->main();

    // 释放内存

    return 0;
}
