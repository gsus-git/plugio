#include "signalManager.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <vector>
#include <memory>

namespace {

template<typename T>
using Signal        = atom::framework::core::Signal<T>;
using SignalBase    = atom::framework::core::SignalBase;
using SignalManager = atom::framework::core::SignalManager;

TEST(Get, CreateMultipleSignals_TheNumberOfSignalsIsRetreived)
{
    SignalManager signalManager;
    std::vector<std::shared_ptr<SignalBase>> signalCollection;
    
    std::string alphabet = "abcdefghijklmnopqrstuvwxyz";
    const static uint32_t NUMBER_OF_SIGNALS = alphabet.size();
    std::for_each( alphabet.begin(), alphabet.end(),[&signalCollection, &signalManager](const char& c)
    { 
        signalCollection.push_back(signalManager.createSignal<bool>(std::string(1, c), true));
    });

    std::cout << "All signals have been created" << std::endl;
    EXPECT_EQ(NUMBER_OF_SIGNALS, signalManager.getNumberOfSignals());
}

}
