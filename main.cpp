#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>
#include <limits>
#include <sstream>
#include <vector>
using namespace std;

class Transaction
{
public:
    string payment_method, card_number, confirmation;
    string response;
    int pin;

    void details(int bill)
    {
        cout << "Enter your Transaction details " << endl;
        cout << "Kindly Enter your Payment method :" << endl;
        cin >> payment_method;

        // Account number validation loop
        while (true)
        {
            cout << "Enter your card number/account number (10 to 16 digits):" << endl;
            cin >> card_number;

            if (card_number.length() >= 10 && card_number.length() <= 16)
            {
                break;
            }
            else
            {
                cout << "Invalid account number! Please enter a number between 10 and 16 digits." << endl;
            }
        }

        // Pin validation loop
        while (true)
        {
            cout << "Enter the pin (4 digits) please :" << endl;
            cin >> pin;

            if (pin >= 1000 && pin <= 9999) // Check if the pin is a 4-digit number
            {
                break;
            }
            else
            {
                cout << "Invalid pin! Please enter a 4-digit pin." << endl;
            }
        }

        cout << "Your total bill is " << bill << endl;
        cout << "Confirm that you want to pay an amount of " << bill << endl;

        do
        {
            cin >> confirmation;
            if (confirmation == "Yes" || confirmation == "yes")
            {
                cout << "An amount of " << bill << " is deducted from your account " << endl;
            }
            else if (confirmation == "No" || confirmation == "no")
            {
                cout << "Transaction failed " << endl;
                cout << "Ride canceled" << endl;
            }
            else
            {
                cout << "Invalid entry! Try Again" << endl;
            }
        } while (confirmation != "Yes" && confirmation != "yes" && confirmation != "No" && confirmation != "no");
    }

    void complaints()
    {
        int answer;
        cout << "Welcome to the Complaint Section " << endl;
        cout << "1) Want to Submit your complaint" << endl;
        cout << "2) Want to read the previous complaints " << endl;
        cin >> answer;
        if (answer == 1)
        {
            cout << "What's your complaint/feedback:";

            cin.ignore();
            getline(cin, response);
            ofstream Project("file.txt", ios::app); // Open file in append mode
            Project << response << endl; // Add newline to separate complaints
            Project.close();

            cout << "Your complaint:" << endl;
            cout << response << endl;
            cout << "Saved! Thanks for your suggestion." << endl;
        }
        else if (answer == 2)
        {
            ifstream reading("file.txt");
            string reader;
            cout << "The previous complaints are:" << endl;
            while (getline(reading, reader))
            {
                cout << reader << endl;
            }
            reading.close();
        }
    }
};

void BZB_main(int totalcost)
{
    char complain;
    Transaction obj1;
    obj1.details(totalcost);
    cout << "Do you have any complaint y/n" << endl;
    cin >> complain;
    if (complain == 'y')
    {
        obj1.complaints();
    }
}



class customer
{
public:
    string destination,vehicle,date;
    int amount,Id,Did;
    void set_data(string goal,int totalcost,string gari,string dat,int id,int did)
    {

        destination = goal;
        amount = totalcost;
        vehicle = gari;
        date = dat;
        Id = id;
        Did = did;
        cout << "added successfully" << endl << endl;

    }
    void display()
    {
       cout << "destination(km): " << destination << endl;
       cout << "amount: " << amount << endl;
       cout << "vehicle: " << vehicle << endl;
       cout << "Date: " << date << endl;
       cout << "User ID: " << Id << endl;
       cout << "Driver ID: " << Did << endl;
    }
};

class Data_in : public customer
{
public:
    void write_to_file(ofstream& file)
    {
        file << destination << endl;
        file << amount << endl;
        file << vehicle << endl;
        file << date << endl;
        file << Id << endl;
        file << Did << endl;
    }
    void read_from_file(ifstream& file)
    {
        getline(file, destination);
        file >> amount;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(file, vehicle);
        getline(file, date);
        file >> Id;
        file.ignore(numeric_limits<streamsize>::max(), '\n');
        file >> Did ;
        file.ignore(numeric_limits<streamsize>::max(), '\n');

    }
};

class Manager
{
private:
    customer **arr;
    int capacity;
    int length;
    void resizee()
    {
        int new_capacity = capacity * 2;
        customer **new_array = new customer *[new_capacity];
        for (int i = 0; i < length; i++)
        {
            new_array[i] = arr[i];
        }
        delete[] arr;
        arr = new_array;
        capacity = new_capacity;
    }

public:
    Manager()
    {
        capacity = 2;
        length = 0;
        arr = new customer *[capacity];
    }
    ~Manager()
    {
        for (int i = 0; i < length; i++)
        {
            delete arr[i];
        }
        delete[] arr;
    }
    void add_data( string goal, int cost, string gari,string date,int id,int Did)
    {

        if (length >= capacity)
        {
            resizee();
        }
        Data_in *data = new Data_in();
        data->set_data(goal, cost, gari, date,id,Did);
        arr[length] = data;
        length++;
        ofstream file("customer_history.txt", ios::app);
        data->write_to_file(file);
        file.close();
    }
    void print()
    {
        ifstream file("customer_history.txt");
        if (!file)
        {
            cout << "\n\t\t\t\t file not open successfully" << endl;
            return;
        }
        file.seekg(0, ios::end);
        if (file.tellg() == 0)
        {
            cout << "\n\t\t\t\t No customer history available." << endl;
            file.close();
            return;
        }
        file.seekg(0, ios::beg);
        while (file)
        {
            Data_in data;
            data.read_from_file(file);
            if (file)
            {
                data.display();
                cout << endl;
            }
        }
        file.close();
    }
    void search_by_id(int id)
    {
        ifstream file("customer_history.txt");
        if (!file)
        {
            cout << "file not open successfully" << endl;
            return;
        }
        file.seekg(0, ios::end);
        if (file.tellg() == 0)
        {
            cout << "No customer history available." << endl;
            file.close();
            return;
        }
        file.seekg(0, ios::beg);
        bool found = false;
        while (file)
        {
            Data_in data;
            data.read_from_file(file);
            if (file && data.Id == id)
            {
                data.display();
                cout << endl;
                found = true;
            }
        }
        cout << endl;
        if (!found)
        {
            cout << "No customer found with ID: " << id << endl;
        }
        file.close();
    }
    void search_by_id_driver(int id)
    {
        ifstream file("customer_history.txt");
        if (!file)
        {
            cout << "file not open successfully" << endl;
            return;
        }
        file.seekg(0, ios::end);
        if (file.tellg() == 0)
        {
            cout << "No driver history available." << endl;
            file.close();
            return;
        }
        file.seekg(0, ios::beg);
        bool found = false;
        while (file)
        {
            Data_in data;
            data.read_from_file(file);
            if (file && data.Did == id)
            {
                data.display();
                cout << endl;
                found = true;
            }
        }
        cout << endl;
        if (!found)
        {
            cout << "No customer found with ID: " << id << endl;
        }
        file.close();
    }


    void clear_data()
    {
        ofstream file("customer_history.txt", ios::trunc);
        file.close();
        cout << "All customer history has been cleared." << endl;
        cout << endl;
    }
};

void history(string destination,int totalcost,string vehicle, string date, int id,int Did)
{

    Manager M;
    int choice;
    M.add_data(destination,totalcost,vehicle,date,id,Did);  // for adding the customer history.
    cout << "\n\t\t\t\t 1. for inspection by id" << endl;
    cout << "\n\t\t\t\t 2. for clearing whole history" << endl;
    cout << "\n\t\t\t\t 3. for exit" << endl;
    cout << endl;

    do
    {
        cout << "\n\t\t\t\t Please! Enter the activity you want to perform: ";
        cin >> choice;
        if(choice == 1)
        {

             M.search_by_id(id);
        }
        else if(choice == 2)
        {
            M.clear_data();
        }
        else if (choice == 3)
        {
            cout << "\n\t\t\t\t Exiting...." << endl;
        }
        else
        {
            cout << "\n\t\t\t\t Wrong input" << endl;
        }
    } while (choice != 3);
}

int location(int id );
class bike {
    int num;
public:
    void Menu()
    {
        cout << "Showing bike menu " << endl;
        cout << " Bike Name " << " Model " << " Rent per Km " << endl;
        cout << "1. CG 125 " << "  2022 " << "       50 " << endl;
        cout << "2. Pridor " << "  2023 " << "       40 " << endl;
        cout << "3. CD 70 " << "   2020 " << "       40 " << endl;
    }
    void booking(int valid, int km , string destination,int id)
    {
        string date;
        int ID = id ,Did;
        cout << id << endl;
        getch();
        cout << "For Choosing your ride enter code number ";
        cin >> num;
        int totalcost = 0;
        if (num == 1)
        {
            cout << "We are going to confirm your order for CG 125 " << endl;
            totalcost = km * 50;
            cout << "Total cost " << totalcost << endl;
            char confirm;
            cout << "Confirm booking? (y/n): ";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y')
            {
                cout << "Enter the ID of driver " << endl;
                cin>> Did;
                cout << "Enter date dd/mm/yyyy " << endl;
                cin >> date ;
                cout << "Booking confirmed." << endl;
                BZB_main(totalcost);
                 history(destination,totalcost,"125",date,ID,Did);


            }
            else
            {
                cout << "Booking cancelled." << endl;
                location(ID);
                valid = 1;

            }
        }
        else if (num == 2)
        {
            cout << "We are going to confirm your order for Pridor " << endl;
            totalcost = km * 40;
            cout << "Total cost " << totalcost << endl;
            char confirm;
            cout << "Confirm booking? (y/n): ";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y')
            {
                cout << "Enter the ID of driver " << endl;
                cin>> Did;
                cout << "Enter date dd/mm/yyyy " << endl;
                cin >> date ;
                cout << "Booking confirmed." << endl;
                 BZB_main(totalcost);
                 history(destination,totalcost,"pridor",date,ID,Did);
            }
            else
            {
                cout << "Booking cancelled." << endl;
                location(ID);
                valid = 1;
            }
        }
        else if (num == 3)
        {
            cout << "We are going to confirm your order for CD 70 " << endl;
            totalcost = km * 40;
            cout << "Total cost " << totalcost << endl;
            char confirm;
            cout << "Confirm booking? (y/n): ";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y')
            {
                cout << "Enter the ID of driver " << endl;
                cin>> Did;
                cout << "Enter date dd/mm/yyyy " << endl;
                cin >> date ;
                cout << "Booking confirmed." << endl;
                 BZB_main(totalcost);
                 history(destination,totalcost,"70",date,ID,Did);

            }
            else
            {
                cout << "Booking cancelled." << endl;
                location(ID);
                valid = 1;
            }
        }
        else
        {
            cout << "Invalid key " << endl;
            valid = 1;
        }
    }
};

class Car {
    int num;
public:
    void Menu()
    {
        cout << "Showing menu of cars " << endl;
        cout << " Car name " << "         Model " << " Rent per Km " << endl;
        cout << "1. Toyota Corolla " << " 2018 " << "       90 " << endl;
        cout << "2. Honda Civic " << "    2022 " << "       110 " << endl;
        cout << "3. Toyota Altis " << "   2014 " << "       100 " << endl;
        cout << "4. Suzuki Alto " << "    2023 " << "       70 " << endl;
    }
    void booking(int valid,int km,string destination,int id )
    {
        string date;
        int ID=id,Did;
        cout << "For Choosing your ride enter code number ";
        cin >> num;
        int totalcost = 0 ;
        if (num == 1)
        {
            cout << "We are going to confirm your order for Toyota Corolla " << endl;
            totalcost = km*90;
            cout << "Total cost " << totalcost << endl;
            char confirm;

            cout << "Confirm booking? (y/n): ";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y')
            {
                cout << "Enter the ID of driver " << endl;
                cin>> Did;
                cout << "Enter date dd/mm/yyyy " << endl;
                cin >> date ;
                cout << "Booking confirmed." << endl;
                 BZB_main(totalcost);
                 history(destination,totalcost,"corolla",date,ID,Did);
            }
            else
            {
                cout << "Booking cancelled." << endl;
                location(ID);
                valid = 1;
            }
             }
        else if (num == 2)
        {
            cout << "We are going to confirm your order for Honda Civic " << endl;
             totalcost = km*110;
            cout << "Total cost " << totalcost << endl;
            char confirm;
            cout << "Confirm booking? (y/n): ";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y')
            {
                cout << "Enter the ID of driver " << endl;
                cin>> Did;
                cout << "Enter date dd/mm/yyyy " << endl;
                cin >> date ;
                cout << "Booking confirmed." << endl;
                 BZB_main(totalcost);
                 history(destination,totalcost,"Civic",date,ID,Did);
            }
            else
            {
                cout << "Booking cancelled." << endl;
              location(ID);
                valid = 1;
            }
        }
        else if (num == 3)
        {
            cout << "We are going to confirm your order for Toyota Altis " << endl;
             totalcost = km*100;
            cout << "Total cost " << totalcost << endl;
            char confirm;
            cout << "Confirm booking? (y/n): ";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y')
            {
                cout << "Enter the ID of driver " << endl;
                cin>> Did;
                cout << "Enter date dd/mm/yyyy " << endl;
                cin >> date ;
                cout << "Booking confirmed." << endl;
                 BZB_main(totalcost);
                 history(destination,totalcost,"Altis",date,ID,Did);
            }
            else
            {
                cout << "Booking cancelled." << endl;
              location(ID);
                valid = 1;
            }
        }
        else if (num == 4)
        {
            cout << "We are going to confirm your order for Suzuki Alto " << endl;
             totalcost = km*70;
            cout << "Total cost " << totalcost << endl;
            char confirm;
            cout << "Confirm booking? (y/n): ";
            cin >> confirm;
            if (confirm == 'y' || confirm == 'Y')
            {
                cout << "Enter the ID of driver " << endl;
                cin>> Did;
                cout << "Enter date dd/mm/yyyy " << endl;
                cin >> date ;
                cout << "Booking confirmed." << endl;
                 BZB_main(totalcost);
                 history(destination,totalcost,"Alto",date,ID,Did);
            }
            else
            {
                cout << "Booking cancelled." << endl;
               location(ID);
                valid = 1;
            }
        }
        else
        {
            cout << "Invalid key " << endl;
            valid = 1;
        }
    }
};

void ride(int km,string destination,int id)
{
    int R, valid = 0;
    int Km = km;
    string Destination = destination ;
    cout << "Welcome To menu " << endl;
    do {
        cout << "Please Enter 0 for bike ride and 1 for car ride ";
        cin >> R;
        if (R == 0)
        {
            bike obj;
            obj.Menu();
            obj.booking(valid,Km,Destination,id);
        }
        else if (R == 1)
        {

            Car obj;
            obj.Menu();
            obj.booking(valid,km,Destination,id);
        }
        else
        {
            valid = 1;
        }
    } while (valid == 1);
}

int location(int id)
{
    int select;
    cout << endl << "Displaying locations" << endl;
    ifstream file("places_from_mianwali.txt");
    ifstream file1("Kms.txt");
    if (!file.is_open() || !file1.is_open())
    {
        cout << "Error opening the file(s)." << endl;
        return 1;
    }


    string line, line1;
    string locations[11];
    int distances[11];
    int i = 0;
    while (getline(file, line) && getline(file1, line1) && i < 11)
    {
        cout << i + 1 << ". " << line << endl;
        locations[i] = line;
        distances[i] = stoi(line1); // Convert the string to integer
        i++;
    }
    file.close();
    file1.close();

    cout << "Select your destination (enter the number): ";
    cin >> select;

    if (select < 1 || select > i)
    {
        cout << "Invalid selection." << endl;
        return 1;
    }

    cout << "You selected: " << locations[select - 1] << endl;

    ride(distances[select - 1],locations[select - 1],id); // Pass the corresponding distance and destination to the ride function


    return 0;
}




vector<string> splitString(const string& str) {
    vector<string> result;
    stringstream ss(str);
    string item;

    while (getline(ss, item, ',')) {
        result.push_back(item);
    }

    return result;
}

class RideRecordSystem {
 protected:
  string username;
  string password;
};

// for driver
void sea(int id, bool& valid)
{
    fstream file("driver.txt");
    string line;
    while (getline(file, line))
    {
        vector<string> result = splitString(line);
        // Assuming splitString returns at least two elements
        if (result.size() >= 2 && result[1] == to_string(id))
        {
            valid = 1;
            return; // Exit the function early since we found a match
        }
    }
    valid = 0; // If no match is found
}

class DriverAccount : public RideRecordSystem {
private:
    bool valid = 0 ,valid1 = 0 ;
    string name;
    int ID;
    string cnic;
    string licenceNumber;
    string city;
    string province;
    string driverPassword;
    string confirmPassword;

public:
    void createAccount() {

        ofstream file("driver.txt", ios::app);
        system("cls");
        cout << "\n\n\t\t\t\tEnter Driver Details\n";
        cout << "\n\t\t\t\tName: ";
        cin.ignore();
        getline(cin, name);
        do{
             cout << "\n\t\t\t\t Enter UNIQUE ID: ";
                  cin>>ID;
                sea(ID,valid);
        }while(valid==1 );


        cout << "\n\t\t\t\tCNIC Number: ";
        cin >> cnic;
        cout << "\n\t\t\t\tLicence Number: ";
        cin >> licenceNumber;
        cout << "\n\t\t\t\tCity: ";
        cin.ignore();
        getline(cin, city);
        cout << "\n\t\t\t\tProvince: ";
        getline(cin, province);
        cout << "\n\t\t\t\tPassword: ";
        cin >> driverPassword;
up:
        cout << "\n\t\t\t\tConfirm Password: ";
        cin >> confirmPassword;

        if (driverPassword != confirmPassword) {
            cout << "\n\t\t\tPasswords do not match. Please try again.";
            getch();
            goto up;
            return;
        }
        ifstream infile("driver.txt");
        bool file_has_content = infile.peek() != ifstream::traits_type::eof();
        infile.close();

        if(file_has_content)
        {
            file << endl;
        }
        file << name << "," <<ID<<","<< cnic << "," << licenceNumber << "," << city << "," << province << "," << driverPassword ;
        file.close();
        cout << "\n\n\t\t\tDriver account created successfully!";
        getch();
    }

bool login() {
    while(1){
    system("cls");
    string loginName, loginPassword;
    cout << "\n\n\t\t\t\tDriver Login\n";
    cout << "\n\t\t\t\tName: ";
    cin.ignore();
    getline(cin, loginName);
    cout << "\n\t\t\t\tPassword: ";
    cin >> loginPassword;
    cout << "\n\t\t\t\tEnter Unique Id " << endl;
    cin >> ID;
    ifstream file("driver.txt");
    string line;
    while(getline(file,line))
    {
        vector<string> result = splitString(line);
        if(result[0] == loginName && result[6] == loginPassword)
        {

            cout << "\n\t\t\t\tLogin Successfully"<<endl;
            char History_check;
            cout << "\n\t\t\t\tDo you want to check your history(y/n): ";
            cin >> History_check;
            if (History_check == 'y')
            {
                Manager His;
                cout << "\n\t\t\t\tPlease give your identity: ";

                His.search_by_id_driver(ID);
                getch();
            }
            else
            {
                 return true;
                 system("cls");
            }

        }
        else{
                continue;
            return false;
    }
}
}
}
};

void sea1(int id, bool& valid)
{
    fstream file("passenger.txt");
    string line;
    while (getline(file, line))
    {
        vector<string> result = splitString(line);
        // Assuming splitString returns at least three elements
        if (result.size() >= 3 && result[2] == to_string(id))
        {
            valid = true;
            return; // Exit the function early since we found a match
        }
    }
    valid = false; // If no match is found
}


class PassengerAccount : public RideRecordSystem {
private:
    bool valid = 0 ;
    string name;
    string cnic;
    int Id,ID;
    string passengerPassword;
    string confirmPassword;

public:
    void createAccount()
    {
        system("cls");
        ofstream file1("passenger.txt" , ios :: app);
        cout << "\n\n\t\t\t\tEnter Passenger Details\n";
        cout << "\n\t\t\t\tName: ";
        cin.ignore();
        getline(cin, name);
         do{
        cout << "\n\t\t\t\tEnter UNIQUE ID: ";
         cin>>Id;
         sea1(Id,valid);
        }while(valid==1 );
        cout << "\n\t\t\t\tCNIC Number: ";
        cin >> cnic;

         cin.ignore();
        cout << "\n\t\t\t\tPassword: ";
        cin >> passengerPassword;
position:
        cout << "\n\t\t\t\tConfirm Password: ";
        cin >> confirmPassword;

    if (passengerPassword != confirmPassword)
        {
            cout << "\n\t\t\tPasswords do not match. Please try again.";
            getch();
    goto position;
            return;
        }

        ifstream infile("passenger.txt");
        bool file_has_content = infile.peek() != ifstream::traits_type::eof();
        infile.close();

        if(file_has_content)
        {
            file1 << endl;
        }
        file1 << name << "," << cnic << "," << Id<< "," << passengerPassword ;
        file1.close();

        cout << "\n\n\t\t\tPassenger Account Created Successfully!";
        location(Id);


        getch();
    }

    bool login() {
        system("cls");
        string loginName, loginPassword;
        cout << "\n\n\t\t\t\tPassenger Login\n";
        cout << "\n\t\t\t\tName: ";
        cin.ignore();
        getline(cin, loginName);
        cout << "\n\t\t\t\tPassword: ";
        cin >> loginPassword;
        cout << "\n\t\t\t\tEnter Unique Id: ";
        cin >> ID;

        ifstream file("passenger.txt");
    string line;
    while(getline(file,line))
    {
        vector<string> result = splitString(line);
        if(result[0] == loginName && result[3] == loginPassword)
        {
            cout << "Succesful Passenger Login!";
            getch();
             location(ID);
            return true;
             system("cls");


        }
        else{
                continue;
            return false;
        }
}
    }
};
int Asim()
{
     DriverAccount driverAccount;
    PassengerAccount passengerAccount;

    while (true) {
        system("cls");
        cout << "\n\n\t\t----------------------------------------------------------------------------------";
        cout << "\n\t\t\t\t               WELCOME TO YAARZ RIDER SYSTEM     ";

        cout << "\n\t\t\t\t               OUR AIM TO FACILITATE YOU!!!";

        cout << "\n\t\t----------------------------------------------------------------------------------";
        cout << "\n\n\n\n\n\t\t\t\t1. USE AS A DRIVER\n";
        cout << "\n\t\t\t\t2. USE AS A PASSENGER\n";
        cout << "\n\t\t\t\t3. Exit\n";
        cout << "\n\n\n \n\t\t\t\tChoose from 1 to 3: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            system("cls");
            cout << "\n\n\t\t\t\t1. New Driver\n";
            cout << "\t\t\t\t2. Existing Driver Login\n";
            cout << "\n\t\t\t\tChoose from 1 or 2: ";
            int driverChoice;
            cin >> driverChoice;

            if (driverChoice == 1) {
                driverAccount.createAccount();
            } else if (driverChoice == 2) {
                if (driverAccount.login()) {
                    system("cls");
                    cout << "Successful!!";
                    string f;
                    cin >> f;
                }
            } else {
                cout << "\t\t\tInvalid entry. Please enter the correct option :)";
                getch();
            }
            break;
        }
        case 2: {
            system("cls");
            cout << "\n\n\t\t\t\t1. New Passenger\n";
            cout << "\t\t\t\t2. Existing Passenger Login\n";
            cout << "\n\t\t\t\tChoose from 1 or 2: ";
            int passengerChoice;
            cin >> passengerChoice;

            if (passengerChoice == 1) {
                passengerAccount.createAccount();
            }
            else if (passengerChoice == 2)
                {
                if (passengerAccount.login()) {
                 }
            }
            else {
                cout << "\t\t\tInvalid entry. Please enter the correct option :)";
                getch();
            }
            break;
        }
        case 3:
            cout << "\n\n\n\n\n\t\t\t\tTHANK YOU FOR USING & VISITING YAARZ RIDER SYSTEM ";
            getch();
            return 0;
        default:
            cout << "\t\t\tInvalid entry. Please enter the correct option :)";
            getch();
            break;
        }
    }
}

int main()
{
Asim();



    return 0;
}
