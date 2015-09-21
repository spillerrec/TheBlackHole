#ifndef DIRECTORY_HPP
#define DIRECTORY_HPP

#include "AFileItem.hpp"
#include "File.hpp"

#include <QFileInfo>
#include <vector>

class Directory : public AFileItem{
	private:
		Directory* parent;
		QFileInfo directory;
		std::vector<Directory> dirs;
		std::vector<File> files;
		
		Cached<int64_t> total_size;
		
	public:
		Directory( Directory* parent, QFileInfo directory )
			: parent(parent), directory(directory) { }
		
		void update();
		int64_t getTotalSize() override;
		
		int64_t filesCount() override;
		int64_t directoriesCount() override;
};

#endif