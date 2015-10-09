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
	scene.setSceneRect( 0,0, viewport()->width(), viewport()->height() );
	item.setRect(       0,0, viewport()->width(), viewport()->height() );
	item.initChildren();
}
