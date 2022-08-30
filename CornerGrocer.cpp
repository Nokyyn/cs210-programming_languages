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
	PyObject* my_module = PyImport_ImportModule("CornerGrocerPy");
	PyErr_Print();
	PyObject* my_function = PyObject_GetAttrString(my_module, procname);
	PyObject* my_result = PyObject_CallObject(my_function, NULL);
	Py_Finalize();

	delete[] procname;
}

/*
Description:
	To call this function, pass the name of the Python function you wish to call and the string parameter you want to send
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
	pName = PyUnicode_FromString((char*)"CornerGrocerPy");
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
	pName = PyUnicode_FromString((char*)"CornerGrocerPy");
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

// open and read frequency.dat and print a histogram of all item sales
void PrintHistogram() {
	ifstream inFS;
	string itemName = "";
	int itemCount = 0;
	int i = 0;

	inFS.open("frequency.dat");
	if (!inFS.is_open()) {  // if file fails to open, return
		cout << "Could not open file" << endl;
		return;
	}

	inFS >> itemName;
	inFS >> itemCount;
	while (!inFS.fail()) {
		cout << itemName << ": ";
		for (i = 0; i < itemCount; ++i) {
			cout << '*';
		}
		cout << endl;
		inFS >> itemName;
		inFS >> itemCount;
	}
	inFS.close();
}

void DisplayMenu() {  // clears screen and displays main menu
	system("CLS");

	cout << "========================================" << endl;
	cout << "           The Corner Grocer            " << endl;
	cout << "========================================" << endl << endl;
	cout << "           Make a selection:            " << endl;
	cout << "----------------------------------------" << endl;
	cout << "1: Print All Daily Item Sales" << endl;
	cout << "2: Search for Item Sales" << endl;
	cout << "3: Display Sales Histogram" << endl;
	cout << "4: Exit" << endl << endl;
}


void main()  // main method begins program execution
{
	bool isRunning = true;
	int userSelect = 0;
	string itemSearch = "";

	CallProcedure("WriteSalesData");  // write to frequency.dat once per program execution, rather than in loop

	while (isRunning) {
		DisplayMenu();
		cin >> userSelect;
		switch (userSelect) {
		case 1:  // option 1: Display daily sales numbers
			system("CLS");
			cout << "========================================" << endl;
			cout << "           The Corner Grocer            " << endl;
			cout << "========================================" << endl << endl;
			cout << "               Daily Sales              " << endl;
			cout << "----------------------------------------" << endl;
			CallProcedure("PrintDailySales");
			cout << endl << endl;
			system("PAUSE");
			break;
		case 2:  // option 2: display sales numbers for a specific, user entered item
			cout << "Search for: ";
			cin >> itemSearch;
			system("CLS");
			cout << "========================================" << endl;
			cout << "           The Corner Grocer            " << endl;
			cout << "========================================" << endl << endl;
			cout << "Today's sales of " << itemSearch << ": " << callIntFunc("GetItemSales", itemSearch) << endl;
			cout << endl << endl;
			system("PAUSE");
			break;
		case 3:  // option 3: print a historgram of the total item sales for the day
			system("CLS");
			cout << "========================================" << endl;
			cout << "           The Corner Grocer            " << endl;
			cout << "========================================" << endl << endl;
			cout << "         Daily Sales Histogram          " << endl;
			cout << "----------------------------------------" << endl;
			PrintHistogram();
			cout << endl << endl;
			system("PAUSE");
			break;
		case 4:  // option 4: exit
			isRunning = false;
			break;
		default:  // default option: return to the beginning of execution
			continue;
		}
	}
}