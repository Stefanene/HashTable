/*This program is a Hash Table based on my previous Student List
    By Stefan Ene
      Works Cited: random file input done with help from COdeSpeedy
*/

#include <iostream>
#include <cstring>
#include <fstream>
#include <time.h>
#include <vector> //for random input, dont worry
#include <time.h>

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
void PRINT(stud** list, int size);
void REMOVE(stud** list, int id, int size);
bool checkCollision(stud** list, int size);
void ADDRANDOM(stud** list, int size, int &randid);

int main() {
  //variables
  bool run = true;
  char input[10];
  int randid = 6; //keeps track or random id value
  //hash table variabes
  stud** list = new stud*[100];
  int size = 100;
  //program
  cout << "==========================" << endl;
  cout << "This is a Hash Table for Student List." << endl;
  while (run) {
    cout << endl << "You can: add, addrand, remove, print, quit." << endl;
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
	cout << endl << "Rebalancd hash table array to double the size." << endl;
	stud** temp = new stud*[size];  //create temp array
	for (int m = 0; m < size; m++) {
	  temp[m] = list[m];
	}
	int newsize = 2*size;
	list = new stud*[newsize]; //recreate list to double
	for (int c = 0; c < newsize; c++) {
          list[c] = NULL;
        }
	//re-add all students to newly sized list
	for (int a = 0; a < size; a++) {
	  if (temp[a] != NULL) {
	    stud* move = temp[a];
	    if (move->next != NULL) {
	      stud* nxt = move->next;
	      move->next = NULL;
	      nxt->prev = NULL;
	      ADD(list, nxt, newsize);
	      if (nxt->next != NULL) {
		stud* dnxt = nxt->next;
		nxt->next = NULL;
		dnxt->prev = NULL;
		ADD(list, dnxt, newsize);
	      }
	    }
	    ADD(list, move, newsize);
	  }
	}
	delete[] temp;
	size = newsize; //update list's size
      }
    }
    else if (strcmp(input, "remove") == 0) {
      cout << "Input ID of student to remove: ";
      int in;
      cin >> in;
      cin.clear();
      cin.ignore(10000, '\n');
      REMOVE(list, in, size);
    }
    else if (strcmp(input, "print") == 0) {
      PRINT(list, size);
    }
    else if (strcmp(input, "addrand") == 0) {
      ADDRANDOM(list, size, randid);
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

//basically the hash function, takes id and gets mod to list' size
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

void ADDRANDOM(stud** list, int size, int &randid) {
  int in;
  srand(time(NULL));
  cout << "How many random students should be added: ";
  cin >> in;
  cin.clear();
  cin.ignore(10000, '\n');
  int temp = in;
  while (in > 0) {
    string line;
    string keepf;
    int ctr = 0;
    int random = rand() % 20;
    ifstream myfile("fnames.txt");
    if (myfile.is_open()) {
      while ( myfile.good()) {
	getline (myfile,line);
	if (ctr == random) {
	  keepf = line;
	  //cout << random << keepf << endl;
	}
	ctr++;
      }
      myfile.close();
    } else cout << "Counld not locate file." << endl;
    string lin;
    string keepl;
    ctr = 0;
    random = rand() % 20;
    ifstream myfile1("lnames.txt");
    if (myfile1.is_open()) {
      while (myfile1.good()) {
	getline (myfile1, lin);
	if (ctr == random) {
	  keepl = lin;
	  //cout << " " << random << keepl << endl;
	}
	ctr++;
      }
    } else cout << "Could not locate file." << endl;
    //make student
    stud* newStud = new stud();
    strcpy(newStud->Fname, keepf.c_str());
    strcpy(newStud->Lname, keepl.c_str());
    newStud->id = randid;
    newStud->gpa = static_cast <float> (rand()) / (static_cast <float> (RAND_MAX/5));
    //add new student to list
    ADD(list, newStud, size);
    
    randid = randid + 100; //increment id coutnter by 100
    in--;
  }
  cout << endl << "Added " << temp << " students." << endl;
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

void PRINT(stud** list, int size) {
  for (int i = 0; i < size; i++) {
    if (list[i] != NULL) {
      cout << list[i]->Fname << " " << list[i]->Lname << "," << list[i]->id;
      if (list[i]->next != NULL) {
	cout << '\t' << list[i]->next->Fname << " " << list[i]->next->Lname << "," << list[i]->next->id;
      }
      cout << endl;
    }
  }
}

void REMOVE(stud** list, int id, int size) {
  int i = id % size;
  if (list[i] == NULL) {
    cout << endl << "No such student to remove." << endl;
  } else {
    if (list[i]->id == id) {
      //found then delete
      if (list[i]->next == NULL) {
	list[i] = NULL; 
      } else {
	//replace with next in collision
	stud* newcurr = list[i]->next;
	newcurr->prev = NULL;
	list[i] = newcurr;
      }
    } else {
      if (list[i]->next == NULL) {
	cout << endl << "No such student to remove." << endl;
      } else {
	if (list[i]->next->id == id) {
	  //found then remove
	  list[i]->next = NULL;
	} else {
	    cout << "No such student to remove." << endl;
	}
      }
    }
  }
}
