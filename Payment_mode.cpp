#include "./Payment_mode.h"
#include <iostream>
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>
#include <algorithm>

// String → Enum converter
PaymentMode toPaymentMode(const std::string& method) {
    static const std::unordered_map<std::string, PaymentMode> lookup = {
        {"paypal", PaymentMode::PayPal},
        {"googlepay", PaymentMode::GooglePay},
        {"creditcard", PaymentMode::CreditCard}
    };

    std::string m = method;
    std::transform(m.begin(), m.end(), m.begin(), ::tolower);

    auto it = lookup.find(m);
    return (it != lookup.end()) ? it->second : PaymentMode::Unknown;
}

// Checkout function
void checkout(const Payment& payment, double amount) {
    if (amount <= 0) {
        std::cout << "Invalid payment amount!\n";
        return;
    }
    payment.process(amount);
}

// Example usage
int main() {
    double amount = 150.75;
    PaymentFactory factory;

    // Simulated user input
    const std::string userInputs[] = {"PayPal", "GooglePay", "CreditCard", "Bitcoin"};

    for (const auto& input : userInputs) {
        PaymentMode mode = toPaymentMode(input);
        auto payment = factory.createPayment(mode);

        if (payment) {
            checkout(*payment, amount);
        } else {
            std::cout << "Unsupported payment method: " << input << '\n';
        }
    }

    return 0;
}
