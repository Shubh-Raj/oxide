#include "Customer.h"

int Customer::nextCustomerId = 0;

Customer::Customer(const string& name, const string& phoneNo, const string& licenseNo){
    this->name = name;
    this->phoneNo = phoneNo;
    this->licenseNo = licenseNo;
    customerId = ++nextCustomerId;
}
int Customer::getCustomerId(){
    return customerId;
}
void Customer::getCustomerDetails(){
    cout << "Customer Name: " << name << endl;
    cout << "Phone No: " << phoneNo << endl;
    cout << "License No: " << licenseNo << endl;
}
