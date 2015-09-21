#ifndef FILE_HPP
#define FILE_HPP

#include <QFileInfo>

#include "AFileItem.hpp"

class File : public AFileItem{
	private:
		class Directory* parent;
		QFileInfo info;
		Cached<int64_t> size;
		
	public:
		File( Directory* parent, QFileInfo info ) : parent(parent), info(info) { }
		int64_t getTotalSize() override { return size.get( [&](){ return info.size(); } ); }
		
		int64_t filesCount() override { return 1; }
		int64_t directoriesCount() override { return 0; }
		int64_t childrenCount() override { return 1; }
		AFileItem& getChild( int ) override { return *this; }
		QString name() override { return info.completeBaseName(); }
};

#endif