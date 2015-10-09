/*	This file is part of TheBlackHole, which is free software and is licensed
 * under the terms of the GNU GPL v3.0. (see http://www.gnu.org/licenses/ ) */

#include <QApplication>
#include <QStringList>
#include <QDebug>
#include <iostream>

#include "filesystem/Directory.hpp"
#include "gui/MainWindow.hpp"


int main( int argc, char* argv[] ){
	QApplication app( argc, argv );
	
	auto args = app.arguments();
	auto folder = (args.size() < 2 ) ? "" : args[1];
	
	MainWindow w( folder );
	w.show();
	
	/*
	Directory dir( nullptr, folder );
	dir.update();
	std::cout << "Total size: " << dir.getTotalSize() << std::endl;
	std::cout << "Dir count: " << dir.directoriesCount() << std::endl;
	std::cout << "Files count: " << dir.filesCount() << std::endl;
	*/
	
	return app.exec();
}