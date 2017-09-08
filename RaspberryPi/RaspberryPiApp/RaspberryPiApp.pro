TYPE = application
PROJECTNAME = RaspberryPiApp

DEPS += \
    gpiopinio \
    raspberrylib

HEADERS += Libraries.h
SOURCES += CDPMain.cpp

DISTFILES += \
    $$files(*.xml, true) \
    $$files(*.lic, true) \
    $$files(Application/www/*.*, true)

load(cdp)
