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