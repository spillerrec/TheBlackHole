/*	This file is part of TheBlackHole, which is free software and is licensed
 * under the terms of the GNU GPL v3.0. (see http://www.gnu.org/licenses/ ) */

#ifndef FILE_ITEM_HPP
#define FILE_ITEM_HPP

#include <QGraphicsRectItem>
#include <memory>

class FileItem : public QGraphicsRectItem{
	private:
		class AFileItem* file;
		std::vector<std::unique_ptr<FileItem>> children;
		class QGraphicsTextItem* text{ nullptr };
		
		void positionChildren();
		
	public:
		FileItem( AFileItem* file, QGraphicsItem* parent=nullptr );
		int64_t mass();
		void initChildren();
		QRectF availableArea() const;
		
		void setSize( QRectF new_size );
};

#endif
