#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "room.h"

using namespace std;

void move(Room*& currentRoom);
void pickUp(vector<Room::Item*>& Inventory, Room* currentRoom);
void printInventory(vector<Room::Item*>& Inventory);
void drop(vector<Room::Item*>& Inventory, Room* currentRoom);
bool checkWin(vector<Room::Item*>& Inventory);

int main(){
  Room* current;
  
  //create rooms
  Room* pavilion = new Room("You're standing in the middle of a large wooden pavilion. Towering evergreens loom all around you. There is a faint whiff of human waste coming from the south");
  Room* portapotties = new Room("You approach a stinkly circle of porta potties. Whens the last time somebody cleaned this place? Look there's one of your kids playing with the toilet paper roll!");
  Room* trailhead1 = new Room("You stumble upon a sign labeled Trail Head 1, there is a looming hill to your north, a river rushing to your east, and a cave on the west.");
  Room* trailhead2 = new Room("You stumble upon a sign labeled Trail Head 2 you hear the distant hum of RV generators");
    
  //create exits
  pavilion->setExit("SOUTH", portapotties);
  pavilion->setExit("NORTH", trailhead1);
  pavilion->setExit("EAST", trailhead2);
  
  portapotties->setExit("NORTH", pavilion);

  //trail head 1 + 2
  trailhead1->setExit("SOUTH", pavilion);
  trailhead2->setExit("WEST", pavilion);

  //create items
  portapotties->addItem("Jared");
  portapotties->addItem("Gertrude");
  portapotties->addItem("Bartholomew");
  char m[10] = "MOVE";
  char p[10] = "PICK UP";
  char d[10] = "DROP";
  char i[20] = "INVENTORY";
  char q[10] = "QUIT";
  char command[100];
  vector<Room::Item*> Inventory;

  current = pavilion;
  cout<<"Your mission: " << endl << "You have lost 3 kids at the campground. Find them. (Have all three in your inventory)"<<endl<<endl;
  current->print();
  cout<<endl;
  
  //play the game
  while(checkWin(Inventory) == false){
    command[0] = '\0';
    cout<<"Choose your next action (MOVE, PICK UP, DROP, INVENTORY or QUIT): "<<endl;
    cin.get(command, 20);
    cin.ignore();

    if(strcmp(command, m) == 0){
      move(current);
      
    }
    else if (strcmp(command, p) == 0){
      pickUp(Inventory, current);
    }
    else if(strcmp(command, d) ==0){
      drop(Inventory, current);
    }
    else if (strcmp(command, i) == 0){
      printInventory(Inventory);
    }
    else if(strcmp(command, q) == 0){
      return 0;
      //destructor
    }
    else{
      cout<<"PLEASE ENTER A VALID COMMAND" <<endl;
    }
  }
  cout<<endl<<"Congrats on finding all your kids! Thank you for playing!"<<endl;
}

void move(Room*& currentRoom){
  char move[50];
  map<const char*,Room*>::iterator it;
  map<const char*, Room*> exitMap = currentRoom->exitMap;
  bool exist = false;
  
  cout<<"Which exit would you like to take?"<<endl;
  cin.get(move, 50);
  cin.ignore();
  
  for(it = exitMap.begin(); it != exitMap.end(); ++it){
    //convert const char to a cstrign so it can be compared
    char e[50];
    strcpy(e, it->first);
   
    if(strcmp(e, move) == 0){
      currentRoom = it->second;
      exist = true;
      it->second->print();
    }
  }
  if(exist == false){
    cout<<"Exit does not exist"<<endl;
  }
}

void pickUp(vector<Room::Item*>& Inventory, Room* currentRoom){
  char itemToPickUp[50];
  bool exist = false;
  vector<Room::Item*> itemsInCurrentRoom = currentRoom->getItems();

  //if there's no items in the room
  if(itemsInCurrentRoom.size() == 0){
    cout<<"There are no items to be picked up in this room!"<<endl;
    return;
  }
  
  
  cout<<"What item would you like to pick up?"<<endl;
  cin.get(itemToPickUp, 50);
  cin.ignore();
  int i =0;
  for(auto it = itemsInCurrentRoom.begin(); it != itemsInCurrentRoom.end(); ++it){
    //input is in char[]
    //item in room is in const char*
    char e[50];
    strcpy(e, (*it)->itemDescription);//dereference it.. cause its too many pointers or something
    if(strcmp(e, itemToPickUp) == 0){
      exist = true;
      Inventory.push_back(currentRoom->getItems()[i]);
      //delete from room
      currentRoom->deleteItem((*it)->itemDescription);
      //then add it to inventory
    }
    i++;
  }
  //search currentRooms item vector for the item typed in

  if(exist == false){
    cout<<"Item does not exist or is not currently in the room"<<endl;
  }

}

//CAUSING SEGMENTATION FAULT!!
void drop(vector<Room::Item*>& Inventory, Room* currentRoom){
  char itemToBeDropped[50];
  bool exist = false;
  
  if(Inventory.size() == 0){
    cout<<"Your inventory is empty, there are no items that could be dropped"<<endl;
    return;
  }
  
  cout<<"What item do you want to drop? (Must be in your inventory)"<<endl;
  cin.get(itemToBeDropped, 50);
  cin.ignore();
  
  for(int i = 0; i < Inventory.size(); i++){
    if(strcmp(Inventory[i]->itemDescription, itemToBeDropped) == 0){
      exist = true;
      //add item to room
      currentRoom->addItem(Inventory[i]->itemDescription);
      //breaks HERE ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
      Inventory.erase(Inventory.begin()+i);
      //delete item from inventory
      //    delete Inventory[i];
      
      
      }
  }

  if(exist == false){
    cout<<"That item name is not in your inventory, use command INVENTORY to verify"<<endl;
  }
}

void printInventory(vector<Room::Item*>& Inventory){
  cout<<"Inventory: " <<endl;
  if(Inventory.size() == 0){
    cout<<"Empty"<<endl;
  }else{    
    for(int i = 0; i < Inventory.size(); i++){
      cout<<Inventory[i]->itemDescription<<" "<< endl;
    }
  }
}

bool checkWin(vector<Room::Item*>& Inventory){
  int kidsFound = 0;
  if(Inventory.size() == 0){
    return false;
  }
  for(int i =0; i< Inventory.size(); i++){
    if(strcmp(Inventory[i]->itemDescription, "Jared") == 0 || strcmp(Inventory[i]->itemDescription, "Gertrude") == 0||strcmp(Inventory[i]->itemDescription, "Bartholomew") == 0){
      kidsFound++;
    }
  }
  if(kidsFound == 3){
    return true;
  }
  return false;
}
