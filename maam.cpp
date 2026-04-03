class AdminBase : public Person
{
protected:
    string username;
    string password;

public:
    AdminBase() : Person()
    {
        username = "admin";
        password = "1234";
    }

    virtual bool login(string u, string p)
    {
        if (u == username && p == password)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void displayInfo() const override
    {
        cout << "Admin: " << username << endl;
    }
    bool authenticate()
    {
        string user, pass;
        int attempts = 3;

        while (attempts--)
        {
            cout << "Enter Username: ";
            cin >> user;
            cout << "Enter Password: ";
            cin >> pass;

            if (login(user, pass))
                return true;
            cout << "Wrong credentials! Attempts left: " << attempts << endl;
        }
        return false;
    }
};
class Hotel : public AdminBase, public Customer
{
private:
    vector<Room> rooms;
    vector<Customer> customers;

public:
    Hotel()
    {
    }

    void addRoom()
    {

        int no = safeInt("Enter Room No: ");
        for (size_t i = 0; i < rooms.size(); i++)
        {
            if (rooms[i].getRoomNo() == no)
            {
                cout << "Room exists!\n";
                return;
            }
        }
        string type;
        cout << "Enter Type ( Single / Double) :";
        cin >> type;
        float price = safeFloat("Enter Price: ");
        rooms.push_back(Room(no, type, price));
        cout << "Room added successfully!\n";
    }

    void displayRooms() const
    {
        cout << left << setw(10) << "Room"
             << setw(10) << "Type"
             << setw(10) << "Price"
             << setw(10) << "Status" << endl;

        displayVector(rooms);
    }

    void bookRoom()
    {
        int id;
        while (true)
        {
            id = safeInt("Enter Customer ID: ");
            bool exists = false;
            for (const auto &c : customers)
            {
                if (c.getCustID() == id)
                {
                    exists = true;
                    break;
                }
            }

            if (exists)
            {
                cout << "Customer ID already exists! Enter a different ID.\n";
            }
            else
            {
                break;
            }
        }
        // int id = safeInt("Enter Customer ID: ");

        string name;
        cout << "Enter Name: ";
        getline(cin, name);

        int roomNo = safeInt("Enter Room No: ");
        int days = safeInt("Enter Days: ");

        for (size_t i = 0; i < rooms.size(); i++)
        {
            if (rooms[i].getRoomNo() == roomNo && !rooms[i].getStatus())
            {
                rooms[i].book();
                customers.push_back(Customer(id, name, roomNo, days));
                cout << " Room booked successfully!\n";
                return;
            }
        }
        cout << "Room not available!\n";
    }

    void checkOut()
    {
        int room = safeInt("Enter Room No: ");
        float food = safeFloat("Enter Food Bill: ");

        for (size_t i = 0; i < rooms.size(); i++)
        {
            if (rooms[i].getRoomNo() == room && rooms[i].getStatus())
            {
                for (size_t j = 0; j < customers.size(); j++)
                {
                    if (customers[j].getRoomNo() == room)
                    {
                        Bill b;
                        b.calculate(customers[j], rooms[i].getPrice(), food);

                        cout << "\n========== BILL ==========\n";
                        cout << "Customer: " << customers[j].getName() << endl;
                        cout << "Room Bill: " << b.roomBill << endl;
                        cout << "Food Bill: " << b.foodBill << endl;
                        cout << "Total: " << b.totalBill << endl;

                        customers.erase(customers.begin() + j);

                        rooms[i].free();
                        return;
                    }
                }
            }
        }

        cout << "Invalid Room or Not Booked!\n";
    }
    void displayCustomers() const
    {
        if (customers.empty())
        {
            cout << "No customers in the hotel at this moment.\n";
            return;
        }
        displayVector(customers);
    }

    void searchRoom() const
    {
        int num = safeInt("Enter Room No: ");
        for (size_t i = 0; i < rooms.size(); i++)
        {
            if (rooms[i].getRoomNo() == num)
            {
                rooms[i].displayInfo();
                return;
            }
        }
        cout << "Room not found!\n";
    }

    void run()
    {
        int choice;
        while (true)
        {
            cout << "\n1.Add Room\n2.Book Room\n3.Check Out\n4.Display Rooms\n5.Display Customers\n6.Search Room\n7.Exit\nEnter choice: ";
            choice = safeInt();
            switch (choice)
            {
            case 1:
                addRoom();
                break;
            case 2:
                bookRoom();
                break;
            case 3:
                checkOut();
                break;
            case 4:
                displayRooms();
                break;
            case 5:
                displayCustomers();
                break;
            case 6:
                searchRoom();
                break;
            case 7:
            {
                string confirm;
                cout << "Exit? (YES/NO): ";
                cin >> confirm;
                if (confirm == "yes" || confirm == "YES")
                    return;
                break;
            }

            default:
                cout << "Invalid choice!\n";
            }
        }
    }
};
int main()
{
    AdminBase admin;
    if (!admin.authenticate())
        return 0;

    Hotel h;
    h.run();
}