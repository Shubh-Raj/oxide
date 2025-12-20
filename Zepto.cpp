#include <bits/stdc++.h>
using namespace std;

class Product{
    int sku; 
    string name;
    double price;
    public:
    Product(int s, string n, double p){
        sku = s;
        name = n;
        price = p;
    }
    int getSku() {
        return this->sku;
    }
    string getName() {
        return this->name;
    }
    double getPrice() {
        return this->price;
    }
};

class ProductFactory {
public:
    static Product* createProduct(int sku) {
        // In reality product comes from DB
        string name;
        double price;

        if (sku == 101) {
            name  = "Apple";
            price = 20;
        }
        else if (sku == 102) {
            name  = "Banana";
            price = 10;
        }
        else if (sku == 103) {
            name  = "Chocolate";
            price = 50;
        }
        else if (sku == 201) {
            name  = "T-Shirt";
            price = 500;
        }
        else if (sku == 202) {
            name  = "Jeans";
            price = 1000;
        }
        else {
            name  = "Item" + to_string(sku);
            price = 100;
        }
        return new Product(sku, name, price);
    }
};

class InventoryStore{
    public:
    virtual ~InventoryStore() {}
    virtual void addProduct(Product* prod, int qty) = 0;
    virtual void removeProduct(int sku, int qty) = 0;
    virtual int checkStock(int sku) = 0;
    virtual vector<Product*> listAvailableProducts() = 0;
};

class DbInventoryStore : public InventoryStore {
private:
    map<int,int>* stock;             // SKU -> quantity
    map<int,Product*>* products;     // SKU -> Product*
public:
    DbInventoryStore(){
        stock = new map<int,int>();
        products = new map<int,Product*> ();
    }
    ~DbInventoryStore(){
        for(auto it: *products){
            delete it.second;
        }
        delete stock;
        delete products;
    }

    void addProduct(Product* product, int qty) override{
        // stock->insert({product->getSku(),qty});
        int sku = product->getSku();
        if (products->count(sku) == 0) {
            // Does not exist
            (*products)[sku] = product;
        } else {
            delete product;
        }
        (*stock)[sku] += qty;
    }

    void removeProduct(int sku, int qty) override{
        if (stock->count(sku) == 0) 
            return;
        if((*stock)[sku]<=qty){
            (*stock).erase(sku);
            // (*products).erase(sku);
        }
        else{
            (*stock)[sku]-=qty;
        }
    }

    int checkStock(int sku){
        if((*stock)[sku]>0){
            return (*stock)[sku];
        }
        return 0;
    }

    vector<Product*> listAvailableProducts() override {
        vector<Product*> availableProducts;
        for(auto it: *(stock)){
            if(it.second>0 && products->count(it.first)){
                availableProducts.push_back((*products)[it.first]);
            }
        }
        return availableProducts;
    }
};

class InventoryManager{ //not singleton as each inventory has a different manager
    InventoryStore* inventoryStore;
    public:
    InventoryManager(InventoryStore* store){
        inventoryStore = store;
    }
    void addStock(int sku, int qty){
        Product* product = ProductFactory::createProduct(sku);
        inventoryStore->addProduct(product,qty);
        cout << "[InventoryManager] Added SKU " << sku << " Qty " << qty << endl;
    }
    void removeStock(int sku, int qty){
        inventoryStore->removeProduct(sku,qty);
    }
    int checkStock(int sku) {
        return inventoryStore->checkStock(sku);
    }
    vector<Product*> getAvailableProducts() {
        return inventoryStore->listAvailableProducts();
    }
};

class ReplenishStrategy{
    public:
    virtual void replenish(InventoryManager* manager, map<int,int> itemsToReplenish) = 0;
    virtual ~ReplenishStrategy() {}
};

class ThresholdReplenishStrategy : public ReplenishStrategy {
private:
    int threshold;
public:
    ThresholdReplenishStrategy(int threshold) {
        this->threshold = threshold;
    }
    void replenish(InventoryManager* manager, map<int,int> itemsToReplenish) override {
        cout << "[ThresholdReplenish] Checking threshold... \n";
        for (auto it : itemsToReplenish) {
            int sku = it.first;
            int qtyToAdd = it.second;
            int current  = manager->checkStock(sku);
            if (current < threshold) {
                manager->addStock(sku, qtyToAdd);
                cout << "  -> SKU " << sku << " was " << current 
                     << ", replenished by " << qtyToAdd << endl;
            }
        }
    }
};

class WeeklyReplenishStrategy : public ReplenishStrategy {
public:
    WeeklyReplenishStrategy() {}
    void replenish(InventoryManager* manager, map<int,int> itemsToReplenish) override {
        //business
        cout << "[WeeklyReplenish] Weekly replenishment triggered for inventory.\n";
    }
};

class DarkStore {
private:
    string name;
    double x, y;                       // location coordinates
    InventoryManager* inventoryManager;
    ReplenishStrategy* replenishStrategy;
public:
    DarkStore(string n, double x_coord, double y_coord) {
        name = n;
        x = x_coord;
        y = y_coord;
        inventoryManager = new InventoryManager(new DbInventoryStore);

    }
    ~DarkStore() {
        delete inventoryManager;
        if (replenishStrategy) delete replenishStrategy;
    }
    double distanceTo(double ux, double uy) {
        return sqrt((x - ux)*(x - ux) + (y - uy)*(y - uy));
    }
    void runReplenishment(map<int,int> itemsToReplenish) {
        if (replenishStrategy) {
            replenishStrategy->replenish(inventoryManager, itemsToReplenish);
        }
    }

    vector<Product*> getAllProducts() {
        return inventoryManager->getAvailableProducts();
    }

    int checkStock(int sku) {
        return inventoryManager->checkStock(sku);
    }

    void removeStock(int sku, int qty) {
        inventoryManager->removeStock(sku, qty); 
    }

    void addStock(int sku, int qty) {
        // Product* prod = ProductFactory::createProduct(sku);
        inventoryManager->addStock(sku, qty);
    }

    // Getters & Setters
    void setReplenishStrategy(ReplenishStrategy* strategy) {
        this->replenishStrategy = strategy;
    }

    string getName() {
        return this->name;
    }

    double getXCoordinate() {
        return this->x;
    }

    double getYCoordinate() {
        return this->y;
    }
    InventoryManager* getInventoryManager() {
        return this->inventoryManager;
    }
};
