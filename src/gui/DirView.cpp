/*	This file is part of TheBlackHole, which is free software and is licensed
 * under the terms of the GNU GPL v3.0. (see http://www.gnu.org/licenses/ ) */

#include "DirView.hpp"

#include <QResizeEvent>
#include <QPainter>

DirView::DirView( QWidget* parent )
	: QWidget(parent), dir( nullptr, QFileInfo() ), item(&dir) { }

void DirView::setPath( QString path ){
	dir = Directory( nullptr, path );
	dir.update();
	
	QResizeEvent event( size(), size() ); //NOTE: Not really nessesary
	resizeEvent( &event );
}

void DirView::resizeEvent( QResizeEvent* )
	{ item.setSize( { QPoint(0,0), size() } ); }

void DirView::paintEvent( QPaintEvent* event ){
	QPainter painter( this );
	item.paint( painter, event->rect() );
}
