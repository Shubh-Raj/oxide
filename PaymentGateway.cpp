#include <bits/stdc++.h>
using namespace std;

class PaymentRequest{
    public:
    string sender, receiver, currency;
    double amount;
    void setPaymentRequest(string& sender, string& receiver, string& currency, double amount){
        this->sender = sender;
        this->receiver = receiver;
        this->currency = currency;
        this->amount = amount;
    }
};
//
class BankingSystem{
    public:
    virtual bool processPayment(double amount) = 0;
    virtual ~BankingSystem() {}
};

class PaytmBankingSystem : public BankingSystem {
public:
    PaytmBankingSystem() {}
    bool processPayment(double amount) override {
            int r = rand() % 100;
            return r < 80;
    }
};

class RazorpayBankingSystem : public BankingSystem {
public:
    RazorpayBankingSystem() {}
    bool processPayment(double amount) override {
        cout << "[BankingSystem-Razorpay] Processing payment of " << amount << "...\n";
        int r = rand() % 100;
        return r < 90;
    }
};

class PaymentGateway{
    protected:
    BankingSystem* bankingSystem;
    public:
    virtual bool processPayment(PaymentRequest* request) {
        if (!validatePayment(request)) {
            cout << "[PaymentGateway] Validation failed for " << request->sender << ".\n";
            return false;
        }
        if (!initiatePayment(request)) {
            cout << "[PaymentGateway] Initiation failed for " << request->sender << ".\n";
            return false;
        }
        if (!confirmPayment(request)) {
            cout << "[PaymentGateway] Confirmation failed for " << request->sender << ".\n";
            return false;
        }
        return true;
    }

    virtual bool validatePayment(PaymentRequest* request) = 0;
    virtual bool initiatePayment(PaymentRequest* request) = 0;
    virtual bool confirmPayment(PaymentRequest* request) = 0;
};

class PaytmGateway : public PaymentGateway {
public:
    PaytmGateway() {
        bankingSystem = new PaytmBankingSystem();
    }
    bool validatePayment(PaymentRequest* request) override {
        cout << "[Paytm] Validating payment for " << request->sender << ".\n";

        if (request->amount <= 0 || request->currency != "INR") {
            return false;
        }
        return true;
    }
    bool initiatePayment(PaymentRequest* request) override {
        cout << "[Paytm] Initiating payment of " << request->amount 
                  << " " << request->currency << " for " << request->sender << ".\n";

        return bankingSystem->processPayment(request->amount);
    }
    bool confirmPayment(PaymentRequest* request) override {
        cout << "[Paytm] Confirming payment for " << request->sender << ".\n";

        return true;
    }
};

class RazorpayGateway : public PaymentGateway {
public:
    RazorpayGateway() {
        bankingSystem = new RazorpayBankingSystem();
    }
    bool validatePayment(PaymentRequest* request) override {
        cout << "[Razorpay] Validating payment for " << request->sender << ".\n";

        if (request->amount <= 0) {
            return false;
        }
        return true;
    }
    bool initiatePayment(PaymentRequest* request) override {
        cout << "[Razorpay] Initiating payment of " << request->amount 
                  << " " << request->currency << " for " << request->sender << ".\n";

        return bankingSystem->processPayment(request->amount);
       
    }
    bool confirmPayment(PaymentRequest* request) override {
        cout << "[Razorpay] Confirming payment for " << request->sender << ".\n";

        return true;
    }
};

class PaymentGatewayProxy : public PaymentGateway{
    PaymentGateway* realPaymentGateway;
    int attempts = 0;
    public:
    PaymentGatewayProxy(PaymentGateway* paymentgateway, int attempts){
        realPaymentGateway = paymentgateway;
        this->attempts = attempts;
    }
    bool processPayment(PaymentRequest* request) override {
        bool result = false;
        for (int attempt = 0; attempt < attempts; ++attempt) {
            if (attempt > 0) {
                cout << "[Proxy] Retrying payment (attempt " << (attempt+1)
                          << ") for " << request->sender << ".\n";
            }
            result = realPaymentGateway->processPayment(request);
            if (result) break;
        }
        if (!result) {
            cout << "[Proxy] Payment failed after " << (attempts)
                      << " attempts for " << request->sender << ".\n";
        }
        return result;
    }
    bool validatePayment(PaymentRequest* request) override {
        return realPaymentGateway->validatePayment(request);
    }
    bool initiatePayment(PaymentRequest* request) override {
        return realPaymentGateway->initiatePayment(request);
    }
    bool confirmPayment(PaymentRequest* request) override {
        return realPaymentGateway->confirmPayment(request);
    }
};

enum class GatewayType{
    PAYTM,
    RAZORPAY
};

class GatewayFactory{
    private:
    static GatewayFactory instance;
    GatewayFactory() {}
    public:
    static GatewayFactory& getInstance(){
        return instance;
    }
    PaymentGateway* getGateway(GatewayType gt){
        if(gt==GatewayType::PAYTM){
            PaymentGateway* paymentGateway = new PaytmGateway();
            return new PaymentGatewayProxy(paymentGateway,3);
        }
        else if(gt==GatewayType::RAZORPAY){
            PaymentGateway* paymentGateway = new RazorpayGateway();
            return new PaymentGatewayProxy(paymentGateway,1);
        }
    }
};

GatewayFactory GatewayFactory::instance;

class PaymentService{
    private:
    static PaymentService instance;
    PaymentGateway* paymentGateway;
    PaymentService(){
        paymentGateway = nullptr;
    }
    public:
    static PaymentService& getInstance(){
        return instance;
    }
    void setGateway(PaymentGateway* g) {
        // if (gateway) delete gateway;
        paymentGateway = g;
    }
     bool processPayment(PaymentRequest* request) {
        if (!paymentGateway) {
            cout << "[PaymentService] No payment gateway selected.\n";
            return false;
        }
        return paymentGateway->processPayment(request);
    }
};

PaymentService PaymentService:: instance;

class PaymentController{
    private:
    static PaymentController instance;
    PaymentController(){}
    // PaymentService* paymentService;
    public:
    static PaymentController& getInstance(){
        return instance;
    }
    bool handlePayment(GatewayType type, PaymentRequest* PaymentRequest){
        PaymentGateway* paymentGateway = GatewayFactory::getInstance().getGateway(type);
        PaymentService::getInstance().setGateway(paymentGateway);
        return PaymentService::getInstance().processPayment(PaymentRequest);
    }
};

PaymentController PaymentController::instance;