#include <iostream>
#include <fstream>
using namespace std;

template <typename T>
class StatisticalCalculation
{
private:
    int size;

public:
    T *data;
    StatisticalCalculation(int size);
    ~StatisticalCalculation();
    void sort(); // Implement sorting algorithm
    // Statistical Calculation functions
    T findMedian();
    T findMin();
    T findMax();
    double findMean();
    T findSummation();

    // Utility Functions
    void displayArray();   // Display sorted array
    void inputData();      // Take input dynamically
    void StatisticsMenu(); // just the menu
};

template <typename T>
StatisticalCalculation<T>::StatisticalCalculation(int size) : size(size), data(new T[size]) {}

template <typename T>
StatisticalCalculation<T>::~StatisticalCalculation()
{
    delete[] data;
    data = nullptr;
}

template <typename T>
void StatisticalCalculation<T>::sort() // i will implement the Bubble sort
{
    for (int i = 0; i < size - 1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (data[j] > data[j + 1])
                swap(data[j], data[j + 1]);
        }
    }
}

template <typename T>
T StatisticalCalculation<T>::findMedian()
{
    if (size % 2 == 1)
        return data[size / 2];
    else
        return double(data[(size / 2) - 1] + data[size / 2]) / 2.0;
}

template <typename T>
T StatisticalCalculation<T>::findMin()
{
    return data[0];
}

template <typename T>
T StatisticalCalculation<T>::findMax()
{
    return data[size - 1];
}

template <typename T>
double StatisticalCalculation<T>::findMean()
{
    return (double)(findSummation()) / size;
}

template <typename T>
T StatisticalCalculation<T>::findSummation()
{
    T summation = 0;
    for (int i = 0; i < size; i++)
    {
        summation += data[i];
    }

    return summation;
}

template <typename T>
void StatisticalCalculation<T>::inputData()
{
    for (int i = 0; i < size; i++)
    {
        cout << "Enter element " << i + 1 << ": ";
        cin >> data[i];
    }
}

template <typename T>
void StatisticalCalculation<T>::StatisticsMenu()
{
    cout << "Select a statistical calculation:\n";
    cout << "1. Find Median\n";
    cout << "2. Find Minimum\n";
    cout << "3. Find Maximum\n";
    cout << "4. Find Mean\n";
    cout << "5. Find Summation\n";

    cout << "Enter your choice (1 - 5): ";

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "Median: " << findMedian() << "\n";
        break;
    case 2:
        cout << "Minimum: " << findMin() << "\n";
        break;
    case 3:
        cout << "Maximum: " << findMax() << "\n";
        break;
    case 4:
        cout << "Mean: " << findMean() << "\n";
        break;
    case 5:
        cout << "Summation: " << findSummation() << "\n";
        break;
    default:
        cout << "Invalid choice! Please insert a number between 1 and 5.\n";
        break;
    }
}

template <typename T>
void StatisticalCalculation<T>::displayArray()
{
    for (int i = 0; i < size; i++)
    {
        cout << data[i] << " ";
    }
    cout << "\n";
}

int main()
{
    ifstream inputFile("statistics.txt"); // Hardcoded file name
    if (!inputFile)
    {
        cerr << "Failed to open file." << endl;
        return 1;
    }

    int n;
    inputFile >> n;

    StatisticalCalculation<int> statistics(n);

    for (int i = 0; i < n; i++)
    {
        inputFile >> statistics.data[i]; // Directly populate the array
    }

    inputFile.close();

    statistics.sort();

    while (true)
    {
        statistics.displayArray();
        statistics.StatisticsMenu();

        cout << "1. Another Operation\n";
        cout << "2. Exit\n";

        int choice;
        cin >> choice;

        if (choice == 2)
            break;
        else if (choice != 1)
            cout << "Invalid choice! Please insert a number between 1 and 2.\n";
    }

    return 0;
}