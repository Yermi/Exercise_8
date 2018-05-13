#include <iostream>
using namespace std;

int ** addLine(int LineNumber, int Steps, int Duration, int **lines, int size)
{
	// find the correct locatin where LineNumber heve to be stored
	int LocationOfNewLine = 0;
	while (LocationOfNewLine < size && (LineNumber > lines[LocationOfNewLine][0]))
	{
		LocationOfNewLine++;
	}

	// initilize the new array of Bus lines
	int ** NewLinesArray = new int*[size+1];
	for (int i = 0; i < size+1; i++)
	{
		NewLinesArray[i] = new int[3];
	}

	// copying all the elements of the previus array to a new array 
	for (int i = 0; i < LocationOfNewLine; i++)
	{
		NewLinesArray[i][0] = lines[i][0];
		NewLinesArray[i][1] = lines[i][1];
		NewLinesArray[i][2] = lines[i][2];
	}

	NewLinesArray[LocationOfNewLine][0] = LineNumber;
	NewLinesArray[LocationOfNewLine][1] = Steps;
	NewLinesArray[LocationOfNewLine][2] = Duration;

	for (int i = LocationOfNewLine+1; i < size+1; i++)
	{
		NewLinesArray[i][0] = lines[i-1][0];
		NewLinesArray[i][1] = lines[i-1][1];
		NewLinesArray[i][2] = lines[i-1][2];
	}

	for (int i = 0; i < size; ++i) {
		delete[] lines[i];
	}

	return NewLinesArray;
}
int ** deleteLine(int LineNumber, int **lines, int size)
{
	// find the locatin where LineNumber heve to be deleted
	int locationToDelete = 0;
	while (LineNumber > lines[locationToDelete][0] && locationToDelete <= size)
	{
		locationToDelete++;
	}

	if (LineNumber != lines[locationToDelete][0])
	{
		return lines;
	}

	// initilize the new array of Bus lines
	int ** NewLinesArray = new int*[size - 1];
	for (int i = 0; i < size - 1; i++)
	{
		NewLinesArray[i] = new int[3];
	}

	for (int i = 0; i < locationToDelete; i++)
	{
		NewLinesArray[i][0] = lines[i][0];
		NewLinesArray[i][1] = lines[i][1];
		NewLinesArray[i][2] = lines[i][2];
	}
	for (size_t i = locationToDelete; i < size-1; i++)
	{
		NewLinesArray[i][0] = lines[i + 1][0];
		NewLinesArray[i][1] = lines[i + 1][1];
		NewLinesArray[i][2] = lines[i + 1][2];
	}

	for (int i = 0; i < size; ++i) {
		delete[] lines[i];
	}

	return NewLinesArray;
}
void printLines(int **Lines, int size) 
{
	for (size_t i = 1; i < size; i++)
	{
		cout << "Bus Line: " << Lines[i][0] << endl;
		cout << "Stops: " << Lines[i][1] << endl;
		cout << "Duration: " << Lines[i][2] << " min" << endl;
		cout << endl;
	}
}
int indexOfBusLine(int LineNumber, int **lines, int size)
{
	int index = -1;
	for (size_t i = 0; i < size; i++)
	{
		if (LineNumber == lines[i][0])
		{
			index = i;
			return index;
		}
	}
	return index;
}
double avarageTravle(int **lines, int size)
{
	double sum = 0, count = -1;
	for (size_t i = 0; i < size; i++)
	{
		sum += lines[i][2];
		count++;
	}
	return (sum / count);
}
int avarageStops(int **lines, int size)
{
	int sum = 0, count = -1;
	for (size_t i = 0; i < size; i++)
	{
		sum += lines[i][1];
		count++;
	}

	double avg = sum / count;
	int intpart = (int)avg;
	double decpart = avg - intpart;


	if (decpart > 0.5)
	{
		return intpart + 1;
	}
	else
	{
		return intpart;
	}

}
int shortest(int **lines, int size)
{

	int shortest = 1;
	if (size == 1)
	{
		return -1;
	}
	for (size_t i = 1; i < size; i++)
	{
		if (lines[i][2] < lines[shortest][2])
		{
			shortest = i;
		}
	}
	return lines[shortest][0];
}


int main()
{
	// create and initilaze the array contain tha data
	int ** Lines = new int*[0];
	*Lines = new int[3];
	for (size_t i = 0; i < 3; i++)
	{
		Lines[0][i] = NULL;
	}
	int size = 1;

	int choice = 0 ;
	while (choice != 7)
	{
		cout << "enter a number bitween 0-7:" << endl;
		cin >> choice;
		switch (choice)
		{
		case 0:
			int BusLine, Stops, Duration;
			cout << "enter the line to add: " << endl;
			cin >> BusLine;
			cout << endl << "enter the number of stops: " << endl;
			cin >> Stops;
			cout << endl << "enter the duration of the ride: " << endl;
			cin >> Duration;
			Lines = addLine(BusLine, Stops, Duration, Lines, size);
			size++;
			printLines(Lines, size);
			break;
		case 1:
			int BusLineToDelete;
			cout << "enter the line to delete: " << endl;
			cin >> BusLineToDelete;
			Lines = deleteLine(BusLineToDelete, Lines, size);

			// TODO::check if the Bus line is exist. if yes - reduce the size of array
			size--;
			printLines(Lines, size);
			break;
		case 2:
			printLines(Lines, size);
			break;
		case 3:
			int BusLineToSearch;
			cout << "enter the line to search for: " << endl;
			cin >> BusLineToSearch;
			cout << "index of line is: " << indexOfBusLine(BusLineToSearch, Lines, size) << endl;
			break;
		case 4:
			cout << "the avarage travle time is: " << avarageTravle(Lines, size) << endl;
			break;
		case 5:
			cout << "the avarage stops number is: " << avarageStops(Lines, size) << endl;
			break;
		case 6:
			cout << "the shortest bus line is: " << shortest(Lines, size) << endl;
			break;
		case 7:
			break;
		default:
			cout << "Error!" << endl;
		}
	}
}