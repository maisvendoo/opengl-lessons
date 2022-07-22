TEMPLATE = app

CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++17

TARGET = cube

DESTDIR = ../../bin

win32 {

    CONFIG(debug, debug|release) {

        TARGET = $$join(TARGET,,,_d)

    } else {

    }

    INCLUDEPATH += $(GLFW_DIR)/include

    LIBS += -L$(GLFW_DIR)/bin -lglfw3
    LIBS += -L../../lib -lshader_s
}

unix {

    CONFIG(debug, debug|release) {

        TARGET = $$join(TARGET,,,_d)

    } else {

    }

}

INCLUDEPATH += ./include
INCLUDEPATH += ../deps/glad/include
INCLUDEPATH += ../shader_s/include
INCLUDEPATH += ../deps/stb/include
INCLUDEPATH += ../deps/glm/include

HEADERS += $$files(./include/*.h)
SOURCES += $$files(./src/*.cpp)
SOURCES += ../deps/glad/src/glad.c
SOURCES += ../deps/stb/src/stb_image.cpp
