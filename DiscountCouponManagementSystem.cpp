#include <bits/stdc++.h>
using namespace std;

class DiscountStrategy
{
public:
    virtual double calculate(double baseAmount) = 0;
    virtual ~DiscountStrategy() {}
};

class FlatDiscountStrategy : public DiscountStrategy
{
    double amount;

public:
    FlatDiscountStrategy(double amt)
    {
        amount = amt;
    }
    double calculate(double baseAmount)
    {
        return min(amount, baseAmount);
    }
};

class PercentageDiscountStrategy : public DiscountStrategy
{
private:
    double percent;

public:
    PercentageDiscountStrategy(double pct)
    {
        percent = pct;
    }
    double calculate(double baseAmount) override
    {
        return (percent / 100.0) * baseAmount;
    }
};

class PercentageWithCapStrategy : public DiscountStrategy
{
private:
    double percent;
    double cap;

public:
    PercentageWithCapStrategy(double pct, double capVal)
    {
        percent = pct;
        cap = capVal;
    }
    double calculate(double baseAmount) override
    {
        double disc = (percent / 100.0) * baseAmount;
        if (disc > cap)
        {
            return cap;
        }
        return disc;
    }
};

enum StrategyType
{
    FLAT,
    PERCENT,
    PERCENT_WITH_CAP
};

class DiscountStrategyManager
{
private:
    static DiscountStrategyManager *instance;
    DiscountStrategyManager() {}

public:
    static DiscountStrategyManager *getInstance()
    {
        if (!instance)
        {
            instance = new DiscountStrategyManager();
        }
        return instance;
    }
    DiscountStrategy *getStrategy(StrategyType type, double param1, double param2 = 0.0) const
    {
        if (type == StrategyType::FLAT)
        {
            return new FlatDiscountStrategy(param1);
        }
        if (type == StrategyType::PERCENT)
        {
            return new PercentageDiscountStrategy(param1);
        }
        if (type == StrategyType::PERCENT_WITH_CAP)
        {
            return new PercentageWithCapStrategy(param1, param2);
        }
        return nullptr;
    }
};

DiscountStrategyManager* DiscountStrategyManager::instance = nullptr;

class Product {
private:
    string name;
    string category;
    double price;
public:
    Product(string name, string category, double price) {
        this->name = name;
        this->category = category;
        this->price = price;
    }
    string getName() {
        return name;
    }
    string getCategory() const {
        return category;
    }
    double getPrice() {
        return price;
    }
};

class CartItem {
private:
    Product* product;
    int quantity;
public:
    CartItem(Product* prod, int qty) {
        product = prod;
        quantity = qty;
    }
    double itemTotal() {
        return product->getPrice() * quantity;
    }
    const Product* getProduct() {
        return product;
    }
};

class Cart {
private:
    vector<CartItem*> items;
    double originalTotal;
    double currentTotal;
    bool loyaltyMember;
    string paymentBank;
public:
    Cart() {
        originalTotal = 0.0;
        currentTotal = 0.0;
        loyaltyMember = false;
        paymentBank = "";
    }

    void addProduct(Product* prod, int qty = 1) {
        CartItem* item = new CartItem(prod, qty);
        items.push_back(item);
        originalTotal += item->itemTotal();
        currentTotal  += item->itemTotal();
    }

    double getOriginalTotal() {
        return originalTotal;
    }

    double getCurrentTotal() {
        return currentTotal;
    }

    void applyDiscount(double d) {
        currentTotal -= d;
        if (currentTotal < 0) {
            currentTotal = 0;
        }
    }

    void setLoyaltyMember(bool member) {
        loyaltyMember = member;
    }

    bool isLoyaltyMember() {
        return loyaltyMember;
    }

    void setPaymentBank(string bank) {
        paymentBank = bank;
    }

    string getPaymentBank() {
        return paymentBank;
    }

    vector<CartItem*> getItems() {
        return items;
    }
};