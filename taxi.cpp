#include <bits/stdc++.h>
using namespace std;
int totalTaxi=10,bookingId=0,totalCustomer=0;
class Taxi
{
private:
    char currentLocation='A';
    char *pickUpLocation;
    char *dropLocation;
    int *pickUpTime;
    int *dropTime;
    int *earnings;
    int *customerId;
    int totalRides=0;
public:

    Taxi()
    {
        pickUpLocation=new char[20];
        dropLocation=new char[20];
        pickUpTime=new int[20];
        dropTime=new int[20];
        earnings=new int[20];
        customerId=new int[20];
        for(int i=0;i<20;i++)
        {
            earnings[i]=0;
        }
    }
    setCurrentLocation(char ch)
    {
        currentLocation=ch;
    }
    char getCurrentLocation()
    {
        return currentLocation;
    }
    setPickUpLocation(int ind,char ch)
    {
        pickUpLocation[ind]=ch;
    }
    char* getPickUpLocation()
    {
        return pickUpLocation;
    }
    setDropLocation(int ind,char ch)
    {
        dropLocation[ind]=ch;

    }
    char* getDropLocation()
    {
        return dropLocation;
    }
    setPickUpTime(int ind,int time)
    {
        pickUpTime[ind]=time;
    }
    int* getPickUpTime()
    {
        return pickUpTime;
    }
    setDropTime(int ind,int time)
    {
        dropTime[ind]=time;
    }
    int* getDropTime()
    {
        return dropTime;
    }
     setTotalEarnings(int ind,int earning)
    {
        earnings[ind]=earning;
    }
    int* getTotalEarnings()
    {
        return earnings;
    }
    setTotalRides()
    {
        totalRides++;
    }
    int getTotalRides()
    {
        return totalRides;
    }
     setCustomerId(int ind,int id)
    {
        customerId[ind]=id;
    }
    int* getCustomerId()
    {
        return customerId;
    }
};
Taxi availableTaxi[10];
class CustomerUtil
{
    public:
    void bookTaxi()
    {
        cout<<"ENTER PICKUP LOCATION   ";
        char pickUpPoint;
        cin>>pickUpPoint;
        cout<<"ENTER DROP LOCATION   ";
        char dropPoint;
        cin>>dropPoint;
        cout<<"ENTER PICKUP TIME   ";
        int pickUpTime;
        cin>>pickUpTime;
        int taxi=0,taxiEarnings=0,set=0;
        Taxi *currentTaxi;
        for(int i=0;i<totalTaxi;i++)
        {

            currentTaxi=&availableTaxi[i];
            int ind;
            if(currentTaxi->getTotalRides()==0)
            {
                ind=0;
            }
            else
            {
                ind=currentTaxi->getTotalRides()-1;
            }
            if(currentTaxi->getCurrentLocation()==pickUpPoint && !(pickUpTime>=currentTaxi->getPickUpTime()[ind] && pickUpTime<=currentTaxi->getDropTime()[ind]))
            {
              //  cout<<"tsdsad "<<endl;
                set=1;
                if(taxi==0){
                taxi=i+1;
          //      cout<<"sddfs "<<taxiEarnings<<" "<<taxi<<endl;
                taxiEarnings=currentTaxi->getTotalEarnings()[ind];
                }
                else{
                    if(currentTaxi->getTotalEarnings()[ind]<taxiEarnings)
                    {
                        taxi=i+1;
                       // cout<<"asdd "<<currentTaxi->getTotalEarnings()[ind]<<" "<<taxiEarnings<<" "<<taxi<<endl;
                        taxiEarnings=currentTaxi->getTotalEarnings()[ind];
                    }
                }
            }

        }
        int distance=100;
        if(set==0)
        {
            for(int i=0;i<totalTaxi;i++)
            {
                currentTaxi=&availableTaxi[i];
                int ind;
            if(currentTaxi->getTotalRides()==0)
            {
                ind=0;
            }
            else
            {
                ind=currentTaxi->getTotalRides()-1;
            }
                if(currentTaxi->getCurrentLocation()-pickUpPoint<distance && !(pickUpTime>=currentTaxi->getPickUpTime()[ind] && pickUpTime<=currentTaxi->getDropTime()[ind]))
                {
                   // cout<<"saadsda"<<endl;
                    set=1;
                    distance=currentTaxi->getCurrentLocation()-pickUpPoint;
                    taxi=i+1;
                    taxiEarnings=currentTaxi->getTotalEarnings()[ind];
                }
                else if(currentTaxi->getCurrentLocation()-pickUpPoint==distance && !(pickUpTime>currentTaxi->getPickUpTime()[ind] && pickUpTime<currentTaxi->getDropTime()[ind]))
                {
                    if(currentTaxi->getTotalEarnings()[ind]<availableTaxi[taxi-1].getTotalEarnings()[availableTaxi[taxi-1].getTotalRides()])
                    {
                      //  cout<<"bjahgjfasj"<<endl;
                        set=1;
                        taxi=i;
                        taxiEarnings=currentTaxi->getTotalEarnings()[ind];
                    }
                }

            }
        }
        if(set==1)
        {
            currentTaxi=&availableTaxi[taxi-1];
           currentTaxi->setCustomerId(availableTaxi[taxi-1].getTotalRides(),++totalCustomer);
           currentTaxi->setPickUpLocation(availableTaxi[taxi-1].getTotalRides(),pickUpPoint);
           currentTaxi->setDropLocation(availableTaxi[taxi-1].getTotalRides(),dropPoint);
            currentTaxi->setPickUpTime(availableTaxi[taxi-1].getTotalRides(),pickUpTime);
         //   cout<<"sdadsa  "<<dropPoint-pickUpPoint<<" "<<pickUpTime+(dropPoint-pickUpPoint)<<" "<<pickUpTime+(dropPoint-pickUpPoint)+1<<endl;
            currentTaxi->setDropTime(availableTaxi[taxi-1].getTotalRides(),pickUpTime+(dropPoint-pickUpPoint));
            currentTaxi->setTotalEarnings(availableTaxi[taxi-1].getTotalRides(),((((dropPoint-pickUpPoint)*15)-5)*10)+100);
            currentTaxi->setCurrentLocation(dropPoint);
            availableTaxi[taxi-1].setTotalRides();
            cout<<"Taxi can be allotted."<<endl;
            cout<<"Taxi-"<<taxi<<" is allotted";
        }
        else
        {
            cout<<"No Taxi Available"<<endl;
        }
    }

};
class AdminUtil
{
    public:
    void displayDetails()
    {
        for(int i=0;i<totalTaxi;i++)
        {

            Taxi currentTaxi=availableTaxi[i];
            if(currentTaxi.getTotalRides()>0){
            cout<<"TAXI "<<i+1<<endl;
            cout<<setw(15)<<"CUSTOMER_ID"
            <<"|"<<setw(15)<<"FROM"
            <<"|"<<setw(15)<<"TO"
            <<"|"<<setw(15)<<"PICKUP "
            <<"|"<<setw(15)<<"DROP"
            <<"|"<<setw(15)<<"EARNINGS"<<endl;

            for(int j=0;j<currentTaxi.getTotalRides();j++)
            {
                cout<<setw(15)<<currentTaxi.getCustomerId()[j];
                cout<<"|"<<setw(15)<<currentTaxi.getPickUpLocation()[j];
                cout<<"|"<<setw(15)<<currentTaxi.getDropLocation()[j];
                cout<<"|"<<setw(15)<<currentTaxi.getPickUpTime()[j];
                cout<<"|"<<setw(15)<<currentTaxi.getDropTime()[j];
                cout<<"|"<<setw(15)<<currentTaxi.getTotalEarnings()[j];
                cout<<endl;
            }
            cout<<endl;
            }
        }
    }
};
int main()
{


    int choice;
    do{
     cout<<"CHOOSE ANY OPERATIONS"<<endl;
    cout<<"1.CALL TAXI BOOKING"<<endl;
    cout<<"2.DISPLAY TAXI DETAILS"<<endl;
    cout<<"3.EXIT"<<endl;
    cin>>choice;
    CustomerUtil customerUtil;
    switch(choice)
    {
    case 1:
        customerUtil.bookTaxi();
        break;
    case 2:
        AdminUtil adminUtil;
        adminUtil.displayDetails();
        break;
    case 3:
        break;
    }
    }while(choice!=3);
}
