#include "PaymentFactory.h"
#include "../strategies/UPIPayment.h"
#include "../strategies/NetBanking.h"

PaymentFactory::PaymentFactory(){}

PaymentFactory* PaymentFactory::instance=nullptr;

PaymentFactory* PaymentFactory::getInstance(){
    if(instance == nullptr){
        instance = new PaymentFactory();
    }
    return instance;
}
PaymentStrategy* PaymentFactory::getStrategy(string type, string id) {
    if (type == "UPI") return new UPIPayment(id);
    if (type == "NetBanking") return new NetBanking(id);
    return nullptr;
}
