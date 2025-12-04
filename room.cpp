#include "room.h"
#include <iostream>
#include<vector>
#include <map>
#include <cstring>

using namespace std;

//Room constructer, set description of new rooms
Room::Room(const char* inDescription){
  description = new char[500];
  strcpy(description, inDescription);
  
}

//what prints when you move to a new room
void Room::print(){
  //print description
  cout<<description<<endl;
  //print items
  cout<<"Items available: ";
  vector<Room::Item*> currentItems = getItems();
  if(currentItems.size() == 0){
    cout<<"No items here ";
  }else{
    for(int i = 0; i < currentItems.size(); i++){
      cout<< currentItems[i]->itemDescription;
    }  
  }

  //print exits
  cout<<endl;
  cout<<"Exits: "<<endl;
  for(map<const char*, Room*>::iterator it = exitMap.begin(); it != exitMap.end(); ++it){
    cout<<it->first<<endl;
  }
}

//adds an exit to the room
void Room::setExit(const char* direction, Room* exitRoom){
  //add direction of exit, and then where that leads
  exitMap.emplace(direction, exitRoom);   
}

//add item to the room
void Room::addItem(const char* inItemDescription){
  Item* i = new Item();
  
  //copy string NOT just the const char* pointer
  char* cstring = new char[strlen(inItemDescription)+1];
  //move input into cstring temporary holder
  strcpy(cstring, inItemDescription);

  //stem the item i's description to that cstring 
  i->itemDescription = cstring;
  itemsInRoom.push_back(i);
}

//deletes item from room
void Room::deleteItem(const char* DitemDescription){
  //find items currently in room
  vector<Room::Item*> currentItems = getItems();

  //loop through room items, delete the one thats equal to the to be deleted item descripton
  for(int i = 0; i < currentItems.size(); i++){
    if(strcmp(currentItems[i]->itemDescription, DitemDescription) == 0){
      itemsInRoom.erase(itemsInRoom.begin() + i);
    }
  }
}

//used in multipule places as a way to get itemsInRoom
vector<Room::Item*> Room::getItems(){
  return itemsInRoom;
}
