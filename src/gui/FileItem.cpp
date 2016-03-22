/*	This file is part of TheBlackHole, which is free software and is licensed
 * under the terms of the GNU GPL v3.0. (see http://www.gnu.org/licenses/ ) */

#include "FileItem.hpp"
#include "../filesystem/AFileItem.hpp"

#include <QBrush>
#include <QPainter>
#include <QColor>
#include <QPen>
#include <QGraphicsTextItem>

FileItem::FileItem( AFileItem* file ) : file(file), text( file->name() ) {
	
}

void setHover( bool enabled ){
	//TODO:
	
}

void FileItem::initChildren(){
	children.clear();
	children.reserve( file->childrenCount() );
	for( int i=0; i<file->childrenCount(); i++ )
		children.emplace_back( &file->getChild(i) );
	
	auto biggest_first = [](auto& a, auto& b){ return a.mass() > b.mass(); };
	std::sort( children.begin(), children.end(), biggest_first );
}

void FileItem::setSize( QRect new_size ){
	position = new_size;
	
	if( new_size.width() * new_size.height() > 5000 ){
		if( children.size() == 0 )
			initChildren();
	}
	else
		children.clear();
	
	positionChildren();
}

QRectF FileItem::availableArea() const{
	auto reserved = text.size().height();
	auto pos = QPointF( position.left(),  position.top()    + reserved );
	auto size = QSizeF( position.width(), position.height() - reserved );
	return QRectF( pos, size );
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
			{ return mass / double(current_mass) * area.height(); }
		
		double currentFit(){
			double fit = 0.0;
			for( auto file : column )
				fit -= std::abs( 1.0 - columnWidth() / itemHeight( file->mass() ) );
			return fit / column.size();
		}
		
		/** Reszises the column, and moves to the next */
		void commit(){
			auto width = columnWidth();
			int i_x = std::round( current.x() );
			int i_width = std::round( current.x() + width ) - i_x;
			
			double progress = current.y();
			for( auto file : column ){
				auto height = itemHeight( file->mass() );
				int i_y = std::round( progress );
				int i_height = std::round( progress + height ) - i_y;
				
				file->setSize( {i_x, i_y, i_width, i_height} );
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
	Positioner positioner( availableArea(), file->getTotalSize() );
	for( auto& child : children )
		positioner.addChild( &child );
	positioner.commit();
}

int64_t FileItem::mass(){ return file->getTotalSize(); }


void FileItem::paint( QPainter& painter, QRect region ){
	//TODO:
	painter.setClipRect( position );
	auto minSize = text.size().height();
	if( position.width() > minSize/2 && position.height() > minSize*0.66 )
		painter.drawStaticText( position.topLeft(), text );
	
	auto color = file->isFolder() ? QColor( 255,255,000, 64 ) : QColor( 0,0,255, 128 );
	painter.setBrush( { color } );
	painter.drawRect( position );
//	qDebug( "painted %d %d %d %d", position.x(), position.y(), position.width(), position.height() );
	
	for( auto& child : children )
		child.paint( painter, child.position );
}
