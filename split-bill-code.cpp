#include <iostream>
#include <vector>
using namespace std;

struct item {
	string name;
	float price; //this is the price for each one item
};

struct person {
	string name;
	float fee; //initial fee for each person is initialized as 0
};

vector<item> itemList;

//mini function : allows user to enter all relevant items with no limit
void insertItems () {
	
	string option;
	cout << "Insert new item (y/n) : "; cin >> option;
	
	while(option == "y"){
		item newitem;
		
		//gets the details for each item
		cout << "Item name : "; cin >> newitem.name;
		cout << "Item price : "; cin >> newitem.price;
		
		//makes each item as an object
		itemList.push_back(newitem);
		cout << "Insert new item (y/n) : "; cin >> option;
	}
}

//mini function : prints all items in the list (DIFFERENT FROM THE FINAL SPLIT BILL!)
void printItemList (){
	int size = itemList.size();
	if(size == 0) {
		cout << "No Items Added." << endl;
		return;
	}
	
	cout << "\nUnpaid Items List" << endl;
	for(int i=0; i<size; i++){
		item it = itemList.at(i);
		cout << i+1 << ") " << it.name << " || Price : " << it.price << endl;
	}
}


//mini function : allows user to insert the names of people who will be splitting the final bill
//and calculates individual fees with tax included
void calculateBill(){ //improvement : hasnt handled wrong user input
	if(itemList.size() == 0) return;
	
	
	vector<person> peopleList;
	float tax; cout << "\nEnter tax rate (%): "; cin >> tax;
	
	string option; string n;
	cout << "\nInsert new person (y/n) : "; cin >> option;
	
	if(option == "n") return;
	
	while(option == "y" && itemList.size() > 0){
		person p;
		
		//gets the details for each person
		cout << "Person name : "; cin >> p.name;
		p.fee = 0;
		
		string willPay = "n";
		cout << "Claim to pay an item (y/n) : "; cin >> willPay;
		
		while(willPay == "y"){
		
			printItemList();
			cout << p.name << " will pay for item number : ";
			int num; cin >> num;
			
			p.fee = p.fee + itemList.at(num-1).price;
			vector<item>::iterator it;
			it=itemList.begin()+num-1;
			itemList.erase(it);
			cout << "Claim to pay another item (y/n) : "; cin >> willPay;
		}
		
		peopleList.push_back(p);
		cout << "\nInsert new person (y/n) : "; cin >> option;
	}
	
	//calculates final bill when added with tax
	cout << "\nFINAL SPLIT (FEE PER PERSON) AFTER TAX RATE" << endl;
	cout << "===========================================" << endl;
	
	int i=0;
	while(i < peopleList.size()){
		person p = peopleList.at(i);
		float addingtax = (tax * p.fee) / 100;
		cout << i+1 << ") " << p.name << " : " << endl;
		cout << "Previous Fee : " << p.fee << " || Tax : " << addingtax << endl;
		cout << "Total Fee : " << p.fee+addingtax << endl;
		i++;
	}
}


//main function : the loop keeps repeating until user quits
int main(){
	int option = 3;
	do{
		cout << "\nMENU" << "\n==================================================" << endl;
		cout << "\n1) Insert new items" << "\n2) Show current item list";
		cout << "\n3) Split and print bill details" << "\n4) Quit";
		cout << "\nEnter number option : ";
		
		cin >> option;
		
		switch(option){
			case 1: {
				insertItems();
				break;
			}
			case 2: {
				printItemList();
				break;
			}
			case 3:{
				calculateBill();
				break;
			}
			default : return 0;
		}
	
	}while(option != 3);
	return 0;
}