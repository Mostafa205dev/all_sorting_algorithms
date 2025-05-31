#include "../utils/Vector.h"

#include <iostream>
#include <chrono>
#include <algorithm>
#include <functional>
using namespace std;
using namespace chrono;
template <typename T>
class SortingSystem
{
public:
	void insertionSort(Vector<T> &vec);
	void selectionSort(Vector<T> &vec);
	void bubbleSort(Vector<T> &vec);
	void shellSort(Vector<T> &vec);
	void mergeSort(Vector<T> &vec, int left, int right);
	void quickSort(Vector<T> &vec, int low = 0, int high = -1);

	// Integer-only sorting algorithms
	void countSort(Vector<int> &vec);
	void radixSort(Vector<int> &vec);
	void bucketSort(Vector<float> &vec);

	// Utility functions
	int partition(Vector<T> &vec, int low, int high);
	void merge(Vector<T> &vec, int left, int mid, int right);
	void interactiveMenu();

private:
	void countingSortForRadix(Vector<int> &vec, int exp, int minVal);
};

template <typename T>
void SortingSystem<T>::insertionSort(Vector<T> &vec)
{
	for (int i = 1; i < vec.get_size(); i++)
	{
		T key = vec[i];
		int j = i - 1;
		while (j >= 0 && vec[j] > key)
		{
			vec[j + 1] = vec[j];
			j--;
		}
		vec[j + 1] = key;
		vec.print(); // Display each step
	}
}

// Selection Sort
template <typename T>
void SortingSystem<T>::selectionSort(Vector<T> &vec)
{
	int n = vec.get_size();
	for (int i = 0; i < n - 1; i++)
	{
		int minIndex = i;
		for (int j = i + 1; j < n; j++)
		{
			if (vec[j] < vec[minIndex])
				minIndex = j;
		}
		vec.swap(i, minIndex);
		vec.print(); // Display each step
	}
}

// Bubble Sort
template <typename T>
void SortingSystem<T>::bubbleSort(Vector<T> &vec)
{
	int n = vec.get_size();
	for (int i = 0; i < n - 1; i++)
	{
		for (int j = 0; j < n - i - 1; j++)
		{
			if (vec[j] > vec[j + 1])
			{
				vec.swap(j, j + 1);
				vec.print(); // Display each step
			}
		}
	}
}

// Shell Sort
template <typename T>
void SortingSystem<T>::shellSort(Vector<T> &vec)
{
	int n = vec.get_size();
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < n; i++)
		{
			T temp = vec[i];
			int j;
			for (j = i; j >= gap && vec[j - gap] > temp; j -= gap)
			{
				vec[j] = vec[j - gap];
			}
			vec[j] = temp;
		}
		vec.print(); // Display each step
	}
}

// Merge Sortkj
template <typename T>
void SortingSystem<T>::mergeSort(Vector<T> &vec, int left, int right)
{
	if (left < right)
	{
		int mid = left + (right - left) / 2;

		mergeSort(vec, left, mid);
		mergeSort(vec, mid + 1, right);
		merge(vec, left, mid, right);
		vec.print(); // Display each step
	}
}

template <typename T>
void SortingSystem<T>::merge(Vector<T> &vec, int left, int mid, int right)
{
	int n1 = mid - left + 1;
	int n2 = right - mid;
	Vector<T> L(n1), R(n2);

	for (int i = 0; i < n1; i++)
		L[i] = vec[left + i];
	for (int i = 0; i < n2; i++)
		R[i] = vec[mid + 1 + i];

	int i = 0, j = 0, k = left;
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
			vec[k++] = L[i++];
		else
			vec[k++] = R[j++];
	}

	while (i < n1)
		vec[k++] = L[i++];
	while (j < n2)
		vec[k++] = R[j++];
}

// Quick Sort
template <typename T>
int SortingSystem<T>::partition(Vector<T> &vec, int low, int high)
{
	T pivot = vec[high];
	int i = low - 1;
	for (int j = low; j < high; j++)
	{
		if (vec[j] < pivot)
		{
			i++;
			vec.swap(i, j);
		}
	}
	vec.swap(i + 1, high);
	vec.print(); // Display each step
	return i + 1;
}

template <typename T>
void SortingSystem<T>::quickSort(Vector<T> &vec, int low, int high)
{
	if (high == -1)
	{
		high = vec.get_size() - 1;
	}
	if (low < high)
	{
		int pi = partition(vec, low, high);
		quickSort(vec, low, pi - 1);
		quickSort(vec, pi + 1, high);
	}
}

template <>
void SortingSystem<int>::countSort(Vector<int> &vec)
{
	int n = vec.get_size();

	// Find max value in the input array
	int maxVal = vec[0];
	for (int i = 1; i < n; i++)
	{
		if (vec[i] > maxVal)
		{
			maxVal = vec[i];
		}
	}

	vector<int> count(maxVal + 1, 0);

	// Count occurrences of each value
	for (int i = 0; i < n; i++)
	{
		count[vec[i]]++;
	}

	for (int i = 1; i <= maxVal; i++)
	{
		count[i] += count[i - 1];
	}

	// Create output array
	Vector<int> output(n);
	for (int i = n - 1; i >= 0; i--)
	{
		output[count[vec[i]] - 1] = vec[i];
		count[vec[i]]--;
	}

	// Copy sorted values back to original vector
	for (int i = 0; i < n; i++)
	{
		vec[i] = output[i];
	}

	vec.print(); // Print final sorted array
}

template <>
void SortingSystem<int>::countingSortForRadix(Vector<int> &vec, int exp, int minVal)
{
	Vector<int> output(vec.get_size());
	Vector<int> count(10); // We are working with base 10 for radix

	// Store count of occurrences
	for (int i = 0; i < vec.get_size(); i++)
		count[((vec[i] - minVal) / exp) % 10]++;

	// Change count[i] so that it contains the actual position of this digit
	for (int i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Build the output array
	for (int i = vec.get_size() - 1; i >= 0; i--)
	{
		output[count[((vec[i] - minVal) / exp) % 10] - 1] = vec[i];
		count[((vec[i] - minVal) / exp) % 10]--;
	}

	// Copy the output array back to the original array
	for (int i = 0; i < vec.get_size(); i++)
		vec[i] = output[i];
}

// Radix Sort (only for integers)
template <>
void SortingSystem<int>::radixSort(Vector<int> &vec)
{

	int maxVal = *max_element(&vec[0], &vec[0] + vec.get_size());
	int minVal = *min_element(&vec[0], &vec[0] + vec.get_size());

	minVal = min(0, minVal);

	// Perform counting sort for every digit, starting from the least significant digit
	for (int exp = 1; maxVal / exp > 0; exp *= 10)
	{
		countingSortForRadix(vec, exp, minVal);
		vec.print(); // Display the array after each step
	}
}

template <>
void SortingSystem<float>::bucketSort(Vector<float> &vec)
{
	if (vec.get_size() <= 1)
	{
		return;
	}
	Vector<Vector<float>> bucket;
	for (int i = 0; i < vec.get_size(); i++)
	{
		Vector<float> v;
		bucket.push(v);
	}

	for (int i = 0; i < vec.get_size(); i++)
	{
		bucket[(int)(vec[i] * vec.get_size())].push(vec[i]);
	}
	for (int i = 0; i < bucket.get_size(); i++)
	{
		// bucket.print();
		if (bucket[i].get_size() > 1)
		{
			cout << "Quick sort on bucket: ";
			quickSort(bucket[i]);
		}
	}

	int iter = 0;
	for (int i = 0; i < bucket.get_size(); i++)
	{
		for (int j = 0; j < bucket[i].get_size(); j++)
		{
			vec[iter++] = bucket[i][j];
		}
	}

	vec.print();
}

template <typename T>
void SortingSystem<T>::interactiveMenu()
{
	Vector<T> vec;
	int size;
	int choice;

	// Input size of the dataset
	std::cout << "Enter the size of the dataset: ";
	std::cin >> size;

	// Input dataset values dynamically
	std::cout << "Enter " << size << " values:" << std::endl;
	for (int i = 0; i < size; i++)
	{
		T value;
		std::cin >> value;
		vec.push(value);
	}

	// Display sorting algorithm options
	std::cout << "Choose a sorting algorithm:" << std::endl;
	std::cout << "1. Insertion Sort\n";
	std::cout << "2. Selection Sort\n";
	std::cout << "3. Bubble Sort\n";
	std::cout << "4. Shell Sort\n";
	std::cout << "5. Merge Sort\n";
	std::cout << "6. Quick Sort\n";
	std::cout << "7. Count Sort (Only for integers)\n";
	std::cout << "8. Radix Sort (Only for integers)\n";
	std::cout << "9. Bucket Sort (Only for floating-point numbers)\n";

	// Get user selection
	cin >> choice;
	switch (choice)
	{
	case 1:
		// (&SortingSystem::insertionSort, &vec);
		this->insertionSort(vec);
		break;
	case 2:
		// (&SortingSystem::selectionSort, vec);
		this->selectionSort(vec);
		break;
	case 3:
		// (&SortingSystem::bubbleSort, vec);
		this->bubbleSort(vec);
		break;
	case 4:
		// (&SortingSystem::shellSort, vec);
		this->shellSort(vec);
		break;
	case 5:
		// (&SortingSystem::mergeSort, vec, 0, vec.get_size() - 1);
		this->mergeSort(vec, 0, vec.get_size() - 1);
		break;
	case 6:
		// (&SortingSystem::quickSort, vec, 0, vec.get_size() - 1);
		this->quickSort(vec, 0, vec.get_size() - 1);
		break;
	case 7:
		if constexpr (std::is_same<T, int>::value)
		{
			this->countSort(vec);
		}
		else
		{
			cout << "Count Sort is only available for integers!" << std::endl;
		}
		break;
	case 8:
		if constexpr (std::is_same<T, int>::value)
		{
			this->radixSort(vec);
		}
		else
		{
			cout << "Radix Sort is only available for integers!" << std::endl;
		}
		break;
	case 9:
		if constexpr (std::is_same<T, float>::value)
		{
			this->bucketSort(vec); // ✅ Correct function call
		}
		else
		{
			std::cout << "Bucket Sort is only available for floating-point numbers!" << std::endl;
		}
		break;

	default:
		std::cout << "Invalid choice!" << std::endl;
		break;
	}

	// Output the sorted array
	std::cout << "Sorted Array: ";
	vec.print();
}

int main()
{
	cout << "Sorting System\n";
	SortingSystem<int> intSorter;
	SortingSystem<float> floatSorter;

	cout << "Select data type:\n1. Integer\n2. Floating-point\n";
	int dataType;
	cin >> dataType;

	if (dataType == 1)
	{
		intSorter.interactiveMenu();
	}
	else if (dataType == 2)
	{
		floatSorter.interactiveMenu();
	}
	else
	{
		cout << "Invalid data type!\n";
	}

	return 0;
}