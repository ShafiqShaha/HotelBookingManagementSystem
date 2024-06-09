#include<iostream>
#include<string>
#include<fstream>
#include<cctype>
#include<cstring>
#include<ctime>
#include<sstream>
#include<iomanip>


#define MAX_ROOMS 100

using namespace std;

//create a struct for customer information
struct Customer {
    int bookingNum;
    string custName;
    string custAddress;
    string custPhoneNum;
    string bookingStartFromDate;
    string bookingEndDate;
    double advancePay;
};

struct Room {
    char roomType;
    char bedType;
    char roomSize;
    int roomNum;
    int roomRate;
    bool isBooked;
    Customer customerInfo;
};

//function prototype declaration
Room addRoomNumber(int roomNum);
void manageRoom(Room roomInfo[], int &roomCount);
void getAvailableRoom(const Room roomInfo[], int roomCount);
void displayRoom(const Room &room);
void roomCheckIn(Room rooms[], int roomCount);
void searchRoomInfo(Room rooms[], int roomCount, int roomNum);
void deleteRoom(Room rooms[], int &roomCount, int roomNum);
void searchCustomerInfo(const Room rooms[], int roomCount, const string &name);
void roomCheckOut(Room rooms[], int roomCount, int roomNumber);
void customerSummaryReport(const Room rooms[], int roomCount);
void writeCustomerFileInfo(const Room &room);
void updateCustomerFileInfo(const Room rooms[], int roomCount);
void generateBill(const Room &room);
double calculateBill(const Room &room);
void pause();

int main(void)
{
    Room rooms[MAX_ROOMS];
    int roomCount = 0;
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
        cout << "\t\n 8. SYSTEM EXIT";
        cout << "\t\n\n SELECT OPTION: ";

        cin >> option;
        cin.ignore();

        switch (option)
        {
            //the room number must be added first before registering any customer
            /* ROOM NUMBER INFORMATION
            TOWER TYPE HOTEL (000 until 039)
            GARDEN TYPE HOTEL (040 until 059)
            WATER CHALET TYPE (060 until 099)
            */
            case 1:
                manageRoom(rooms, roomCount);
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
            //Exiting the system
            case 7:
                if (roomCount == 0) 
                {
                    cout << "\n\tNo Rooms are available at the moment, please add the available room number first!";
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
                        cout << "\n\tThe Room is not booked by any customer or the room number is invalid!";
                        pause();
                    }
                }
                break;
            //Exiting the system
            case 8:
                cout << "\n\tCOME AGAIN ANYTIME SOON!"<<endl<<endl;
                break;
            
            //keep pop up if the user does not put the correct options number
            default:
                cout << "\tPlease select the correct option!" << endl;
                break;
        }

    } while (option != 8);

    return 0;
}

Room addRoomNumber(int roomNumber) {
    Room room;
    room.roomNum = roomNumber;
    cout << "\n\tRoom Type information (Tower View/Garden View/Water Chalet)(T/G/W): ";
    cin >> room.roomType;
    cout << "\n\tRoom Size (Normal/Deluxe/Presidential)(N/D/P): ";
    cin >> room.roomSize;
    cout << "\n\tBed Size information (Single Bed/Queen Bed/King Bed)(S/Q/K): ";
    cin >> room.bedType;
    cout << "\n\tRoom rate per night: ";
    cin >> room.roomRate;
    room.isBooked = false;

    cout << "\n\tThe Room has been added successfully!" << endl<<endl;
    cin.ignore();
    pause();
    return room;
}

//Function to display room details
void displayRoom(const Room &room) {
    cout << "\n\tRoom Number: " << room.roomNum;
    cout << "\n\tRoom Type: " << room.roomType;
    cout << "\n\tRoom Size: " << room.roomSize;
    cout << "\n\tBed Size: " << room.bedType;
    cout << "\n\tRoom Rate Per night: " << room.roomRate;
}

//function to search for room information
void searchRoomInfo(Room rooms[], int roomCount, int roomNumber) {
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

    bool roomFound = false;

    for (int room = 0; room < roomCount; room++) {
        if (rooms[room].roomNum == roomNumber) {
            roomFound = true;
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
            cout << "\n\tThe Room is booked starts from (YYYY-MM-DD): ";
            getline(cin, rooms[room].customerInfo.bookingStartFromDate); // Use getline to read the start date
            cout << "\n\tThe booking will end on (YYYY-MM-DD): ";
            getline(cin, rooms[room].customerInfo.bookingEndDate); // Use getline to read the end date
            cout << "\n\tCustomer Advance Payment: RM";
            cin >> rooms[room].customerInfo.advancePay;
            cin.ignore(); // Clear input buffer after reading advance payment

            rooms[room].isBooked = true;
            writeCustomerFileInfo(rooms[room]);

            cout << "\n\tThe Customer has been checked in successfully!";
            pause();
            return;
        }
    }
    if (!roomFound) {
        cout << "\n\tSorry, the room number you are searching for is not found!";
        pause();
    }
}



//Function to get room availability information
void getAvailableRoom(const Room rooms[], int roomCount) {
    bool found = false;
    cout << "=================================================================================" << endl;
    cout << "||                          ROOM AVAILABILITY INFORMATION                      ||" << endl;
    cout << "=================================================================================" << endl << endl;

    for (int room = 0; room < roomCount; room++)
    {
        if (rooms[room].isBooked == false)
        {
            displayRoom(rooms[room]);
            cout << "\n";
            found = true;
        }
    }

    if (!found)
    {
        cout << "\n\tNo available rooms found!";
    }
    pause();
}

//Function to manage room addition and deletion
void manageRoom(Room rooms[], int &roomCount) {
    int option, roomNumber;
    cout << "=================================================================================" << endl;
    cout << "||                              ROOM MANAGEMENT                                ||" << endl;
    cout << "=================================================================================" << endl << endl;
    cout << "\t\n1. Add Room";
    cout << "\t\n2. Delete Room";
    cout << "\t\n3. Back to Main Menu\n\n";
    cout << "\t\n\nSELECT OPTION: ";
    cin >> option;
    cin.ignore();

    switch (option) {
        case 1:
            cout << "\n\tEnter Room Number to be added: ";
            cin >> roomNumber;
            cin.ignore();
            rooms[roomCount] = addRoomNumber(roomNumber);
            roomCount++;
            break;
        case 2:
            cout << "\n\tEnter Room Number to be deleted: ";
            cin >> roomNumber;
            cin.ignore();
            deleteRoom(rooms, roomCount, roomNumber);
            break;
        case 3:
            break;
        default:
            cout << "\tPlease select the correct option!" << endl;
            break;
    }
}

//Function to delete a room
void deleteRoom(Room rooms[], int &roomCount, int roomNumber) {
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
}

//Function to check out a customer from a room.
void roomCheckOut(Room rooms[], int roomCount, int roomNumber) {
    for (int room = 0; room < roomCount; room++)
    {
        if (rooms[room].roomNum == roomNumber)
        {
            if (rooms[room].isBooked == false)
            {
                cout << "\n\tThe Room is already available for booking!";
                pause();
                return;
            }

            rooms[room].isBooked = false;
            rooms[room].customerInfo = Customer(); // Reset customer information

            double bill = calculateBill(rooms[room]);
            cout << "\n\tThe total bill for the room is RM" << bill;

            updateCustomerFileInfo(rooms, roomCount);

            cout << "\n\tThe Customer has been checked out successfully!";
            pause();
            return;
        }
    }
    cout << "\n\tSorry, the room number you are searching for is not found!";
    pause();
}

//function to search customer information
void searchCustomerInfo(const Room rooms[], int roomCount, const string &name) {
    for (int room = 0; room < roomCount; room++) {
        if (rooms[room].isBooked && rooms[room].customerInfo.custName == name) {
            cout << "\n\tCustomer Information:";
            cout << "\n\tCustomer Name: " << rooms[room].customerInfo.custName;
            cout << "\n\tCustomer Address: " << rooms[room].customerInfo.custAddress;
            cout << "\n\tCustomer Phone Number: " << rooms[room].customerInfo.custPhoneNum;
            cout << "\n\tBooking Number: " << rooms[room].customerInfo.bookingNum;
            cout << "\n\tBooking From: " << rooms[room].customerInfo.bookingStartFromDate;
            cout << "\n\tBooking To: " << rooms[room].customerInfo.bookingEndDate;
            cout << "\n\tAdvance Payment: RM" << rooms[room].customerInfo.advancePay;
            pause();
            return;
        }
    }
    cout << "\n\tSorry, the customer information you are searching for is not found!";
    pause();
}

double calculateBill(const Room &room) {
    int daysStayed;

    tm startDate = {};
    istringstream(room.customerInfo.bookingStartFromDate) >> get_time(&startDate, "%Y-%m-%d");
    time_t startTime = mktime(&startDate);

    tm endDate = {};
    istringstream(room.customerInfo.bookingEndDate) >> get_time(&endDate, "%Y-%m-%d");
    time_t endTime = mktime(&endDate);

    daysStayed = difftime(endTime, startTime) / (24 * 60 * 60);

    double bill = daysStayed * room.roomRate;
    return bill;
}

void generateBill(const Room &room) {
    if (room.isBooked) {
        double bill = calculateBill(room);

        cout << "\n\tCustomer Name: " << room.customerInfo.custName;
        cout << "\n\tRoom Number: " << room.roomNum;
        cout << "\n\tRoom Rate Per Night: RM" << room.roomRate;
        cout << "\n\tTotal Bill: RM" << bill;
        pause();
    } else {
        cout << "\n\tThe Room is not booked by any customer or the room number is invalid!";
        pause();
    }
}

//Function to generate a summary report of all customers
void customerSummaryReport(const Room rooms[], int roomCount) {
    cout << "=================================================================================" << endl;
    cout << "||                          Customer Summary Report                            ||" << endl;
    cout << "=================================================================================" << endl << endl;

    for (int room = 0; room < roomCount; room++)
    {
        if (rooms[room].isBooked)
        {
            cout << "\n\tCustomer Name: " << rooms[room].customerInfo.custName;
            cout << "\n\tCustomer Address: " << rooms[room].customerInfo.custAddress;
            cout << "\n\tCustomer Phone Number: " << rooms[room].customerInfo.custPhoneNum;
            cout << "\n\tBooking Number: " << rooms[room].customerInfo.bookingNum;
            cout << "\n\tBooking From: " << rooms[room].customerInfo.bookingStartFromDate;
            cout << "\n\tBooking To: " << rooms[room].customerInfo.bookingEndDate;
            cout << "\n\tAdvance Payment: RM" << rooms[room].customerInfo.advancePay;
            cout << "\n";
        }
    }
    pause();
}

//Function to write customer information to a file
void writeCustomerFileInfo(const Room &room) {
    ofstream file("customerInfo.txt", ios::app);
    if (file.is_open())
    {
        file << "Customer Name: " << room.customerInfo.custName << endl;
        file << "Customer Address: " << room.customerInfo.custAddress << endl;
        file << "Customer Phone Number: " << room.customerInfo.custPhoneNum << endl;
        file << "Booking Number: " << room.customerInfo.bookingNum << endl;
        file << "Booking From: " << room.customerInfo.bookingStartFromDate << endl;
        file << "Booking To: " << room.customerInfo.bookingEndDate << endl;
        file << "Advance Payment: RM" << room.customerInfo.advancePay << endl;
        file << "Room Number: " << room.roomNum << endl;
        file << "Room Type: " << room.roomType << endl;
        file << "Room Size: " << room.roomSize << endl;
        file << "Bed Size: " << room.bedType << endl;
        file << "Room Rate: RM" << room.roomRate << endl;

        file << "=================================================================================" << endl;
        file.close();
    }
    else
    {
        cout << "\n\tUnable to open the file to write!";
    }
}

//Function to update customer information in a file
void updateCustomerFileInfo(const Room rooms[], int roomCount) {
    ofstream file("customerInfo.txt");
    if (file.is_open())
    {
        for (int room = 0; room < roomCount; room++)
        {
            if (rooms[room].isBooked)
            {
                file << "Customer Name: " << rooms[room].customerInfo.custName << endl;
                file << "Customer Address: " << rooms[room].customerInfo.custAddress << endl;
                file << "Customer Phone Number: " << rooms[room].customerInfo.custPhoneNum << endl;
                file << "Booking Number: " << rooms[room].customerInfo.bookingNum << endl;
                file << "Booking From: " << rooms[room].customerInfo.bookingStartFromDate << endl;
                file << "Booking To: " << rooms[room].customerInfo.bookingEndDate << endl;
                file << "Advance Payment: RM" << rooms[room].customerInfo.advancePay << endl;
                file << "Room Number: " << rooms[room].roomNum << endl;
                file << "Room Type: " << rooms[room].roomType << endl;
                file << "Room Size: " << rooms[room].roomSize << endl;
                file << "Bed Size: " << rooms[room].bedType << endl;
                file << "Room Rate: RM" << rooms[room].roomRate << endl;
                
                file << "=================================================================================" << endl;
            }
        }
        file.close();
    }
    else
    {
        cout << "\n\tUnable to open the file to write!";
    }
}

//Function to pause the program until the user presses a key
void pause() {
    cout << "\n\tPress any key to continue..."<<endl<<endl;
    cin.get();
    cin.ignore();
}
