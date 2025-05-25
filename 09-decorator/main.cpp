#include <iostream>

class DataSource {
public:
    virtual void writeData(const char* data) = 0;
    virtual const char* readData() = 0;
};

class FileDataSource : public DataSource {
protected:
    std::string _filename;
    const char* _data;
public:
    virtual void writeData(const char* data) override {
        std::cout << "Write: " << data << std::endl;
        _data = data;
    }

    virtual const char* readData() override {
        std::cout << "Read: " << _data << std::endl;
        return _data;
    }
};

class DataSourceDecorator : public DataSource {
protected:
    DataSource* _data_source;
public:
    DataSourceDecorator(DataSource* dataSource) : _data_source(dataSource) {}

    virtual void writeData(const char* data) override {
        _data_source->writeData(data);
    }

    virtual const char* readData() override {
        return _data_source->readData();
    }
};

class EncryptionDecorator : public DataSourceDecorator {
public:
    EncryptionDecorator(DataSource* ds) : DataSourceDecorator(ds) {}

    virtual void writeData(const char* data) override {
        std::cout << "Encryption." << std::endl;
        DataSourceDecorator::writeData(data);
    }

    virtual const char* readData() override {
        const char* data = DataSourceDecorator::readData();
        std::cout << "Decryption." << std::endl;
        return data;
    }
};

class CompressionDecorator : public DataSourceDecorator {
public:
    CompressionDecorator(DataSource* ds) : DataSourceDecorator(ds) {}

    virtual void writeData(const char* data) override {
        std::cout << "Compression." << std::endl;
        DataSourceDecorator::writeData(data);
    }

    virtual const char* readData() override {
        const char* data = DataSourceDecorator::readData();
        std::cout << "Decompression." << std::endl;
        return data;
    }
};

int main(int argc, char* argv[]) {
    FileDataSource* fds = new FileDataSource;
    CompressionDecorator* cd = new CompressionDecorator(fds);
    EncryptionDecorator* ed = new EncryptionDecorator(cd);

    ed->writeData("Hello World !");
    const char* data = ed->readData();

    std::cout << "Data: " << data << std::endl;

    // 释放内存
    
    return 0;
}
