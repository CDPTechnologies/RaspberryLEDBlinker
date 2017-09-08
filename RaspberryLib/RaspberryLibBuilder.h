/**
RaspberryLibBuilder header file.
*/

#ifndef RASPBERRYLIB_RASPBERRYLIBBUILDER_H
#define RASPBERRYLIB_RASPBERRYLIBBUILDER_H

#include <CDPSystem/Application/CDPBuilder.h>

namespace RaspberryLib {

class RaspberryLibBuilder : public CDPBuilder
{
public:
    RaspberryLibBuilder(const char* libName,const char* timeStamp);
    CDPComponent* CreateNewComponent(const std::string& type) override;
    CDPBaseObject* CreateNewCDPOperator(const std::string& modelName,const std::string& type,const CDPPropertyBase* inputProperty) override;
};

}

#endif // RASPBERRYLIB_RASPBERRYLIBBUILDER_H
