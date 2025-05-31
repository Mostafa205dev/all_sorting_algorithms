#include <iostream>
#include <fstream>
#include <string>
using namespace std;

const int MAX_PATIENTS = 100;

class Patient
{
public:
	string name;
	int severity;
	int arrival_time;

	void set(string n, int s, int a)
	{
		name = n;
		severity = s;
		arrival_time = a;
	}

	bool is_higher_priority_than(const Patient &other) const
	{
		if (severity != other.severity)
			return severity > other.severity;
		return arrival_time < other.arrival_time;
	}
};

class MaxHeap
{
private:
	Patient heap[MAX_PATIENTS];
	int size;

	void swap(Patient &a, Patient &b)
	{
		Patient temp = a;
		a = b;
		b = temp;
	}

	void heapify_up(int index)
	{
		while (index > 0)
		{
			int parent = (index - 1) / 2;
			if (heap[index].is_higher_priority_than(heap[parent]))
			{
				swap(heap[index], heap[parent]);
				index = parent;
			}
			else
			{
				break;
			}
		}
	}

	void heapify_down(int index)
	{
		while (index < size)
		{
			int left = 2 * index + 1;
			int right = 2 * index + 2;
			int largest = index;

			if (left < size && heap[left].is_higher_priority_than(heap[largest]))
				largest = left;
			if (right < size && heap[right].is_higher_priority_than(heap[largest]))
				largest = right;

			if (largest != index)
			{
				swap(heap[index], heap[largest]);
				index = largest;
			}
			else
			{
				break;
			}
		}
	}

public:
	MaxHeap()
	{
		size = 0;
	}

	void insert(const Patient &p)
	{
		if (size >= MAX_PATIENTS)
		{
			cout << "Heap is full!" << endl;
			return;
		}
		heap[size] = p;
		heapify_up(size);
		size++;
	}

	Patient extract_max()
	{
		if (size == 0)
		{
			Patient empty;
			empty.set("None", -1, -1);
			return empty;
		}
		Patient max = heap[0];
		heap[0] = heap[size - 1];
		size--;
		heapify_down(0);
		return max;
	}

	void print_heap()
	{
		for (int i = 0; i < size; i++)
		{
			cout << heap[i].name << " ";
		}
		cout << endl;
	}

	bool is_empty() const
	{
		return size == 0;
	}
};

int main()
{
	MaxHeap queue;
	ifstream infile("testp4.txt");
	if (!infile)
	{
		cout << "Error: Could not open test_cases.txt" << endl;
		return 1;
	}

	Patient patients[10];
	int i = 0;
	while (infile && i < 10)
	{
		string name;
		int severity, arrival_time;
		infile >> name >> severity >> arrival_time;
		if (infile)
		{
			patients[i].set(name, severity, arrival_time);
			i++;
		}
	}
	infile.close();

	cout << "Inserting patients:\n";
	for (int j = 0; j < i; j++)
	{
		cout << "Inserting: " << patients[j].name << endl;
		queue.insert(patients[j]);
		cout << "Heap: ";
		queue.print_heap();
	}

	cout << "\nTreatment Order:\n";
	while (!queue.is_empty())
	{
		Patient p = queue.extract_max();
		cout << "Treating: " << p.name << endl;
	}
}
