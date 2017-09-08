#include "LEDController.h"

using namespace RaspberryLib;

/**
 * @brief LEDController::LEDController
 * Constructor, will be called once upon construction of the object.
 */
LEDController::LEDController()
{
}

/**
 * @brief LEDController::~LEDController
 * Destructor, will be called when the object is destroyed or the
 * lifetime has reached its end.
 */
LEDController::~LEDController()
{
}

/**
 * @brief LEDController::Create
 * @param fullName
 * Here the different nodes "signals, parameters ..." get initialized with their name
 * and this component as their parent.
 */
void LEDController::Create(const char* fullName)
{
    CDPComponent::Create(fullName);

    // These are CDPSignal<bool>
    // the code was generated using: context menu->CDP->Add->Signal
    L0.Create("L0",this);
    L1.Create("L1",this);
    L2.Create("L2",this);
}


void LEDController::CreateModel()
{
    CDPComponent::CreateModel();
    /**
     * @brief RegisterStateProcess
     * This code registers our states to the component.
     * The code was generated when adding states via the context menu
     * Context menu->CDP->Add->State
     */
    RegisterStateProcess("Null", (CDPCOMPONENT_STATEPROCESS)&LEDController::ProcessNull, "Initial Null state");
    RegisterStateProcess("Sine",(CDPCOMPONENT_STATEPROCESS)&LEDController::ProcessSine,"");
    RegisterStateProcess("Sequence",(CDPCOMPONENT_STATEPROCESS)&LEDController::ProcessSequence,"");
    RegisterStateProcess("Random",(CDPCOMPONENT_STATEPROCESS)&LEDController::ProcessRandom,"");

    /**
     * @brief RegisterStateTransitionHandler
     * This code registers all the possible transitions with the component
     * Generated when adding state transitions via the context menu
     */
    RegisterStateTransitionHandler("Null","Random",(CDPCOMPONENT_STATETRANSITIONHANDLER)&LEDController::TransitionNullToRandom,"");
    RegisterStateTransitionHandler("Null","Sequence",(CDPCOMPONENT_STATETRANSITIONHANDLER)&LEDController::TransitionNullToSequence,"");
    RegisterStateTransitionHandler("Null","Sine",(CDPCOMPONENT_STATETRANSITIONHANDLER)&LEDController::TransitionNullToSine,"");
    RegisterStateTransitionHandler("Random","Null",(CDPCOMPONENT_STATETRANSITIONHANDLER)&LEDController::TransitionRandomToNull,"");
    RegisterStateTransitionHandler("Random","Sequence",(CDPCOMPONENT_STATETRANSITIONHANDLER)&LEDController::TransitionRandomToSequence,"");
    RegisterStateTransitionHandler("Random","Sine",(CDPCOMPONENT_STATETRANSITIONHANDLER)&LEDController::TransitionRandomToSine,"");
    RegisterStateTransitionHandler("Sequence","Null",(CDPCOMPONENT_STATETRANSITIONHANDLER)&LEDController::TransitionSequenceToNull,"");
    RegisterStateTransitionHandler("Sequence","Random",(CDPCOMPONENT_STATETRANSITIONHANDLER)&LEDController::TransitionSequenceToRandom,"");
    RegisterStateTransitionHandler("Sequence","Sine",(CDPCOMPONENT_STATETRANSITIONHANDLER)&LEDController::TransitionSequenceToSine,"");
    RegisterStateTransitionHandler("Sine","Null",(CDPCOMPONENT_STATETRANSITIONHANDLER)&LEDController::TransitionSineToNull,"");
    RegisterStateTransitionHandler("Sine","Random",(CDPCOMPONENT_STATETRANSITIONHANDLER)&LEDController::TransitionSineToRandom,"");
    RegisterStateTransitionHandler("Sine","Sequence",(CDPCOMPONENT_STATETRANSITIONHANDLER)&LEDController::TransitionSineToSequence,"");

    /**
     * @brief RegisterMessage
     * This code registers messages to the component. The code was generated
     * when adding messages using the context menu.
     */
    RegisterMessage(CM_TEXTCOMMAND,"TO_SINE","",(CDPOBJECT_MESSAGEHANDLER)&LEDController::MessageTO_SINE);
    RegisterMessage(CM_TEXTCOMMAND,"TO_SEQUENCE","",(CDPOBJECT_MESSAGEHANDLER)&LEDController::MessageTO_SEQUENCE);
    RegisterMessage(CM_TEXTCOMMAND,"TO_RANDOM","",(CDPOBJECT_MESSAGEHANDLER)&LEDController::MessageTO_RANDOM);
    RegisterMessage(CM_TEXTCOMMAND,"TO_NULL","",(CDPOBJECT_MESSAGEHANDLER)&LEDController::MessageTO_NULL);
}

void LEDController::Configure(const char* componentXML)
{
    CDPComponent::Configure(componentXML);
}

/**
 * @brief LEDController::ProcessNull
 * The ProcessNull function is the processing function for the default state, the "Null" state.
 * We use it as our "OFF" state in this component.
 *
 * The "Process" function corresponding to the state that the component is in will be called on
 * a interval determined when we create the component. This is the components "fs" property.
 * The "fs" property defaults to 5 times per second, but this can be changed later even while the
 * system is running.
 */
void LEDController::ProcessNull()
{
    L0 = false; // We turn the LED's off by setting L0,L1 and L2 to false
    L1 = false;
    L2 = false;
}

/**
 * @brief ProcessSine()
 * We use a counter that will increment each time the ProcessSine function is called "5 times per second"
 * We set the LED's to light up "true" whenever the counter reaches their number.
 * We flip the increment when the counter reaches an end, this makes it start counting backwards.
 */
int counter = 0;
int increment = 1;
void LEDController::ProcessSine()
{
    L0 = (counter == 0); // True only if counter is equal to 0
    L1 = (counter == 1);
    L2 = (counter == 2);
    counter += increment;
    if(counter == 0 || counter == 2){
        increment *= -1; // Flipping the increment when counter is  0 or 2
    }
}



void LEDController::ProcessSequence()
{
    if(L0 + L1 + L2 != 1){ // We make sure that only one of "L0, L1, L2" is true before we shift the values
        L0 = true;
        L1 = false;
        L2 = false;
    }
    bool temp = L2; // We shift the values so that the next LED can light up.
    L2 = L1;
    L1 = L0;
    L0 = temp;
}

/* Alternative implementation

void LEDController::ProcessSequence()
{
    L0 = (counter == 0); // True only if counter is equal to 0
    L1 = (counter == 1);
    L2 = (counter == 2);
    counter = (counter+1)%3; // The modulo will turn this in to a ring of size 3 "0,1,2,0,1,2..."
}

*/

void LEDController::ProcessRandom()
{
    L0 = rand()%2; // Simple cointoss, 0 or 1 | true or false | 50/50
    L1 = rand()%2;
    L2 = rand()%2;
}


/**
 * @brief LEDController::TransitionNullToRandom
 * The transition functions generated by adding the transitions have not been used in this code.
 * They can be used for setting up before entering a state.
 */
bool LEDController::TransitionNullToRandom()
{
    if(requestedState=="Random")
        // Here we could place some code that would run right before entering the "Random" state.
        // maybe we would like all the LED's to be turned on
        // L0 = L1 = L2 = true;
        return true;
    else
        return false;
}



bool LEDController::TransitionNullToSequence()
{
    if(requestedState=="Sequence")
        return true;
    else
        return false;
}



bool LEDController::TransitionNullToSine()
{
    if(requestedState=="Sine")
        return true;
    else
        return false;
}



bool LEDController::TransitionRandomToNull()
{
    if(requestedState=="Null")
        return true;
    else
        return false;
}



bool LEDController::TransitionRandomToSequence()
{
    if(requestedState=="Sequence")
        return true;
    else
        return false;
}



bool LEDController::TransitionRandomToSine()
{
    if(requestedState=="Sine")
        return true;
    else
        return false;
}



bool LEDController::TransitionSequenceToNull()
{
    if(requestedState=="Null")
        return true;
    else
        return false;
}



bool LEDController::TransitionSequenceToRandom()
{
    if(requestedState=="Random")
        return true;
    else
        return false;
}



bool LEDController::TransitionSequenceToSine()
{
    if(requestedState=="Sine")
        return true;
    else
        return false;
}



bool LEDController::TransitionSineToNull()
{
    if(requestedState=="Null")
        return true;
    else
        return false;
}



bool LEDController::TransitionSineToRandom()
{
    if(requestedState=="Random")
        return true;
    else
        return false;
}



bool LEDController::TransitionSineToSequence()
{
    if(requestedState=="Sequence")
        return true;
    else
        return false;
}


/**
 * @brief LEDController::MessageTO_SINE
 * These are message handlers. They get called whenever the component
 * recieves their corresponding message
 */
int LEDController::MessageTO_SINE(void* message)
{
    // We use the message handlers to set the requested state.
    // This will ensure that the state will change as soon as the component is able.
    requestedState = "Sine";
    return 1;

}



int LEDController::MessageTO_SEQUENCE(void* message)
{
    requestedState = "Sequence";
    return 1;

}



int LEDController::MessageTO_RANDOM(void* message)
{
    requestedState = "Random";
    return 1;

}



int LEDController::MessageTO_NULL(void* message)
{
    requestedState = "Null";
    return 1;

}
