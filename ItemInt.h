#ifndef ITEM_INT_H
#define ITEM_INT_H
/**
 * integer item user can add/sub 1
 * max and min value can be defined
 * created by S. Fambach under the GNU Public Licence
 */
class ItemInt : public Item{

private:
    int* _value;
    int  _min = 0;
    int  _max = 100;
    void (*_callback) (int);

public:
    ItemInt(String name, Item* parent, int* value, int min, int max, void (*callback)(int)) : Item(name, parent), _value(value),_min(min), _max(max), _callback(callback){
     
    }

    virtual String getContent(){
      return String(*_value);
    }

    virtual boolean optionRight(){
      return (*_value) < _max;
    }

    virtual boolean optionLeft(){
      return (*_value) > _min;
    }
    virtual Item* right(){
      if(optionRight()){
        (*_value)++;
        if(_callback){
          _callback(*_value);
        }
      } 
      return this;
    }

    virtual Item* left(){
      if(optionLeft()){
        (*_value) --;
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

#endif // ITEM_INT_H


