# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Debug/MinGW-Windows
TARGET = 6Box2DTestbed
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += debug 
PKGCONFIG +=
QT = core gui widgets
SOURCES += main.cpp
HEADERS += H:/Dropbox/practice/qt/Qt4ZetCode/6Box2DTestbed/CircularNode.hpp H:/Dropbox/practice/qt/Qt4ZetCode/6Box2DTestbed/DrawBoard.hpp H:/Dropbox/practice/qt/Qt4ZetCode/6Box2DTestbed/GraphicsViewWidget5.hpp H:/Dropbox/practice/qt/Qt4ZetCode/6Box2DTestbed/GraphicsViewWidget6.hpp H:/Dropbox/practice/qt/Qt4ZetCode/6Box2DTestbed/Parameters.hpp H:/Dropbox/practice/qt/Qt4ZetCode/6Box2DTestbed/PhysicsWorld.hpp H:/Dropbox/practice/qt/Qt4ZetCode/6Box2DTestbed/PolygonNode.hpp
FORMS +=
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Debug/MinGW-Windows
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += /C/Programs/Box2D/include /C/Qt/5.5/mingw492_32/include 
LIBS += -lQt5Cored -lQt5Guid -lQt5Widgetsd C:/Programs/Box2D/lib/libliquidfun.dll.a  
equals(QT_MAJOR_VERSION, 4) {
QMAKE_CXXFLAGS += -std=c++11
}
equals(QT_MAJOR_VERSION, 5) {
CONFIG += c++11
}
