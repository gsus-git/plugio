#include "slot.hpp"
#include "signalTypes.hpp"

namespace plugio::framework::core {

SlotBase::SlotBase(const std::string & name) :
    name_(name)
{ }

SlotBase::~SlotBase()
{ }

void SlotBase::signalChange(Boolean value)
{
    std::cout << "Error: This slot does not support Boolean" << std::endl;
}

void SlotBase::signalChange(Number value)
{
    std::cout << "Error: This slot does not support Number" << std::endl;
}

}

