TEMPLATE = lib
CONFIG -= qt
CONFIG += c++11
TARGET = ocvcr

INCLUDEPATH += $$(GODOT_HOME)/godot_headers \
               $$(GODOT_HOME)/include \
			   $$(GODOT_HOME)/include/core \
			   $$(GODOT_HOME)/include/gen

DEPENDPATH += $$(GODOT_HOME)/godot_headers \
              $$(GODOT_HOME)/include \
			  $$(GODOT_HOME)/include/core \
			  $$(GODOT_HOME)/include/gen

SOURCES += \
	ocv-camera-reader.cpp \
	screen.cpp

HEADERS += \
    screen.h

unix:!macx: LIBS += -L$$(GODOT_HOME)/bin/ -lgodot-cpp.linux.release.64

unix:!macx: PRE_TARGETDEPS += $$(GODOT_HOME)/bin/libgodot-cpp.linux.release.64.a

unix: CONFIG += link_pkgconfig
unix: PKGCONFIG += opencv4
