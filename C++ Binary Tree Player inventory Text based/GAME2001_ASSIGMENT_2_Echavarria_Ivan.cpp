// Game2001_A2.cpp : Defines the entry point for the console application.
// December 26th 2017
// Ivan Echavarria StudentID: 101092562

//#include "stdafx.h"
#include<iostream>
#include<string>

using namespace std;


class Weapon {
public:
	string weaponName;
	int range;
	int damage;
	float weight;
	float cost;

	Weapon(string n, int rang, int dam, float w, float c) {
		weaponName = n;
		damage = dam;
		range = rang;
		weight = w;
		cost = c;
	}
};


class Node {
public:
	Weapon * myWeapon;
	Node * left;
	Node * right;
	Node(Weapon* aWeapon) {
		myWeapon = aWeapon;
		left = right = NULL ;
	}

};

class BinaryTree {
public:
	Node * root;

	BinaryTree()     //Constructor of the BinaryTree class
	{
		root = NULL; //setting the Node root to NULL
	}

	void insert(Weapon* newWeapon)            // Inserting new Node to BinaryTree with a given Weapon 
	{
		Node * newNode = new Node(newWeapon); //creating new Node with newWeapon
		if (root == NULL)                     //Case 1: if the BinaryTree is empty
		{
			root = newNode;					  // root is equal to newNode 
			return;
		}
											  //Case 2: if the BinaryTree is not empty
		else
		{
			Node * parent = root;             //creating parent Node points to root
			Node * current = root;            //creating current Node points to root
			while (current != NULL)			  //If our current node is null then we make that node the new node
			{
				parent = current;			  //assigning current to parent
				// if the weapon name of the current is less than the weapon name to be inserted(Alphabetically), then the new node must be inserted on the right side of our BinrayTree  
				// Move to the right branch of the tree 
				if (current->myWeapon->weaponName.compare(newNode->myWeapon->weaponName) < 0)
					current = current->right;
				else
					// Move to the left branch of the tree
					current = current->left;
			}
			// to make sure that we are in the right position we check again and inserting the new Node
			// if the weapon name of the parent is less than the weapon name to be inserted, then the new node must be inserted on the right side of our BinrayTree  
			// Move to the right branch of the tree and insert the new Node
			if (parent->myWeapon->weaponName.compare(newNode->myWeapon->weaponName) < 0)
				parent->right = newNode;
			else
				// Move to the left branch of the tree and insert the new Node
				parent->left = newNode;
		}
	}

	Node* searchNode(Node* curr, string key)
	{
		//Case 1: if curr is NULL then return NULL
		if (curr == NULL) return NULL;
		//Case 2: if the curr node's weapon name is equal to the key then return curr node
		if (key.compare(curr->myWeapon->weaponName) == 0)
			return curr;
		//Case 3: if the curr node's weapon name is not equal to the key then check if the key is grater or less than curr nade's weapon name
		// if the weapon name of the current is greater than key, then the key must be in the left branch of BinrayTree  
		if (key.compare(curr->myWeapon->weaponName) < 0)
		{
			//Move to the left branch and search for the key recursively and return curr
			curr = searchNode(curr->left, key);
			return curr;
		}
		else if (key.compare(curr->myWeapon->weaponName) > 0) // if the weapon name of the current is less than key, then the key must be in the right branch of BinrayTree
		{
			//Move to the right branch and search for the key recursively and return curr
			curr = searchNode(curr->right, key);
			return curr;		
		}
	}

	Node* search(string key)                 //searching to a Node in BinaryTree with the given weapon name (key)
	{
		return searchNode(root, key);		// return the Node from the searchNode() function
	}

	void displayInOrder() {
		cout << " In-Order :  " << endl;
		inOrder(root);
		cout << endl;
	}

	void inOrder(Node * n) {
		if (n != NULL) {
			inOrder(n->left);
			cout << "Name: "<< n->myWeapon->weaponName << "   Damage: "<< n->myWeapon->damage<< "   Cost:$ " << n->myWeapon->cost<<endl;
			inOrder(n->right);
		}
	}

	Node* deleteWeapon(Node* parent, string weaponToDelete)
	{
		//If node is null, then there is no weapon in the shop. Return Null
		if (parent == NULL)
		{
			cout << "No weapon found in the shop" << endl;
			return NULL;
		}
		//If the name of the weapon to be deleted is less than the current weapon name in the current parent node, then the weapon must be on the left side of our tree
		else if (weaponToDelete.compare(parent->myWeapon->weaponName) < 0)
		{
			//Move to the left branch and search for the weapon recursively
			parent->left = deleteWeapon(parent->left, weaponToDelete);
		}
		//If the name of the weapon to be deletes is greated than the current weapon name, then the weapon must be on the right side of our tree
		else if (weaponToDelete.compare(parent->myWeapon->weaponName) > 0)
		{
			//Move to the right branch and search for the weapon recursively
			parent->right = deleteWeapon(parent->right, weaponToDelete);
		}
		else // Weapon name found
		{
			// Case 1: The node we want to delete has not children
			if (parent->left == NULL && parent->right == NULL)
			{
				cout << "Weapon: " << parent->myWeapon->weaponName << " Has been deleted" << endl;
				delete parent; // Free memory
				parent = NULL;

			}
			// Case 2: Parent has one child, case left child is null
			else if (parent->left == NULL)
			{
				cout << "Weapon: " << parent->myWeapon->weaponName << " Has been deleted" << endl;
				Node* temp = parent; // get a hold (Point) to the current parent memory address location
				parent = parent->right; // Update parent pointer to the current parent right child memory address location
				delete(temp); // Delete temp pointer to free memory allocated from previous parent

			}
			//Case 2: Parent has one child, case right child is null
			else if (parent->right == NULL)
			{
				cout << "Weapon: " << parent->myWeapon->weaponName << " Has been deleted" << endl;
				Node* temp = parent; // Hold memory location to be freed (Node to be deleted)
				parent = parent->left; // Update memory location from parent to left child
				delete(temp);// Free memory location hold by temp 

			}
			//Annoying Case 3: Parent has two children
			else
			{
				Node* temp = getInOrderSucc(parent->right); // Find the minimun value on the right side of the tree
				cout << "Weapon: " << parent->myWeapon->weaponName << " Has been replaced by in order successor" << endl;
				cout << "In order successor duplicate will be deleted: ";
				parent->myWeapon = temp->myWeapon; // copy the weapon from the most left node into the parent (current node)
				parent->right = deleteWeapon(parent->right, temp->myWeapon->weaponName); // Call delete node to erase the duplicate node 
			}
		}
		return parent;
	}

	//Returns the most left node on the current branch.
	Node* getInOrderSucc(Node* node)
	{
		Node* curr = node;
		while (curr->left != NULL)
			curr = curr->left;

		return curr;
	}
	// Calls the deleteWeapon function
	void deleteWeaponInvoke(string weaponToDelete) {
		root = deleteWeapon(root, weaponToDelete);
	}

};

class Player {
public:
	string name;
	Weapon ** backpack;
	int numItems;
	float money;

	Player(string n, float m) {
		name = n;
		money = m;
		numItems = 0;
		backpack = new Weapon*[10];
	}

	void buy(Weapon * w) {
		cout << w->weaponName << " bought..." << endl;
		backpack[numItems] = w;
		numItems++;
		cout << "Number of Items " << numItems << endl;
	}
	void withdraw(float amt) {
		money = money - amt;
	}

	bool inventoryFull() {
		bool full = false;
		if (numItems == 10)full = true;
		return full;
	}


	void printCharacter() {
		cout << " Name:" << name << "\n Money:" << money << endl;
		printBackpack();
	}

	void printBackpack() {
		cout << " " << name << ", you own " << numItems << " Weapons:" << endl;
		for (int x = 0; x<numItems; x++) {
			cout << " " << backpack[x]->weaponName << endl;
		}
		cout << endl;
	}

};

void addWeapons(BinaryTree* b) {
	cout << "***********WELCOME TO THE WEAPON ADDING MENU*********" << endl;
	string weaponName; int weaponRange; int weaponDamage; float weaponWeight; float weaponCost;
	cout << "Please enter the NAME of the Weapon ('end' to quit):"; cin >> weaponName;
	while (weaponName.compare("end") != 0) {
		cout << "Please enter the Range of the Weapon (0-10):"; cin >> weaponRange;
		cout << "Please enter the Damage of the Weapon:"; cin >> weaponDamage;
		cout << "Please enter the Weight of the Weapon (in pounds):"; cin >> weaponWeight;
		cout << "Please enter the Cost of the Weapon:"; cin >> weaponCost;
		Weapon *w = new Weapon(weaponName, weaponRange, weaponDamage, weaponWeight, weaponCost);
		b->insert(w);
		cout << endl;

		cout << "Please enter the NAME of another Weapon ('end' to quit):"; cin >> weaponName;
	}

}

void showRoom(BinaryTree* bT, Player *p) {
	string choice;
	cout << "WELCOME TO THE SHOWROOM!!!!" << endl;
	bT->displayInOrder();
	cout << " You have " << p->money << " money." << endl;
	cout << "Please select a weapon to buy('end' to quit):"; cin >> choice;
	while (choice.compare("end") != 0 && !p->inventoryFull()) {
		
		// Search tree for the weapon of choice
		Node* temporaryHolder;    // Temporary holder if we find the node with our choice.
		Weapon *w;                // Weapon holder 

		if ((temporaryHolder = bT->search(choice)) != NULL)  //if choice is found 
		{
		   w = temporaryHolder->myWeapon;  // Take the weapon from the temporary holder and put it on our weapon holder
		}				
		else                          //choice is not found
			w = NULL;

		if (w != NULL) {
			if (w->cost > p->money) {
				cout << "Insufficient funds to buy " << w->weaponName << endl;
			}
			else {
				p->buy(w);
				p->withdraw(w->cost);
				bT->deleteWeaponInvoke(choice); // deleting choice from BinaryTree 
				cout << endl;
				bT->displayInOrder();           // printing BinaryTree In-Order
				cout << " You have " << p->money << " money." << endl;
			}
		}
		else {
			cout << " ** " << choice << " not found!! **" << endl;
		}
		cout << "Please select another weapon to buy('end' to quit):"; cin >> choice;
	}
	cout << endl;
}


int main() {
	string pname;
	cout << "Please enter Player name:" << endl;
	cin >> pname;
	Player pl(pname, 45);
	BinaryTree *bt = new BinaryTree();
	addWeapons(bt);
	cout << endl;
	showRoom(bt, &pl);
	cout << endl;
	pl.printCharacter();
	return 0;
}



