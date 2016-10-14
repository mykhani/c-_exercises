#include <iostream>
#include <string.h>
#include <cstdlib>
#include "Exception.h"

using namespace std;
using namespace myExceptions;
/* macro to print object name along with contents */
#define PrintPretty(x) cout << #x << " = " << x << endl;

/* forward declaration required to declare << operator overload */
template <class T>
class Set;

template <class T>
ostream& operator << (ostream&, Set<T>&);

/* overriden >> operator to input sets in set notation {} */
template <class T>
istream& operator >> (istream&, Set<T>&);

/* class set is an array that contains unique elements */
template <class T>
class Set {
private:
	T *elements;
	int maxCount;
	int count;
	int index;

public:
	Set(int maxCount);
	~Set();
	bool Contains(T);
	void Insert(T) throw (OverflowException);
	friend istream& operator >> <T> (istream&, Set&);
	friend ostream& operator << <T> (ostream&, Set&); /* If it is defined inline, then <T>
							   * is not needed after << as each
							   * definition is part of class according to type T */
};

template <class T>
Set<T>::Set(int size)
{
	elements = new T[size];
	maxCount = size;
	count = 0;
	index = 0;
}

template <class T>
Set<T>::~Set()
{
	delete [] elements;
}

template <class T>
bool Set<T>::Contains(T element)
{
	int i;
	
	for (i = 0; i < count; i++) {
		if (elements[i] == element)
			return true;
	}
	
	return false;
}

template <class T>
void Set<T>::Insert(T element) throw (OverflowException)
{
	/* first check if element doesn't exist already */
	if (Contains(element)) {
		return ;
	}

	if (count >= maxCount) {
		throw OverflowException();
		return;
	} 

	elements[index++] = element;
	count++;
}

/* provide a specialization for strings objects */
typedef char * Str;
template <>
bool Set<Str>::Contains(Str str)
{
	int i;

	for (i = 0; i < count; i++) {
		if (strncmp(elements[i], str, strlen(str)) == 0)
			return true;
	}

	return false;
}

template <class T>
ostream& operator << (ostream& os, Set<T>& set)
{
	int i;

	os << "{";

	for (i = 0; i < set.count; i++) {
		if (i > 0)
			os << ", ";

		os << set.elements[i]; 
	}

	os << "}";

	return os;
}

template <>
istream& operator >> (istream& is, Set<int>& set)
{
	char ch;
	int index = 0;
	char input[255];
	/* check for { */
	while (ch = is.get()) {
		if (ch == '{') {
			while ((ch = is.get())) {
				if (ch == ',' || ch == '}') {
					input[index] = '\0';
					if (strlen(input) > 0) {
						try {
							set.Insert((int)strtol(input, NULL, 10));
						}
						catch (OverflowException e) {
							e.Print();
							return is;
						}	
					}
					index = 0;

					if (ch == '}')
						break;
				} else {
					input[index++] = ch;
				}
			}
		break;
		}
	}

	return is;
}

int main(int argc, char *argv[])
{
	Set<int>  nums(10);
	Set<Str>  strings(10);
	cout << "Exercise 11.1 \n";
	try {
		nums.Insert(1);
		nums.Insert(2);
		nums.Insert(3);
		nums.Insert(4);
		nums.Insert(4);
		nums.Insert(4);
	}
	catch (OverflowException e) {
		e.Print();
	}

	strings.Insert("String1");
	strings.Insert("String2");
	strings.Insert("String3");
	strings.Insert("String4");
	strings.Insert("String4");
	strings.Insert("String4");
	strings.Insert("String4");
	
	cout << nums << endl;
	cout << strings << endl;

	cout << "Please enter elements in set notation : \n";
	cin >> nums;
	
	cout << nums << endl;
	
	/* a pretty version or print */
	PrintPretty(nums);
	
	return 0;
}
