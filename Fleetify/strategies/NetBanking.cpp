#include "NetBanking.h"

NetBanking::NetBanking(string id){
    this->id = id;
}
bool NetBanking::processPayment(int amount){
    cout<<"Successfully paid amount "<<amount<<" via net banking.\n";
    return true;
}
