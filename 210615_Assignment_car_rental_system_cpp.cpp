#include <bits/stdc++.h>
using namespace std;

/*
    READ ME : My program is an interactive car rental system made by me. There are Customer, Employees, and Manager. My program satisfies
    all the functionalities expected by the problem statement of the assignment. Program is self explanatory but some key points
    regarding the program are - 

->  It does not have a system to check how much money individual holds. If someone wants to rent a car, it is already expected that 
    user has enough money to rent a car. In case of customer, Rs. 1000 are deducted and it will get printed on the terminal when
    customer rents a car. In case of Employee, Rs. 850 are deducted(15% discount) and it will also be shown on the terminal.
->  At the start of program, no one has rented any car, but some customer have bad customer record just for the sake of
    our program to satisy all the requirements. I have taken good customer record as an integer. If someone has customer record>=0 
    I have taken the convention that customer is good. If someone has bad record then their customer record < 0. Bad customers 
    are not allowed to rent a car however they can return a car if they have rented earlier.
->  Car rental duration in my program is 7 days (Real world), if a user returns car after due date, their customer record is 
    updated as bad customer and fine is added. However if a user returns a car before or on due date, they are seen
    as good user(customer/employee).
->  Just like customer record, employee record is also maintained in my program. 
->  All the databases are in manager class and encapsulated. I will now give an example of how databases are in my program : 
    vector<User> customerDatabase = {
        {"user1", "pass1", 0, 0, 1};
                           |  |  |
            ...............|  |  |......................
            |                 |                        |
        cars rented        Dues Pending            Customer record

    here user1 is username or userid, pass1 is password for that respective username, first 0 is for cars rented. second 0 is for dues 
    pending. third 1 is the customer record as i explained, >=0 means good and <0 means bad.
->  If a new user is added, they are registered with 0,0,0 (for respective psitions after userid and password as described above)
    actually manager is asked for what to fill, but it is expected by the manager to follow the above convention.      
->  In manager class inside the database you can see password and userid for logging in as customer or employee. But to save your time 
    you can start with following data , userid for customer : user1 and password is pass1, for employee :emp1 and pass1, 
    for manager : manager1 , password is pass1.
->  Due to security reasons, the customer and employee will get logged out after performing their operation (renting or returning car)
    However, Manager wont be logged out. This is the advantage, only  Manager gets in my program.
->  As stated in the problem statement, I have started with 5 customer, 5 cars, 5 employees and 1 Manager.    
->  Cars are stated as car name, year and condition. However renting any kind of car will deduct same amount of money. Cars are 
    available in 3 conditions : Good, Mid and Bad and i know these terms are self explanatory.
->  When renting a car, it will be asked : " Enter the number of the car you want to rent "  -> in this case you are expected
    to enter the serial number of car and not the model year. For example :
    1. Name: Ford, Year: 1980, Condition: Bad
    2. Name: Toyota, Year: 2005, Condition: Mid

    You are expected to enter 1 to rent Ford and 2 to rent Toyota and so on.
->  When returning a car, it is expected that user is honest and enters right details of the cars. 
->  I have mostly tested it, but in case it fails on some input, I am sorry in advance. But I would appreciate the feedback
    so that i can improve as a programmer :)

                           That's all !!! Enjoy this car rental system made by-
                           Bhavishya Prakash Singh
                           210267
*/

class Car_available;

struct User
{
    string userid;
    string pass;
    int rentedCars;
    int fineAmount;
    int goodCustomer;
};

class Car_available
{
public:
    struct Car
    {
        string name;
        int year;
        string condition;
    };

    vector<Car> cars_available = {
        {"Ford", 1980, "Bad"},
        {"Toyota", 2005, "Mid"},
        {"BMW", 1995, "Good"},
        {"Mercedes", 2023, "Good"},
        {"Audi", 2003, "Bad"}};

    bool areCarsAvailable()
    {
        return !cars_available.empty();
    }

    void printAvailableCars()
    {
        if (!cars_available.empty())
        {
            cout << "Available Cars:" << endl;
            int i = 1;
            for (auto &car : cars_available)
            {
                cout << i << ". Name: " << car.name << ", Year: " << car.year << ", Condition: " << car.condition << endl;
                i++;
            }
        }
        else
        {

            cout << "No cars available." << endl;
        }
    }

    void removeCar(int index)
    {
        if (index >= 1 && index <= cars_available.size())
        {
            cars_available.erase(cars_available.begin() + index - 1);
        }
        else
        {
            cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid index. Car not removed." << endl;
        }
    }
};

class RentalRecord
{
private:
    string carName;
    string customerId;
    time_t rentalDate;
    time_t returnDate;

public:
    RentalRecord(string &car, string &customer) : carName(car), customerId(customer)
    {
        rentalDate = time(nullptr); 
        returnDate = 0;             
    }

    string getCarName() { return carName; }
    string getCustomerId() { return customerId; }
    time_t getRentalDate() { return rentalDate; }
    time_t getReturnDate() { return returnDate; }

    void setReturnDate() { returnDate = time(nullptr); }

    void printRentalRecord()
    {
        cout << "Car Name: " << carName << ", ";
        cout << "Customer ID: " << customerId << ", ";
        cout << "Rental Date: " << ctime(&rentalDate);
        if (returnDate != 0)
        {
            cout << "Return Date: " << ctime(&returnDate);
        }
        else
        {
            cout << "Return Date: Not returned yet";
        }
    }
};

class Manager
{
private:
    vector<User> existingUsers = {
        {"manager1", "pass1", 0, 0, 0}};

    vector<User> customerDatabase = {
        {"user1", "pass1", 0, 0, 1},
        {"user2", "pass2", 0, 100, -1},
        {"user3", "pass3", 0, 0, 1},
        {"user4", "pass4", 0, 0, 1},
        {"user5", "pass5", 0, 2000, -20}};

    vector<User> employeeDatabase = {
        {"emp1", "pass1", 0, 0, 1},
        {"emp2", "pass2", 0, 100, -1},
        {"emp3", "pass3", 0, 0, 1},
        {"emp4", "pass4", 0, 0, 1},
        {"emp5", "pass5", 0, 2000, -20}};

    vector<RentalRecord> rentalRecords;

    Car_available &carAvailability;

public:
    Manager(Car_available &cars) : carAvailability(cars) {}
    vector<User> &getExistingUsers()
    {
        return existingUsers;
    }
    vector<User> &getExistingCustomers()
    {
        return customerDatabase;
    }
    vector<User> &getExistingEmployee()
    {
        return employeeDatabase;
    }
    void addUserToCustomerDatabase(User &user)
    {
        customerDatabase.push_back(user);
    }
    void addUserToEmployeeDatabase(User &user)
    {
        employeeDatabase.push_back(user);
    }
    void addCustomer(const string &username, const string &pass, int car_rented, int Dues, int customerrecord)
    {
        User newUser = {username, pass, car_rented, Dues, customerrecord};
        customerDatabase.push_back(newUser);
    }
    void deleteCustomer(const string &userid)
    {
        auto it = customerDatabase.begin();
        while (it != customerDatabase.end())
        {
            if (it->userid == userid)
            {
                it = customerDatabase.erase(it);
                cout << "Customer deleted successfully!" << endl;

                return;
            }
            else
            {
                ++it;
            }
        }
        cout << "Customer not found." << endl;
    }
    void addEmployee(const string &username, const string &pass, int car_rented, int Dues, int employeerecord)
    {
        User newUser = {username, pass, car_rented, Dues, employeerecord};
        employeeDatabase.push_back(newUser);
    }
    void deleteEmployee(const string &userid)
    {
        auto it = employeeDatabase.begin();
        while (it != employeeDatabase.end())
        {
            if (it->userid == userid)
            {
                it = employeeDatabase.erase(it);
                cout << "Employee deleted successfully!" << endl;
                return;
            }
            else
            {
                ++it;
            }
        }
        cout << "Employee not found." << endl;
    }

    void registerUser()
    {
        cout << "Create your username/user id: ";
        string userid;
        cin >> userid;
        if (isUserIdAvailable(userid))
        {
            cout << "User ID '" << userid << "' is available." << endl;
            cout << "Create your password: ";
            string pass;
            cin >> pass;
            existingUsers.push_back({userid, pass, 0, 0, 1});
            cout << "User successfully registered!" << endl;
        }
        else
        {
            cout << "User ID '" << userid << "' is not available." << endl;
        }
    }

    void printRentalRecords()
    {
        cout << "Rental Records:" << endl;
        for (auto &record : rentalRecords)
        {
            record.printRentalRecord();
            cout << endl;
        }
    }
    void loginUser()
    {
        cout << "Enter your username: ";
        string userid;
        cin >> userid;
        cout << "Enter your password: ";
        string pass;
        cin >> pass;
        if (isUserAuthenticated(userid, pass))
        {

            cout << "Welcome, " << userid << "🫡!" << endl;
            for (auto &user : existingUsers)
            {
                if (user.userid == userid)
                {
                    while (true)
                    {
                        cout << "What would you like to do?" << endl;
                        cout << "Press 1 to see available cars, Press 2 to see list of rented cars and their users, Press 3 to add/delete/update customer, Press 4 to add/delete/update employee, Press 5 to add/deleted/update cars, Press 6 or any other key to log out !!!" << endl;
                        char button;
                        cin >> button;
                        if (button == '1')
                        {
                            carAvailability.printAvailableCars();
                        }
                        else if (button == '2')
                        {
                            printRentalRecords();
                        }
                        else if (button == '3')
                        {
                            cout << "Press 1 to add a customer, Press 2 to delete a customer" << endl;
                            int customerChoice;
                            cin >> customerChoice;
                            if (customerChoice == 1)
                            {
                                string username, pass;
                                int car_rented, Dues, customerrecord;
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Enter username: ";
                                cin >> username;
                                cout << "Enter password: ";
                                cin >> pass;
                                cout << "Enter number of cars rented: ";
                                cin >> car_rented;
                                cout << "Enter dues: ";
                                cin >> Dues;
                                cout << "Enter customer record: ";
                                cin >> customerrecord;
                                addCustomer(username, pass, car_rented, Dues, customerrecord);

                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            }
                            else if (customerChoice == 2)
                            {
                                cout << "Enter the userid of the customer to delete: ";
                                string userid;
                                cin >> userid;
                                deleteCustomer(userid);
                            }
                            else
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Invalid choice." << endl;
                            }
                        }
                        else if (button == '4')
                        {
                            cout << "Press 1 to add an Employee, Press 2 to delete an Employee" << endl;
                            int employeeChoice;
                            cin >> employeeChoice;
                            if (employeeChoice == 1)
                            {
                                string username, pass;
                                int car_rented, Dues, employeerecord;
                                cout << "Enter username: ";
                                cin >> username;
                                cout << "Enter password: ";
                                cin >> pass;
                                cout << "Enter number of cars rented: ";
                                cin >> car_rented;
                                cout << "Enter dues: ";
                                cin >> Dues;
                                cout << "Enter customer record: ";
                                cin >> employeerecord;
                                addEmployee(username, pass, car_rented, Dues, employeerecord);
                            }
                            else if (employeeChoice == 2)
                            {
                                cout << "Enter the userid of the employee to delete: ";
                                string userid;
                                cin >> userid;
                                deleteEmployee(userid);
                            }
                            else
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Invalid choice." << endl;
                            }
                        }
                        else if (button == '5')
                        {
                            cout << "Press 1 to Add a car, 2 to delete a car" << endl;
                            int choice;
                            cin >> choice;
                            if (choice == 1)
                            {
                                
                                cout << "Enter name of the New Car" << endl;
                                string NewCarName;
                                cin >> NewCarName;
                                Car_available::Car returnedCar;
                                returnedCar.name = NewCarName;
                                cout << "Enter the year of the car: "<<endl;
                                cin >> returnedCar.year;
                                cout << "Enter the condition of the car: "<<endl;
                                cin >> returnedCar.condition;
                                carAvailability.cars_available.push_back(returnedCar);
                                cout << "Car added successfully!" << endl;
                                
                            }
                            else if (choice == 2)
                            {
                                //
                                if (carAvailability.areCarsAvailable())
                                {
                                    carAvailability.printAvailableCars();
                                    int carChoice;
                                    cout << "Enter the number of the car you want to rent: ";
                                    cin >> carChoice;
                                    if (carChoice >= 1 && carChoice <= carAvailability.cars_available.size())
                                    {
                                        carAvailability.removeCar(carChoice);
                                        cout << "Car deleted successfully!" << endl;
                                        cout << "Loading..." << endl;
                                        cout << "You are being logged out..." << endl;
                                        cout << endl;
                                    }
                                    else
                                    {
                                        cin.clear();
                                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                        cout << "Invalid choice. Please try again." << endl;
                                    }
                                }
                                else
                                {
                                    cin.clear();
                                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                    cout << "No cars available." << endl;
                                }
                                //
                            }
                            else
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "Invalid input" << endl;
                            }
                        }
                        else 
                        {
                            cout << "You are being logged out..." << endl;
                            break;
                        }
                    }
                }
                else
                {
                    cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "Incorrect username or password. Please try again." << endl;
                    break;
                }
            }
        }
        else
        {
            cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Wrong userid or password please try again !!!" << endl;
        }
    }
    void addRentalRecord(RentalRecord &record)
    {
        rentalRecords.push_back(record);
    }

    bool isUserIdAvailable(string &userid)
    {
        for (auto &user : existingUsers)
        {
            if (user.userid == userid)
            {
                return false;
            }
        }
        return true;
    }

    bool isUserAuthenticated(string &userid, string &pass)
    {
        for (auto &user : existingUsers)
        {
            if (user.userid == userid && user.pass == pass)
            {
                return true;
            }
        }
        return false;
    }
};

class Customer
{
public:
    Car_available &carAvailability;
    Manager &manager;

public:
    Customer(Car_available &cars, Manager &mgr) : carAvailability(cars), manager(mgr) {}

    vector<User> &getExistingUsers()
    {
        return manager.getExistingCustomers();
    }

    void deleteCustomer(string &userid)
    {
        auto &customerDatabase = manager.getExistingCustomers(); 
        auto it = customerDatabase.begin();
        while (it != customerDatabase.end())
        {
            if (it->userid == userid)
            {
                it = customerDatabase.erase(it);
                cout << "Customer deleted successfully!" << endl;
                return;
            }
            else
            {
                ++it;
            }
        }
        cout << "Customer not found." << endl;
    }

    void registerUser()
    {
        cout << "Create your username/user id: ";
        string userid;
        cin >> userid;

        if (isUserIdAvailable(userid))
        {
            cout << "User ID '" << userid << "' is available." << endl;
            cout << "Create your password: ";
            string pass;
            cin >> pass;

           
            User newUser = {userid, pass, 0, 0, 1};

            manager.addUserToCustomerDatabase(newUser);

            cout << "User successfully registered!" << endl;
        }
        else
        {
            cout << "User ID '" << userid << "' is not available." << endl;
        }
    }

    void loginUser()
    {
        cout << "Enter your username: ";
        string userid;
        cin >> userid;
        cout << "Enter your password: ";
        string pass;
        cin >> pass;

        if (isUserAuthenticated(userid, pass))
        {
            cout << "Welcome, " << userid << "!" << endl;
            vector<User> &existingUsers = manager.getExistingCustomers();

            bool found = false;
            for (auto &user : existingUsers) 
            {
                if (user.userid == userid)
                {
                    found = true;
                    cout << "You have rented " << user.rentedCars << " Cars" << endl;
                    cout << "Your Fine amount is Rs. " << user.fineAmount << endl;
                    cout << "Your customer record is: ";
                    if (user.goodCustomer >= 0)
                    {
                        cout << "GOOD :) You are eligible to rent a car" << endl;
                        cout << "Press 1 to rent a car, press 2 to return a car, press 3 to exit" << endl;
                        char action;
                        cin >> action;
                        switch (action)
                        {
                        case '1':
                            rentCar(user); 
                            break;
                        case '2':
                            returnCar(user);
                            break;
                        case '3':
                            break;
                        default:
                            cout << "Invalid choice." << endl;
                            break;
                        }
                        break;
                        
                    }
                    else
                    {
                        
                        cout << "BAD :(" << endl;
                        cout << "You can't rent any car. Do you want to return any car?" << endl;
                        cout << "Press 1 return a car, any other number key to log out" << endl;
                        int c;
                        cin >> c;
                        if (c == 1)
                        {
                            returnCar(user);
                        }
                        else
                        {
                            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "You are being logged out..." << endl;
                            break;
                        }
                        break;
                    
                    break;
                    }
                }
            }
            if (!found)
            {
                cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Incorrect username or password. Please try again." << endl;
            }
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Wrong userid or password. Please try again." << endl;
        }
    }

private:
    void rentCar(User &user)
    {
        if (carAvailability.areCarsAvailable())
        {
            carAvailability.printAvailableCars();
            int carChoice;
            cout << "Enter the number of the car you want to rent: ";
            cin >> carChoice;
            if (carChoice >= 1 && carChoice <= carAvailability.cars_available.size())
            {
                carAvailability.removeCar(carChoice);
                cout << "Car rented successfully!" << endl;
                cout<<"Rs. 1000 have been deducted because you rented a car"<<endl;
                user.rentedCars++;  
                RentalRecord record(carAvailability.cars_available[carChoice - 1].name, user.userid);
                manager.addRentalRecord(record);
                time_t now = time(nullptr);
                time_t returnTime = now + 7 * 24 * 60 * 60;    
                cout << "Your car is due for return on: " << ctime(&returnTime);
                cout << "Loading..." << endl;
                cout << "You are being logged out..." << endl;
                cout << endl;
            }
            else
            {
                cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice. Please try again." << endl;
            }
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "No cars available." << endl;
        }
    }

    void returnCar(User &user)
    {
        time_t now = time(nullptr);
        time_t returnTime = now + 7 * 24 * 60 * 60; 

     
        if (now > returnTime)
        {
            int extraDays = (now - returnTime) / (24 * 60 * 60);
            int fine = extraDays * 100;
            cout << "Enter the name of the car you are returning: ";
            string returnedCarName;
            cin >> returnedCarName;
            Car_available::Car returnedCar;
            returnedCar.name = returnedCarName;
            cout << "Enter the year of the car: ";
            cin >> returnedCar.year;
            cout << "Enter the condition of the car: ";
            cin >> returnedCar.condition;
            carAvailability.cars_available.push_back(returnedCar);
            cout << "Car returned successfully!" << endl;
            cout << "You returned the car after the due date." << endl;
            cout << "You have been fined Rs. " << fine << " for " << extraDays << " extra days." << endl;

            user.goodCustomer = -1;  
            user.fineAmount += fine; 
            user.rentedCars--;
        }
        else
        {
            cout << "Enter the name of the car you are returning: ";
            string returnedCarName;
            cin >> returnedCarName;
            Car_available::Car returnedCar;
            returnedCar.name = returnedCarName;
            cout << "Enter the year of the car: ";
            cin >> returnedCar.year;
            cout << "Enter the condition of the car: ";
            cin >> returnedCar.condition;
            carAvailability.cars_available.push_back(returnedCar);
            cout << "Car returned successfully!" << endl;
            user.goodCustomer = 1;  
            user.rentedCars--;
        }
    }

    bool isUserIdAvailable(string &userid)
    {
        vector<User> &existingUsers = manager.getExistingCustomers();
        for (auto &user : existingUsers)
        {
            if (user.userid == userid)
            {
                return false;
            }
        }
        return true;
    }

    bool isUserAuthenticated(string &userid, string &pass)
    {
        vector<User> &existingUsers = manager.getExistingCustomers();
        for (auto &user : existingUsers)
        {
            if (user.userid == userid && user.pass == pass)
            {
                return true;
            }
        }
        return false;
    }
};

class Employee
{
private:
    Car_available &carAvailability;
    Manager &manager;

public:
    Employee(Car_available &cars, Manager &mgr) : carAvailability(cars), manager(mgr) {}

    vector<User> &getExistingUsers()
    {
        return manager.getExistingEmployee();
    }

    void deleteEmployee(string &userid)
    {
        auto &employeeDatabase = manager.getExistingEmployee(); 
        auto it = employeeDatabase.begin();
        while (it != employeeDatabase.end())
        {
            if (it->userid == userid)
            {
                it = employeeDatabase.erase(it);
                cout << "Employee deleted successfully!" << endl;
                return;
            }
            else
            {
                ++it;
            }
        }
        cout << "Employee not found." << endl;
    }

    void registerUser()
    {
        cout << "Create your username/user id: ";
        string userid;
        cin >> userid;

        if (isUserIdAvailable(userid))
        {
            cout << "User ID '" << userid << "' is available." << endl;
            cout << "Create your password: ";
            string pass;
            cin >> pass;

            User newUser = {userid, pass, 0, 0, 1};

            manager.addUserToEmployeeDatabase(newUser);

            cout << "User successfully registered!" << endl;
        }
        else
        {
            cout << "User ID '" << userid << "' is not available." << endl;
        }
    }

    void loginUser()
    {
        cout << "Enter your username: ";
        string userid;
        cin >> userid;
        cout << "Enter your password: ";
        string pass;
        cin >> pass;

        if (isUserAuthenticated(userid, pass))
        {
            cout << "Welcome, " << userid << "!" << endl;
            vector<User> &existingUsers = manager.getExistingEmployee();
            bool found = false;
            for (auto &user : existingUsers) 
            {
                if (user.userid == userid)
                {
                    found = true;
                     
                    cout << "You have rented " << user.rentedCars << " Cars" << endl;
                    cout << "Your Fine amount is Rs. " << user.fineAmount << endl;
                    cout << "Your customer record is: ";
                    if (user.goodCustomer >= 0)
                    {
                        cout << "GOOD :) You are eligible to rent a car" << endl;
                        
                        cout << "Press 1 to rent a car, press 2 to return a car, press 3 to exit" << endl;
                        char action;
                        cin >> action;
                        switch (action)
                        {
                        case '1':
                            rentCar(user); 
                            break;
                        case '2':
                            returnCar(user);
                            break;
                        case '3':
                            break;
                        default:
                            cout << "Invalid choice." << endl;
                            break;
                        }
                        
                    }
                    else
                    {
                        cout << "BAD :(" << endl;
                       
                        cout << "You cant rent any car. Do you want to return any car?" << endl;
                        cout << "Press 1 return a car, any other number key to log out" << endl;
                        char c;
                        cin >> c;
                        if (c == '1')
                        {
                            returnCar(user);
                        }
                        else
                        {
                            cin.clear();
                            cin.ignore(numeric_limits<streamsize>::max(), '\n');
                            cout << "You are being logged out..." << endl;
                            break;
                        }
                    
                    
                    }
                }
                
            }
            if (!found)
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Incorrect username or password. Please try again." << endl;
            }
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Wrong userid or password. Please try again." << endl;
        }
    }

private:
    void rentCar(User &user)
    {
        if (carAvailability.areCarsAvailable())
        {
            carAvailability.printAvailableCars();
            int carChoice;
            cout << "Enter the number of the car you want to rent: ";
            cin >> carChoice;
            if (carChoice >= 1 && carChoice <= carAvailability.cars_available.size())
            {
                carAvailability.removeCar(carChoice);
                cout << "Car rented successfully!" << endl;
                cout<<"Rs. 850 deducted successfully because you rented a car"<<endl;
                user.rentedCars++; // Increase rented cars by 1
                RentalRecord record(carAvailability.cars_available[carChoice - 1].name, user.userid);
                manager.addRentalRecord(record);
                time_t now = time(nullptr);
                time_t returnTime = now + 7 * 24 * 60 * 60; 
                cout << "Your car is due for return on: " << ctime(&returnTime);
                cout << "Loading..." << endl;

                cout << "You are being logged out..." << endl;
                cout << endl;
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice. Please try again." << endl;
            }
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "No cars available." << endl;
        }
    }

    void returnCar(User &user)
    {
        time_t now = time(nullptr);
        time_t returnTime = now + 7 * 24 * 60 * 60; 

        if (now > returnTime)
        {
            int extraDays = (now - returnTime) / (24 * 60 * 60);
            int fine = extraDays * 100;
            cout << "Enter the name of the car you are returning: ";
            string returnedCarName;
            cin >> returnedCarName;
            Car_available::Car returnedCar;
            returnedCar.name = returnedCarName;
            cout << "Enter the year of the car: ";
            cin >> returnedCar.year;
            cout << "Enter the condition of the car: ";
            cin >> returnedCar.condition;
            carAvailability.cars_available.push_back(returnedCar);
            user.rentedCars--;
            cout << "Car returned successfully!" << endl;
            cout << "You returned the car after the due date." << endl;
            cout << "You have been fined Rs. " << fine << " for " << extraDays << " extra days." << endl;

            user.goodCustomer = -1;  
            user.fineAmount += fine; 
            user.rentedCars--;
        }
        else
        {
            cout << "Enter the name of the car you are returning: ";
            string returnedCarName;
            cin >> returnedCarName;
            Car_available::Car returnedCar;
            returnedCar.name = returnedCarName;
            cout << "Enter the year of the car: ";
            cin >> returnedCar.year;
            cout << "Enter the condition of the car: ";
            cin >> returnedCar.condition;
            carAvailability.cars_available.push_back(returnedCar);
            cout << "Car returned successfully!" << endl;
            user.goodCustomer = 1; 
            user.rentedCars--;
        }
    }

    bool isUserIdAvailable(string &userid)
    {
        vector<User> &existingUsers = manager.getExistingEmployee();
        for (auto &user : existingUsers)
        {
            if (user.userid == userid)
            {
                return false;
            }
        }
        return true;
    }

    bool isUserAuthenticated(string &userid, string &pass)
    {
        vector<User> &existingUsers = manager.getExistingEmployee();
        for (auto &user : existingUsers)
        {
            if (user.userid == userid && user.pass == pass)
            {
                return true;
            }
        }
        return false;
    }
};

int main()
{

    Car_available carAvailability;
    Manager manager(carAvailability);
    Customer customer(carAvailability, manager);
    Employee employee(carAvailability, manager);

    while (true)
    {
        cout<<endl;
        cout << "Press the following for your respective post :" << endl;
        cout << "Press 1 for customer, 2 for employee, 3 for Manager, 4 to exit" << endl;

        int button;
        cin >> button;
        if (button == 1)
        {
            cout << "Press 1 for New Customer, Press 2 for registered Customer" << endl;
            int choice;
            cin >> choice;
            if (choice == 1)
            {
                customer.registerUser();
            }
            else if (choice == 2)
            {

                customer.loginUser();
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice." << endl;
            }
        }
        else if (button == 2)
        {
            cout << "Press 1 for New Employee, Press 2 for already registered employee" << endl;
            int choice;
            cin >> choice;
            if (choice == 1)
            {
                employee.registerUser();
            }
            else if (choice == 2)
            {
                employee.loginUser();
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice." << endl;
            }
        }
        else if (button == 3)
        {
            cout << "Press 1 for Registering as a New Manager, Press 2 for Old Manager" << endl;
            int choice;
            cin >> choice;
            if (choice == 1)
            {
                manager.registerUser();
            }
            else if (choice == 2)
            {
                manager.loginUser();
            }
            else
            {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Invalid choice." << endl;
            }
        }
        else if (button == 4)
        {
            break;
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please try again with valid input." << endl;
        }
    }

    return 0;
}
