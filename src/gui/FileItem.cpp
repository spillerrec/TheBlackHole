/*	This file is part of TheBlackHole, which is free software and is licensed
 * under the terms of the GNU GPL v3.0. (see http://www.gnu.org/licenses/ ) */

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

void FileItem::setSize( QRectF new_size ){
	setRect( new_size );
	text->setPos( new_size.topLeft() );
}


class Positioner{
	private:
		QRectF area;
		QPointF current;
		std::vector<FileItem*> column;
		int64_t total_mass;
		int64_t current_mass{ 0 };
		
		
		void addFileItem( FileItem* item ){
			column.push_back( item );
			current_mass += item->mass();
		}
		void clear(){
			column.clear();
			current_mass = 0;
		}
		Positioner( const Positioner& copy ) = default;
		
	public:
		Positioner( QRectF area, int64_t total_mass )
			: area(area), current(area.topLeft()), total_mass(total_mass) { }
		
		double columnWidth() const
			{ return current_mass / double(total_mass) * area.width(); }
			
		double itemHeight( int64_t mass ) const
			{ return area.height() * (mass / double(current_mass)); }
		
		double currentFit(){
			double fit = 0.0;
			for( auto file : column )
				fit -= std::abs( 1.0 - columnWidth() / itemHeight( file->mass() ) );
			return fit / column.size();
		}
		
		/** Reszises the column, and moves to the next */
		void commit(){
			auto width = columnWidth();
			double progress = current.y();
			for( auto file : column ){
				auto height = itemHeight( file->mass() );
				file->setSize( {current.x(), progress, width, height} );
				progress += height;
			}
			current.setX( current.x() + width );
			
			
			clear();
		}
		
		void addChild( FileItem* child ){
			//Copy where this child have been added
			auto added = Positioner(*this);
			added.addFileItem( child );
			
			//Finalize column if it does not make sense to add more to it
			if( added.currentFit() < currentFit() )
				commit();
			
			addFileItem( child );
		}
};

void FileItem::positionChildren(){
	text->setPos( rect().topLeft() );
	auto reserved = text->boundingRect().height();
	
	auto biggest_first = [](auto a, auto b){ return a->mass() > b->mass(); };
	std::sort( children.begin(), children.end(), biggest_first );
	
	auto available = QRectF( rect().left(), rect().top() + reserved, rect().width(), rect().height() );
	Positioner positioner( available, file->getTotalSize() );
	for( auto child : children )
		positioner.addChild( child );
}

int64_t FileItem::mass(){ return file->getTotalSize(); }
