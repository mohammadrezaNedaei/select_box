#include <iostream>
#include <sstream>
#include <string>

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

int main()
{
	package pack[10];
	pack[0].requredSpace = 3;
	pack[1].requredSpace = 5;
	pack[2].requredSpace = 8;
	pack[3].requredSpace = 10;
	pack[4].requredSpace = 11;
	pack[5].requredSpace = 12;
	box boxes[10];
	boxes[0].series = -1;
	boxes[0].space = 3;
	boxes[1].series = 1;
	boxes[1].space = 12;
	boxes[2].series = 2;
	boxes[2].space = 11;
	boxes[3].series = 2;
	boxes[3].space = 9;
	boxes[4].series = 3;
	boxes[4].space = 10;
	boxes[5].series = 3;
	boxes[5].space = 5;
	boxes[6].series = 3;
	boxes[6].space = 14;
	selectBox(pack, boxes, 0, 5);
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
	secondEmptySpace = stringToNum(first, 2);
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
	stringstream text;
	text << firstSeries << " " << firstEmptySpace + secondEmptySpace;
	return text.str();
}

int stringToNum(string inputText ,int choice) 
{
	int number;
	string temp;
	stringstream text(inputText);
	text >> temp;
	number = stoi(temp);
	if (choice == 1)
		return number;
	text >> temp;
	number = stoi(temp);
	return number;
}