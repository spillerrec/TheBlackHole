/*	This file is part of TheBlackHole, which is free software and is licensed
 * under the terms of the GNU GPL v3.0. (see http://www.gnu.org/licenses/ ) */

#ifndef FILE_ITEM_HPP
#define FILE_ITEM_HPP

#include <QWidget>
#include <QStaticText>
#include <memory>

class FileItem{
	private:
		class AFileItem* file;
		std::vector<FileItem> children;
		QStaticText text;
		QRect position;
		
		void positionChildren();
		
		
	public:
		FileItem( AFileItem* file );
		int64_t mass();
		void initChildren();
		QRect availableArea() const;
		
		void setSize( QRect new_size );
		void paint( QPainter& painter, QRect region );
		
		void setHover( bool enabled );
};

#endif
