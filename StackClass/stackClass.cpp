////////////////////////////////////////////////////////////////////////////////////////////////////////////
//  This program randomly generates data and puts it into a binary file as well as implement a stack. The
//  data will be read in from the file and pushed onto the stack.
//
//  Christy Mims
//
//  07/14/2019
//
/////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include<iostream>
#include<fstream>
#include<ctime>


using namespace std;



struct node
{
	// stores the data
	int number;

	// location of the adjacent node. In a stack the top node(last node) is looked at and the others are
	// in front of it
	node *behind;
};

class stack
{
	// private class members to the stack
private:

	// pointer to keep track of the front
	node *top;
	// pointer to insert at the back
	node *bottom;

public:

	// Default constructor with built in override tht sets the front and back pointers to NULL
	stack()
	{
		top = NULL;
		bottom = NULL;

		// notifies console that stack has been created
		cout << endl << "Stack object has been created" << endl;
	}

	// Destructor
	~stack()
	{
		// notifies user that the stack has been deleted from memory
		cout << endl << "Stack Object Deleted" << endl;
	}

	// class member to put data into the stack
	int putIntoStack(int data)
	{
		//create a node to put into stack
		node *temp = new node;

		// check to see if node got created
		if (temp == NULL)
		{
			cout << endl << "Fatal error, could not create node." << endl << endl;
			system("PAUSE");
			return (1);
		}



		// pushes the new node onto the top of the stack
		temp->number = data;
		temp->behind = top;
		top = temp;

		//cout << temp->behind << endl;
		//cout << top << endl;

		
	}

	// class member function to let us peek at top of stack
	int peekTop()
	{
		if (top != NULL)
		{
			return top->number;
		}
		else
		{
			cout << endl << "Nothing to peek at!" << endl;
			return NULL;
		}
	}

	// class member function that gets the item from the front of the stack
	int getTop()
	{
		if (top != NULL)
		{
			// stores data currently at the top of the stack
			int Data = top->number;

			// create a temp node and set it equal to top so we can traverse the list
			// and delete the old top
			struct node *temp = top;


			// if it is not last node 
			if (top != bottom)
			{
				// moves the node pointer to the node in front of the last
				top = top->behind;

				// deletes the temp node that marks the last node in the stack
				delete temp;

				// returns the data from the old back node
				return Data;
			}



			// last node in list
			else
			{
				// deletes temp node
				delete temp;

				// since no more nodes in list we can reset pointers to NULL
				top = NULL;
				bottom = NULL;

				// reutrns the last piece of data
				return Data;

			}
		}

		// if here there should not be anything in stack
		else
		{
			cout << endl << "Nothing in stack to get!" << endl;
			return NULL;
		}
	}

	void viewStack()
	{
		// message to console for demonstration purpose only
		// notifies the user that entire stack is going to be displayed
		cout << endl << "View the items in the stack: " << endl << endl;

		// counter for the formatting to console and data counting
		int counter = 1;

		// loop while there is data in the stack
		while (top != NULL)
		{
			// call the member function to get the top of the stack data and write it to console
			// tab is added for formatting
			cout << getTop() << "\t";

			// formats the console with 10 values per line
			if (counter % 10 == 0)
			{
				cout << endl;
			}

			// increment the counter
			counter = counter + 1;
		}

		// the stack has been emptied. Report to console the number of items that was in stack.
		// the counter was initialized to one for correct formatting, 1 is subtracted to get data count.
		cout << endl << endl << "Total items in stack was " << counter - 1 << endl << endl;
	}

};


int GetSize(int);
int CreateDataFile(int);
int DoWork(int);

int main(int argc, char *argv[])
{
	// check to see if correct and valid paramaters were passed in
	if (argc == 2)
	{
		//  variable to hold the size of the data. Created here so it is updated as 
		// needed and the functions that will need it have access
		int size = atoi(argv[1]);

		// check to see if a valid number got passed in
		if (!size)
		{

			// output to let user know valid quantity was not passed in
			cout << "Not a valid quantity." << endl;

			// calls the getSize function to get valid size as well as catch the returned value
			size = GetSize(size);
		}

		// calls DoWork Function
		DoWork(size);
	}

	else
	{
		// variable to hold size of list to be generated
		int size = 0;
		
		// call the GetSize function and catch the returned value in size
		size = GetSize(size);

		// calls the DoWork function
		DoWork(size);
	}

	// pauses the output window for debugging purposes
	system("PAUSE");
	return(0);
}

int GetSize(int size)
{
	// prompt user for size of list to be generated

	while (size < 1 || size > 100)
	{
		cout << endl;
		cout << "How much data do you want to generate between 1 and 100?" << endl;
		cin >> size;

		// check to see if valid number was entered
		if (cin.fail() || size < 1 || size > 100)
		{
			// clears cin and what is in buffer
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');

			// notifies user that invalid option was entered
			cout << endl << "Invalid option.";
		}

		// formatting
		cout << endl << endl;
	}

	// return value that user entered
	return(size);
}

int CreateDataFile(int size)
{
	// create outstream writer and name it write binary
	ofstream WriteBinary;

	// open the WriteBinary file or create it if does not already exist
	WriteBinary.open("numbers.bin", ios::out | ios::binary);

	// check to see if file opened
	if (!WriteBinary)
	{
		cout << "Could not open binary file for writing." << endl << endl;
		system("PAUSE");
		return(1);
	}

	// lets user know writing to file has begun
	cout << "Writing file: numbers.bin" << endl << endl;

	// 'seeding' random number generator with the time from the computer
	srand(int(time(NULL)));

	// create variable to store randomly generated int
	int Data = 0;

	// counter variable to use to format the console
	int counter = 1;

	// for loop to get the required amount of data to write to the file
	for (int i = 0; i < size; i++)
	{
		// generates a random number and stores it in Data
		// mod by 100 to get smaller numbers
		Data = rand() % 100;

		// write the randomly generated data to binary file
		WriteBinary.write(reinterpret_cast<const char *>(&Data), sizeof(int));

		// writes data to console for user to see and formats the output
		// so 10 values are printed on each line and are separated by tab spacing
		cout << Data << "\t";
		if (counter % 10 == 0)
		{
			cout << endl;
			counter = 0;
		}

		counter = counter + 1;
	}

	// closes the file the data was wrote to
	WriteBinary.close();

	// notify the user that the file was successfully written to
	cout << endl << endl << "The binary data file was created successfully." << endl;

}

int DoWork(int size)
{
	// calls the CreateDataFile
	CreateDataFile(size);

	// creates stack to hold the data
	stack MyStack;

	// create stream reader to read the data from the binary file
	ifstream readBinary;

	// stream reader to open file that contains the data from the binary file
	readBinary.open("numbers.bin", ios::in | ios::binary);

	// check to see if file was opened for reading
	if (!readBinary)
	{
		cout << "Could not open binary file for reading." << endl << endl;
		system("PAUSE");
		return(1);
	}

	// variable to hold the data that is being read in
	int Data = 0;

	// while loop to read data while it is present
	while (readBinary)
	{
		// reads in single piece of data at a time
		readBinary.read((char*)&Data, sizeof(int));

		// check to see if we are at end of file and if so break out
		if (readBinary.eof()) break;

		// if here then a piece of data needs to be put into the stack
		// calls the function that inserts the data in the order it was read 
		MyStack.putIntoStack(Data);
	}

	// function call to see everything in stack
	MyStack.viewStack();


	// peek to see if stack is empty
	if (MyStack.peekTop() != NULL)
	{
		cout << MyStack.peekTop() << endl;
	}

	// Tries to get data from empty stack and have to catch or will lose forever
	int data = MyStack.getTop();

	// if data gets returned
	if (data != NULL)
	{
		cout << data << endl;
	}

}