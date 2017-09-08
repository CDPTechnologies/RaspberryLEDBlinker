#ifndef RASPBERRYLIB_LEDCONTROLLER_H
#define RASPBERRYLIB_LEDCONTROLLER_H

#include <CDPSystem/Base/CDPComponent.h>
#include <Signal/CDPSignal.h>
#include <CDPParameter/CDPParameter.h>
#include <CDPAlarm/CDPAlarm.h>

namespace RaspberryLib {

class LEDController : public CDPComponent
{
public:
    LEDController();
    ~LEDController() override;

    void Create(const char* fullName) override;
    void CreateModel() override;
    void Configure(const char* componentXML) override;
    void ProcessNull() override;
    void ProcessSine();
    void ProcessSequence();
    void ProcessRandom();
    bool TransitionNullToRandom();
    bool TransitionNullToSequence();
    bool TransitionNullToSine();
    bool TransitionRandomToNull();
    bool TransitionRandomToSequence();
    bool TransitionRandomToSine();
    bool TransitionSequenceToNull();
    bool TransitionSequenceToRandom();
    bool TransitionSequenceToSine();
    bool TransitionSineToNull();
    bool TransitionSineToRandom();
    bool TransitionSineToSequence();
    int MessageTO_SINE(void* message);
    int MessageTO_SEQUENCE(void* message);
    int MessageTO_RANDOM(void* message);
    int MessageTO_NULL(void* message);

protected:
    CDPSignal<bool> L0;
    CDPSignal<bool> L1;
    CDPSignal<bool> L2;
    using CDPComponent::requestedState;
    using CDPComponent::ts;
    using CDPComponent::fs;
};

} // namespace RaspberryLib

#endif
