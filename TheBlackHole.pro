TEMPLATE = app
TARGET = TheBlackHole
QT += widgets
QMAKE_CXXFLAGS += -std=c++14

# Input
HEADERS += src/filesystem/AFileItem.hpp \
           src/filesystem/Directory.hpp \
           src/filesystem/File.hpp
SOURCES += src/main.cpp src/filesystem/Directory.cpp src/filesystem/File.cpp

# Gui
HEADERS += src/gui/MainWindow.hpp src/gui/DirView.hpp src/gui/FileItem.hpp
SOURCES += src/gui/MainWindow.cpp src/gui/DirView.cpp src/gui/FileItem.cpp