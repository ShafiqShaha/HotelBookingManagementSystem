#include<iostream>
#include<string>
#include<fstream>
#include<cctype>
#include<cstring>
#include<ctime>
#include<sstream>
#include<iomanip>
#include <limits>
#include<cstdlib>
#include<chrono>

#define MAX_ROOMS 100

using namespace std;

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
    char roomType;
    char bedType;
    char roomSize;
    int roomNum;
    int roomRate;
    bool isBooked;
    Customer customerInfo;
};

bool isValidRoomType(char type){
    return type == 'T' || type == 't' || type == 'G' || type == 'g' || type == 'W' || type == 'w';
}

bool isValidRoomSize(char size) {
    return size == 'N' || size == 'n' || size == 'D' || size == 'd' || size == 'P' || size == 'p';
}

bool isValidBedType(char bed){
    return bed == 'S' || bed == 's' || bed == 'Q' || bed == 'q' || bed == 'K' || bed == 'k';
}

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
int calculateRemainingDays(const tm& startDate, const tm& endDate);
double calculateBill(const Room &room);
pair<double, double> priceMinMax();
int calculateDaysStayed(const Room& room);
double priceAverage();
void readRooms(Room rooms[], int &roomCount);
void saveRooms(Room rooms[], int roomCount);
void readCustomers(Customer customers[], int &count);
void pause();

int main(void)
{
    Room rooms[MAX_ROOMS];
    int roomCount = 0;
    int option, roomNumber;
    char custName[100];

    readRooms(rooms , roomCount);
    system("cls");

    do
    {
        // Option selection for Hotel Booking management system
        cout << "\t\n 1. ROOM MANAGEMENT";
        cout << "\t\n 2. SHOW AVAILABLE ROOM";
        cout << "\t\n 3. ROOM CHECK IN";
        cout << "\t\n 4. SEARCH CUSTOMER INFORMATION";
        cout << "\t\n 5. ROOM CHECK OUT";
        cout << "\t\n 6. GUEST DETAIL SUMMARY REPORT";
        cout << "\t\n 7. GENERATE BILL";
        cout << "\t\n 8. CALCULATE AVERAGE";
        cout << "\t\n 9. SYSTEM EXIT";
        cout << "\t\n\n SELECT OPTION: ";

        cin >> option;
        cin.ignore();

        system("cls");

        switch (option)
        {
            case 1:
                manageRoom(rooms, roomCount);
                saveRooms(rooms, roomCount);
                break;
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
            case 6:
                customerSummaryReport(rooms, roomCount);
                break;
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
            case 8:
                cout<<"do nothing"<< endl;
                break;
            case 9:
                cout << "\n\tCOME AGAIN ANYTIME SOON!"<<endl<<endl;
                break;
            default:
                cout << "\tPlease select the correct option!" << endl;
                break;
        }
    } while (option != 9);

    return 0;
}

Room addRoomNumber(int roomNumber) {
    Room room;
    room.roomNum = roomNumber;

    double roomPrice;
    do {
        cout << "\n\tRoom Type information (Tower View/Garden View/Water Chalet)(T/G/W): ";
        cin >> room.roomType;
        if (!isValidRoomType(room.roomType)){
            cout << "\n\tInvalid room type! Please enter T, G, or W only.";
        }
        else if (room.roomType == 'T') {
            roomPrice = 550.0;
        }
        else if (room.roomType == 'G') {
            roomPrice = 500.0;
        }
        else {
            roomPrice = 600.0;
        }
    } while (!isValidRoomType(room.roomType));

    do {
        cout << "\n\tRoom Size (Normal/Deluxe/Presidential)(N/D/P): ";
        cin >> room.roomSize;
        if(!isValidRoomSize(room.roomSize)){
            cout << "\n\tInvalid room size! Please enter N, D, or P only.";
        }
        else if (room.roomSize == 'D') {
            roomPrice += 100.0;
        }
        else if (room.roomSize == 'P') {
            roomPrice += 200.0;
        }
    } while(!isValidRoomSize(room.roomSize));

    do {
        cout << "\n\tBed Size information (Single Bed/Queen Bed/King Bed)(S/Q/K): ";
        cin >> room.bedType;
        if(!isValidBedType(room.bedType))
        {
            cout << "\n\tInvalid bed type! Please enter S, Q, or K only.";
        }
        else if (room.bedType == 'Q') {
            roomPrice += 50.0;
        }
        else if (room.bedType == 'K') {
            roomPrice += 100.0;
        }
    } while(!isValidBedType(room.bedType));

    room.roomRate = roomPrice;
    room.isBooked = false;

    cout << "\n\tThe Room has been added successfully!" << endl<<endl;
    cout << "\t\tPress'Enter' to main menu" << endl;
    cin.ignore();

    pause();
    system("cls");
    return room;
}

void displayRoom(const Room &room) {
    cout << "\n\tRoom Number: " << room.roomNum;
    cout << "\n\tRoom Type: " << room.roomType;
    cout << "\n\tRoom Size: " << room.roomSize;
    cout << "\n\tBed Size: " << room.bedType;
    cout << "\n\tRoom Rate Per night: " << room.roomRate;
}

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
            getline(cin, rooms[room].customerInfo.custName);
            cout << "\n\tEnter the Customer Address: ";
            getline(cin, rooms[room].customerInfo.custAddress);
            cout << "\n\tEnter Customer Phone Number: ";
            getline(cin, rooms[room].customerInfo.custPhoneNum);
            cout << "\n\tThe Room is booked starts from (YYYY-MM-DD): ";
            getline(cin, rooms[room].customerInfo.bookingStartFromDate);
            cout << "\n\tThe booking will end on (YYYY-MM-DD): ";
            getline(cin, rooms[room].customerInfo.bookingEndDate);
            cout << "\n\tCustomer Advance Payment: RM";
            cin >> rooms[room].customerInfo.advancePay;
            cin.ignore();

            rooms[room].isBooked = true;
            writeCustomerFileInfo(rooms[room]);

            cout << "\n\tThe Customer has been checked in successfully!";
            pause();
            system("cls");
            return;
        }
    }
    if (!roomFound) {
        cout << "\n\tSorry, the room number you are searching for is not found!";
        pause();
    }
}

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
    system("cls");
}

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

    system("cls");

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
            rooms[room].customerInfo = Customer();

            double bill = calculateBill(rooms[room]);
            cout << "\n\tThe total bill for the room is RM" << bill;

            updateCustomerFileInfo(rooms, roomCount);

            cout << "\n\tThe Customer has been checked out successfully!";
            pause();
            system("cls");
            return;
        }
    }
    cout << "\n\tSorry, the room number you are searching for is not found!";
    pause();
    system("cls");
}

void searchCustomerInfo(const Room rooms[], int roomCount, const string &name) {
    for (int room = 0; room < roomCount; room++) {
        if (rooms[room].isBooked && rooms[room].customerInfo.custName == name) {
            int daysStayed = calculateDaysStayed(rooms[room]);

            tm startDate, endDate;
            istringstream iss1(rooms[room].customerInfo.bookingStartFromDate);
            iss1 >> get_time(&startDate, "%Y-%m-%d");
            istringstream iss2(rooms[room].customerInfo.bookingEndDate);
            iss2 >> get_time(&endDate, "%Y-%m-%d");

            int remainingDays = calculateRemainingDays(startDate, endDate);
            cout << "\n\tCustomer Information:";
            cout << "\n\tCustomer Name: " << rooms[room].customerInfo.custName;
            cout << "\n\tCustomer Address: " << rooms[room].customerInfo.custAddress;
            cout << "\n\tCustomer Phone Number: " << rooms[room].customerInfo.custPhoneNum;
            cout << "\n\tBooking Number: " << rooms[room].customerInfo.bookingNum;
            cout << "\n\tBooking From: " << rooms[room].customerInfo.bookingStartFromDate;
            cout << "\n\tBooking To: " << rooms[room].customerInfo.bookingEndDate;
            cout << "\n\tDays Stayed: " << daysStayed;
            cout << "\n\tRemaining Days: " << remainingDays;
            cout << "\n\tAdvance Payment: RM" << rooms[room].customerInfo.advancePay;
            pause();
            system("cls");
            return;
        }
    }
    cout << "\n\tSorry, the customer information you are searching for is not found!";
    pause();
}

double calculateBill(const Room &room) {
    int daysStayed;

    tm startDate = {};
    istringstream startDateStream(room.customerInfo.bookingStartFromDate);
    startDateStream >> get_time(&startDate, "%Y-%m-%d");
    time_t startTime = mktime(&startDate);

    tm endDate = {};
    istringstream endDateStream(room.customerInfo.bookingEndDate);
    endDateStream >> get_time(&endDate, "%Y-%m-%d");
    time_t endTime = mktime(&endDate);

    daysStayed = difftime(endTime, startTime) / (24 * 60 * 60) + 1;

    double bill = daysStayed * room.roomRate - room.customerInfo.advancePay;
    return bill > 0 ? bill : 0;
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
    system("cls");
}

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
    system("cls");
}

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

void pause() {
    cout << "\n\t\tPress any key to continue..."<<endl<<endl;
    cin.get();
    cin.ignore();
}

void readRooms(Room rooms[], int &roomCount) {
    ifstream inFile("roomsInfo.txt");
    roomCount = 0;

    if (inFile.is_open()) {
        while (inFile >> rooms[roomCount].roomNum >> rooms[roomCount].roomType >> rooms[roomCount].roomSize
                      >> rooms[roomCount].bedType >> rooms[roomCount].roomRate >> rooms[roomCount].isBooked) {
            inFile.ignore();
            getline(inFile, rooms[roomCount].customerInfo.custName);
            getline(inFile, rooms[roomCount].customerInfo.custAddress);
            getline(inFile, rooms[roomCount].customerInfo.custPhoneNum);
            getline(inFile, rooms[roomCount].customerInfo.bookingStartFromDate);
            getline(inFile, rooms[roomCount].customerInfo.bookingEndDate);
            inFile >> rooms[roomCount].customerInfo.bookingNum >> rooms[roomCount].customerInfo.advancePay;
            inFile.ignore();
            roomCount++;
        }
        inFile.close();
    } else {
        cout << "\n\tUnable to open the rooms info file!";
    }
}

void saveRooms(Room rooms[], int roomCount) {
    ofstream outFile("roomsInfo.txt");

    if (outFile.is_open()) {
        for (int i = 0; i < roomCount; ++i) {
            outFile << rooms[i].roomNum << ' ' << rooms[i].roomType << ' ' << rooms[i].roomSize << ' '
                    << rooms[i].bedType << ' ' << rooms[i].roomRate << ' ' << rooms[i].isBooked << '\n'
                    << rooms[i].customerInfo.custName << '\n'
                    << rooms[i].customerInfo.custAddress << '\n'
                    << rooms[i].customerInfo.custPhoneNum << '\n'
                    << rooms[i].customerInfo.bookingStartFromDate << '\n'
                    << rooms[i].customerInfo.bookingEndDate << '\n'
                    << rooms[i].customerInfo.bookingNum << ' ' << rooms[i].customerInfo.advancePay << '\n';
        }
        outFile.close();
    } else {
        cout << "\n\tUnable to open the rooms info file for saving!";
    }
}

void readCustomers(Customer customers[], int &count) {
    ifstream inFile("customerinfo.txt");

    count = 0;
    if (inFile.is_open()) {
        string line;
        while (getline(inFile, line)) {
            istringstream iss(line);
            if (iss >> customers[count].custName >> customers[count].bookingNum >> customers[count].numberOfNights >> customers[count].advancePay) {
                count++;
            }
        }
    }

    inFile.close();
}
