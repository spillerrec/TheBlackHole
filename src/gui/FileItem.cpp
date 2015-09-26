#include "FileItem.hpp"
#include "../filesystem/AFileItem.hpp"

#include <QBrush>
#include <QColor>
#include <QGraphicsTextItem>

FileItem::FileItem( AFileItem* file, QGraphicsItem* parent ) : QGraphicsRectItem(parent), file(file) {
	setBrush( QBrush( QColor( 255,255,000, 128 ) ) );
	text = new QGraphicsTextItem( file->name(), this );
	setFlags( QGraphicsItem::ItemClipsChildrenToShape );
}

void FileItem::initChildren(){
	for( auto& child : children ) delete child;
	children.clear();
	children.reserve( file->childrenCount() );
	for( int i=0; i<file->childrenCount(); i++ )
		children.push_back( new FileItem( &file->getChild(i), this ) );
	
	positionChildren();
}

void FileItem::positionChildren(){
	text->setPos( rect().topLeft() );
	auto reserved = text->boundingRect().height();
	
	std::sort( children.begin(), children.end()
		,	[](auto a, auto b){ return a->mass() > b->mass(); } );
	
	double total = (rect().height()-reserved) / file->getTotalSize();
	double progress = rect().y() + reserved;
	for( auto child : children ){
		double height = child->mass() * total;
		child->setRect( rect().x(), progress, rect().width(), height );
		progress += height;
		child->positionChildren();
	}
}

int64_t FileItem::mass(){ return file->getTotalSize(); }