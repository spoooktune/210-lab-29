// include headers (list, string, map, fstream, iostream, etc.)
#include <iostream>
#include <list>
#include <string>
#include <map>
#include <fstream>
#include <random>
#include <cmath>

using namespace std;
const int AR_SIZE = 3, RATING_MAX = 1000, RATING_MIN = 100, PRICE_MAX = 6000, PRICE_MIN = 500;

void new_item(map<string, list<double>[AR_SIZE]>& store);
void sale(list<double> (&item)[AR_SIZE]);
void price_hike(list<double> (&item)[AR_SIZE]);
void rating_decrease(list<double> (&item)[AR_SIZE]);
void calc_daily_sold(list<double> (&item)[AR_SIZE]);

// Define function to simulate new items added
void new_item(map<string, list<double>[AR_SIZE]>& store){
    // get random item name from external file
    ifstream item_list;
    item_list.open("items.txt");
    if (!item_list.good()){
        cout << "Unable to open file" << endl;
    }
    int r = rand() % 59;
    int currentLine = 0;
    string name = "";
    while(!item_list.eof()){
        currentLine++;
        getline(item_list, name);
        if (currentLine == r){
            break;
        }
    }
    item_list.close();
    
    // declare and initialize array of lists
    list<double> (item_info)[AR_SIZE];
    // insert random double (1-10, round to 1 decimals) into ratings list (2)
    double r = (rand() % (RATING_MAX - RATING_MIN + 1) + RATING_MIN) / (double) 100;

    // insert random double (5-60, round to 2 decimals) into prices list (1)
    // call function to calculate number of copies sold per day (0)
    // insert new pair into map (item name, array of lists)
    // output "new item added: " name, price, rating
}

// Define function to simulate an item going on sale
    // params: &array for item
    // get sale % from random int (10-60)
    // declare int = most recent price * sale %
    // insert new price into prices list
    // insert new value into ratings list = same as most recent rating
    // output item "has gone on sale for " [sale %]
    // output past price -> current price

// Define function to simulate an item going up in price
    // params: &array for item
    // get price increase % from random int (10-60)
    // declare int = most recent price * price decrease %
    // insert new price into prices list
    // insert new value into ratings list = same as most recent rating
    // output "price for " item " has increased by " [increase %]
    // output past price -> current price

// Define function to simulate rating decrease
    // params: &array for item
    // get rating decrease % from random int (5-30)
    // declare int = most recent rating * rating decrease %
    // insert new price into ratings list
    // insert new value into prices list = same as most recent price
    // output item "'s rating has decreased"
    // output past rating -> current rating

// Define function to calculate daily amount of items sold
    // params: &array for item
    // copies sold today = (most recent rating)*(60 - most recent price)
    // insert value above into copies sold list

// Define main function
int main(){

}
    // declare map <string, array of lists [3]>
    // Day 1 - run for loop 5 times to add items to store
        // call func to add new items
    // Day 2 to 50 - for run for loop to simulate each day
        // declare int r = 0 -> determines if event occurs
        // for loop that iterates through each item in map
            // set r to random int (1-100)
            // if r meets condition for price hike
                // call price hike func

            // set r to random int (1-100)
            // if r meets condition for sale
                // call sale func
            
            // set r to random int (1-100)
            // if r meets condition for rating decrease
                // call rating decrease func
        // call func to calculate copies sold today
        // set r to random int (1-100)
        // if r meets condition for new release
            // call new release func

    // after whole simulation is completed, use for loop to display data 
    // for each item - data upon release vs. final data 