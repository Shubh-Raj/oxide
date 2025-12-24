#ifndef UPIPAYMENT_H
#define UPIPAYMENT_H

#include "../interfaces/PaymentStrategy.h"

class UPIPayment : public PaymentStrategy {
    private:
    string upiId;
    public:
    UPIPayment(string upiId);
    bool processPayment(int amount);
};

#endif
