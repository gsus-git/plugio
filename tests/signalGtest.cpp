#include "signal.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <iostream>
#include <condition_variable>
#include <chrono>

namespace {

template<typename T>
using Signal = plugio::framework::core::Signal<T>;

TEST(Set, DISABLED_SetSillyTests)
{
    bool notified = false;
    Signal<bool> * signal1 = new Signal<bool>(0, false);
    Signal<bool> * signal2 = new Signal<bool>(1, true);
    auto id1 = signal1->connect([signal2](bool value)
    { 
        std::cout << "new value signal 2 = " << (value ? "true" : "false") << std::endl; 
        signal2->set(!value);
    });
    
    auto id2 = signal2->connect([signal1](bool value)
    { 
        std::cout << "new value signal 1 = " << (value ? "true" : "false") << std::endl; 
        signal1->set(value);
    });

    signal1->set(true); 
    sleep(2);
    signal1->disconnect(id1);
    signal2->disconnect(id2);
    delete signal1;
    delete signal2;
    EXPECT_TRUE(notified);
}

TEST(Set, SetNewBoolValue_ObserverIsNotified)
{
    std::condition_variable cv;
    std::mutex mtx;
    std::unique_lock<std::mutex> lck(mtx);

    Signal<bool> signal(0, false);
    signal.connect([&cv, &mtx](bool value)
    {
        std::unique_lock<std::mutex> lck(mtx);
        cv.notify_all();
    });
    signal.set(true); 

    auto cvWait = cv.wait_for(lck, std::chrono::seconds(1)); 
    EXPECT_EQ(std::cv_status::no_timeout, cvWait);
}

TEST(Set, SetNewNumValue_ObserverIsNotified)
{
    std::condition_variable cv;
    std::mutex mtx;
    std::unique_lock<std::mutex> lck(mtx);

    Signal<float> signal(0, 0);
    signal.connect([&cv, &mtx](float value)
    {
        std::unique_lock<std::mutex> lck(mtx);
        cv.notify_all();
    });
    signal.set(true);

    auto cvWait = cv.wait_for(lck, std::chrono::seconds(1));
    EXPECT_EQ(std::cv_status::no_timeout, cvWait);    
}

TEST(Set, SetNewStrValue_ObserverIsNotified)
{
    std::condition_variable cv;
    std::mutex mtx;
    std::unique_lock<std::mutex> lck(mtx);

    Signal<std::string> signal(0, "");
    signal.connect([&cv, &mtx](std::string value)
    {
        std::unique_lock<std::mutex> lck(mtx);
        cv.notify_all();
    });
    signal.set("abc");
    
    auto cvWait = cv.wait_for(lck, std::chrono::seconds(1));
    EXPECT_EQ(std::cv_status::no_timeout, cvWait);
}

TEST(Set, SetSameBoolValue_ObserversAreNotNotified)
{
    bool notified = false;
    Signal<bool> signal(0, false);
    signal.connect([&notified](bool value){ notified = true; });    
    signal.set(false);
    
    sleep(0.1);
    EXPECT_FALSE(notified);
}

TEST(Set, SetSameNumValue_ObserversAreNotNotified)
{
    bool notified = false;
    Signal<float> signal(0, 33);
    signal.connect([&notified](float value){ notified = true; });    
    signal.set(33);
    
    sleep(0.1);
    EXPECT_FALSE(notified);
}

TEST(Set, SetSameStrValue_ObserversAreNotNotified)
{
    bool notified = false;
    Signal<std::string> signal(0, "abc");
    signal.connect([&notified](std::string value){ notified = true; });    
    signal.set("abc");
    
    sleep(0.1);
    EXPECT_FALSE(notified);
}

TEST(Set, SetNewBoolValue_MultipleObserversAreNotified)
{
    std::condition_variable cv;
    std::mutex mtx;
    std::unique_lock<std::mutex> lck(mtx);
    
    bool notified_1 = false;
    bool notified_2 = false;
    bool notified_3 = false;

    Signal<bool> signal(0, false);

    signal.connect([&notified_1](bool value){ notified_1 = true;});    
    signal.connect([&notified_2](bool value){ notified_2 = true;});    
    signal.connect([&notified_3](bool value){ notified_3 = true;});    
    signal.connect([&cv, &mtx](bool value)
    {
        std::unique_lock<std::mutex> lck(mtx);
        cv.notify_all();
    });
    signal.set(true); 

    auto cvWait = cv.wait_for(lck, std::chrono::seconds(1)); 
    
    EXPECT_EQ(std::cv_status::no_timeout, cvWait);
    EXPECT_TRUE(notified_1);
    EXPECT_TRUE(notified_2);
    EXPECT_TRUE(notified_3);
}

TEST(Set, SetNewNumValue_MultipleObserversAreNotified)
{
    std::condition_variable cv;
    std::mutex mtx;
    std::unique_lock<std::mutex> lck(mtx);
    
    bool notified_1 = false;
    bool notified_2 = false;
    bool notified_3 = false;

    Signal<float> signal(0, 0);

    signal.connect([&notified_1](float value){ notified_1 = true;});    
    signal.connect([&notified_2](float value){ notified_2 = true;});    
    signal.connect([&notified_3](float value){ notified_3 = true;});    
    signal.connect([&cv, &mtx](float value)
    {
        std::unique_lock<std::mutex> lck(mtx);
        cv.notify_all();
    });
    signal.set(0.4); 

    auto cvWait = cv.wait_for(lck, std::chrono::seconds(1)); 
    
    EXPECT_EQ(std::cv_status::no_timeout, cvWait);
    EXPECT_TRUE(notified_1);
    EXPECT_TRUE(notified_2);
    EXPECT_TRUE(notified_3);
}

TEST(Set, SetNewStrValue_MultipleObserversAreNotified)
{
    std::condition_variable cv;
    std::mutex mtx;
    std::unique_lock<std::mutex> lck(mtx);
    
    bool notified_1 = false;
    bool notified_2 = false;
    bool notified_3 = false;

    Signal<std::string> signal(0, "");

    signal.connect([&notified_1](std::string value){ notified_1 = true;});    
    signal.connect([&notified_2](std::string value){ notified_2 = true;});    
    signal.connect([&notified_3](std::string value){ notified_3 = true;});    
    signal.connect([&cv, &mtx](std::string value)
    {
        std::unique_lock<std::mutex> lck(mtx); 
        cv.notify_all();
    });    
    signal.set("Signaling..."); 

    auto cvWait = cv.wait_for(lck, std::chrono::seconds(1)); 
    
    EXPECT_EQ(std::cv_status::no_timeout, cvWait);
    EXPECT_TRUE(notified_1);
    EXPECT_TRUE(notified_2);
    EXPECT_TRUE(notified_3);
}

TEST(Get, SetNewNumValue_SameValueIsReturnsGet)
{
    Signal<float> signal(0, 0);
    signal.set(1);
    EXPECT_EQ(1, signal.get());
}

TEST(Get, SetNewBoolValue_SameValueIsReturnsGet)
{
    Signal<bool> signal(0, false);
    signal.set(true);
    EXPECT_EQ(true, signal.get());
}

TEST(Get, SetNewStrValue_SameValueIsReturnsGet)
{
    Signal<std::string> signal(0, "sdf");
    signal.set("abc");
    EXPECT_EQ("abc", signal.get());
}

}
