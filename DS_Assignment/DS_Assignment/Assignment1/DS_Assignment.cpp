#include <iostream>
#include "./utils/Vector.h"
#include "./one/Guest.h"
#include "./one/Guest.cpp"
#include "./one/IftarManager.h"
#include "./one/IftarManager.cpp"
#include "./four/SortManager.cpp"
#include "./two/Polynomial.h"
#include "./two/Polynomial.cpp"
#include "./three/SortedLinkedList.cpp"

using namespace std;

void p1_test_cases()
{
	IftarManager manager;
	Guest guest1("Aisha", "aisha@example.com", "2025-03-15");
	Guest guest2("Omar", "omar@example.com", "2025-03-18");
	Guest guest3("Zainab", "zainab@example.com", "2025-03-20");
	manager.add_guest(guest1);
	manager.add_guest(guest2);
	manager.add_guest(guest3);
	// Display guest list
	manager.display_all_guests();
	// Update invitation date for Omar
	manager.update_guest_invitation("Omar", "2025-03-15");
	// Display updated guest lis
	manager.display_all_guests();
	// Send reminders
	manager.send_reminders("2025-03-15");
}

void p2_test_cases()
{
	int order1, order2;
	cout << "Order of first polynomial: ";
	cin >> order1;
	Polynomial poly1(order1);
	poly1.input();
	poly1.display();

	cout << "Order of second polynomial: ";
	cin >> order2;
	Polynomial poly2(order2);
	poly2.input();

	cout << "First polynomial: ";
	poly1.display();

	cout << "Second polynomial: ";
	poly2.display();

	Polynomial sum = poly1.add(poly2);
	cout << "Sum of polynomials: ";
	sum.display();

	Polynomial difference = poly1.subtract(poly2);
	cout << "Difference of polynomials: ";
	difference.display();
}

void p4_test_cases()
{
	SortManager<int> sort;

	Vector<int> v;
	v.push(1);
	v.push(-1);
	v.push(15);
	v.push(10);
	v.push(2315);
	v.push(-21);
	v.push(7);
	v.push(10);

	v = sort.merge_sort(v);
	// v = sort.selection_sort(v);
	// v = sort.bubble_sort(v);

	v.print();
}

void p3_test_cases(){
    SortedLinkedList L;
    L.insert(5); 
    L.insert(8);
    L.insert(7);
    L.insert(6); 
    L.insert(6); 
    cout << L<<endl; // Output: [5, 6, 6, 7, 8]

    L.remove(0); 
    cout << L<<endl; // Output: [6, 6, 7, 8]

    L.remove(100); // No change 
    cout << L<<endl; // Output: [6, 6, 7, 8]

    L.remove(2); 
    cout << L<<endl; // Output: [6, 6, 8]

    L.remove(2); 
    cout << L; // Output: [6, 6]    
}

int main()
{
	
	p3_test_cases();
}