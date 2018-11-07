#ifndef ITEM_H
#define ITEM_H
#include <LinkedList.h> 

/** abstact item for the menu 
 *  created by S. Fambach under the GNU Public Licence
*/
class Item {

private:
  String _name;
  Item*  _parent;

public:
  Item (String name, Item* parent):_name(name),_parent(parent){
  }

  /** returns the name of this item */
  String getName(){
    return _name;
  }

  /** return the parent or itself if parent is null*/
  Item* getParent(){
    if(_parent != NULL){
      return _parent;
    } else return this;
  }
  

  virtual String getContent() = 0;
  virtual Item* right() = 0;
  virtual Item* left() = 0;
  virtual Item* up() { return getParent();}
  virtual Item* down() = 0;
  
  virtual boolean optionRight() = 0;
  virtual boolean optionLeft() = 0;
  virtual boolean optionUp() { return _parent != NULL;}
  virtual boolean optionDown() = 0;
 
  
};
#endif // ITEM_H
