/* Ella MacPherson
   C++ Zuul 12/4/2025
   A game where you can move through rooms and pick up items
   Win Condition: pick up all 3 kids
*/

#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "room.h"

using namespace std;

//function definetions. Each action + check win
void move(Room*& currentRoom);
void pickUp(vector<Room::Item*>& Inventory, Room* currentRoom);
void printInventory(vector<Room::Item*>& Inventory);
void drop(vector<Room::Item*>& Inventory, Room* currentRoom);
bool checkWin(vector<Room::Item*>& Inventory);

//main: initialize everything
int main(){
  //room pointer to keep track of current room the player is in
  Room* current;
  
  //create rooms
  Room* pavilion = new Room("You're standing in the middle of a large wooden pavilion. Towering evergreens loom all around you. There is a faint whiff of human waste coming from the south");
  Room* portapotties = new Room("You approach a stinkly circle of porta potties. Whens the last time somebody cleaned this place? Look there's one of your kids playing with the toilet paper roll!");
  Room* trailhead1 = new Room("You stumble upon a sign labeled Trail Head 1, there is a looming hill to your north, a river rushing to your east, and a cave on the west.");
  Room* trailhead2 = new Room("You stumble upon a sign labeled Trail Head 2 you hear the distant hum of RV generators");
  Room* rvcampground = new Room("You walk into a cleared out dirt patch in the forest. There are three RVs set up. You head childish laughter coming from one");
  Room* RV1 = new Room("You investigate an RV labeled RV 1. There's one of your kids! He's sitting with the RV owners eating a smore");
  Room* RV2 = new Room("You look around an RV labeled RV 2, hmmm.. No one here");
  Room* RV3 = new Room("You knock on the door of an RV labeled RV 3, an old man opens it. Says he saw a kid at one of the other RVs, he offers you a choclate bar!");
  Room* cave = new Room("You step into the cold dark cave, you hear the screeches of bats to your west. Mine cart tracks go off to the south");
  Room* cavern = new Room("You walk into a massive cavern with water rushing through the middle. A bat swoops down from overhead. You look at your feet. Is that a skull?");
  Room* goldMine = new Room("You step into an abandoned gold mine! oooh is that a lump of gold?");
  Room* stream = new Room("You walk up to a rushing stream, theres a fishing rock up north");
  Room* fishingRock = new Room("You step up onto the rock, nothing here but a discarded fishing rod");
  Room* hill = new Room("You walk to the base of a hill, looks like there's an view point further up north");
  Room* outlook = new Room("You climb all the way up the hill and reach an outlook in the trees, wow what a stunning view. There's an old campfire to the east, an old campsite to your west");
  Room* oldcampsite = new Room("You walk into an old campsite, cans scattered. Is that one of my kids?!");
  Room* oldfirepit = new Room("You are at the old fire pit, nothing here but charcols");
    
  //create exits
  pavilion->setExit("SOUTH", portapotties);
  pavilion->setExit("NORTH", trailhead1);
  pavilion->setExit("EAST", trailhead2);
  
  portapotties->setExit("NORTH", pavilion);

  trailhead2->setExit("SOUTH", rvcampground);
  trailhead2->setExit("WEST", pavilion);

  trailhead1->setExit("SOUTH", pavilion);
  trailhead1->setExit("WEST", cave);
  trailhead1->setExit("EAST", stream);
  trailhead1->setExit("NORTH", hill);

  rvcampground->setExit("NORTH", trailhead2);
  rvcampground->setExit("EAST", RV2);
  rvcampground->setExit("SOUTH", RV1);
  rvcampground->setExit("WEST",RV3);

  RV2->setExit("WEST", rvcampground);
  RV1->setExit("NORTH", rvcampground);
  RV3->setExit("EAST", rvcampground);

  hill->setExit("SOUTH", trailhead1);
  hill->setExit("NORTH", outlook);

  outlook->setExit("SOUTH",hill);
  outlook->setExit("EAST", oldfirepit);
  outlook->setExit("WEST", oldcampsite);

  oldfirepit->setExit("WEST", outlook);
  oldcampsite->setExit("EAST", outlook);

  stream->setExit("WEST", trailhead1);
  stream->setExit("NORTH", fishingRock);

  fishingRock->setExit("SOUTH", stream);

  cave->setExit("SOUTH", goldMine);
  cave->setExit("WEST", cavern);
  cave->setExit("EAST", trailhead1);

  goldMine->setExit("NORTH", cave);

  cavern->setExit("EAST", cave);

  //create items
  portapotties->addItem("Jared");
  RV1->addItem("Gertrude");
  oldcampsite->addItem("Bartholomew");
  RV3->addItem("Choclate Bar");
  cavern->addItem("Bat Skull");
  goldMine->addItem("Gold");
  fishingRock->addItem("FishingRod");

  //command shortcuts
  char m[10] = "MOVE";
  char p[10] = "PICK UP";
  char d[10] = "DROP";
  char i[20] = "INVENTORY";
  char q[10] = "QUIT";

  //command input var
  char command[100];
  //vector to store items that are currently in players inventory
  vector<Room::Item*> Inventory;

  //set room = first room
  current = pavilion;
  //print beginning text
  cout<<"Your mission: " << endl << "You have lost 3 kids at the campground. Find them. (Have all three in your inventory)"<<endl<<endl;
  current->print();
  cout<<endl; //spacing

  
  //play the game while win =! true
  while(checkWin(Inventory) == false){
    //clear command input, reprint question, take in command
    command[0] = '\0';
    cout<<"Choose your next action (MOVE, PICK UP, DROP, INVENTORY or QUIT): "<<endl;
    cin.get(command, 20);
    cin.ignore();

    //compare command input to possible commands (m,p,d,i,q), if match, run the coresponding function
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
    //if invalid command is entered
    else{
      cout<<"PLEASE ENTER A VALID COMMAND" <<endl;
    }
  }
  //once winning codition is met:
  cout<<endl<<"Congrats on finding all your kids! Thank you for playing!"<<endl;
}

//function to complete action: MOVE!
void move(Room*& currentRoom){
  //create move input, and var to keep track of existence of the exit
  bool exist = false;
  char move[50];

  //create iterator for map, and set exitMap = to the current rooms exit map in room.cpp
  map<const char*,Room*>::iterator it;
  map<const char*, Room*> exitMap = currentRoom->exitMap;
  
  //take in input
  cout<<"Which exit would you like to take?"<<endl;
  cin.get(move, 50);
  cin.ignore();

  //iterate through the exit map
  for(it = exitMap.begin(); it != exitMap.end(); ++it){
    //convert const char to a cstring so it can be compared to the input
    char e[50];
    strcpy(e, it->first);

    //if they match, move the current room to the room linked to that exit, print the words for that, and clarify it exists
    if(strcmp(e, move) == 0){
      currentRoom = it->second;
      exist = true;
      it->second->print();
    }
  }
  //if exist does not exist or entered incorrectly
  if(exist == false){
    cout<<"Exit does not exist"<<endl;
  }
}

//function to complete ITEM PICKUPS!
void pickUp(vector<Room::Item*>& Inventory, Room* currentRoom){
  //input var and existence var
  char itemToPickUp[50];
  bool exist = false;
  
  //vector of items in our current room, fetched from the currentRoom get items in room.cpp
  vector<Room::Item*> itemsInCurrentRoom = currentRoom->getItems();

  //if there's no items in the room
  if(itemsInCurrentRoom.size() == 0){
    cout<<"There are no items to be picked up in this room!"<<endl;
    return;
  }

  //continue as if there is items in room
  cout<<"What item would you like to pick up?"<<endl;
  //take in input
  cin.get(itemToPickUp, 50);
  cin.ignore();

  //iterate through items in current room (could've used no iterator, but was unsure at this point!)
  int i =0;
  for(auto it = itemsInCurrentRoom.begin(); it != itemsInCurrentRoom.end(); ++it){
    //input is in char[] and item in room is in const char* fix:
    char e[50];
    strcpy(e, (*it)->itemDescription);//dereference cause its a too many pointers out

    //if it does exist
    if(strcmp(e, itemToPickUp) == 0){
      exist = true;
      //then add it to inventory
      Inventory.push_back(currentRoom->getItems()[i]);
      //delete from room
      currentRoom->deleteItem((*it)->itemDescription);
    }
    //keep track of index to push back the correct item in the room
    i++;
  }

  //Entered wrong
  if(exist == false){
    cout<<"Item does not exist or is not currently in the room"<<endl;
  }

}

//function for dropping an item
void drop(vector<Room::Item*>& Inventory, Room* currentRoom){
  //exist var and input var
  char itemToBeDropped[50];
  bool exist = false;

  //if nothing in inventory, return early
  if(Inventory.size() == 0){
    cout<<"Your inventory is empty, there are no items that could be dropped"<<endl;
    return;
  }

  //continue with something in inventory, and get input
  cout<<"What item do you want to drop? (Must be in your inventory)"<<endl;
  cin.get(itemToBeDropped, 50);
  cin.ignore();

  //loop through inventory
  for(int i = 0; i < Inventory.size(); i++){
    //if item is  found in inventory..
    if(strcmp(Inventory[i]->itemDescription, itemToBeDropped) == 0){
      exist = true;
      //add item to room
      currentRoom->addItem(Inventory[i]->itemDescription);
      //delete item from inventory
      Inventory.erase(Inventory.begin()+i);
      }
  }

  if(exist == false){
    cout<<"That item name is not in your inventory, use command INVENTORY to verify"<<endl;
  }
  
}

//function performs INVENTORY check
void printInventory(vector<Room::Item*>& Inventory){
  cout<<"Inventory: " <<endl;
  //if empty
  if(Inventory.size() == 0){
    cout<<"Empty"<<endl;
  }
  else{    //print each item descption out
    for(int i = 0; i < Inventory.size(); i++){
      cout<<Inventory[i]->itemDescription;
      cout<<", ";
    }
  }
  cout<<endl;
}

//check the win
bool checkWin(vector<Room::Item*>& Inventory){
  //keep track of the # of kids you have in inventory
  int kidsFound = 0;
  //if inventory empty obviously not win--return early
  if(Inventory.size() == 0){
    return false;
  }

  //if kid found in inventory, add 1 to kidsfound
  for(int i =0; i< Inventory.size(); i++){
    if(strcmp(Inventory[i]->itemDescription, "Jared") == 0 || strcmp(Inventory[i]->itemDescription, "Gertrude") == 0||strcmp(Inventory[i]->itemDescription, "Bartholomew") == 0){
      kidsFound++;
    }
  }
  //when 3 kids found the player wins!!
  if(kidsFound == 3){
    return true;
  }
  return false;
}
