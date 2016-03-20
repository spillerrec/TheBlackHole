/*	This file is part of TheBlackHole, which is free software and is licensed
 * under the terms of the GNU GPL v3.0. (see http://www.gnu.org/licenses/ ) */

#include "DirView.hpp"

DirView::DirView( QWidget* parent )
	: QGraphicsView(parent), scene(this), dir( nullptr, QFileInfo() ), item(&dir) {
//	scene.setBackgroundBrush(Qt::blue);
	scene.addItem( &item );
	setScene(&scene);
}

void DirView::setPath( QString path ){
	dir = Directory( nullptr, path );
	dir.update();
	updateScene();
}

void DirView::updateScene(){
	scene.setSceneRect(  0,0, viewport()->width(), viewport()->height()  );
	item.setSize(      { 0,0, viewport()->width(), viewport()->height() });
}
