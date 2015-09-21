#include <QApplication>
#include <QStringList>
#include <QDebug>
#include <iostream>

#include "filesystem/Directory.hpp"
#include "gui/MainWindow.hpp"
#include "gui/DirView.hpp"


int main( int argc, char* argv[] ){
	QApplication app( argc, argv );
	auto args = app.arguments();
	
	if( args.size() < 2 ){
		qDebug() << "Insufficient arguments, specify folder to find";
		return -1;
	}
	auto folder = args[1];
	
	DirView w( folder );
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