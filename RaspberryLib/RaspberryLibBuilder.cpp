/**
RaspberryLibBuilder implementation.
*/

#include "LEDController.h"
#include "RaspberryLibBuilder.h"

using namespace RaspberryLib;

RaspberryLibBuilder::RaspberryLibBuilder(const char* libName, const char* timeStamp)
    : CDPBuilder(libName, timeStamp)
{
}

CDPComponent* RaspberryLibBuilder::CreateNewComponent(const std::string& type)
{
    if (type=="RaspberryLib.LEDController")
        return new LEDController;
    
    return CDPBuilder::CreateNewComponent(type);
}

CDPBaseObject* RaspberryLibBuilder::CreateNewCDPOperator(const std::string& modelName, const std::string& type, const CDPPropertyBase* inputProperty)
{
    return CDPBuilder::CreateNewCDPOperator(modelName, type, inputProperty);
}
