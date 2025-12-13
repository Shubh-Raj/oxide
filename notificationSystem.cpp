#include <bits/stdc++.h>
using namespace std;

class INotification
{
public:
    virtual string getContent() const = 0;
    virtual ~INotification() {}
};

class SimpleNotification : public INotification
{
private:
    string text;

public:
    SimpleNotification(string &text)
    {
        this->text = text;
    }
    string getContent() const override
    {
        return text;
    }
};

class INotificationDecorator : public INotification
{
protected:
    INotification *notification;

public:
    INotificationDecorator(INotification *n)
    {
        notification = n;
    }
    virtual ~INotificationDecorator()
    {
        delete notification;
    }
};

class TimeStampDecorator : public INotificationDecorator
{
public:
    
    TimeStampDecorator(INotification *n) : INotificationDecorator(n) {}
    string getContent()
    {
        return "13th Dec" + notification->getContent();
    }
};

class SignatureDecorator : public INotificationDecorator
{
private:
    string signature;

public:
    SignatureDecorator(INotification *n, const string &sig) : INotificationDecorator(n)
    {
        signature = sig;
    }
    string getContent() const override
    {
        return notification->getContent() + "\n-- " + signature + "\n\n";
    }
};

//Observer Pattern

class IObserver{
    public:
    virtual void update() = 0;
    virtual ~IObserver() {};
};

class IObservable {
public:
    virtual void addObserver(IObserver* observer) = 0;
    virtual void removeObserver(IObserver* observer) = 0;
    virtual void notifyObservers() = 0;
};

class NotificationObservable :  public IObservable {
private:
    vector<IObserver*> observers;
    INotification* currentNotification;
public:
    NotificationObservable() { 
        currentNotification = nullptr; 
    }

    void addObserver(IObserver* obs) override {
        observers.push_back(obs);
    }

    void removeObserver(IObserver* obs) override {
        observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void notifyObservers() override {
        for (unsigned int i = 0; i < observers.size(); i++) {
            observers[i]->update();
        }
    }

    void setNotification(INotification* notification) {
        if (currentNotification != nullptr) {
            delete currentNotification;
        }
        currentNotification = notification;
        notifyObservers();
    }

    INotification* getNotification() {
        return currentNotification;
    }

    string getNotificationContent() {
        return currentNotification->getContent();
    }

    ~NotificationObservable() {
        if (currentNotification != NULL) {
            delete currentNotification;
        }
    }
};

class Logger : public IObserver {
private:
    NotificationObservable* notificationObservable;

public:
    Logger(NotificationObservable* observable) {
        this->notificationObservable = observable;
    }

    void update() {
        cout << "Logging New Notification : \n" << notificationObservable->getNotificationContent();
    }
};

int main(){
    cout<<"0";
}