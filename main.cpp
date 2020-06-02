/*This program is a Hash Table based on my previous Student List
    By Stefan Ene
*/

#include <iostream>
#include <cstring>

using namespace std;

struct stud {
  char Fname[81];
  char Lname[81];
  int id;
  float gpa;
  stud* next;
  stud* prev;
};

//functions
void ADD(stud** list, stud* &newStud, int size);
void PRINT(stud** list);
void REMOVE(stud** list);
bool checkCollision(stud** list, int size);

int main() {
  //variables
  bool run = true;
  char input[10];
  //hash table variabes
  stud** list = new stud*[100];
  int size = 100;
  //program
  cout << "=====================" << endl;
  cout << "This is a Hash Table for Student List." << endl;
  while (run) {
    cout << endl << "You can: add, remove, print, quit." << endl;
    cin.get(input, 10);
    cin.clear();
    cin.ignore(10000, '\n');
    if (strcmp(input, "add") == 0) {
      //get info from user input
      stud* newStud = new stud();
      newStud->next = NULL;
      newStud->prev = NULL;
      cout << "Enter first name: " << endl;
      cin >> newStud->Fname;
      cin.clear();
      cin.ignore(81,'\n');
      cout << "Enter last name: " << endl;
      cin >> newStud->Lname;
      cin.clear();
      cin.ignore(81,'\n');
      cout << "Enter ID: " << endl;
      cin >> newStud->id;
      cin.clear();
      cin.ignore(81,'\n');
      cout << "Enter GPA: " << endl;
      cin >> newStud->gpa;
      cin.clear();
      cin.ignore(81, '\n');
      ADD(list, newStud, size);
      cout << endl << "New student added to hash table." << endl;
      //balance if collision
      if (checkCollision(list, size)) {
	cout << "balance" << endl;
	stud** temp = new stud*[size];  //create temp array
	for (int m = 0; m < size; m++) {
	  temp[m] = list[m];
	}
	int newsize = 2*size;
	list = new stud*[newsize]; //recreate list to double
	for (int c = 0; c < newsize; c++) {
          list[c] = NULL;
        }
	//add all students to newly sized list
	for (int a = 0; a < size; a++) {
	  stud* move = temp[a];
	  cout << " c1" << endl;
	  ADD(list, move, newsize);
	  cout << " c2" << endl;
	  cout << a << endl;
	}
	size = newsize; //update list's size
      }
    }
    else if (strcmp(input, "remove") == 0) {
      
    }
    else if (strcmp(input, "print") == 0) {

    }
    else if (strcmp(input, "quit") == 0) {
      cout << endl << "Thank you for using this program." << endl;
      cout << "========================" << endl << endl;
      run = false;
    } else {
      cout << endl << "Invalid input. Try again." << endl;
    }
  }
  return 0;
}

void ADD(stud** list, stud* &newStud, int size) {
  int index = (newStud->id) % size;
  //put new student in current array
  if (list[index] == NULL) {
    //no colision, simply add to list
    list[index] = newStud;
  } else {
    //collision, then add as next ptr
    if ((list[index])->next == NULL) {
      //no previous collision
      (list[index])->next = newStud;
      (list[index]->next)->prev = (list[index])->next;
    } else {
      //already a collision existent there
      ((list[index])->next)->next = newStud;
      (((list[index])->next)->next)->prev = ((list[index])->next)->next;
    }
  }
}

bool checkCollision(stud** list, int size) {
  bool newlist = false;  //keep trak whether there's a need to make a new list
  int ctr = 0;
  while (newlist == false && ctr < size) {
    if (list[ctr] != NULL) {
      if ((list[ctr])->next != NULL) {
	if (((list[ctr])->next)->next != NULL) {
	  newlist = true;
	}
      }
    }
    ctr++;
  }
  return newlist;
}
