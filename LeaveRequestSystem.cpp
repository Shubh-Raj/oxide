#include <bits/stdc++.h>
using namespace std;

class IPosition {
protected:
    IPosition* next = nullptr;

public:
    virtual ~IPosition() {}

    void setNextHandler(IPosition* n) {
        next = n;
    }

    virtual void handleReq(int days) = 0;
};

class HeadPos : public IPosition {
public:
    void handleReq(int days) override {
        if (days <= 2) {
            cout << "Approved by the team head\n";
        } else if (next) {
            next->handleReq(days);
        }
    }
};

class ManagerPos : public IPosition {
public:
    void handleReq(int days) override {
        if (days <= 7) {
            cout << "Approved by the team manager\n";
        } else if (next) {
            next->handleReq(days);
        }
    }
};

class DirectorPos : public IPosition {
public:
    void handleReq(int days) override {
        if (days <= 10) {
            cout << "Approved by the team director\n";
        } else {
            cout << "Cannot be approved\n";
        }
    }
};

int main() {
    int days;
    cout << "How many days of leave do you want: ";
    cin >> days;

    if (days <= 0) {
        cout << "Are you serious?\n";
        return 0;
    }

    HeadPos head;
    ManagerPos manager;
    DirectorPos director;

    head.setNextHandler(&manager);
    manager.setNextHandler(&director);

    head.handleReq(days);
}
