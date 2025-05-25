#include <iostream>

class Device {
protected:
    bool _enabled;
    int _volume;
    int _channel;
public:
    bool isEnabled() {
        return _enabled;
    }

    void enable() {
        _enabled = true;
    }

    void disable() {
        _enabled = false;
    }

    int getVolume() {
        return _volume;
    }

    void setVolume(int volume) {
        _volume = volume;
    }

    int getChannel() {
        return _channel;
    }

    void setChannel(int channel) {
        _channel =  channel;
    }
};

class Remote {
private:
    Device* _device;
public:
    Remote(Device* device) : _device(device) {}

    void togglePower() {
        if (_device->isEnabled()) {
            _device->disable();
        } else {
            _device->enable();
        }
    }

    void volumeDown() {
        _device->setVolume(_device->getVolume() - 1);
    }

    void volumeUp() {
        _device->setVolume(_device->getVolume() + 1);
    }

    void channelDown() {
        _device->setChannel(_device->getChannel() - 1);
    }

    void channelUp() {
        _device->setChannel(_device->getChannel() + 1);
    }
};

class AdvanceRemote : public Remote {
// TODO
};

class Television : public Device {
// TODO
};

class Radio : public Device {
// TODO
};

int main(int argc, char* argv[]) {
    
    
    return 0;
}
