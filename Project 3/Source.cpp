#include <Python.h>
#include <iostream>
#include <Windows.h>
#include <cmath>
#include <string>
#include <fstream>

using namespace std;

/*
Description:
	To call this function, simply pass the function name in Python that you wish to call.
Example:
	callProcedure("printsomething");
Output:
	Python will print on the screen: Hello from python!
Return:
	None
*/
void CallProcedure(string pName)
{
	char* procname = new char[pName.length() + 1];
	std::strcpy(procname, pName.c_str());

	Py_Initialize();
	PyObject* my_module = PyImport_ImportModule("PythonCode");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("PrintMe","Test");
Output:
	Python will print on the screen:
		You sent me: Test
Return:
	100 is returned to the C++
*/
int callIntFunc(string proc, string param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	char* paramval = new char[param.length() + 1];
	std::strcpy(paramval, param.c_str());


	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(z)", paramval);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;
	delete[] paramval;


	return _PyLong_AsInt(presult);
}

/*
Description:
	To call this function, pass the name of the Python functino you wish to call and the string parameter you want to send
Example:
	int x = callIntFunc("doublevalue",5);
Return:
	25 is returned to the C++
*/
int callIntFunc(string proc, int param)
{
	char* procname = new char[proc.length() + 1];
	std::strcpy(procname, proc.c_str());

	PyObject* pName, * pModule, * pDict, * pFunc, * pValue = nullptr, * presult = nullptr;
	// Initialize the Python Interpreter
	Py_Initialize();
	// Build the name object
	pName = PyUnicode_FromString((char*)"PythonCode");
	// Load the module object
	pModule = PyImport_Import(pName);
	// pDict is a borrowed reference 
	pDict = PyModule_GetDict(pModule);
	// pFunc is also a borrowed reference 
	pFunc = PyDict_GetItemString(pDict, procname);
	if (PyCallable_Check(pFunc))
	{
		pValue = Py_BuildValue("(i)", param);
		PyErr_Print();
		presult = PyObject_CallObject(pFunc, pValue);
		PyErr_Print();
	}
	else
	{
		PyErr_Print();
	}
	//printf("Result is %d\n", _PyLong_AsInt(presult));
	Py_DECREF(pValue);
	// Clean up
	Py_DECREF(pModule);
	Py_DECREF(pName);
	// Finish the Python Interpreter
	Py_Finalize();

	// clean 
	delete[] procname;

	return _PyLong_AsInt(presult);
}
//Display Menu
void DisplayMenu() {
	cout << "1 - Produce a list of all item purchased in a given day along";
	cout << "with the number of times each item was purchased.\n";
	cout << "2 - Produce a number representing how many times a specific";
	cout << "item was purchased in a given day.\n";
	cout << "3 - Produce a text-based histogram listing all items purchased";
	cout << "in a given day, along with a representation of the number of times each item was purchased.\n";
	cout << "4 - Exit Program \n";
}


void main()
{
	//declare variables
	int num1;
	string input1;
	string item;
	int freq;
	int i;
	string entry;
	bool validation;
	
	//do-while loop to loop while user num1 is != 4 which is ("exit")
	do {
		//Call display menu
		DisplayMenu();
		cout << endl;

		cout << "Enter your selection as a number 1, 2, 3, or 4.\n";
		cin >> num1;

		//While loop to validate num1 input.
		//if less than 1 or greater than 4 asks user to re-enter.
		while (num1 < 1 || num1 > 4) {
			cout << "Not a valid entry.\n";
			cout << "Please select 1, 2, 3, or 4.\n";
			cin >> num1;
		}
		//If-else statments to check and execute based on user entry.
		if (num1 == 1) {
			//Produce a list of all items in items.txt and their frequency
			//Provided by professor. Outputs Total Inventory followed by calling the determineInventory func from pythoncode.py
			cout << "TOTAL INVENTORY" << endl;
			CallProcedure("determineInventory");
			cout << endl;
		}
		else if (num1 == 2) {
			//cin string and ask user what item to search for.
			//search items.txt for string and return string and frequency.
			cout << "Please enter an item to search for: " << endl;
			cin >> input1;
			//take user input1 and change the character at location 0 to Uppercase to account for uservalidation in .txt file.
			input1[0] = toupper(input1[0]);
			//if statement to check if input is in txt document
			//calling ifstream and assigning it myfile variable.
			ifstream myfile;
			//setting boolean value to false before input validation in while loop.
			validation = false;
			//first while loop loop while validation isn't = to true.
			while (validation != true) {
				//calling the .open func with my class to open items.txt doc.
				//opened here to so that it will reopen every time we loop.
				myfile.open("items.txt");
				//nested-while loop using the getline func to store each line into the entry variable and read myfile line by line.
				while (getline(myfile, entry)) {
					//if statement calling the .find func on the entry variable to check if user input1 appears in .txt file.
					//Using string::npos to determine if there is or isn't a match.
					if (entry.find(input1) != std::string::npos) {
						//If there is a match validation bool set to true.
						validation = true;
						//break loop
						break;
					}
				}
				//if validation is true it means there is a match between user input and file data.
				if (validation) {
					cout << endl;
					//Primarly provided by prof. 
					//Outputting user input1 and calling determineFrequency func from pythoncode.py to verify frequency in file data.
					cout << input1 << " occurs " << callIntFunc("determineFrequency", input1) << " times." << endl;
					cout << endl;
				}
				else {
					//else to trigger if validation is false. Asks user to input a valid input.
					cout << "Please enter a valid input: " << endl;
					cin >> input1;
					cout << endl;
				}
				//closes the file.
				myfile.close();
			}
		}
		else if (num1 == 3) {
			//Produce a text based histogram for items in items.txt and frequency.
			//Essentially same as first part of if statment only instead of number use stars(*) or tilda(~) etc..
			//Using the CallProcedure func to call the output func from pythoncode.py
			CallProcedure("output");
			//calling the ifstream class and declaring myfile variable.
			ifstream myfile;
			//using the .open func to access the frequency.dat file created with CallProcedure("output").
			myfile.open("frequency.dat");
			//while loop to read through myfile assigning item and freq until end of file.
			while (myfile >> item >> freq) {
				//Output item followed by a space.
				cout << item << " ";
				//for-loop that iterates freq number of times and outputs a * for each loop.
				for (i = 0; i < freq; i++) {
					cout << '*';
				}
				cout << endl;	
			}
			cout << endl;

		}
		
		else if (num1 == 4) {
			//Exit program
			exit(0);
		}
	//end of do-while 
	} while (num1 != 4);

}