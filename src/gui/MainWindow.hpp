/*	This file is part of TheBlackHole, which is free software and is licensed
 * under the terms of the GNU GPL v3.0. (see http://www.gnu.org/licenses/ ) */

#ifndef MAIN_WINDOW_HPP
#define MAIN_WINDOW_HPP

#include <QWidget>

#include "DirView.hpp"

class MainWindow : public QWidget{
	private:
		DirView view;
		
	public:
		MainWindow( QString path, QWidget* parent=nullptr );
		void setDirectory();
};

#endif