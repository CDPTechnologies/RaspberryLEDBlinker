CDPVERSION = 4.2
TYPE = library
PROJECTNAME = RaspberryLib

DEPS += \

HEADERS += \
    raspberrylib.h \
    RaspberryLibBuilder.h \
    LEDController.h

SOURCES += \
    RaspberryLibBuilder.cpp \
    LEDController.cpp

DISTFILES += $$files(*.xml, true) \
    Templates/Models/RaspberryLib.LEDController.xml

load(cdp)
