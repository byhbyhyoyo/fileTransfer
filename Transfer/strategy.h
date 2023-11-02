#pragma once
class TransferStrategy {
public:
    virtual void transfer(void* sock_ptr) = 0;
    virtual void receive(void* sock_ptr) = 0;
};

class LocalNetworkStrategy:public TransferStrategy {
public:
    void transfer(void* sock_ptr) override;
    void receive(void* sock_ptr) override;
};

class PublicNetworkStrategy :public TransferStrategy {
public:
    void transfer(void* sock_ptr) override {};
    void receive(void* sock_ptr) override {};
};

class TransferContext {
private:
    TransferStrategy* strategy;
public:
    TransferContext(TransferStrategy* start):strategy(start){}
    void set_strategy(TransferStrategy* start) {
        strategy = start;
    }
    void perform_transfer(void* sock_ptr) {
        strategy->transfer(sock_ptr);
    }
    void perform_receive(void* sock_ptr) {
        strategy->receive(sock_ptr);
    }
};