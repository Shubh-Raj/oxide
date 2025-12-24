#ifndef PAYMENTSTRATEGY_H
#define PAYMENTSTRATEGY_H

#include "../common.h"

class PaymentStrategy{
    public:
    virtual bool processPayment(int amount) = 0;
    virtual ~PaymentStrategy(){};
};

#endif
