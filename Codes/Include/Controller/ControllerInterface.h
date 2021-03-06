#ifndef _ControllerInterface_h_
#define _ControllerInterface_h_

#include "ace/Reactor.h"

class ControllerInterface: public ACE_Event_Handler
{
public:
    ControllerInterface() {};
    virtual ~ControllerInterface() {};

    static ControllerInterface &GetInstance();
    virtual bool Start(ACE_Reactor *reactor, const char *cfgPath) = 0;
};



#endif