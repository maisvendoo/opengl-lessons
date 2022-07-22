TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++17

TARGET = transform

DESTDIR = ../../bin

win32 {

    CONFIG(debug, debug|release) {

        TARGET = $$join(TARGET,,,_d)

    } else {

    }

    INCLUDEPATH += $(GLFW_DIR)/include

    LIBS += -L$(GLFW_DIR)/bin -lglfw3

}

unix {

    CONFIG(debug, debug|release) {

        TARGET = $$join(TARGET,,,_d)

    } else {

    }

}

INCLUDEPATH += ./include
INCLUDEPATH += ../deps/glad/include
INCLUDEPATH += ../deps/shader_s/include
INCLUDEPATH += ../deps/stb/include
INCLUDEPATH += ../deps/glm/include

HEADERS += $$files(./include/*.h)
SOURCES += $$files(./src/*.cpp)
SOURCES += ../deps/glad/src/glad.c
SOURCES += ../deps/shader_s/src/shader.cpp
SOURCES += ../deps/stb/src/stb_image.cpp
