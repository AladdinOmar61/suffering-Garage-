#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Car
{
public:
    int count = 0;
    string data;
    Car *next = NULL;
};

class Stack
{
public:
    Car *head = NULL;
    Car *tail = NULL;
    // Car *curNode = NULL;
    // Car *sucNode = NULL;
    int limit = 0;

    void searchCar(string key)
    {
        Car *temp = head;
        if (head == NULL)
        {
            cout << "No cars here...";
        }
        while (temp != NULL)
        {
            if (temp->data == key)
            {
                temp = head;
                while (temp->data != key)
                {
                    temp = temp->next;
                    head = temp;
                }
                temp = temp->next;

                break;
            }
            else
            {
                temp = temp->next;
            }
        }
        limit--;
        cout << "Car " << temp->data << " Successfully removed! Took " << temp->count << " movements. Limit: " << limit << endl;
    }
    void arrivals(string line)
    {
        Car *arrivingCar = new Car;
        if (head != NULL)
        {
            arrivingCar->next = head;
            head = arrivingCar;
            arrivingCar->data = line;
            arrivingCar->data.erase(0, 2);
            limit++;
            cout << "car " << arrivingCar->data << " has arrived. Limit:" << limit << endl;
        }
        else
        {
            head = arrivingCar;
            tail = arrivingCar;
            head->data = line;
            if (head->data[0] == 'A')
            {
                arrivingCar->data.erase(0, 2);
                limit++;
                cout << "car " << arrivingCar->data << " has arrived at. Limit:" << limit << endl;
            }
            else if (head->data[0] == 'D')
            {
                // make a case for departing a car that doesnt exist
                // arrivingCar->data.erase(0, 2);
                // limit--;
                cout << "car does not exist in garage" << endl;
            }
        }
    }
};

int main()
{
    Stack lane1;
    Stack lane2;
    Stack street;

    string line;

    ifstream inFile("ParkingGarage.txt", ios::in);

    if (inFile.is_open())
    {
        while (getline(inFile, line))
        {
            if (lane1.limit != 10)
            {
                if (line[0] == 'D')
                {
                    line.erase(0, 2);
                    if (lane2.head == NULL)
                    {

                    }
                }
                else
                {
                    lane1.arrivals(line);
                }
            }
            else if (lane1.limit == 10 && lane2.limit != 10)
            {
                if (line[0] == 'D' && lane2.limit == 0)
                {
                    cout << "lane 2 empty, moving back to lane1" << endl;
                    lane1.searchCar(line.erase(0, 2));
                }
                else
                {
                    cout << "lane1 full, adding to lane2" << endl;
                    if (line[0] == 'D')
                    {
                        lane2.searchCar(line.erase(0, 2));
                    }
                    else
                    {
                        lane2.arrivals(line);
                    }
                }
            }
            else if (lane2.limit == 10 && street.limit != 10)
            {
                if (line[0] == 'D' && street.limit == 0)
                {
                    cout << "street empty, moving back to lane2" << endl;
                    lane2.searchCar(line.erase(0, 2));
                }
                else
                {
                    cout << "both lanes full, adding to the street" << endl;
                    if (line[0] == 'D')
                    {
                        street.searchCar(line.erase(0, 2));
                    }
                    else
                    {
                        street.arrivals(line);
                    }
                }
            }
            else
            {
                cout << "No more cars can enter. Please come back later" << endl;
            }
        }
        inFile.close();
    }
    else
    {
        cout << "error" << endl;
    }
}