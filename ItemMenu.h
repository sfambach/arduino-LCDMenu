#ifndef ITEM_MENU_H
#define ITEM_MENU_H
/**
   menu item can have other items as children
   created by S. Fambach under the GNU Public Licence
*/

class ItemMenu : public Item {
  private:
    bool _value;
    void (*_callback) (bool);
    LinkedList<Item*>* _children;

    int _selChild = 0;

  public:
    ItemMenu(String name, Item* parent ) : Item(name,parent) {
      _children = new LinkedList<Item*>();
    }

    void addChild(Item* item){
      _children->add(item);
    }

    Item* getSelChild() {
      return _children->get(_selChild);
    }

    /** get the current sub item name, returns NO CHILD in Case of missing options*/
    virtual String getContent() {
      if (_children->size() > 0) {
        return getSelChild()->getName();
      }
      else return "NO CHILD";
    }

    boolean selFirstChild() {
      return  _selChild == 0;
    }
    boolean selLastChild() {
      return  (_children->size() - 1 == _selChild ) ;
    }
    boolean moreThanOneChild() {
      return (_children->size() > 1);
    }

    int getChildCount() {
      return _children->size();
    }

    int getSelChildIndex() {
      return _selChild;
    }

    virtual bool optionRight() {
      return !selLastChild();
    }

    virtual bool optionLeft() {
      return !selFirstChild();
    }

    virtual bool optionDown() {
      return _children->size() > 0;
    }
    virtual Item* right() {

      if (_children->size() > 0) {
        if (!selLastChild()) {
          _selChild++;
          //return getSelChild();
        }
      }
      return this;
    }

    virtual Item* left() {
      if (_children->size() > 0) {
        if (!selFirstChild()) {
          _selChild--;
          //return getSelChild();
        }
      }
      return this;
    }

    virtual Item* down() {
      return getSelChild();
    }

};

#endif // ITEM_MENU_H
