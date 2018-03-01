/*************************************************************************
* Title: Catching All Exceptions
* File: CIS278_Week9-17.26.cpp
* Author: James Eli
* Date: 2/13/2018
*
* Exercise 17.26 on page 782, Catching All Exceptions
* Write a program that demonstrates several exception types being caught 
* with the catch(...) exception handler.
*
* Notes:
*  (1) Compiled with MS Visual Studio 2017 Community (v141).
*
* Submitted in partial fulfillment of the requirements of PCC CIS-278.
*************************************************************************
* Change Log:
*   02/13/2018: Initial release. JME
*************************************************************************/
#include <iostream>  // cout/endl
#include <exception> // exception info
#include <typeinfo>  // typeid
#include <new>       // bad_alloc
#include <vector>

using namespace std;

// Define my exception.
class myException : public exception 
{
public:
	virtual const char* what() const throw()
	{
		return "My exception happened!";
	}
};

int main()
{
	cout << "Exception throw/catch demonstration.\n\n";

	// Terminate handler function, automatically called when the exception handling process is 
	// abandoned for some reason, i.e., when no catch handler is found for a thrown exception.
	set_terminate([](){cout << "\nterminateFunction called.\n"; exit(EXIT_FAILURE);});

	// Loop through example exceptions.
	for (int i = 0; i < 5; i++) {
		// Dispaly exception info.
		auto eWhat = [](const exception& e){ cout << " caught: " << typeid(e).name() << ", " << e.what();};

		try
		{
			switch(i) 
			{
			case 0:
				throw runtime_error("Runtime error happend!");
				break;
			case 1:
				throw logic_error("Logic error happened!");
				break;
			case 2:
				throw bad_alloc();
				break;
			case 3:
				throw myException();
				break;
			default:
				throw bad_cast();
				break;
			}
		}
		// Catch specific exceptions.
		catch (const myException& e)
		{
			cout << "myEception";
			eWhat(e);
		}
		catch (const bad_alloc& e)
		{
			cout << "bad_alloc";
			eWhat(e);
		}
		catch (const runtime_error& e)
		{
			cout << "runtime_error";
			eWhat(e);
		}
		catch (const logic_error& e)
		{
			cout << "logic_error";
			eWhat(e);
		}
		// All other exceptions caught/rethrown here.
		catch (...)
		{
			// Exception pointer.
			exception_ptr exp;

			exp = current_exception();
			cout << "catch all";
			try {
				if (exp)
					rethrow_exception(exp);
			}
			catch (const exception& e)
			{
				eWhat(e);
			}
		}

		cout << endl;
	}

	// Throw an uncaught exception to trigger terminate function.
	throw;

	return 0;
}

