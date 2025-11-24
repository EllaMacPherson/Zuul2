#include "room.h"
#include <iostream>
#include<vector>
#include <map>
#include <cstring>

using namespace std;

Room::Room(const char* inDescription){
  description = new char[500];
  strcpy(description, inDescription);
  
}

void Room::print(){
  cout<<description<<endl;
  cout<<"Items available: ";
  vector<Room::Item*> currentItems = getItems();
  if(currentItems.size() == 0){
    cout<<"No items here ";
  }else{
    for(int i = 0; i < currentItems.size(); i++){
      cout<< currentItems[i]->itemDescription;
    }  
  }
  
  cout<<endl;
  cout<<"Exits: "<<endl;
  for(map<const char*, Room*>::iterator it = exitMap.begin(); it != exitMap.end(); ++it){
    cout<<it->first<<endl;
  }
}

void Room::setExit(const char* direction, Room* exitRoom){
  //map somewhere here
  exitMap.emplace(direction, exitRoom);   
}

void Room::addItem(const char* inItemDescription){
  Item* i;
  i->itemDescription = inItemDescription;
  itemsInRoom.push_back(i);
}

vector<Room::Item*> Room::getItems(){
  return itemsInRoom;
}
