#include <iostream>
#include <cstring>
#include <vector>
#include <map>
#include "room.h"

using namespace std;

void move(Room*& currentRoom);

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

  //create items
  portapotties->addItem("Jared");

  bool go = true;
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
  while(go == true){
    command[0] = '\0';
    cout<<"Choose your next action (MOVE, PICK UP, DROP, INVENTORY or QUIT): "<<endl;
    cin.get(command, 20);
    cin.ignore();

    if(strcmp(command, m) == 0){
      move(current);
      
    }
    else if (strcmp(command, p) == 0){
      //pick up an item
    }
    else if(strcmp(command, d) ==0){
      //drop an item
    }
    else if (strcmp(command, i) == 0){
      //view your inventory
    }
    else if(strcmp(command, q) == 0){
      return 0;
      //destructor
    }
    else{
      cout<<"PLEASE ENTER A VALID COMMAND" <<endl;
    }
  }
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
