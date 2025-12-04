#include <iostream>
#include <vector>
#include <map> //figure out how to use lol.


using namespace std;


class Room{
 public:
  //func to set description
  Room(const char* inDescription);
  //set exits with map?
  void setExit(const char*, Room*);
  //print when they enter room
  void print();

  //map variable for each room, first var is direction of exit , second var is WHERE that exit goes too
  map<const char*, Room*> exitMap;

  
  //item struct
  struct Item{
    const char* itemDescription;
  };

  //keep track of items in room
  vector<Item*> itemsInRoom;

  //add, remov, retrieve items
  void addItem(const char*);
  void deleteItem(const char*);
  vector<Item*> getItems();
  

 protected:
  //room
  char* description;
  //vector of items in room
  vector<Item*> roomItems;
};
