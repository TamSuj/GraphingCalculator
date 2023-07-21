TEMPLATE = app
CONFIG += console
#CONFIG -= app_bundle

#since we want to use qDebug, we
#will not subtract qt.
#CONFIG -= qt

SOURCES += main.cpp \
    system.cpp \
    random.cpp \
    sidebar.cpp \
    animate.cpp

#LIBS += -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
##LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
#INCLUDEPATH += usr/local/include
#DEPENDPATH += usr/local/include
#------------------------------------------
##Add these lines for SFML:

CONFIG += c++11


LIBS += -L"/usr/local/lib"

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window
CONFIG(debug, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-system -lsfml-network -lsfml-window

INCLUDEPATH += "/usr/local/include"
DEPENDPATH += "/usr/local/include"
#-----------------------------------------


HEADERS += \
    constants.h \
    system.h \
    random.h \
    sidebar.h \
    animate.h
