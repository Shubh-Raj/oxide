#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "../common.h"

class Customer{
    private:
    static int nextCustomerId;
    int customerId;
    string name, phoneNo, licenseNo;
    public:
    Customer(const string& name, const string& phoneNo, const string& licenseNo);
    int getCustomerId();
    void getCustomerDetails();
};

#endif
