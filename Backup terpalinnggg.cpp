#include<iostream>
#include<string>
#include<fstream>
#include<cctype>
#include<cstring>
#include<ctime>
#include<sstream>
#include<iomanip>
#include<utility>
#include <limits>
#include<cstdlib>
#include <stdexcept>
#include<chrono>
#include<vector>
#include<algorithm>

#define MAX_ROOMS 100
#define MAX_CUSTOMERS 100

using namespace std;

//create a struct for customer information
struct Customer {
    int bookingNum;
    string custName;
    string custAddress;
    string custPhoneNum;
    string bookingStartFromDate;
    string bookingEndDate;
    int numberOfNights;
    double advancePay;
};

struct Room {
    string roomType;
    string bedType;
    string roomSize;
    int roomNum = -1;
    double roomRate = 0.0;
    bool isBooked = false;
    Customer customerInfo;
};
//create a vector to store existing room numbers
vector<int> existingRoomNumbers;
//Bool created to make sure the user is entering the correct input

bool isValidRoomType(char type){
return type == 'T' || type == 't' || type == 'G' || type == 'g' || type == 'W' || type == 'w';
}

bool isValidRoomSize(char size) {
return size == 'N' || size == 'n' || size == 'D' || size == 'd' || size == 'P' || size == 'p';
}

bool isValidBedType(char bed){
return bed == 'S' || bed == 's' || bed == 'Q' || bed == 'q' || bed == 'K' || bed == 'k';
}


// Room Management Functions
Room addRoomNumber();
void manageRoom(Room roomInfo[], int &roomCount);
void getAvailableRoom(const Room roomInfo[], int roomCount);
void displayRoom(const Room &room);
void roomCheckIn(Room rooms[], int roomCount);
void searchRoomInfo(Room rooms[], int roomCount, int roomNum);
void deleteRoom(Room rooms[], int &roomCount, int roomNum);
void roomCheckOut(Room rooms[], int roomCount, int roomNumber);
void generateBill(const Room &room);
double calculateBill(const Room &room);
void readRooms(Room rooms[], int &roomCount); // Read the room data
void saveRooms(Room rooms[], int roomCount); // Save the room data

// Customer Management Functions
void saveRoomAndCustomerInfo(const Room rooms[], int roomCount);// Save the room and customer data
void readRoomAndCustomerInfo(Room rooms[], int &roomCount);// Read the room and customer data
void searchCustomerInfo(const Room rooms[], int roomCount, const string &name);
void customerSummaryReport(const Room rooms[], int roomCount);
/* 
void writeCustomerFileInfo(const Room &room);
void updateCustomerFileInfo(const Room rooms[], int roomCount);
void readCustomers(Customer customers[], int &customerCount); // Load the customer data
void readCustomerFileInfo(Room rooms[], int roomCount); // Read the customer info from file */

// Billing and Price Calculation Functions
pair<double, double> priceMinMax(const string& customerInfoFilename);
double priceAverage(const string& customerInfoFilename);

// Utility Functions
tm convertStringToTm(const string& dateString);
void pause();

//Main function code for Hotel Booking management system
int main(void)
{
    Room rooms[MAX_ROOMS];
    int roomCount = 0;
    Room newRoom = addRoomNumber();

    Customer customers[MAX_CUSTOMERS];

    string customerInfoFile = "customerInfo.txt";
    readRoomAndCustomerInfo(rooms, roomCount);
    
    system("cls");
    
    int option, roomNumber;
    char custName[100];

    do
    {
        cout << "=================================================================================" << endl;
        cout << "||                          WELCOME TO THE HOTEL CALIFORNIA                    ||" << endl;
        cout << "=================================================================================" << endl << endl;
        //Option selection for Hotel Booking management system
        cout << "\t\n 1. ROOM MANAGEMENT";
        cout << "\t\n 2. SHOW AVAILABLE ROOM";
        cout << "\t\n 3. ROOM CHECK IN";
        cout << "\t\n 4. SEARCH CUSTOMER INFORMATION";
        cout << "\t\n 5. ROOM CHECK OUT";
        cout << "\t\n 6. GUEST DETAIL SUMMARY REPORT";
        cout << "\t\n 7. GENERATE BILL";
        cout << "\t\n 8. CALCULATE AVERAGE"; //add new mix max
        cout << "\t\n 9. SYSTEM EXIT";
        cout << "\t\n\n SELECT OPTION: ";

        cin >> option;
        cin.ignore();

        system("cls");

        switch (option)
        {
            //the room number must be added first before registering any customer
            
            //room management
            case 1:
                manageRoom(rooms, roomCount);
                readRoomAndCustomerInfo(rooms, roomCount);
                
                break;
            //search for room availability
            case 2:
                if (roomCount == 0)
                {
                    cout << "\n\tNo Rooms are available at the moment, please add the available room number first!";
                    pause();
                }
                else
                {
                    getAvailableRoom(rooms, roomCount);
                }
                break;
            //Customer Check In to the room available
            case 3:
                if (roomCount == 0)
                {
                    cout << "\n\tNo Rooms are available at the moment, please add the available room number first!";
                    pause();
                }
                else
                {
                    roomCheckIn(rooms, roomCount);
                }
                break;
            //Search for customer information by typing their name
            case 4:
                if (roomCount == 0)
                {
                    cout << "\n\tCustomers information is not available at the moment!";
                    pause();
                }
                else
                {
                    cout << "\n\tEnter customers name: ";
                    cin.getline(custName, sizeof(custName));
                    searchCustomerInfo(rooms, roomCount, custName);
                }
                break;
            //Search for room number information
            case 5:
                if (roomCount == 0)
                {
                    cout << "\n\tNo Rooms are available at the moment, please add the available room number first!";
                    pause();
                }
                else
                {
                    cout << "\n\tEnter Room Number information: ";
                    cin >> roomNumber;
                    cin.ignore();
                    roomCheckOut(rooms, roomCount, roomNumber);
                }
                break;
            //printing the customer detail summary report 
            case 6:
                customerSummaryReport(rooms, roomCount);
                break;
            //generate bill
            case 7:
                if (roomCount == 0) 
                {
                    cout << "\n\tNo Rooms are available at the moment\n\tNo bill is generated, please add the available room number first!\n\n";
                    pause();
                } 
                else 
                {
                    cout << "\n\tEnter Room Number: ";
                    cin >> roomNumber;
                    cin.ignore();
                    bool roomFound = false;
                    for (int i = 0; i < roomCount; i++) 
                    {
                        if (rooms[i].roomNum == roomNumber) 
                        {
                            generateBill(rooms[i]);
                            roomFound = true;
                            break;
                        }
                    }
                    if (!roomFound) 
                    {
                        cout << "\n\tThe Room is not booked by any customer or the room number is invalid!\n\n";
                        pause();
                    }
                }
                
                break;
            //Calculating the average price
            case 8:
            {
                double averagePrice = priceAverage(customerInfoFile);
                pair<double, double> minMaxPrices = priceMinMax(customerInfoFile);
                cout << "\n\tMinimum price: RM" << fixed << setprecision(2) << minMaxPrices.first; 
                cout << "\n\tMaximum price: RM" << fixed << setprecision(2) << minMaxPrices.second; 
                cout << "\n\tAverage price: RM" << fixed << setprecision(2) << averagePrice << endl<<endl;

                pause();
                break;
            }
            
            //Exiting the system
            case 9:
                cout << "\n\tCOME AGAIN ANYTIME SOON!"<<endl<<endl;
                break;
            
            default:
                cout << "\tPlease select the correct option!" << endl;
                break;
        }   
    saveRoomAndCustomerInfo(rooms, roomCount);
    system("cls");

    } while (option != 9);

    system("cls");

    return 0;
}
//function to add room number
Room addRoomNumber() {
    Room room;

    string roomType, roomSize, bedType;

    // Input room number
    do {
        cout << "\n\tEnter Room Number: ";
        cin >> room.roomNum;

        // Check if the room number already exists
        auto it = find(existingRoomNumbers.begin(), existingRoomNumbers.end(), room.roomNum);
        if (it != existingRoomNumbers.end()) {
            cout << "\n\tRoom number already exists! Please enter a different room number." << endl;
        }
    } while (find(existingRoomNumbers.begin(), existingRoomNumbers.end(), room.roomNum) != existingRoomNumbers.end());

    existingRoomNumbers.push_back(room.roomNum); // Add room number to existing room list

    // Clear screen and display header for room information (not recommended to use system("cls") in production code)
    system("cls");
    cout << "=================================================================================" << endl;
    cout << "||                          Add Room Number Information                        ||" << endl;
    cout << "=================================================================================" << endl << endl;
    cout << "                               Room View Type                                    " << endl;
    cout << "        Tower View = RM550.0 / Garden View = RM500.0/ Water Chalet = RM600.0     " << endl;
    cout << "                               Room Size Type                                    " << endl;
    cout << "    Normal = no additional prices / Deluxe = +RM100.0/ Presidential = +RM200.0   " << endl;
    cout << "                               Bed Size Type                                     " << endl;
    cout << "       Single = no additional prices/ Queen = +RM50.0/ King = +RM100.0           " << endl;

    // Input room type
    do {
        cout << "\n\tRoom Type (T/G/W): ";
        cin >> roomType;
        roomType[0] = toupper(static_cast<unsigned char>(roomType[0])); // Convert the first character to uppercase

        if (!isValidRoomType(roomType[0])) {
            cout << "\n\tInvalid room type! Please enter T, G, or W only." << endl;
        }
    } while (!isValidRoomType(roomType[0]));

    // Set room rate and type based on room type
    switch (roomType[0]) {
        case 'T':
            room.roomType = "Tower View";
            room.roomRate = 550.0; // Tower View room rate
            break;
        case 'G':
            room.roomType = "Garden View";
            room.roomRate = 500.0; // Garden View room rate
            break;
        case 'W':
            room.roomType = "Water Chalet";
            room.roomRate = 600.0; // Water Chalet room rate
            break;
    }

    // Input room size
    do {
        cout << "\n\tRoom Size (N/D/P): ";
        cin >> roomSize;
        roomSize[0] = toupper(static_cast<unsigned char>(roomSize[0])); // Convert the first character to uppercase

        if (!isValidRoomSize(roomSize[0])) {
            cout << "\n\tInvalid room size! Please enter N, D, or P only." << endl;
        }
    } while (!isValidRoomSize(roomSize[0]));

    // Adjust room rate based on room size
    switch (roomSize[0]) {
        case 'N':
            room.roomSize = "Normal";
            break;
        case 'D':
            room.roomSize = "Deluxe";
            room.roomRate += 100.0; // Deluxe Room size
            break;
        case 'P':
            room.roomSize = "Presidential";
            room.roomRate += 200.0; // Presidential Room size
            break;
    }

    // Input bed type
    do {
        cout << "\n\tBed Type (S/Q/K): ";
        cin >> bedType;
        bedType[0] = toupper(static_cast<unsigned char>(bedType[0])); // Convert the first character to uppercase

        if (!isValidBedType(bedType[0])) {
            cout << "\n\tInvalid bed type! Please enter S, Q, or K only." << endl;
        }
    } while (!isValidBedType(bedType[0]));

    // Adjust room rate based on bed type
    switch (bedType[0]) {
        case 'S':
            room.bedType = "Single";
            break;
        case 'Q':
            room.bedType = "Queen";
            room.roomRate += 50.0; // Queen Bed type
            break;
        case 'K':
            room.bedType = "King";
            room.roomRate += 100.0; // King Bed type
            break;
    }

    return room;
}


/* Room addRoomNumber(int roomNumber) {    
    static int numExistingRooms = 0;
    static int existingRoomNumbers[MAX_ROOMS]; // Increase size to MAX_ROOMS for larger capacity


    // Check if the room number already exists
    for (int i = 0; i < numExistingRooms; i++) {
        if (existingRoomNumbers[i] == roomNumber) {
            cout << "\n\tRoom number already exists! \n\tPlease enter a different room number." << endl;
            Room emptyRoom;
            emptyRoom.roomNum = -1;
            return emptyRoom;
        }
    }

    //Room number is unique , proceed to add the room number
    Room room;
    room.roomNum = roomNumber;

    if (numExistingRooms < MAX_ROOMS) {
        existingRoomNumbers[numExistingRooms] = roomNumber;
        numExistingRooms++;
    } else {
        cout << "\n\tCannot add more rooms. Maximum limit reached!" << endl;
        Room emptyRoom;
        emptyRoom.roomNum = -1;
        return emptyRoom;
    }

    // Clear screen and display header for room information
    system("cls");
    cout << "=================================================================================" << endl;
    cout << "||                          Add Room Number Information                        ||" << endl;
    cout << "=================================================================================" << endl << endl;
    cout << "                               Room View Type                                    " << endl;
    cout << "        Tower View = RM550.0 / Garden View = RM500.0/ Water Chalet = RM600.0     " << endl;
    cout << "                               Room Size Type                                    " << endl;
    cout << "    Normal = no additional prices / Deluxe = +RM100.0/ Presidential = +RM200.0   " << endl;
    cout << "                               Bed Size Type                                     " << endl;
    cout << "       Single = no additional prices/ Queen = +RM50.0/ King = +RM100.0           " << endl;


    // Input room type
    do {
        cout << "\n\tRoom Type information (Tower View/Garden View/Water Chalet)(T/G/W): ";
        cin >> room.roomType;
        if (!isValidRoomType(room.roomType)){
            cout << "\n\tInvalid room type! Please enter T, G, or W only.";
        }
  } while (!isValidRoomType(room.roomType));

    // Set room rate based on room type
    switch(room.roomType) {
        case 'T' :
        case 't':
            room.roomRate = 550.0; // Tower View room rate
            break;
        case 'G':
        case 'g':
            room.roomRate = 500.0; // Garden View room rate
            break;
        case 'W':
        case 'w':
            room.roomRate = 600.0; // Water Chalet room rate
            break;
    }

    // Input room size
    do {
        cout << "\n\tRoom Size (Normal/Deluxe/Presidential)(N/D/P): ";
        cin >> room.roomSize;
        if(!isValidRoomSize(room.roomSize)){
            cout << "\n\tInvalid room size! Please enter N, D, or P only.";
        }
  } while(!isValidRoomSize(room.roomSize));
  
    switch(room.roomSize) {
        case 'N' :
        case 'n': // No price changes if Normal Room size
            break;
        case 'D':
        case 'd':
            room.roomRate += 100.0; // Plus another RM100.00 if Deluxe Room size
            break;
        case 'P':
        case 'p':
            room.roomRate += 200.0; // Plus another RM200.00 if Presidential Room size
            break;
    }

    // Input bed type
    do {
        cout << "\n\tBed Size information (Single Bed/Queen Bed/King Bed)(S/Q/K): ";
        cin >> room.bedType;
        if(!isValidBedType(room.bedType))
        {
            cout << "\n\tInvalid bed type! Please enter S, Q, or K only.";
        }
  } while(!isValidBedType(room.bedType));

      switch(room.bedType) {
        case 'S' :
        case 's': // No price changes if Normal Room size
            break;
        case 'Q':
        case 'q':
            room.roomRate += 50.0; // Plus another RM100.00 if Deluxe Room size
            break;
        case 'K':
        case 'k':
            room.roomRate += 100.0; // Plus another RM200.00 if Presidential Room size
            break;
    }

    room.isBooked = false;
    cout << "\n\tRoom Rate: RM" << room.roomRate << endl;

    cin.ignore();
    pause();
    system("cls");

    return room;
}
 */

//Function to display room details
void displayRoom(const Room &room) {

    cout << "=================================================================================" << endl;
    cout << "||                          Display Room Information                           ||" << endl;
    cout << "=================================================================================" << endl << endl;

    cout << "\n\tRoom Number: " << room.roomNum;
    cout << "\n\tRoom Type: " << room.roomType;
    cout << "\n\tRoom Size: " << room.roomSize;
    cout << "\n\tBed Size: " << room.bedType;
    cout << "\n\tRoom Rate Per night: " << room.roomRate;
    cout << "\n\n";
}

//function to search for room information
void searchRoomInfo(Room rooms[], int roomCount, int roomNumber) {

    
    cout << "=================================================================================" << endl;
    cout << "||                          Search Room Information                            ||" << endl;
    cout << "=================================================================================" << endl << endl;
    for (int room = 0; room < roomCount; room++)
    {
        if (rooms[room].roomNum == roomNumber)
        {
            cout << "\n\tRoom Information";
            if (rooms[room].isBooked == true)
            {
                cout << "\n\tThe Room has been reserved for a customer.";
            }
            else
            {
                cout << "\n\tThe Room is available for booking!";
            }
            displayRoom(rooms[room]);
            pause();
            return;
        }
    }
    cout << "\n\tSorry, the room number you are searching for is not found!";
    pause();
}

//function to checkin a customer to a room
void roomCheckIn(Room rooms[], int roomCount) {
    int roomNumber;
    cout << "=================================================================================" << endl;
    cout << "||                       CUSTOMER CHECK IN DETAIL INFORMATION                   ||" << endl;
    cout << "=================================================================================" << endl << endl;
    cout << "\n\tEnter Room Number: ";
    cin >> roomNumber;
    cin.ignore(); 

    for (int room = 0; room < roomCount; room++) {
        if (rooms[room].roomNum == roomNumber) {
            if (rooms[room].isBooked) {
                cout << "\n\tThe Room has already been booked by another customer!";
                pause();
                return;
            }

            rooms[room].customerInfo.bookingNum = rand() % 1000 + 1000;
            cout << "\n\tBooking Number: " << rooms[room].customerInfo.bookingNum << endl;

            cout << "\n\tEnter the Customer Name: ";
            getline(cin, rooms[room].customerInfo.custName); // Use getline to read the name
            cout << "\n\tEnter the Customer Address: ";
            getline(cin, rooms[room].customerInfo.custAddress); // Use getline to read the address
            cout << "\n\tEnter Customer Phone Number: ";
            getline(cin, rooms[room].customerInfo.custPhoneNum); // Use getline to read the phone number
            cout << "\n\tThe Room is booked starts from (DD-MM-YYYY): ";
            getline(cin, rooms[room].customerInfo.bookingStartFromDate); // Use getline to read the start date
            cout << "\n\tThe booking will end on (DD-MM-YYYY): ";
            getline(cin, rooms[room].customerInfo.bookingEndDate); // Use getline to read the end date
            cout << "\n\tCustomer Advance Payment: RM";
            cin >> rooms[room].customerInfo.advancePay;
            cin.ignore(); // Clear input buffer after reading advance payment

            rooms[room].isBooked = true;
            saveRoomAndCustomerInfo(rooms, roomCount);

            cout << "\n\tThe Customer has been checked in successfully!";
            pause();
            return;
        }
    }
        cout << "\n\tSorry, the room number you are searching for is not found!";
        pause();
}


//Function to get room availability information
void getAvailableRoom(const Room rooms[], int roomCount) {
    bool found = false;
    cout << "=================================================================================" << endl;
    cout << "||                          ROOM AVAILABILITY INFORMATION                      ||" << endl;
    cout << "=================================================================================" << endl << endl;

    for (int room = 0; room < roomCount; ++room) {
        if (!rooms[room].isBooked) {
            displayRoom(rooms[room]);
            found = true;
        }
    }

    if (!found) {
        cout << "\n\tNo available rooms found!" << endl;
    }

    pause();
}

//function to manage room (add, delete, back to main menu)
void manageRoom(Room rooms[], int &roomCount) {
    cout << "=================================================================================" << endl;
    cout << "||                              ROOM MANAGEMENT                                ||" << endl;
    cout << "=================================================================================" << endl << endl;
    cout << "\t\n1. Add Room";
    cout << "\t\n2. Delete Room";
    cout << "\t\n3. Back to Main Menu\n\n";
    cout << "\t\n\nSELECT OPTION: ";

    int option = 0, roomNumber = 0;
    cin >> option;
    cin.ignore();

    switch (option) {
        case 1: {
            Room newRoom = addRoomNumber();
            rooms[roomCount] = newRoom;
            roomCount++;
            cout << "\n\tThe Room has been added successfully!" << endl << endl;
            // Optionally display the added room information
            // displayRoom(newRoom);
            break;
        }
        case 2:
            cout << "\n\tEnter Room Number to be deleted: ";
            cin >> roomNumber;
            // Implement deleteRoom functionality
            break;
        case 3:
            break;
        default:
            cout << "\tPlease select the correct option!" << endl;
            break;
    }

    // Pause and clear screen (not recommended to use system("pause") and system("cls") in production code)
    system("pause");
    system("cls");
}

//Function to delete a room
void deleteRoom(Room rooms[], int &roomCount, int roomNumber) {
    cout << "=================================================================================" << endl;
    cout << "||                                 Room Deletion                               ||" << endl;
    cout << "=================================================================================" << endl << endl;
    
    for (int room = 0; room < roomCount; room++)
    {
        if (rooms[room].roomNum == roomNumber)
        {
            for (int j = room; j < roomCount - 1; j++)
            {
                rooms[j] = rooms[j + 1];
            }
            roomCount--;
            cout << "\n\tThe Room has been deleted successfully!";
            pause();
            return;
        }
    }
    cout << "\n\tSorry, the room number you are trying to delete is not found!";
    pause();
    system("cls");
}
/* 
// Function to check out a customer from a room.
void roomCheckOut(Room rooms[], int roomCount, int roomNumber) {
    cout << "=================================================================================" << endl;
    cout << "||                                 Room Checkout                               ||" << endl;
    cout << "=================================================================================" << endl << endl;
    for (int room = 0; room < roomCount; room++) {
        if (rooms[room].roomNum == roomNumber) {
            if (rooms[room].isBooked == false) {
                cout << "\n\tThe Room is already available for booking!";
                pause();
                return;
            }

            rooms[room].isBooked = false;
            rooms[room].customerInfo = Customer(); // Reset customer information

            double bill = calculateBill(rooms[room]);
            if (bill < 0) {
                cout << "\n\tError calculating bill due to date parsing issues." << endl;
            } else {
                cout << "\n\tThe total bill for the room is RM" << bill;
            }

            updateCustomerFileInfo(rooms, roomCount);

            cout << "\n\tThe Customer has been checked out successfully!";
            pause();
            return;
        }
    }
    cout << "\n\tSorry, the room number you are searching for is not found!";
    pause();
}
 */

//function to search customer information
void searchCustomerInfo(const Room rooms[], int roomCount, const string &name) {
    
    cout << "=================================================================================" << endl;
    cout << "||                         SEARCH CUSTOMER INFORMATION                         ||" << endl;
    cout << "=================================================================================" << endl << endl;

    bool customerFound = false;
    for (int room = 0; room < roomCount; room++) {
        if (rooms[room].isBooked && rooms[room].customerInfo.custName == name) {
            cout << "\n\tRoom Number: " << rooms[room].roomNum;
            cout << "\n\tCustomer Name: " << rooms[room].customerInfo.custName;
            cout << "\n\tCustomer Address: " << rooms[room].customerInfo.custAddress;
            cout << "\n\tCustomer Phone Number: " << rooms[room].customerInfo.custPhoneNum;
            cout << "\n\tBooking Number: " << rooms[room].customerInfo.bookingNum;
            cout << "\n\tBooking From: " << rooms[room].customerInfo.bookingStartFromDate;
            cout << "\n\tBooking To: " << rooms[room].customerInfo.bookingEndDate;
            cout << "\n\tAdvance Payment: RM" << rooms[room].customerInfo.advancePay << endl << endl;

            customerFound = true;
        }
    }
        if (!customerFound) {
        cout << "\n\tSorry, the customer information you are searching for is not found!" << endl;
    }
    pause();
    system("cls");
    
} 

//Function to generate bill for customer
void generateBill(const Room &room) {
    
    cout << "=================================================================================" << endl;
    cout << "||                             Bill INFORMATION                                ||" << endl;
    cout << "=================================================================================" << endl << endl;
    
    if (room.isBooked) {
        double bill = calculateBill(room);
        if (bill < 0) {
            cout << "\n\tError calculating bill due to date parsing issues." << endl;
        }
        else {
            cout << "\n\tCustomer Name: " << room.customerInfo.custName;
            cout << "\n\tRoom Number: " << room.roomNum;
            cout << "\n\tRoom Type: " << room.roomType;
            cout << "\n\tRoom Rate: RM" << room.roomRate;
            cout << "\n\tRoom Size: " << room.roomSize;
            cout << "\n\tBed Size: " << room.bedType;
            cout << "\n\tDays Stayed: " << (bill / room.roomRate);
            cout << "\n\tTotal Bill: RM" << bill << endl;
        }
    } 
    else 
    {
        cout << "\n\tThe Room is not booked by any customer or the room number is invalid!";
    }
    pause();

}

//Function to generate a summary report of all customers
void customerSummaryReport(const Room rooms[], int roomCount) {
    cout << "=================================================================================" << endl;
    cout << "||                          Customer Summary Report                            ||" << endl;
    cout << "=================================================================================" << endl << endl;

    bool anyBooked = false;

    for (int room = 0; room < roomCount; room++){
        if (rooms[room].isBooked)
        {
            anyBooked = true;
            cout << "\n\tCustomer Name: " << rooms[room].customerInfo.custName;
            cout << "\n\tCustomer Address: " << rooms[room].customerInfo.custAddress;
            cout << "\n\tCustomer Phone Number: " << rooms[room].customerInfo.custPhoneNum;
            cout << "\n\tBooking Number: " << rooms[room].customerInfo.bookingNum;
            cout << "\n\tBooking Start From: " << rooms[room].customerInfo.bookingStartFromDate;
            cout << "\n\tBooking End : " << rooms[room].customerInfo.bookingEndDate;
            cout << "\n\tAdvance Payment: RM" << rooms[room].customerInfo.advancePay << endl;
        
        }
    }
    
        if(!anyBooked) {
            cout << "\n\tThere is no customer booked to this hotel yet!";
        }
    
    pause();
}


// Function to calculate minimum and maximum prices

pair<double, double> priceMinMax(const string& customerInfoFilename) {
    double minPrice = numeric_limits<double>::infinity(); // Start with infinity for minimum
    double maxPrice = -numeric_limits<double>::infinity(); // Start with negative infinity for maximum
    double price;

    // Open the customerInfo.txt file
    ifstream file("customerInfo.txt");
    if (!file.is_open()) {
        cerr << "Failed to open the file " << customerInfoFilename << endl;
        return make_pair(0.0, 0.0); // Return a pair of zeros if the file can't be opened
    }

    string line;
    while (getline(file, line)) {
        if (line.find("Advance Payment: RM") != string::npos) {
            try {
                size_t pos = line.find(": RM");
                price = stod(line.substr(pos + 2));
                if (price < minPrice)
                    minPrice = price;
                if (price > maxPrice)
                    maxPrice = price;
            } catch (const invalid_argument& e) {
                cerr << "Invalid number format in line: " << line << endl;
            } catch (const out_of_range& e) {
                cerr << "Number out of range in line: " << line << endl;
            }
        }
    }
    file.close();

    if (minPrice == numeric_limits<double>::infinity() || maxPrice == -numeric_limits<double>::infinity())
    {
        cerr << "No valid data found in file: " << customerInfoFilename << endl;
        return make_pair(0.0, 0.0); // Handle no valid data found
    }

    return make_pair(minPrice, maxPrice); // Return a pair of minPrice and maxPrice
}

// Function to calculate average price from file
double priceAverage(const string& customerInfoFilename) {
    double sum = 0;
    int count = 0;
    double price;

    ifstream file(customerInfoFilename);
    if (!file.is_open()) {
        cerr << "Failed to open the file: " << customerInfoFilename << endl;
        return -1.0; // Return -1.0 error value if the file can't be opened
    }

    string line;
    while (getline(file, line)) {
        size_t pos = line.find("Advance Payment: RM");
        if (pos != string::npos) {
            try {
                // +18 to move past "Advance Payment: RM"
                price = stod(line.substr(pos + 18));
                sum += price;
                count++;
            } catch (const invalid_argument& e) {
                cerr << "Invalid number format in line: " << line << endl;
            } catch (const out_of_range& e) {
                cerr << "Number out of range in line: " << line << endl;
            }
        }
    }
    file.close();
    if(count == 0){
        cerr << "No data found in the file: " << customerInfoFilename << endl;
        return -1.0;
    }

    return sum / count;
}

double calculateBill(const Room &room) {
    tm startDate = {};
    istringstream startDateStream(room.customerInfo.bookingStartFromDate);
    startDateStream >> get_time(&startDate, "%d-%m-%Y");
    if (startDateStream.fail()) {
        cerr << "Error: Failed to parse the start date" << endl;
        return -1;
    }
    time_t startTime = mktime(&startDate);

    tm endDate = {};
    istringstream endDateStream(room.customerInfo.bookingEndDate);
    endDateStream >> get_time(&endDate, "%d-%m-%Y");
    if (endDateStream.fail()) {
        cerr << "Error: Failed to parse the end date" << endl;
        return -1;
    }
    time_t endTime = mktime(&endDate);

    // Check for invalid date range
    if (difftime(endTime, startTime) < 0) {
        cerr << "Error: The end date is before the start date" << endl;
        return -1;
    }

    int daysStayed = difftime(endTime, startTime) / (24 * 60 * 60);
    if (daysStayed < 1) {
        cerr << "Error: Invalid stay duration" << endl;
        return -1;
    }

    double bill = daysStayed * room.roomRate;
    return bill;
}
// Function to convert a date string to a tm structure
tm convertStringToTm(const string& dateString) {
    tm time = {};
    istringstream ss(dateString);
    ss >> get_time(&time, "%d-%m-%Y");

    if (ss.fail()) {
        cerr << "Error: Failed to parse date string" << endl;
    }

    return time;
}

// Function to write room and customer information to a file
// Function to write room and customer information to a file
void saveRoomAndCustomerInfo(const Room rooms[], int roomCount) {
    ofstream file("customerInfo.txt");

    if (file.is_open()) {
        for (int i = 0; i < roomCount; ++i) {
            file << "=================================================================================" << endl;
            file << "Room Number: " << rooms[i].roomNum << endl;
            file << "Room Type: " << rooms[i].roomType << endl;
            file << "Room Size: " << rooms[i].roomSize << endl;
            file << "Bed Size: " << rooms[i].bedType << endl;
            file << "Room Rate: RM" << rooms[i].roomRate << endl;
            file << "Is Booked: " << rooms[i].isBooked << endl;

            if (rooms[i].isBooked) {
                file << "Customer Name: " << rooms[i].customerInfo.custName << endl;
                file << "Customer Address: " << rooms[i].customerInfo.custAddress << endl;
                file << "Customer Phone Number: " << rooms[i].customerInfo.custPhoneNum << endl;
                file << "Booking Number: " << rooms[i].customerInfo.bookingNum << endl;

                tm startDate = convertStringToTm(rooms[i].customerInfo.bookingStartFromDate);
                tm endDate = convertStringToTm(rooms[i].customerInfo.bookingEndDate);
                file << "Booking Start Date: " << put_time(&startDate, "%d-%m-%Y") << endl;
                file << "Booking End Date: " << put_time(&endDate, "%d-%m-%Y") << endl;

                file << "Advance Payment: RM" << rooms[i].customerInfo.advancePay << endl;
            }
        }
        file.close();
    } else {
        cout << "\n\tUnable to open the file to write room and customer information!" << endl;
    }
}

// Function to read room and customer information from a file
void readRoomAndCustomerInfo(Room rooms[], int &roomCount) {
    ifstream file("customerInfo.txt");
    roomCount = 0;

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            if (line.find("Room Number: ") != string::npos) {
                rooms[roomCount].roomNum = stoi(line.substr(line.find(": ") + 2));

                getline(file, line); rooms[roomCount].roomType = line.substr(line.find(": ") + 2);
                getline(file, line); rooms[roomCount].roomSize = line.substr(line.find(": ") + 2);
                getline(file, line); rooms[roomCount].bedType = line.substr(line.find(": ") + 2);
                getline(file, line); rooms[roomCount].roomRate = stod(line.substr(line.find(": RM") + 4));

                getline(file, line); 
                string isBookedStr = line.substr(line.find(": ") + 2);
                rooms[roomCount].isBooked = (isBookedStr == "1");

                if (rooms[roomCount].isBooked) {
                    getline(file, line); rooms[roomCount].customerInfo.custName = line.substr(line.find(": ") + 2);
                    getline(file, line); rooms[roomCount].customerInfo.custAddress = line.substr(line.find(": ") + 2);
                    getline(file, line); rooms[roomCount].customerInfo.custPhoneNum = line.substr(line.find(": ") + 2);
                    getline(file, line); rooms[roomCount].customerInfo.bookingNum = stoi(line.substr(line.find(": ") + 2));
                    getline(file, line); rooms[roomCount].customerInfo.bookingStartFromDate = line.substr(line.find(": ") + 2);
                    getline(file, line); rooms[roomCount].customerInfo.bookingEndDate = line.substr(line.find(": ") + 2);
                    getline(file, line); rooms[roomCount].customerInfo.advancePay = stod(line.substr(line.find(": RM") + 4));
                }
                roomCount++;
            }
        }
        file.close();
    } else {
        cout << "\n\tUnable to open the file to read room and customer information!" << endl;
    }
}

// Function to update room and customer information for checkout
void checkoutRoom(Room rooms[], int roomCount, int roomNumber) {
    for (int i = 0; i < roomCount; ++i) {
        if (rooms[i].roomNum == roomNumber) {
            if (rooms[i].isBooked) {
                // Clear customer information
                rooms[i].customerInfo = {};
                rooms[i].isBooked = false;

                // Save the updated information
                saveRoomAndCustomerInfo(rooms, roomCount);

                cout << "\n\tRoom " << roomNumber << " has been checked out successfully!" << endl;
            } else {
                cout << "\n\tRoom " << roomNumber << " is not currently booked!" << endl;
            }
            return;
        }
    }
    cout << "\n\tRoom " << roomNumber << " not found!" << endl;
}

//Function to pause the program until the user presses a key
void pause() {
    cout << "\n\t\tPress any key to continue..."<<endl<<endl;
    cin.get();
}

