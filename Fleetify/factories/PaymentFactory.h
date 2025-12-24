#ifndef PAYMENTFACTORY_H
#define PAYMENTFACTORY_H

#include "../common.h"
#include "../interfaces/PaymentStrategy.h"

class PaymentFactory{
    private:
    PaymentFactory();
    static PaymentFactory* instance;
    public:
    static PaymentFactory* getInstance();
    PaymentStrategy* getStrategy(string type, string id);
};

#endif
