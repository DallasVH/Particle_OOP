#include <iostream>
#include <windows.h>
using namespace std;

//Particle group
class particle {
	//Values
	public:
		int type;
		//time doesn't work. Is in seconds and as intended when reaching 0 it will remove itself from the software
		int time;
		int size;
		int degree;
		int vel;
		int number;
		//This would not be a string in the game engine but for the program's purposes it is a string
		string location;

		//Builds particle groups
		void cp(int ty, int t, int s, int d, int v, int n, string l) {
			this->type = ty;
			this->time = t;
			this->size = s;
			this->degree = d;
			this->vel = v;
			this->number = n;
			this->location = l;
		}
		//returns group type
		string getType() {
			string ans;
			if (type == 1) {
				ans = "Type 1";
			}
			else if (type == 2) {
				ans = "Type 2";
			}
			else if (type == 3) {
				ans = "Type 3";
			}
			else {
				ans = "Uh Oh";
			}
			return ans;
		}

		//Prints group details
		void print() {
			cout << endl << "Type of group: " << getType() << endl;
			cout << "Amount of particles: " << number << endl;
			cout << "Size of particles: " << size << endl;
			cout << "Time left for particles: " << time << endl;
			cout << "Degree particles are rotated: " << degree << endl;
			cout << "Speed of the particles: " << vel << endl;
			cout << "Location of the particles: " << location << endl;
		}
};

//Creates particale groups based on 3 types
particle createP(int ID)
{
	particle p;

	if (ID == 1) {
		p.cp(ID, 10, 2, 0, 30, 25, "Storage");
	}
	else if (ID == 2) {
		p.cp(ID, 30, 1, 90, 50, 100, "Storage");
	}
	else if (ID == 3) {
		p.cp(ID, 60, 5, 180, 10, 5, "Storage");
		//p.startCount();
	}
	else {
		
	}

	return p;
}

//Linked list node
struct Node
{
	particle data;
	Node* next;
};

//Adds new particale group to the end of the list
void append(struct Node** head, particle node_data)
{
	struct Node* newNode = new Node;
	struct Node* last = *head;

	newNode->data = node_data;
	newNode->next = NULL;

	if (*head == NULL){
		*head = newNode;
		return;
	}

	while (last->next != NULL) {
		last = last->next;
	}
	last->next = newNode;
	return;
}

//Prints the LL and shows the groups based on type
void displayList(struct Node* node)
{
	int count = 0;
	cout << endl;
	while (node != NULL){
		cout << count << ". " << node->data.getType() << endl;
		node = node->next;
		count++;
	}
}

//gets a specific group in the LL based on an index
particle getNth(Node* head, int index)
{
	Node* current = head;

	int count = 0;
	while (count <= index) {
		if (count == index) {
			return (current->data);
		}
		count++;
		current = current->next;
	}
}

//This allows particale group information to be changed and saved to the LL
void edit(Node* head, int index, particle p)
{
	Node* current = head;

	int count = 0;
	while (count <= index) {
		if (count == index) {
			current->data = p;
		}
		count++;
		current = current->next;
	}
}

//Allows the user to prematurely end a particale group's time.
void remove(Node* head, int index)
{
	Node* current = head;

	int count = 0;
	while (count <= index) {
		if (count == index) {
			current->next = current->next->next;
		}
		count++;
		current = current->next;
	}
	cout << "Deleted " << index << " spot" << endl;
}

//Program
void program(int prog, Node* head, int cho){
	//Runs while the user enters valid answers
	int count = -1;
	while (prog >= 1 && prog <= 5) {
		//resets typeID value
		int typeID = 1;
		//Runs at start and if player enters 1
		if (prog == 1) {
			//runs till player enters a valid type ID
			while (typeID >= 1 && typeID <= 3) {
				cout << endl << "There are 3 types of particle groups." << endl << "1. 25 particles that are size 2, rotated 0 degrees, with a speed of 30 and will be up for 10 seconds and placed on screen space." << endl << "2. 100 particles that are size 1, rotated 90 degrees, with a speed of 50 and will be up for 30 seconds and placed at a location." << endl << "3. 5 particles that are size 5, rotated 180 degrees, with a speed of 10 and will be up for 60 seconds and attached to a model." << endl << "Please enter the particale type ID you wish to create for the group : ";
				cin >> typeID;
				if (typeID >= 1 && typeID <= 3) {
					append(&head, createP(typeID));
					typeID = 0;
					count++;
				}
				else {
					cout << "Not a valid type." << endl;
				}
			}
		}
		//Replaces how a UI in the game system would reflect
		cout << endl << "What would you like to do with your particles?" << endl << "1. Add another particle group?" << endl << "2. View a partcle group's details?" << endl << "3. View your particle groups by type in the list?" << endl << "4. Edit an existing particle group? (This includes location)" << endl << "5. Prematurly delete a particle group prematurly?" << endl << "Type any of the above options as an int or type an option not available to end the program: ";
		cin >> prog;
		//Where the user chooses what group to edit
		if (prog == 4) {
			int resp = 0;
			cout << "Enter which particle group you wish to edit's position on the list (Start with 0): ";
			cin >> cho;
			particle p = getNth(head, cho);
			p.print();
			string ans;
			//Allows the user to alter details of existing particle groups
			cout << endl << "What about this group do you wish to edit? Please enter number, size, degree, speed, or location: ";
			cin >> ans;
			//Changes group's number of particles
			if (ans == "number") {
				cout << "What would you like the new number of particles to be? ";
				cin >> resp;
				p.number = resp;
				edit(head, cho, p);
				cout << "Done." << endl;
			}
			//Changes the particle's in the group size
			else if (ans == "size") {
				cout << "What would you like the new size of the particles to be? ";
				cin >> resp;
				p.size = resp;
				edit(head, cho, p);
				cout << "Done." << endl;
			}
			//Has the user change the angle of the particles in the group
			else if (ans == "degree") {
				cout << "What would you like the new degrees for the particles to be rotated? ";
				cin >> resp;
				p.degree = resp;
				edit(head, cho, p);
				cout << "Done." << endl;
			}
			//Allows the user to change the speed
			else if (ans == "speed") {
				cout << "What would you like the new speed for the particles to be? ";
				cin >> resp;
				p.vel = resp;
				edit(head, cho, p);
				cout << "Done." << endl;
			}
			//Allows the user to assign a location for the group
			else if (ans == "location") {
				string re;
				cout << "Where would you like to place the particle group? (Type model, UI, or location): ";
				cin >> re;
				if (re == "model") {
					cout << "Here is where the program would read the model file in the game software" << endl;
					//Where the model file would be applied
					p.location = resp;
					edit(head, cho, p);
					cout << "Done." << endl;
				}
				else if (re == "UI") {
					cout << "Here is where the program would read the UI file in the game software" << endl;
					//Where the UI file would be applied
					p.location = resp;
					edit(head, cho, p);
					cout << "Done." << endl;
				}
				else if (re == "location") {
					cout << "Here is where the program would allow the user to type in the vector info from the user in the game software" << endl;
					//Where the Vector3 location would be given by the user
					p.location = resp;
					edit(head, cho, p);
					cout << "Done." << endl;
				}
				//Covers any wrong responses
				else {
					cout << "Invalid Response" << endl;
				}
			}
			//Covers any wrong responses
			else {
				cout << "Invalid response." << endl;
			}
		}
		//Prints list of groups 
		else if (prog == 3) {
			displayList(head);
		}
		//deletes a group where the user would need to delete one before the time runs out
		else if (prog == 5) {
			cout << "Enter which particle group you wish to delete's position on the list (Start with 0): ";
			cin >> cho;
			if (cho > count) {
				cout << "This spot does not exist";
			}
			else {
				/*Sets time to 0 thus removing it.
				In a game software I would have it deleted.
				Does not actually remove it from the LL due to it not being possible to remove OOP LL.
				This would remove it from the game software none the less because the particle groups would not be stored in LL in that case.*/
				particle rem = getNth(head, cho);
				rem.time = 0;
				edit(head, cho, rem);
				cout << "Done." << endl;
			}
		}
		//Allows the user to check particle group details
		else if (prog == 2) {
			cout << "Enter which particle group you wish to look at's position on the list (Start with 0): ";
			cin >> cho;
			if (cho > count) {
				cout << "This spot does not exist";
			}
			else {
				particle p = getNth(head, cho);
				p.print();
			}
		}
		//If the user enters an option not available it ends the program
		else {

		}
	}
}

//Runs Program
int main()
{
	//Sets application start values
	int prog = 1;
	struct Node* head = NULL;
	int cho = 0;
	program(prog, head, cho);
	return 0;
}