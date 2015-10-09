/*	This file is part of TheBlackHole, which is free software and is licensed
 * under the terms of the GNU GPL v3.0. (see http://www.gnu.org/licenses/ ) */

#ifndef DIR_VIEW_HPP
#define DIR_VIEW_HPP

#include <QGraphicsView>
#include <QGraphicsScene>

#include "../filesystem/Directory.hpp"
#include "FileItem.hpp"

class DirView : public QGraphicsView{
	private:
		QGraphicsScene scene;
		Directory dir;
		FileItem item;
		
		void updateScene();
		
	public:
		DirView( QWidget* parent=nullptr );
		void setPath( QString path );
		
	protected:
		void resizeEvent( class QResizeEvent* ) override { updateScene(); }
};

#endif