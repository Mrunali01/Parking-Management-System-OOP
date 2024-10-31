#include <iostream>
using namespace std;

static int countSlot=0;

class ParkingFacility
{
    public:
            int slots;
            ParkingFacility()
            {
                cout<<"Enter number of parking slots available : ";
                cin>>slots;
            }
};

class Customer
{
    string name;
    string phone;

    public:
            Customer()
            {
                cout<<"Enter customer details"<<endl;
                cout<<"NAME : ";
                cin>>name;
                cout<<"\nPHONE : ";
                cin>>phone;
            }
            void displayCustomerDetails()
            {
                cout<<"NAME : "<<name;
                cout<<"PHONE : "<<phone;
            }
};

class Vehicle : public Customer
{
    string regNo;
    string type;

    public:
            Vehicle()
            {
                cout<<"Enter Vehicle Details"<<endl;
                cout<<"REGISTRATION NO."<<endl;
                cin>>regNo;
                cout<<"TYPE OF VEHICLE"<<endl;
                cin>>type;
            }
            void getTicket()
            {
                cout<<"----ONLINE TICKET----"<<endl;
                displayCustomerDetails();
                displayCarDetails();


            }
            void displayCarDetails()
            {
                cout<<"TYPE OF VEHICLE : "<<type<<endl;
                cout<<"REGISTRATION NO. : "<<regNo<<endl;
            }           
};

class Ticket : public

int main()
{
    cout<<"------WELCOME TO PARKING MANAGEMENT SYSTEM------"<<endl;
    cout<<"Please Enter details of you Parking facility"<<endl;
    ParkingFacility pf1;
    cout<<".....saved"<<endl;

    cout<<"\n";

    cout<<"Choose from below options"<<endl;
    cout<<"1. ENTRY OF A CAR"<<endl;
    cout<<"2. EXIT OF A CAR"<<endl;
    cout<<"3. DISPLAY DETAILS OF A CAR"<<endl;
    cout<<"4. GENERATE TICKET"<<endl;
    cout<<"5. EXIT"<<endl;
    int x;
    cin>>x;
    switch(x)
    {
        case 
    }
}

