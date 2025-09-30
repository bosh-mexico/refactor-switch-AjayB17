#ifndef PAYMENT_MODE_H_
#define PAYMENT_MODE_H_
#include <iostream>
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>
#include <algorithm>

// Enum for payment modes
enum class PaymentMode {
    PayPal,
    GooglePay,
    CreditCard,
    Unknown
};

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
        std::cout << "Processing PayPal payment of $" << amount << '\n';
    }
};

// GooglePay Payment
class GooglePayPayment : public Payment {
 public:
    void process(double amount) const override {
        std::cout << "Processing GooglePay payment of $" << amount << '\n';
    }
};

// Credit Card Payment
class CreditCardPayment : public Payment {
 public:
    void process(double amount) const override {
        std::cout << "Processing Credit Card payment of $" << amount << '\n';
    }
};

// Payment Factory
class PaymentFactory {
 public:
    using Creator = std::function<std::unique_ptr<Payment>()>;

    PaymentFactory() {
        registry[PaymentMode::PayPal]     = [](){ return std::make_unique<PayPalPayment>(); };
        registry[PaymentMode::GooglePay]  = [](){ return std::make_unique<GooglePayPayment>(); };
        registry[PaymentMode::CreditCard] = [](){ return std::make_unique<CreditCardPayment>(); };
    }

    std::unique_ptr<Payment> createPayment(PaymentMode mode) {
        auto it = registry.find(mode);
        if (it != registry.end()) {
            return it->second();
        }
        return nullptr;  // Unknown payment mode
    }

 private:
    std::unordered_map<PaymentMode, Creator> registry;
};
#endif  // PAYMENT_MODE_H_
