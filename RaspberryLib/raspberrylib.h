/**
RaspberryLib header file. Include this file in the project to use the library.
*/
#ifndef RASPBERRYLIB_RASPBERRYLIB_H
#define RASPBERRYLIB_RASPBERRYLIB_H

#include "RaspberryLibBuilder.h"

namespace RaspberryLib {

/** Instantiate the RaspberryLibBuilder for this object */
RaspberryLibBuilder gRaspberryLibBuilder("RaspberryLib", __TIMESTAMP__);

}

#endif // RASPBERRYLIB_RASPBERRYLIB_H
