#include "../utils/Vector.h"
using namespace std;

class Guest
{
	string name;
	string contact;
	string iftar_date;

public:
	Guest() {};
	Guest(string name, string contact, string iftar_date) : name(name), contact(contact), iftar_date(iftar_date) {};
	void display_guest();
	void update_invitation(string new_date);
	string getName();
	string getContact();
	string getIftarDate();
	friend ostream &operator<<(ostream &os, const Guest &guest)
	{
		os << "Name: " << guest.name << endl;
		os << "Contact: " << guest.contact << endl;
		os << "Iftar Date: " << guest.iftar_date << endl;
		return os;
	}

	bool operator<(Guest &g)
	{
		return iftar_date < g.iftar_date;
	}

	bool operator>(Guest &g)
	{
		return iftar_date > g.iftar_date;
	}
};

void Guest::display_guest()
{
	cout << "--------------\n";
	cout << "-Name: " << name << endl;
	cout << "-Contact Email: " << contact << endl;
	cout << "-Iftar Date: " << iftar_date << endl;
	cout << "--------------\n\n";
}

void Guest::update_invitation(string date)
{
	iftar_date = date;
}

string Guest::getName()
{
	return name;
}

string Guest::getContact()
{
	return contact;
}

string Guest::getIftarDate()
{
	return iftar_date;
}

class IftarManager
{
private:
	Vector<Guest> guest_list;

public:
	void add_guest(Guest guest);
	void remove_guest(string guest);
	void display_all_guests();
	void update_guest_invitation(string name, string new_date);
	void send_reminders(string date);
	void sort_guest_list();
};

void IftarManager::add_guest(Guest guest)
{
	
	
	for (int i = 0; i < guest_list.get_size(); i++)
	{
		if (guest_list[i].getName() == guest.getName())
		{
			cout << "Guest with the same name already registered\n";
			return;
		}
	}
	
	guest_list.push(guest);
	
}

void IftarManager::remove_guest(string name)
{
    for (int i = 0; i < guest_list.get_size(); i++)
    {
        if (guest_list[i].getName() == name)
        {
            cout << "Removed " << name << endl;
            guest_list.removeAt(i);
            return;
        }
    }
    cout << "No guest registered with that name\n";
}

void IftarManager::display_all_guests()
{
	for (int i = 0; i < guest_list.get_size(); i++)
	{
		guest_list[i].display_guest();
	}
}

void IftarManager::update_guest_invitation(string name, string new_date)
{
	for (int i = 0; i < guest_list.get_size(); i++)
	{
		if (guest_list[i].getName() == name)
		{
			cout << "Updating info for " << name << endl;
			guest_list[i].update_invitation(new_date);
			return;
		}
	}
	cout << "No Guest with that name found\n";
}

void IftarManager::send_reminders(string date)
{
	bool flag = false;
	cout << "Sending reminders...\n";
	for (int i = 0; i < guest_list.get_size(); i++)
	{
		if (guest_list[i].getIftarDate() == date)
		{
			cout << guest_list[i].getName() << " notifed! Iftar Date is " << guest_list[i].getIftarDate() << endl;
			flag = true;
		}
	}

	if (!flag)
	{
		cout << "No guests notifed\n";
	}
}

void IftarManager::sort_guest_list()
{
	guest_list.sort();
}

int main()
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
	manager.remove_guest("Omar");
	manager.display_all_guests();
	return 0;
}