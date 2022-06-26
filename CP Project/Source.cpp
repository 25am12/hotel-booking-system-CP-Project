#include<iostream>																		//standard input output library
#include<string>																		//standard string library
#include<fstream>																		//library for file handling
#include<Windows.h>																		//library for beep, sleep and color function

using namespace std;

struct hotelStr																			//structure for saving hotels info
{
	int code;
	string city;
	string name;
	string description;
	int priceForOne;
	int priceForMore;
	int maxPeople;
};
int numOfHotels=0;																		//total num of hotels

struct cutomerStr																		//sturcture for saving customer info
{
	int code;
	string name;
	string dateCheckIn;
	int days;
	int numOfPeople;
	int hotelCode;
	int roomCode;
	float bill;

};
int numOfCustomers = 0;																	//total num of customers

struct cabStr																			//structure for saving cab rides info
{
	int code;
	int customerCode;
	int hotelCode;
	bool fromHotel;
	string toFro;
};
int numOfCabs = 0;																		//total num of cabs

struct roomStr {
	int code;
	int floor;
	bool status;
	int hotelCode;
};
int numOfRooms = 0;																		//total num of rooms

void intro();																			//Printing Intro for BookMyPlace
void customerLoading(cutomerStr customers[100]);										//Function for loading customer data from file
void hotelLoading(hotelStr hotels[100]);												//Function for loading hotel data from file
void roomLoading(roomStr rooms[100]);													//Function for loading room data from file
void cabLoading(cabStr cabs[100]);														//Function for loading cab rides data from file
void addhotel(hotelStr hotels[100]);													//Function for adding a new hotel
void viewHotel(hotelStr hotels[100]);													//Function for displaying hotels info
void viewRooms(roomStr rooms[100], int hotelCode);														//Function for displaying rooms info
void bookHotel(cutomerStr customers[100], hotelStr hotels[100], roomStr rooms[100]);						//Function for booking a hotel
void viewCustomer(cutomerStr customers[100], hotelStr hotels[100]);						//Function for viweing customer info
void cabCalling(cutomerStr customers[100], hotelStr hotels[100], cabStr cabs[100]);		//Function for calling a cab
void writeRooms(roomStr rooms[100]);
int main()
{
	intro();																			//Calling Intro Function To Print BMP

	system("cls");
	
	system("Color B5");																	//Purple Text & Aqua Background
	int select = 0;
	hotelStr hotels[100];																//Array for Saving Hotel Data 
	cutomerStr customer[100];															//Array for Saving Customer Data
	cabStr cabs[100];																	//Array for Saving Cabs Data
	roomStr rooms[100];																	//Array for Saving Rooms Data

	hotelLoading(hotels);																//Loading Hotels Data into Array 
	customerLoading(customer);															//Loading Customers Data into Array
	cabLoading(cabs);																	//Loading Cabs Data into Arrays
	roomLoading(rooms);																	//Loading Rooms Data into Arrays

	while (select != 5)
	{
		cout << "Welcome to Book My Place\n";
		cout << "Select \n 1:Book Hotel\n 2:View Booking Details\n 3:Add Hotel\n 4:Call A Cab\n 5:Exit\n";
		cin >> select;
		switch (select)																		//Switch for Performing desired action 
		{

		case 1:																			//For Booking Hotel
			system("Color 47");
			bookHotel(customer, hotels,rooms);
			break;
		case 2:																			//For Viewing Booking Details
			system("Color 34");
			viewCustomer(customer, hotels);
			break;
		case 3:																			//For Adding Hotel
			system("Color 04");
			addhotel(hotels);
			break;
		case 4:																			//For Calling a Cab
			system("Color 60");
			cabCalling(customer, hotels, cabs);
			break;
		case 5:
			system("Color 60");
			cout << "Thanks For Visiting Book My Place" << endl;
			break;
		default:																		//If user makes an Invalid Entry
			system("Color 4F");
			system("cls");
			cout << "Invalid Entry\n";
			break;
		}

		cout << endl << endl << "For Any Queries Our Help Line 123-BOOKMYPLACE\n" << endl << endl;
		system("pause");
		system("cls");
	}
}

void hotelLoading(hotelStr hotels[100])													//Function for loading hotel data from file
{
	ifstream hotelRead("hotel.txt");													//Opening File with Hotel Data in Read Mode
	while (hotelRead.good())															//Reading Data from Hotel File
	{

		hotelRead >> hotels[numOfHotels].code;
		getline(hotelRead, hotels[numOfHotels].city);
		getline(hotelRead, hotels[numOfHotels].city);
		getline(hotelRead, hotels[numOfHotels].name);
		getline(hotelRead, hotels[numOfHotels].description);
		hotelRead >> hotels[numOfHotels].priceForOne;
		hotelRead >> hotels[numOfHotels].priceForMore;
		hotelRead >> hotels[numOfHotels].maxPeople;
		numOfHotels++; 
	}
	numOfHotels--;
	hotelRead.close();																	//Closing Hotel File

}

void addhotel(hotelStr hotels[100])														//Function for adding a new hotel
{
	int cityNum;
	system("cls");																		//Getting Hotel Info From User
	hotels[numOfHotels].code = numOfHotels;
	cout << "Select city for your hotel." << endl << "1)ISL" << endl << "2)LHR" << endl << "3)KHI" << endl;
	cin >> cityNum;

	switch (cityNum)
	{
	case 1:
		hotels[numOfHotels].city = "ISL";
		break;
	case 2:
		hotels[numOfHotels].city = "LHR";
		break;
	case 3:
		hotels[numOfHotels].city = "KHI";
		break;
	default:
		cout << "Invaild Entry\n";
		system("pause");
		exit(0);
		break;
	}

	cout << "Enter the name of your hotel:";
	cin.ignore();
	getline(cin, hotels[numOfHotels].name);
	cout << "Enter a description for your Hotel:";
	getline(cin, hotels[numOfHotels].description);
	cout << "Enter price for one:";
	cin >> hotels[numOfHotels].priceForOne;
	cout << "Enter Increment for people after one:";
	cin >> hotels[numOfHotels].priceForMore;
	cout << "Enter Maximum number of people:";
	cin >> hotels[numOfHotels].maxPeople;

	system("cls");

	cout << "Code: " << hotels[numOfHotels].code << endl								//Printing Your Hotel Info
		<< "Name: " << hotels[numOfHotels].name << endl
		<< "Description: " << hotels[numOfHotels].description << endl
		<< "Price for One: " << hotels[numOfHotels].priceForOne << endl
		<< "Increment for 2 or more: " << hotels[numOfHotels].priceForMore << endl
		<< "Maximum Number of People: " << hotels[numOfHotels].maxPeople << endl;

	ofstream hotelWrite("hotel.txt",ios::app);											//Opening File in Write Append Mood to write at the end of File 
	hotelWrite << hotels[numOfHotels].code << endl;
	hotelWrite << hotels[numOfHotels].city << endl;
	hotelWrite << hotels[numOfHotels].name << endl;
	hotelWrite << hotels[numOfHotels].description << endl;
	hotelWrite << hotels[numOfHotels].priceForOne << endl;
	hotelWrite << hotels[numOfHotels].priceForMore << endl;
	hotelWrite << hotels[numOfHotels].maxPeople << endl;
	hotelWrite.close();																	//Closing Hotel File

}

void customerLoading(cutomerStr customers[100])											//Function for loading customer data from file
{
	ifstream customerRead("customer.txt");												//Opening File with Customer Data in Read Mode
	while (customerRead.good())															//Reading Data from Customer File
	{
		customerRead >> customers[numOfCustomers].code;
		getline(customerRead, customers[numOfCustomers].name);
		getline(customerRead, customers[numOfCustomers].name);
		getline(customerRead, customers[numOfCustomers].dateCheckIn);
		customerRead >> customers[numOfCustomers].days;
		customerRead >> customers[numOfCustomers].numOfPeople;
		customerRead >> customers[numOfCustomers].hotelCode;
		customerRead >> customers[numOfCustomers].bill;
		customerRead >> customers[numOfCustomers].roomCode;
		numOfCustomers++;
	}
	customerRead.close();																//Closing Customer File
	numOfCustomers--;
}

void cabLoading(cabStr cabs[100])														//Function for loading cab rides data from file
{
	ifstream cabRead("cab.txt");														//Opening File with Cab Ride Data in Read Mode
	while (cabRead.good())																//Reading Data from Cab File
	{
		cabRead >> cabs[numOfCabs].code;
		cabRead >> cabs[numOfCabs].customerCode;
		cabRead >> cabs[numOfCabs].hotelCode;
		cabRead >> cabs[numOfCabs].fromHotel;
		getline(cabRead, cabs[numOfCabs].toFro);
		getline(cabRead, cabs[numOfCabs].toFro);
		numOfCabs++;
	}
	cabRead.close();																	//Closing Cab File
}

void viewHotel(hotelStr hotels[100])													//Function For Displaying Hotels
{
	int sort;
	int cityNum;
	string city;

	system("cls");
	cout << "Select city for your hotel." << endl << "1)ISL" << endl << "2)LHR" << endl << "3)KHI" << endl;
	cin >> cityNum;

	switch (cityNum)
	{
	case 1:
		city = "ISL";
		break;
	case 2:
		city = "LHR";
		break;
	case 3:
		city = "KHI";
		break;
	default:
		cout << "Invaild Entry\n";
		system("pause");
		exit(0);
		break;
	}

	system("cls");
	cout << "Sort by: \n 1:Default \n 2:Price Low to High \n";
	cin >> sort;
	system("cls");

	if (sort == 1)																		//IF for Default Sorting
	{
		for (int i = 0; i < numOfHotels; i++)											//Printing Hotels (Default)
		{
			if (hotels[i].city == city)
			{
				cout << "Code: " << hotels[i].code << endl
					<< "Name: " << hotels[i].name << endl
					<< "Description: " << hotels[i].description << endl
					<< "Price for One: " << hotels[i].priceForOne << endl
					<< "Increment for 2 or more: " << hotels[i].priceForMore << endl
					<< "Maximum Number of People: " << hotels[i].maxPeople << endl;
				cout << endl << endl;
			}

		}
	}
	else if (sort == 2)																	//IF for Sorting by Price(High To Low)
	{
		int prices[100];
		for (int i = 0; i < 100; i++)													//Sorting Hotels Acc. To Price
		{
			prices[i] = hotels[i].priceForOne;
		}
		for (int i = 0; i < numOfHotels; i++) {
			for (int j = i + 1; j < numOfHotels; j++)
			{
				if (prices[j] < prices[i]) {
					int temp = prices[i];
					prices[i] = prices[j];
					prices[j] = temp;


					temp = hotels[i].code;
					hotels[i].code = hotels[j].code;
					hotels[j].code = temp;

					string tempp = hotels[i].city;
					hotels[i].city = hotels[j].city;
					hotels[j].city = tempp;

					tempp = hotels[i].name;
					hotels[i].name = hotels[j].name;
					hotels[j].name = tempp;

					tempp = hotels[i].description;
					hotels[i].description = hotels[j].description;
					hotels[j].description = tempp;

					temp = hotels[i].priceForOne;
					hotels[i].priceForOne = hotels[j].priceForOne;
					hotels[j].priceForOne = temp;

					temp = hotels[i].priceForMore;
					hotels[i].priceForMore = hotels[j].priceForMore;
					hotels[j].priceForMore = temp;

					temp = hotels[i].maxPeople;
					hotels[i].maxPeople = hotels[j].maxPeople;
					hotels[j].maxPeople = temp;
				}
			}
		}

		for (int i = 0; i < numOfHotels; i++)											//Printing Hotels (Price)
		{
			if (hotels[i].city == city)
			{
				cout << "Code: " << hotels[i].code << endl
					<< "Name: " << hotels[i].name << endl
					<< "Description: " << hotels[i].description << endl
					<< "Price for One: " << hotels[i].priceForOne << endl
					<< "Increment for 2 or more: " << hotels[i].priceForMore << endl
					<< "Maximum Number of People: " << hotels[i].maxPeople << endl;
				cout << endl << endl;
			}

		}

		for (int i = 0; i < numOfHotels; i++)											//Sorting back to Default So Our Data Base Stays Accurate
		{
			for (int j = i + 1; j < numOfHotels; j++)
			{
				if (hotels[j].code < hotels[i].code)
				{
					int temp = prices[i];
					prices[i] = prices[j];
					prices[j] = temp;


					temp = hotels[i].code;
					hotels[i].code = hotels[j].code;
					hotels[j].code = temp;

					string tempp = hotels[i].city;
					hotels[i].city = hotels[j].city;
					hotels[j].city = tempp;

					tempp = hotels[i].name;
					hotels[i].name = hotels[j].name;
					hotels[j].name = tempp;

					tempp = hotels[i].description;
					hotels[i].description = hotels[j].description;
					hotels[j].description = tempp;

					temp = hotels[i].priceForOne;
					hotels[i].priceForOne = hotels[j].priceForOne;
					hotels[j].priceForOne = temp;

					temp = hotels[i].priceForMore;
					hotels[i].priceForMore = hotels[j].priceForMore;
					hotels[j].priceForMore = temp;

					temp = hotels[i].maxPeople;
					hotels[i].maxPeople = hotels[j].maxPeople;
					hotels[j].maxPeople = temp;
				}
			}
		}


	}
	else
	{
		for (int i = 0; i < numOfHotels; i++)											//Printing Hotels (Default)
		{
			if (hotels[i].city == city)
			{
				cout << "Code: " << hotels[i].code << endl
				<< "Name: " << hotels[i].name << endl
				<< "Description: " << hotels[i].description << endl
				<< "Price for One: " << hotels[i].priceForOne << endl
				<< "Increment for 2 or more: " << hotels[i].priceForMore << endl
				<< "Maximum Number of People: " << hotels[i].maxPeople << endl;
				cout << endl << endl;
			}

		}
	}

}

void bookHotel(cutomerStr customers[100], hotelStr hotels[100],roomStr rooms[100])							//Function for booking a hotel
{
	viewHotel(hotels);																	//Calling Function To Print Hotels Info

	customers[numOfCustomers].code = numOfCustomers;									//Getting Customer Data From User
	cout << "Enter Your Name: ";
	getline(cin, customers[numOfCustomers].name);
	getline(cin, customers[numOfCustomers].name);
	cout << "Enter Date CheckIn: ";
	getline(cin, customers[numOfCustomers].dateCheckIn);
	cout << "Enter Number of Days You'll Stay: ";
	cin >> customers[numOfCustomers].days;
	cout << "Enter Code For Hotel You Want To Book: ";
	cin >> customers[numOfCustomers].hotelCode;
	viewRooms(rooms, customers[numOfCustomers].hotelCode);
	cout << "Enter Code For Room You Want To Book: ";
	cin >> customers[numOfCustomers].roomCode;
	cout << "Enter Number of People (Less Than Equal To Maximum People): ";
	do
	{
		cin >> customers[numOfCustomers].numOfPeople;
	} while (customers[numOfCustomers].numOfPeople > hotels[customers[numOfCustomers].hotelCode].maxPeople);

	customers[numOfCustomers].bill = (hotels[customers[numOfCustomers].hotelCode].priceForOne + (hotels[customers[numOfCustomers].hotelCode].priceForMore * (customers[numOfCustomers].numOfPeople - 1)))* customers[numOfCustomers].days;
	
	system("cls");
	
	cout << "Your Customer Code: " << customers[numOfCustomers].code << endl;			//Printing Customer Reciept
	cout << "Name: " << customers[numOfCustomers].name << endl;
	cout << "Date CheckIn: " << customers[numOfCustomers].dateCheckIn << endl;
	cout << "Number Of Days: " << customers[numOfCustomers].days << endl;
	cout << "Code For Your Hotel: " << customers[numOfCustomers].hotelCode << endl;
	cout << "Name of Your Hotel: " << hotels[customers[numOfCustomers].hotelCode].name << endl;
	cout << "Number Of People: " << customers[numOfCustomers].numOfPeople << endl;
	cout << "Amount To Be Paid: " << customers[numOfCustomers].bill << endl;
	cout<< "Room Code: "<< customers[numOfCustomers].roomCode << endl;
	rooms[customers[numOfCustomers].roomCode].status = 1;

	writeRooms(rooms);
	ofstream customerWrite("customer.txt", ios::app);									//Opening File in Write Append Mood to write at the end of File 
	customerWrite << customers[numOfCustomers].code << endl;
	customerWrite << customers[numOfCustomers].name << endl;
	customerWrite << customers[numOfCustomers].dateCheckIn << endl;
	customerWrite << customers[numOfCustomers].days << endl;
	customerWrite << customers[numOfCustomers].numOfPeople << endl;
	customerWrite << customers[numOfCustomers].hotelCode << endl;
	customerWrite << customers[numOfCustomers].bill << endl;
	customerWrite << customers[numOfCustomers].roomCode << endl;
	customerWrite.close();																//Closing Customer File

}

void viewCustomer(cutomerStr customers[100], hotelStr hotels[100])						//Function for viweing customer info
{

	int customCode;

	cout << "Enter Your Customer Code: ";
	do
	{
		cin >> customCode;
	} while (customCode >= numOfCustomers);

	system("cls");

	cout << "Your Customer Code: " << customers[customCode].code << endl;				//Printing Customer Details
	cout << "Name: " << customers[customCode].name << endl;
	cout << "Date CheckIn: " << customers[customCode].dateCheckIn << endl;
	cout << "Number Of Days: " << customers[customCode].days << endl;
	cout << "Code For Your Hotel: " << customers[customCode].hotelCode << endl;
	cout << "Name of Your Hotel: " << hotels[customers[customCode].hotelCode].name << endl;
	cout << "Number Of People: " << customers[customCode].numOfPeople << endl;
	cout << "Amount To Be Paid: " << customers[customCode].bill << endl;
}

void cabCalling(cutomerStr customers[100], hotelStr hotels[100], cabStr cabs[100])		//Function for calling a cab
{
	system("cls");

	cabs[numOfCabs].code = numOfCabs;													//Getting Cab Details From Customer
	cout << "Enter Your Customer Code: ";
	cin >> cabs[numOfCabs].customerCode;
	cabs[numOfCabs].hotelCode = customers[cabs[numOfCabs].customerCode].hotelCode;
	cout << "Press: \n1)If you want cab to Pick You Up From Hotel.\n2)If You Want Cab To Pick You Up From Somewhere.\n";
	cin >> cabs[numOfCabs].fromHotel;
	cout << "Enter Destination Or Starting Point Other Than Your Hotel: ";
	getline(cin, cabs[numOfCabs].toFro);
	getline(cin, cabs[numOfCabs].toFro);

	system("cls");
	cout << "Your Cab Will Be There In A While\n";

	ofstream cabWrite("cab.txt", ios::app);												//Opening File in Write Append Mood to write at the end of File 
	cabWrite << cabs[numOfCabs].code << endl;
	cabWrite << cabs[numOfCabs].customerCode << endl;
	cabWrite << cabs[numOfCabs].hotelCode << endl;
	cabWrite << cabs[numOfCabs].fromHotel << endl;
	cabWrite << cabs[numOfCabs].toFro << endl;
}

void roomLoading(roomStr rooms[100])													//Function for loading room data from file
{
	ifstream roomRead("room.txt");													//Opening File with Hotel Data in Read Mode
	while (roomRead.good())															//Reading Data from Hotel File
	{

		roomRead >> rooms[numOfRooms].code;
		roomRead >> rooms[numOfRooms].hotelCode;
		roomRead >> rooms[numOfRooms].floor;
		roomRead >> rooms[numOfRooms].status;
		numOfRooms++;
	}
	numOfHotels--;
	roomRead.close();
}
void intro()																			//Printing Intro for BookMyPlace
{
	system("cls");

	system("color 94");																	//background: light blue AND text: red 
	Beep(200, 500);																		//Beep 200 Hz and 500ms

	cout << "********\n";																//Printing B
	cout << "*       *\n";
	cout << "********\n";
	cout << "*       *\n";
	cout << "********\n";

	cout << endl;

	Sleep(500);																			//Delay for 500ms

	system("color 14");																	//background: blue AND text: red 
	Beep(300, 500);																		//Beep 300 Hz and 500ms

	cout << "**   **\n";																//Printing M
	cout << "* * * *\n";
	cout << "*  *  *\n";
	cout << "*     *\n";
	cout << "*     *\n";

	cout << endl;

	Sleep(500);																			//Delay for 500ms

	system("color 24");																	//background: green AND text: red 
	Beep(400, 500);																		//Beep 400 Hz and 500ms

	cout << "*****\n";																	//Printing P
	cout << "*    *\n";
	cout << "*****\n";
	cout << "*\n";
	cout << "*\n";

	cout << endl;

	Sleep(500);																			//Delay for 500ms

	system("color F4");																	//background: white AND text: red 
	Beep(500, 500);																		//Beep 500 Hz and 500ms

	Sleep(2000);																			//Delay for 2s
}

void viewRooms(roomStr rooms[100], int hotelCode)														//Function for displaying rooms info
{
	for (int i = 0; i < numOfRooms; i++)											//Printing Hotels (Default)
	{
		if (rooms[i].hotelCode == hotelCode && rooms[i].status==0)
		{
			cout << "ROOM: " << endl;
			cout << "Code: " << rooms[i].code << endl
				<< "Hotel Code: " << rooms[i].hotelCode << endl
				<< "Floor: " << rooms[i].floor << endl;
			cout << endl << endl;
		}

	}
}

void writeRooms(roomStr rooms[100])
{
	ofstream roomsWrite("rooms.txt");									//Opening File in Write Append Mood to write at the end of File 
	for (int i = 0; i <= numOfRooms; i++)
	{
		roomsWrite << rooms[i].code << endl;
		roomsWrite << rooms[i].hotelCode << endl;
		roomsWrite << rooms[i].floor << endl;
		roomsWrite << rooms[i].status << endl;
	}
	roomsWrite.close();
}

/* _________________________________________
|											|
|	Program  For Hotel Reservation Systey	|
|___________________________________________|
|	Written By:								|
|			  Ahmar Hafeez					|
|			  Abdur Rehman Muhammad			|
|			  Hammad Rao					|
|			  Shahzaib Ali					|
|___________________________________________*/