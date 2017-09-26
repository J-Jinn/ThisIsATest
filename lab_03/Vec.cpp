/* Vec.cpp defines the methods for Vec, a simple vector class.
 * Student Name: Joseph Jinn
 * Date: 9/26/17
 * Begun by: Joel C. Adams, for CS 112 at Calvin College.
 * Lab03 - Vec.
 */

#include "Vec.h"
#include <stdexcept>
#include <ostream>
#include <istream>
#include <cstdlib>
using namespace std;

/*
 * Default constructor.
 */

Vec::Vec() {
	mySize = 0;
	myArray = NULL;
}

/*
 * Explicit constructor.
 *
 * @param: size - unsigned variable.
 *
 * Precondition: None.
 * Postcondition: mySize is set to size. myArray is instantiated
 * as an array of capacity size.
 */

Vec::Vec(unsigned size) {
	mySize = size;

	if (size == 0) {
		myArray = NULL;
		return;
	}

	myArray = new double[size];

	for (unsigned i = 0; i < mySize; i++) {
		myArray[i] = 0;
	}
}

/*
 * Copy constructor.
 *
 * @param: original - Vec class reference variable.
 *
 * Precondition: None.
 * Postcondition: Copies the dynamically allocated memory of the original
 * array to a new array.
 */

Vec::Vec(const Vec& original) {

	mySize = original.mySize;

	if (mySize == 0) {
		myArray = NULL;
		return;
	}

	myArray = new double[mySize];

	for (unsigned i = 0; i < mySize; i++) {
		myArray[i] = original.myArray[i];
	}
}

/*
 * Destructor.
 *
 * Preconditon: None.
 * Postcondition: Returns dynamically allocated memory back to the heap.
 * Sets mySize to 0 and myArray to NULL.
 */

Vec::~Vec() {

	delete[] myArray;
	myArray = NULL;
	mySize = 0;
}

/*
 * Assignment operation function.
 *
 * @return: this - Vec class reference object.
 *
 * Precondition: Not an self-assignment operation.
 * Postcondition: Copies the values of the original array to the new array.
 * Overwrites previous values of the new array.
 */

Vec& Vec::operator=(const Vec& original) {

	//Check for self-assignment.
	if (this->myArray == original.myArray) {
		cout << "Self-assignment. Aborting." << flush;
		return *this;
	}

	//Check for null array.
	if (original.myArray == NULL) {
		this->mySize = 0;
		this->myArray = NULL;
		return *this;
	}

	this->mySize = original.mySize;
	this->myArray = new double[mySize];

	//Copy values of members of the array.
	for (unsigned i = 0; i < this->mySize; i++) {
		this->myArray[i] = original.myArray[i];
	}

	return *this;
}

/*
 * Getter method. Retrieves size of the Vec class object.
 *
 * @return: mySize - unsigned variable.
 *
 * Precondition: None.
 * Postcondition: Returns the size of the array.
 */

unsigned Vec::getSize() const {
	return mySize;
}

/*
 * Setter method. Sets the value of an Item in the Vec class
 * object.
 *
 * Precondition: None.
 * Postcondition: Item at index [i] is set to the value specified
 * by the argument "it".
 */

void Vec::setItem(unsigned index, const Item& it) {

	if (mySize == 0) {
		cout << "Empty array. Aborting." << flush;
		throw range_error("Vec(index, it) - array size must be positive.");
	}
	if (index >= mySize) {
		cout << "Exceeded array bounds. Aborting." << flush;
		throw range_error("Vec(index, it) - array bounds exceeded.");
	}

	for (unsigned i = 0; i < mySize; i++) {
		if (i == index) {
			myArray[i] = it;
			return;
		}
	}
}

/*
 * Getter method. Retrieves the value of a member of the Vec array at
 * index [i].
 *
 * @return: value - typedef double Item variable. Alias.
 *
 * Precondition: None.
 * Postcondition: The value of the Item at index [i] is returned.
 */

Item Vec::getItem(unsigned index) const {
	Item value;

	if (mySize == 0) {
		cout << "Empty array. Aborting." << flush;
		throw range_error("Vec(index, it) - array size must be positive.");
	}
	if (index >= mySize) {
		cout << "Exceeded array bounds. Aborting." << flush;
		throw range_error("Vec(index, it) - array bounds exceeded.");
	}

	for (unsigned i = 0; i < mySize; i++) {
		if (i == index) {
			value = myArray[i];
		}
	}

	return value;
}

/*
 * Setter method. Sets the size of the array in Vec.
 *
 * @param: newSize - unsigned variable.
 *
 * Precondition: None
 * Postcondition: The size of the Vec array is changed to the value
 * specified by the argument "newSize".
 */

void Vec::setSize(unsigned newSize) {

	//Condition 0
	if (newSize == 0) {
		cout << "Setting to empty array." << flush;
		delete[] myArray;
		myArray = NULL;
		mySize = 0;
		return;
	}
	//Condition 1
	if (mySize == 0) {
		cout << "Old size is 0. Default values set to zero." << flush;
		delete[] myArray;
		myArray = NULL;
		mySize = newSize;
		myArray = new double[mySize];

		for (unsigned i = 0; i < mySize; i++) {
			myArray[i] = 0;
			//cout << myArray[i] << endl;
		}
		return;
	}
	//Condition 2
	if (newSize > mySize) {
		unsigned oldSize = mySize;
		mySize = newSize;
		Item* newArray;
		newArray = new double[mySize];

		for (unsigned i = 0; i < oldSize; i++) {
			newArray[i] = myArray[i];
			//cout << myArray[i] << endl;
		}
		for (unsigned i = oldSize; i < mySize; i++) {
			newArray[i] = 0;
		}

		delete[] myArray;
		myArray = NULL;
		myArray = newArray;
		return;
	}
	//Condition 3
	if (newSize < mySize) {
		mySize = newSize;
		Item* newArray;
		newArray = new double[mySize];

		for (unsigned i = 0; i < mySize; i++) {
			newArray[i] = myArray[i];
		}
		delete[] myArray;
		myArray = NULL;
		myArray = newArray;
		return;
	}
}

/*
 * Comparison operation function.
 *
 * @param: v2 - Vec class reference object.
 * @return: compare - bool variable.
 *
 * Precondition: None.
 * Postcondition: Returns true if both Vec class objects are the same.
 * Returns false otherwise.
 */

bool Vec::operator==(const Vec& v2) {

	//Condition 0
	if (mySize != v2.mySize) {
		return false;
	}
	//Condition 1
	for (unsigned i = 0; i < mySize; i++) {
		if (myArray[i] != v2.myArray[i]) {
			return false;
		}
	}
	return true;
}

/*
 * Method to write to output.
 *
 * @param: out - ostream reference variable.
 *
 * Precondition: Output source exists.
 * Postcondition: Writes values of members of a Vec class object
 * to output.
 */

void Vec::writeTo(ostream& out) const {

	//out << mySize << '\n';

	for (unsigned i = 0; i < mySize; i++) {
		out << myArray[i] << '\n';
	}
}

/*
 * Method to parse from input.
 *
 * @param: in - istream reference variable.
 *
 * Precondition: Input source exists.
 * Postcondition: Parses values of members of a Vec class object
 * to input.
 */

void Vec::readFrom(istream& in) {

	string size;
	string value;
	getline(in, size);
	mySize = atoi(size.c_str());
	myArray = new double[mySize];

	for(unsigned i = 0; i < mySize; i++)
	{
		getline(in, value);
		myArray[i] = atof(value.c_str());

	}
  }
