#include "UPIPayment.h"

UPIPayment::UPIPayment(string upiId){
    this->upiId = upiId;
}
bool UPIPayment::processPayment(int amount){
    cout<<"Successfully paid amount "<<amount<<" via UPI.\n";
    return true;
}
