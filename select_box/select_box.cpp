#include <iostream>
#include <sstream>
#include <string>
#include <fstream>

using namespace std;

struct box
{
	int series;
	int space;
};
struct package
{
	int requredSpace;
	int emptySpace;
	box bestBox;
};
string selectBox(package[], box[], int, int, int = 0);
void sort(package[]);
int stringToNum(string, int);
void readFile(package[], box[]);

int main()
{
	package pack[10];
	box boxes[10];
	readFile(pack, boxes);
	int a = stringToNum(selectBox(pack, boxes, 0, 5), 2);
	cout << a << endl; 
	int i = 0;
	while (pack[i].requredSpace > 0)
	{
		cout << pack[i].requredSpace << " " << pack[i].bestBox.space << endl;
		i++;
	}
}

string selectBox(package pack[], box boxes[], int start, int finish, int series)
{
	//base
	if (start == finish)
	{
		int q, i = 1, empS = 100000; //counter, endOfAnyBoxproducer, emptySpace
		while (boxes[i].space > 0)
		{
			if (series != 0)
				if (series != boxes[i].series)
				{
					i++;
					continue;
				}
			if (boxes[i].space - pack[start].requredSpace < 0)
			{
				i++;
				continue;
			}
			if (empS > boxes[i].space - pack[start].requredSpace)
			{
				empS = boxes[i].space - pack[start].requredSpace;
				pack[start].emptySpace = empS;
				pack[start].bestBox = boxes[i];
			}
			i++;
		}
		//to return two values used string
		//a string like "firstNum secondNum"
		stringstream text;
		text << pack[start].bestBox.series << " " << pack[start].emptySpace;
		return text.str() ;
	}
	int pivot = (start + finish) / 2;
	int firstSeries, firstEmptySpace, secondSeries, secondEmptySpace;
	string first, second, temp;
	//get lower values 
	first = selectBox(pack, boxes, start, pivot, series);
	second = selectBox(pack, boxes, pivot + 1, finish, series);
	//turn string to 2 numbers
	firstSeries = stringToNum(first, 1);
	firstEmptySpace = stringToNum(first, 2);
	secondSeries = stringToNum(second, 1);
	secondEmptySpace = stringToNum(second, 2);
	//for when series are equal
	if (firstSeries == secondSeries)
	{
		stringstream text;
		text << firstSeries << " " << firstEmptySpace + secondEmptySpace;
		return text.str();
	}
	//for when series are not equal
	if (firstEmptySpace > secondEmptySpace)
	{
		second = selectBox(pack, boxes, pivot + 1, finish, firstSeries);
		secondSeries = stringToNum(second, 1);
		secondEmptySpace = stringToNum(second, 2);
	}
	else if (firstEmptySpace < secondEmptySpace)
	{
		first = selectBox(pack, boxes, start, pivot, secondSeries);
		firstSeries = stringToNum(first, 1);
		firstEmptySpace = stringToNum(first, 2);
	}
	//when empty spaces are equal 
	else
	{ //get empty space for other series to check properly
		first = selectBox(pack, boxes, start, pivot, secondSeries);
		second = selectBox(pack, boxes, pivot + 1, finish, firstSeries);
		firstSeries = stringToNum(first, 1);
		firstEmptySpace = stringToNum(first, 2);
		secondSeries = stringToNum(second, 1);
		secondEmptySpace = stringToNum(second, 2);
		//check the minimum
		if (firstEmptySpace > secondEmptySpace)
		{
			second = selectBox(pack, boxes, pivot + 1, finish, firstSeries);
			secondSeries = stringToNum(second, 1);
			secondEmptySpace = stringToNum(second, 2);
		}
		else if (firstEmptySpace < secondEmptySpace)
		{
			first = selectBox(pack, boxes, start, pivot, secondSeries);
			firstSeries = stringToNum(first, 1);
			firstEmptySpace = stringToNum(first, 2);
		}
	}
	//to return two values used string
	//a string like "firstNum secondNum"
	stringstream text;
	text << firstSeries << " " << firstEmptySpace + secondEmptySpace;
	return text.str();
}

//turn strings like "number number" to in 
//has 2 values for choice 1 for first number and 2 for the second one
int stringToNum(string inputText ,int choice) 
{
	int number;
	string temp;
	stringstream text(inputText);
	text >> temp;
	number = stoi(temp);
	//to get the first number
	if (choice == 1)
		return number;
	//to get the second number
	text >> temp;
	number = stoi(temp);
	return number;
}

void readFile(package pack[], box boxes[])
{
	ifstream in("in.txt");
	if (!in)
	{
		cout << "file didn't opend"<<endl <<"please close";
		system("pause");
		return;
	}
	int temp, counter;
	string temp2;
	in >> counter;
	for (int i = 0; i < counter; i++)
	{
		in >> temp;
		pack[i].requredSpace = temp;
	}
	in >> counter;
	boxes[0].series = -1;
	boxes[0].space = counter;
	getline(in, temp2);
	int j = 1;
	for (int i = 1; i <= counter; i++)
	{
		getline(in, temp2);
		stringstream line(temp2);
		while (line >> temp)
		{
			boxes[j].series = i;
			boxes[j].space = temp;
			j++;
		}
	}
}