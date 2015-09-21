#ifndef FILE_ITEM_HPP
#define FILE_ITEM_HPP

#include <QGraphicsRectItem>

class FileItem : public QGraphicsRectItem{
	private:
		class AFileItem* file;
		std::vector<FileItem*> children;
		class QGraphicsTextItem* text;
		
		void positionChildren();
		
	public:
		FileItem( AFileItem* file, QGraphicsItem* parent=nullptr );
		int64_t mass();
		void initChildren();
};

#endif