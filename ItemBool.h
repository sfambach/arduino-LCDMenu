#ifndef ITEM_BOOL_H
#define ITEM_BOOL_H

/**
 * Boolean benu item
 * You are able to switch it off and on
 * created by S. Fambach under the GNU Public Licence
 */
class ItemBool : public Item {
private:
    boolean* _value;
    void (*_callback) (boolean);

public:
    ItemBool(String name, Item* parent, boolean* value, void (*callback)(boolean)) : Item(name, parent), _value(value), _callback(callback){
      
    }

    virtual String getContent(){
      return (*_value) ? "ON" : "OFF";
    }

    virtual boolean optionRight(){
      return !(*_value);
    }

    virtual boolean optionLeft(){
      return (*_value);
    }
    virtual Item* right(){
      if(optionRight()){
        (*_value) = true;
        if(_callback){
          _callback(*_value);
        }
      } 
      return this;
    }

    virtual Item* left(){
      if(optionLeft()){
        (*_value) = false;
        if(_callback){
          _callback(*_value);
        }
      } 
      return this;
    }

    virtual Item* down(){
      return this;
    }
    
  virtual boolean optionDown() { return false;}
};

#endif // ITEM_BOOL_H

