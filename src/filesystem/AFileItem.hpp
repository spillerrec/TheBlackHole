#ifndef A_FILE_ITEM_HPP
#define A_FILE_ITEM_HPP

#include <cstdint>

class QString;

class AFileItem{
	public:
		virtual int64_t getTotalSize() = 0;
	//	virtual bool deleteItem() = 0;
		virtual int64_t filesCount() = 0;
		virtual int64_t directoriesCount() = 0;
		
		virtual int64_t childrenCount() = 0;
		virtual AFileItem& getChild( int index ) = 0;
		
		virtual QString name() = 0;
		
		virtual ~AFileItem() { };
};

/** Stores a value which require heavy initialization */
template<typename CachedType>
class Cached{
	private:
		bool valid = false;
		CachedType value;
		
	public:
		/** Returns the value from cache if possible. If not, it calculates it
		 *  using f and updates the cache with the new value
		 *  @param f A function taking no parameters which calculates the value */
		template<typename Func>
		CachedType get( Func f ){
			if( valid ) return value;
			
			valid = true;
			return value = f();
		}
		
		/// Forces recalculation on next call of get()
		void invalidate(){ valid = false; }
};

#endif