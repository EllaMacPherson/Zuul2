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
  //print when they enter such room
  void print();

  //map variable for each room, first var is direction of exit , second var is WHERE that exit goes too
  map<const char*, Room*> exitMap;
  
  struct Item{
    const char* itemDescription;
  };

  vector<Item*> itemsInRoom;
  void addItem(const char*);
  void deleteItem(const char*);
  vector<Item*> getItems();
  

 protected:
  //location
  char* description;
  //vector of items in room.
  vector<Item*> roomItems;
};
