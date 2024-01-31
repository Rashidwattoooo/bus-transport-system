#include <iostream>
#include <vector>
#include <string>
#include <fstream>
using namespace std;
int admin_flag = 0;
class Bus
{
private:
    static int next_id;
    int id;
    string name;
    int total_seats;
    string bus_num;
    bool *seats;
    string route;
    int fare;

public:
    Bus():name(""),id(next_id++),bus_num(""),fare(0),total_seats(0){
        seats = nullptr;
    }
    Bus(string name, int total_seats, string bus_num, string route, int fare) : id(next_id++), name(name), total_seats(total_seats), bus_num(bus_num), route(route), fare(fare)
    {
        seats = new bool[total_seats];
        for (int i = 0; i < total_seats; i++)
        {
            seats[i] = 0;
        }
    }
    ~Bus()
    {
        delete[] seats;
    }
    int get_id()
    {
        return id;
    }
    string get_name()
    {
        return name;
    }
    int get_total_seats()
    {
        return total_seats;
    }
    string get_bus_num()
    {
        return bus_num;
    }
    void set_name()
    {
        cout << "Enter Bus name:" << endl;
        cin >> name;
    }
    void set_num()
    {
        cout << "Enter Bus number:" << endl;
        cin >> bus_num;
    }
    void set_route()
    {
        cout << "Enter Bus route:" << endl;
        cin >> route;
    }
    void set_fare()
    {
        cout << "Enter Bus fare:" << endl;
        cin >> fare;
    }
    void set_total_seats()
    {
        cout << "Enter Total Seats:" << endl;
        cin >> total_seats;
    }

    void set_seats(bool *seats)
    {
        this->seats = seats;
    }
    void reserve_seat(int seat_num)
    {
        seats[seat_num] = true;
    }
    string get_route()
    {
        return route;
    }
    int get_fare()
    {
        return fare;
    }
    int print_seats()
    {
        int count = 0;
        for (int i = 0; i < total_seats; i++)
        {
            if (this->seats[i]==true)
            {
                cout << " " << i << " "
                     << "Occcupied" << endl;
            }
            else if(this->seats[i]==false)
            {
                cout << " " << i << " "
                     << "Empty" << endl;
                count++;
            }
            else{
                cout<<i<<" "<<seats[i]<<endl;
            }
        }
        return count;
    }
    void user_bus_data(string filename)
    {
        ifstream infile(filename + ".txt");
        if (!infile.is_open())
        {
            cout << "Error opening the file." << endl;
            return;
        }

        for (int i = 0; i < 4; ++i)
        {
            string line;
            getline(infile, line);
            cout << "Skipping line: " << line << endl;
        }

        // Assuming the remaining content in the file is structured properly
        if (infile >> this->id >> this->name >> this->total_seats >> this->bus_num >> this->route >> this->fare)
        {
            return;
        }
        else
        {
            cout << "Error reading data from the file." << endl;
        }

        // Close the file when done
        infile.close();
    }

    void display_info()
    {
        cout << "id: " << this->id <<endl<< "Name: " << name <<endl<< "Bus Number: " << bus_num <<endl<< "Total Seats: " << total_seats <<endl<< "Route: " << route <<endl<< "fare: " << fare << endl;
    }
    void save_data_bus()
    {
        ofstream outfile("busses_data.txt", ios::app);
        if (!outfile.is_open())
        {
            cout << "Error opening the file for append." << endl;
            return;
        }

        outfile << this->id << " " << this->name << " " << this->total_seats << " " << this->bus_num << " " << this->route << " " << this->fare << endl;

        outfile.close();
    }

    void load_data_bus(istream &infile)
    {
        infile >> id >> name >> fare>> bus_num >> route >> total_seats;
        seats = new bool[total_seats];
        print_seats();
       this->empty_bus();
        print_seats();

    }
    void empty_bus(){
        for (int i = 0; i < total_seats; i++){
            seats[i] = false;
        }
    }
};

class User
{
protected:
    static int next_id;
    int id;
    string name;
    string password;
    string phone_number;
    Bus *b1;

public:
    User()
    {
        id = next_id++;

        this->name = "";
        this->password = "";
        this->phone_number = "";
        b1 = nullptr;
    };
    User(string name, string password, string phone_number)
    {
        this->id = next_id++;
        this->name = name;
        this->password = password;
        this->phone_number = phone_number;
        b1 = nullptr;
    }
    int get_id()
    {
        return id;
    }
    string get_name()
    {
        return name;
    }
    string get_password()
    {
        return password;
    }
    string get_phone_number()
    {
        return phone_number;
    }
    void set_name(string name)
    {
        this->name = name;
    }
    Bus *get_bus()
    {
        return b1;
    }
    void set_password(string password)
    {
        this->password = password;
    }
    void set_phone_number(string phone_number)
    {
        this->phone_number = phone_number;
    }
    void take_bus(Bus &bus)
    {
        this->b1 = &bus;
        b1->print_seats();
        cout << "Enter the index of Seat you want to reserve" << endl;
        int index;
        cin >> index;
        b1->reserve_seat(index);
         cout<<index<<" Number seat has been reserved for you"<<endl;
    }
    void load_data(string file_name)
    {
        
        ifstream infile(file_name + ".txt");
        infile >> name >> password >> phone_number >> id;
     
        infile.close();
        b1 = new Bus();
        b1->user_bus_data(name);
    }
    void display_info()
    {
        cout << "Name: " << name << "Password: " << password << "Phone Number" << phone_number << endl;
    }
};

class Anas_Transport
{
    int choice;

public:
    vector<User> users;
    vector<Bus *> buses;
    User *sign_in_and_up()
    {
        
        string name;
        string password;
        string phone_number;
        cout<<"Enter 1 for signing up"<<endl;
        cout<<"Enter 2 for signing in"<<endl;
        cin>>choice;
        if (choice == 1)
        {
            cout << "Enter your name: ";
            cin >> name;
            cout << "Enter your password: ";
            cin >> password;
            cout << "Enter your phone number: ";
            cin >> phone_number;
             cout << "You have successfully signed up" << endl;
            return new User(name, password, phone_number);
           
        }
        else if (choice == 2)
        {
            User *u1;
            cout << "Enter your name: ";
            cin >> name;
            u1 = Anas_Transport::load_user_data(name);
            cout << "Enter your password: ";
            cin >> password;
            if (u1->get_password() == password)
            {
                cout << "You have successfully logged in" << endl;
                return u1;
            }
        }
    }
    Bus *create_bus()
    {
        Bus *b1 = new Bus();
        b1->set_name();
        b1->set_num();
        b1->set_route();
        b1->set_fare();
        b1->set_total_seats();
        b1->set_seats(new bool[b1->get_total_seats()]);
        b1->empty_bus();
        return b1;
    }

    static void save_data(User u1)
    {
        Bus *bus = u1.get_bus();
        ofstream file(u1.get_name() + ".txt");

        file << u1.get_name() << endl;
        file << u1.get_password() << endl;
        file << u1.get_phone_number() << endl;
        file << u1.get_id() << endl;
        file << bus->get_id() << endl;
        file << bus->get_name() << endl;
        cout << bus->get_name() << endl;
        file << bus->get_total_seats() << endl;
        file << bus->get_bus_num() << endl;
        file << bus->get_route() << endl;
        file << bus->get_fare() << endl;
        file << bus->print_seats() << endl;
        file.close();
    }
    static User *load_user_data(string filename)
    {
        User *u1 = new User();
        u1->load_data(filename);
        return u1;
    }
    void load_busses_data()
    {
        ifstream infile("busses_data.txt");
        if (!infile.is_open())
        {
            cout << "Error opening the file." << endl;
            return;
        }
        int i;
        while (!infile.eof())
        {
            Bus *b1 = new Bus();
            b1->load_data_bus(infile);
            b1->empty_bus();
            buses.push_back(b1);
        }

        infile.close();
        for (int i=0; i <buses.size()-1; i++)
        {
            buses[i]->display_info();
        }
    }
    void Menu()
    {
        User *u1;
        load_busses_data();
        while (1)
        {
            int choice = 0;
            cout << "Press 1 to Sign in or sign up or to switch the user" << endl;
            cout << "Press 2 for creating busses " << endl;
            cout << "Press 3 for Displaying Busses" << endl;
            cout << "Press 4 to display your information" << endl;
            cout << "Press 5 to display_users" << endl;
            cout << "Press 6 to save_data of busses as well as users" << endl;
            cout << "Press 7 to reserve a seat in the bus" << endl;
            cout << "Press 8 if you are a administrator" << endl;
            cin >> choice;
            if (choice == 1)
            {
                u1 = sign_in_and_up();
                users.push_back(*u1);
            }
            else if (choice == 2)
            {
                Bus *b1 = create_bus();
                buses.push_back(b1);
            }
            else if (choice == 3)
            {
                for (int i = 0; i < buses.size(); i++)
                {
                    buses[i]->display_info();
                }
            }
            else if (choice == 5)
            {
                if (admin_flag == 1)
                {
                    for (int i = 0; i < users.size(); i++)
                    {
                        users[i].display_info();
                    }
                }
                else
                {
                    cout << "Only admin can access Users data" << endl;
                }
            }
            else if (choice == 4)
            {
                u1->display_info();
            }
            else if (choice == 6)
            {
                for (int i = 0; i < users.size(); i++)
                {
                    save_data(users[i]);
                }
                for (int i = 0; i < buses.size(); i++)
                {
                    buses[i]->save_data_bus();
                }
            }
            else if (choice == 7)
            {
                for (int i = 0; i < buses.size()-1; i++)
                {
                    buses[i]->display_info();
                }
                string name;
                cout << "Enter the name of bus in which you want to rreserve seat" << endl;
                cin.ignore();
                cin >> name;
                for (int i = 0; i < buses.size(); i++)
                {
                    if (buses[i]->get_name() == name)
                    {
                        u1->take_bus(*buses[i]);
                        cout<<"To re-check display your information"<<endl;
                    }
                }
            }
        }
    }
};
int User::next_id = 1;
int Bus::next_id = 1;
int main()
{
    Anas_Transport t1;
    t1.Menu();
}