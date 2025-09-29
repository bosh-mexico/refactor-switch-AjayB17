#include <iostream>
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>
#include <algorithm>
using namespace std;

// Enum for payment modes
enum class PaymentMode {
    PayPal,
    GooglePay,
    CreditCard,
    Unknown
};

// String → Enum converter
PaymentMode toPaymentMode(const string& method) {
    string m = method;
    // normalize to lowercase
    transform(m.begin(), m.end(), m.begin(), ::tolower);

    if (m == "paypal")      return PaymentMode::PayPal;
    if (m == "googlepay")   return PaymentMode::GooglePay;
    if (m == "creditcard")  return PaymentMode::CreditCard;
    return PaymentMode::Unknown;
}

// Base Payment class (abstract)
class Payment {
public:
    virtual ~Payment() = default;
    virtual void process(double amount) const = 0;
};

// PayPal Payment
class PayPalPayment : public Payment {
public:
    void process(double amount) const override {
        cout << "Processing PayPal payment of $" << amount << endl;
    }
};

// GooglePay Payment
class GooglePayPayment : public Payment {
public:
    void process(double amount) const override {
        cout << "Processing GooglePay payment of $" << amount << endl;
    }
};

// Credit Card Payment
class CreditCardPayment : public Payment {
public:
    void process(double amount) const override {
        cout << "Processing Credit Card payment of $" << amount << endl;
    }
};

// Payment Factory
class PaymentFactory {
public:
    using Creator = function<unique_ptr<Payment>()>;

    PaymentFactory() {
        registry[PaymentMode::PayPal]     = [](){ return make_unique<PayPalPayment>(); };
        registry[PaymentMode::GooglePay]  = [](){ return make_unique<GooglePayPayment>(); };
        registry[PaymentMode::CreditCard] = [](){ return make_unique<CreditCardPayment>(); };
    }

    unique_ptr<Payment> createPayment(PaymentMode mode) {
        auto it = registry.find(mode);
        if (it != registry.end()) {
            return it->second();
        }
        return nullptr; // Unknown payment mode
    }

private:
    unordered_map<PaymentMode, Creator> registry;
};

// Checkout function
void checkout(const Payment& payment, double amount) {
    if (amount <= 0) {
        cout << "Invalid payment amount!" << endl;
        return;
    }
    payment.process(amount);
}

// Example usage
int main() {
    double amount = 150.75;
    PaymentFactory factory;

    // Simulated user input
    string userInputs[] = {"PayPal", "GooglePay", "CreditCard", "Bitcoin"};

    for (const auto& input : userInputs) {
        PaymentMode mode = toPaymentMode(input);
        auto payment = factory.createPayment(mode);

        if (payment) {
            checkout(*payment, amount);
        } else {
            cout << "Unsupported payment method: " << input << endl;
        }
    }

    return 0;
}
