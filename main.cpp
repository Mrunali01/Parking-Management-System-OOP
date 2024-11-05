#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

static int countSlot=0;

class Customer 
{
    string name;
    string phone;

public:
    void getCustomerDetails() 
    {
        cout << "\nEnter customer details" << endl;
        cout << "NAME : ";
        cin >> name;
        cout << "PHONE : ";
        cin >> phone;
    }
    string getName() 
    {
        return name;
    }
    string getPhone() 
    {
        return phone;
    }
};



class Vehicle : public Customer 
{
    string regNo;
    string type;
    int slotNo, charges;
    time_t entryTime, exitTime;
    int isPaid;

    public:
        void forEntry(int slot) 
        {
            slotNo = slot;
            getCustomerDetails();
            cout << "Enter Vehicle Details" << endl;
            cout << "TYPE OF VEHICLE : ";
            cin >> type;
            cout << "REGISTRATION NO. : ";
            cin >> regNo;
            entryTime = time(0);
            string t1 = ctime(&entryTime);
            cout << "ENTRY TIME : " << t1 << endl;
        }
        void forExit() 
        {
            exitTime = time(0);
            string t2 = ctime(&exitTime);
            displayTicket();
            cout<<"\n Pay "<<charges<<"/-"<<" (1 for Paid, 0 for Not Paid) : ";
            cin>>isPaid;
            if(isPaid==1)
            {
                cout << "Exit successful" << endl;
            }
            else
            {
                cout << "\n\nPlease pay first" << endl;
                forExit();
            } 

        }

        int getSlotNo() 
        { 
            return slotNo; 
        }

        int calculateCharges()
        {
            long long duration = exitTime - entryTime;
            int min = duration/60;
            int hrs = min/60;
            int minutes = min%60;

            if(hrs<=0 && minutes<=30)
            {
                charges = 15;
            }
            else if(hrs>=1)
            {
                charges = 25;
            }
            else
            {
                charges = 30;
            }
            return charges;
        }

        void displayTicket() 
        {
            cout << "\n-----------ONLINE TICKET----------" << endl;
            cout << "------------------------------------" << endl;
            cout << "\n1. OWNER NAME : " << getName()<<endl;
            cout << "2. PHONE NUMBER : "<< getPhone()<<endl;
            cout << "3. TYPE OF VEHICLE : " << type << endl;
            cout << "4. REGISTRATION NUMBER : " << regNo << endl;
            cout << "5. PARKING SLOT NUMBER : " << slotNo << endl;
            cout << "6. ENTRY TIME : " << ctime(&entryTime);
            cout << "7. EXIT TIME : " << ctime(&exitTime);
            cout << "8. TOTAL CHARGES : " << calculateCharges() <<"/-"<< endl;
            cout << "------------------------------------" << endl;
            cout << "------------------------------------" << endl;
        }
        
        void displayDetails()
        {
            cout << "\n-------DETAILS OF PARKED CAR-------"<<endl;
            cout << "\n1. OWNER NAME : " << getName()<<endl;
            cout << "2. PHONE NUMBER : "<< getPhone()<<endl;
            cout << "3. TYPE OF VEHICLE : " << type << endl;
            cout << "4. REGISTRATION NUMBER : " << regNo << endl;
            cout << "5. PARKING SLOT NUMBER : " << slotNo << endl;
            cout << "6. ENTRY TIME : " << ctime(&entryTime);   
            cout << "*** CAR PARKED AT SLOT NUMBER "<<slotNo<<" ***"<<endl;
            cout << "-----------------------------------"<<endl;
        }
};

class ParkingFacility 
{
    int capacity, occupied;
    vector<bool> parkingSlots;
    vector<Vehicle> vehicles;

    public:
        ParkingFacility() 
        {
            cout << "\nEnter the capacity of parking facility : ";
            cin >> capacity;
            occupied = 0;
            parkingSlots.resize(capacity, false);
        }

        bool ifAvailable() 
        {
            return occupied < capacity;
        }

        int getFreeSlot() 
        {
            for (int i = 0; i < capacity; ++i) 
            {
                if (!parkingSlots[i]) 
                {
                    parkingSlots[i] = true;
                    occupied++;
                    return i + 1;
                }
            }
            return -1;
        }

        void newVehicle(Vehicle &x) 
        {
            vehicles.push_back(x);
        }
        
        Vehicle* findVehicleBySlot(int slot) 
        { 
            for (auto &vehicle : vehicles) 
            {
                if (vehicle.getSlotNo() == slot) 
                {
                    return &vehicle;
                }
            }
            return nullptr;
        }

        void deleteVehicle(int slot) 
        {
            parkingSlots[slot - 1] = false;
            occupied--;

            for (auto i = vehicles.begin(); i != vehicles.end(); ++i) 
            {
                if (i->getSlotNo() == slot) 
                {
                    vehicles.erase(i);
                    break;
                }
            }
        }


        int getCapacity() 
        {
            return capacity;
        }

        void parkingSlotDetails()
        {
            while(true)
            {
                int y;
                cout<<"\nChoose from below options : "<<endl;
                cout<<"1. Check the capacity of Parking Facility"<<endl;
                cout<<"2. Check occupied spots"<<endl;
                cout<<"3. Check available parking slots"<<endl;
                cout<<"4. Exit"<<endl;
                cout<<"Enter your choice : ";
                cin>>y;
                if(y>=1 && y<=4)
                {
                    switch(y)
                    {
                        case 1:
                                cout<<"CAPACITY OF PARKING FACILITY : "<<capacity<<endl;
                                break;

                        case 2:
                                cout<<"OCCUPIED PARKING SLOTS : ";
                                for(int i=0;i<parkingSlots.size();i++)
                                {
                                    if(parkingSlots[i]==true)
                                        cout<<i+1<<" ";
                                }
                                break;

                        case 3:
                                cout<<"AVAILABLE PARKING SLOTS : ";
                                for(int i=0;i<parkingSlots.size();i++)
                                {
                                    if(parkingSlots[i]==false)
                                        cout<<i+1<<" ";
                                }
                                break;

                        case 4:
                                return;
                    }
                }
                else
                {
                    cout<<"Please enter a valid choice"<<endl;
                    parkingSlotDetails();
                }
            }
        }
};

void vehicleEntry(ParkingFacility &pl) 
{
    if (pl.ifAvailable()) 
    {
        int slot = pl.getFreeSlot();
        Vehicle obj;
        obj.forEntry(slot);
        pl.newVehicle(obj);
        cout<< "Alloted Slot : "<<slot<<endl;
        cout << "Entry successful" << endl;
    } 
    else 
    {
        cout << "\nSorry, there are no empty parking space available!" << endl;
    }
}

void vehicleExit(ParkingFacility &p1) 
{
    int ticketSlot;
    cout << "Enter the parking slot number for exit: ";
    cin >> ticketSlot;
    if (ticketSlot <= 0 || ticketSlot > p1.getCapacity()) 
    {
        cout << "Invalid parking slot number!" << endl;
        return;
    }
    Vehicle* vehicle = p1.findVehicleBySlot(ticketSlot);
    if (vehicle != nullptr) 
    {
        vehicle->forExit();
        p1.deleteVehicle(ticketSlot);
    } else 
    {
        cout << "No vehicle found in the given slot!" << endl;
    }
}

int main() 
{
    cout << "\n\n************************************************" << endl;
    cout << "******WELCOME TO PARKING MANAGEMENT SYSTEM******" << endl;
    cout << "************************************************" << endl;
    ParkingFacility p1;
    cout << ".....saved" << endl;
    while(true)
    {
        cout << "\nChoose from below options :" << endl;
        cout << "1. ENTRY OF A CAR" << endl;
        cout << "2. EXIT OF A CAR" << endl;
        cout << "3. DISPLAY DETAILS OF A CAR" << endl;
        cout << "4. DISPLAY DETAILS OF PARKING FACILITY"<<endl;
        cout << "5. EXIT" << endl;
        cout << "Enter your choice : ";
        int x;
        cin >> x;

        if(x>=1 && x<=5)
        {
            switch (x) 
            {
                case 1:
                    vehicleEntry(p1);
                    break;

                case 2:
                    vehicleExit(p1);
                    break;

                case 3:
                    int slot;
                    cout << "Enter slot number to display ticket: ";
                    cin >> slot;
                    if (Vehicle* vehicle = p1.findVehicleBySlot(slot)) 
                    {
                        vehicle->displayDetails();
                    } 
                    else 
                    {
                        cout << "No vehicle found in this slot!" << endl;
                    }
                    break;

                case 4:
                        p1.parkingSlotDetails();
                        break;

                case 5:
                    cout << "*********************************************" << endl;
                    cout << "*******************THANK YOU*****************" << endl;
                    cout << "*********************************************" << endl;
                    exit(0);

                default:
                    cout << "Enter a valid choice" << endl;
                    break;
            }
        }
        else
        {
            cout<<"Invalid input, please try again!"<<endl;
        }
    }
    return 0;
}
