#ifndef NETBANKING_H
#define NETBANKING_H

#include "../interfaces/PaymentStrategy.h"

class NetBanking : public PaymentStrategy {
    private:
    string id;
    public:
    NetBanking(string id);
    bool processPayment(int amount);
};

#endif
