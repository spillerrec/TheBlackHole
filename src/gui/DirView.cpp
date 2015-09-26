#include "DirView.hpp"

DirView::DirView( QString path, QWidget* parent )
	: QGraphicsView(parent), scene(this), dir( nullptr, path ), item(&dir) {
//	scene.setBackgroundBrush(Qt::blue);
	scene.addItem( &item );
	setScene(&scene);
	
	dir.update();
	item.setRect( 0,0, width(), height() );
	item.initChildren();
}

void DirView::resizeEvent( QResizeEvent* ) {
	item.setRect( 0,0, width(), height() );
	item.initChildren();
}