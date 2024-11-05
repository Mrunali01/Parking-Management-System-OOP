#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

static int countSlot=0;

class Customer {
    string name;
    string phone;

public:
    void getCustomerDetails() {
        cout << "Enter customer details" << endl;
        cout << "NAME : ";
        cin >> name;
        cout << "PHONE : ";
        cin >> phone;
    }
    string getName() {
        return name;
    }
    string getPhone() {
        return phone;
    }
};

class Vehicle : public Customer {
    string regNo;
    string type;
    int slotNo;
    time_t entryTime, exitTime;
    bool isPaid;

public:
    void forEntry(int slot) {
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
        cout << "Pay 20/- entry fees (1 for Yes, 0 for No): ";
        cin >> isPaid;
        cout<<"Alloted slot : "<<slotNo<<endl;
    }
    void forExit() {
        exitTime = time(0);
        string t2 = ctime(&exitTime);
        if (!isPaid) {
            cout << "Please pay first" << endl;
            return;
        } else {
            cout << "Exit successful" << endl;
        }
        displayTicket();
    }
    void displayTicket() 
    {
        cout << "\n-----------ONLINE TICKET----------" << endl;
        cout << "------------------------------------" << endl;
        cout << "1. Type of vehicle : " << type << endl;
        cout << "2. Registration Number : " << regNo << endl;
        cout << "3. Parking slot number : " << slotNo << endl;
        cout << "4. Entry Time : " << ctime(&entryTime);
        cout << "5. Exit Time : " << ctime(&exitTime);
        cout << "*All Charges Paid*" << endl;
        cout << "------------------------------------" << endl;
        cout << "------------------------------------" << endl;
    }
    int getSlotNo() 
    { 
        return slotNo; 
    }
    bool isPaymentMade() 
    { 
        return isPaid; 
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
        }

        int getCapacity() 
        {
            return capacity;
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
            cout << "Entry successful" << endl;
        } else 
        {
            cout << "Sorry no empty parking space available!" << endl;
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
    cout << "*********************************************" << endl;
    cout << "******WELCOME TO PARKING MANAGEMENT SYSTEM******" << endl;
    cout << "*********************************************" << endl;
    ParkingFacility p1;
    cout << ".....saved" << endl;

    while (true) 
    {
        cout << "\nChoose from below options" << endl;
        cout << "1. ENTRY OF A CAR" << endl;
        cout << "2. EXIT OF A CAR" << endl;
        cout << "3. DISPLAY DETAILS OF A CAR" << endl;
        cout << "4. EXIT" << endl;
        int x;
        cin >> x;
        
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
                if (Vehicle* vehicle = p1.findVehicleBySlot(slot)) {
                    vehicle->displayTicket();
                } else {
                    cout << "No vehicle found in this slot!" << endl;
                }
                break;

            case 4:
                exit(0);

            default:
                cout << "Enter a valid choice" << endl;
        }
    }
    return 0;
}
