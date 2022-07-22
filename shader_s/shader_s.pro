TEMPLATE = lib

CONFIG += staticlib
CONFIG -= qt
CONFIG += c++17

TARGET = shader_s

DESTDIR = ../../lib

win32 {

}

unix {


}

INCLUDEPATH += ./include
INCLUDEPATH += ../deps/glad/include
INCLUDEPATH += ../deps/glm/include

HEADERS += $$files(./include/*.h)
SOURCES += $$files(./src/*.cpp)
SOURCES += ../deps/glad/src/glad.c
