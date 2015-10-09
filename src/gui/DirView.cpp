#include "DirView.hpp"

DirView::DirView( QString path, QWidget* parent )
	: QGraphicsView(parent), scene(this), dir( nullptr, path ), item(&dir) {
//	scene.setBackgroundBrush(Qt::blue);
	scene.addItem( &item );
	setScene(&scene);
	
	dir.update();
	updateScene();
}

void DirView::updateScene(){
	scene.setSceneRect( 0,0, viewport()->width(), viewport()->height() );
	item.setRect(       0,0, viewport()->width(), viewport()->height() );
	item.initChildren();
}
