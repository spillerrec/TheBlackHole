/*	This file is part of TheBlackHole, which is free software and is licensed
 * under the terms of the GNU GPL v3.0. (see http://www.gnu.org/licenses/ ) */

#include "MainWindow.hpp"

#include <QFileDialog>
#include <QHBoxLayout>

MainWindow::MainWindow( QString path, QWidget* parent ) : QWidget(parent), view( this ) {
	setLayout( new QHBoxLayout( this ) );
	layout()->addWidget( &view );
	layout()->setContentsMargins(0,0,0,0);
	
	if( path.isEmpty() )
		setDirectory();
	else
		view.setPath( path );
}

void MainWindow::setDirectory(){
	view.setPath( QFileDialog::getExistingDirectory( this, "Select folder to analyse" ) );
}

