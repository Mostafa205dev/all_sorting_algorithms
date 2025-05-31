#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main()
{
	ifstream infile("testp3.txt");
	string line;
	int arr[1000];
	int n = 0;

	// Read first line (array values)
	int size = 0;
	if (getline(infile, line))
	{
		istringstream iss(line);
		while (iss >> arr[n])
		{
			n++;
		}
	}

	// Read second line (k)
	int k;
	infile >> k;

	// Debug output
	// cout << "Array size = " << n << endl;
	// cout << "k = " << k << endl;
	// cout << "arr = ";
	// for (int i = 0; i < n; ++i)
	// {
	//     cout << arr[i] << " ";
	// }
	// cout << endl;

	int res = 0;

	for (int i = 0; i < n && (i + k) <= n; i++)
	{
		if (arr[i] == 0)
		{
			res++;
			int turnNum = k;
			for (int j = i; turnNum--; j++)
			{
				arr[j] = !arr[j];
				// cout << "i flipped index " << j << "\n";
			}
		}
	}

	for (int i = 0; i < n; ++i)
	{
		if (arr[i] == 0)
		{
			res = -1;
			break;
		}
	}

	cout << res;

	// // new arr

	// cout << "\n\n\nNew arr\n\n";
	// for (int i = 0; i < n; ++i)
	// {
	//     cout << arr[i] << " ";
	// }
	// cout << "\nres is " << res << "\n";

	return 0;
}
