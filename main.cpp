// include headers (list, string, map, fstream, iostream, etc.)
#include <iostream>
#include <list>
#include <string>
#include <array>
#include <map>
#include <fstream>
#include <random>
#include <cmath>
#include <iomanip>

using namespace std;
const int AR_SIZE = 3, RATING_MAX = 1000, RATING_MIN = 100, PRICE_MAX = 6000, PRICE_MIN = 500;
const int P_CHANGE_MAX = 60, P_CHANGE_MIN = 10, R_CHANGE_MAX = 30, R_CHANGE_MIN = 5;
const int NEW_ITEM = 10, SALE = 7, PRICE_HIKE = 7, RATING_DEC = 10;
const int SW_TITLE = 40;

void new_item(map<string, array<list<double>, AR_SIZE>>& store);
void sale(array<list<double>, AR_SIZE> &item);
void price_hike(array<list<double>, AR_SIZE> &item);
void rating_decrease(array<list<double>, AR_SIZE> &item);
void calc_daily_sold(array<list<double>, AR_SIZE> &item);

// Define function to simulate new items added
void new_item(map<string, array<list<double>, AR_SIZE>>& store){
    // get random item name from external file
    ifstream item_list;
    bool need_new_item = true;
    string name = "";
    while(need_new_item){
        item_list.open("items.txt");
        if (!item_list.good()){
            cout << "Unable to open file" << endl;
        }
        int r1 = rand() % 59;
        int currentLine = 0;
        while(!item_list.eof()){
            currentLine++;
            getline(item_list, name);
            if (currentLine == r1){
                break;
            }
        }
        item_list.close();
        if (store.empty()){
            break;
        }
        else{
            for (const auto &pair : store){
                if (name == pair.first){
                    break;
                }
                else{
                    need_new_item = false;
                }
            }
        }
    }
    
    // declare and initialize array of lists
    array<list<double>, AR_SIZE> item_info;
    // insert random double (1-10, round to 1 decimals) into ratings list (2)
    double r2 = (rand() % (RATING_MAX - RATING_MIN + 1) + RATING_MIN) / (double) 100;
    double rat = round(r2 * 10.0)/10.0;
    item_info[2].push_back(rat);
    // insert random double (5-60, round to 2 decimals) into prices list (1)
    r2 = (rand() % (PRICE_MAX - PRICE_MIN + 1) + PRICE_MIN) / (double) 100;
    double pr = round(r2 * 100.0)/100.0;
    item_info[1].push_back(pr);
    // call function to calculate number of copies sold per day (0)
    calc_daily_sold(item_info);
    // insert new pair into map (item name, array of lists)
    store.insert(make_pair(name, item_info));
    // output "new item added: " name, price, rating
    cout << "New item added to store: " << name << " [$" << pr << ", " << rat << "]" << endl;
}

// Define function to simulate an item going on sale
void sale(array<list<double>, AR_SIZE> &item){
    // get sale % from random int (10-60)
    int p_change = (rand() % (P_CHANGE_MAX - P_CHANGE_MIN + 1)) + P_CHANGE_MIN;
    double old_price = item[1].back();
    // declare int = most recent price * sale %
    double new_price = old_price - (item[1].back() * (p_change/100.0));
    new_price = round(new_price * 100.0) / 100.0;
    // insert new price into prices list
    item[1].push_back(new_price);
    // insert new value into ratings list = same as most recent rating
    item[2].push_back(item[2].back());
    // output item "has gone on sale for " [sale %]
    // output past price -> current price
    cout << " has gone on sale for " << p_change << "% [$" << old_price << " -> $" << new_price << "]" << endl;
}

// Define function to simulate an item going up in price
void price_hike(array<list<double>, AR_SIZE> &item){
    // get price increase % from random int (10-60)
    int p_change = (rand() % (P_CHANGE_MAX - P_CHANGE_MIN + 1)) + P_CHANGE_MIN;
    double old_price = item[1].back();
    // declare int = most recent price * price decrease %
    double new_price = old_price + (item[1].back() * (p_change/100.0));
    new_price = round(new_price * 100.0) / 100.0;
    // insert new price into prices list
    item[1].push_back(new_price);
    // insert new value into ratings list = same as most recent rating
    item[2].push_back(item[2].back());
    // output "price for " item " has increased by " [increase %]
    // output past price -> current price
    cout << " has increased by " << p_change << "% [$" << old_price << " -> $" << new_price << "]" << endl;
}

// Define function to simulate rating decrease
void rating_decrease(array<list<double>, AR_SIZE> &item){
    // get rating decrease % from random int (5-30)
    int r_change = (rand() % (R_CHANGE_MAX - R_CHANGE_MIN + 1)) + R_CHANGE_MIN;
    double old_rating = item[2].back();
    // declare int = most recent rating * rating decrease %
    double new_rating = old_rating - (item[2].back() * (r_change/100.0));
    new_rating = round(new_rating * 10.0) / 10.0;
    // insert new price into ratings list
    item[2].push_back(new_rating);
    // insert new value into prices list = same as most recent price
    item[1].push_back(item[1].back());
    // output item "'s rating has decreased"
    // output past rating -> current rating
    cout << "'s rating has decreased by " << r_change << "% [" << old_rating << " -> " << new_rating <<"]" << endl;
}

// Define function to calculate daily amount of items sold
void calc_daily_sold(array<list<double>, AR_SIZE> &item){
    // copies sold today = (most recent rating)*(60 - most recent price)
    double recent_rat = item[2].back();
    cout << recent_rat << endl;
    double recent_pr = item[1].back();
    cout << recent_pr << endl;
    cout << (recent_rat)*(PRICE_MAX - recent_pr) << endl;
    int copies_sold = (recent_rat)*(PRICE_MAX - recent_pr);
    // insert value above into copies sold list
    item[0].push_back(copies_sold);
}

void print_summary(map<string, array<list<double>, AR_SIZE>>& store){
    cout << "--Daily Summary--" << endl;
    for (const auto &pair : store){
        string name = pair.first;
        array<list<double>, AR_SIZE> item = pair.second;
        double pr = item[1].back();
        double rat = item[2].back();
        cout << "> " << name << " [$" << pr << ", " << rat << "]" << endl;
    }
}

// Define main function
int main(){
    srand(time(0));
    // declare map <string, array of lists [3]>
    map<string, array<list<double>, AR_SIZE>> store;
    // Day 1 - run for loop 5 times to add items to store
        // call func to add new items
    cout << "Day 1 - Store Opens" << endl;
    for (int i = 0; i < 1; i++){
        new_item(store);
    }
    cout << endl;
    // Day 2 to 50 - for run for loop to simulate each day
    for (int i = 2; i <= 5; i++){
        bool event = false;
        cout << "Day " << i << endl;
        int r = 0;
        // declare int r = 0 -> determines if event occurs
        // for loop that iterates through each item in map
        for (auto &pair : store){
            // set r to random int (1-100)
            r = rand() % 100 + 1;
            // if r meets condition for price hike
            if (r == PRICE_HIKE){
                // call price hike func
                cout << "Price for " << pair.first;
                price_hike(pair.second);
                event = true;
                break;
            }
            // set r to random int (1-100)
            r = rand() % 100 + 1;
            // if r meets condition for sale
            if (r == SALE){
                // call sale func
                cout << pair.first;
                sale(pair.second);
                event = true;
                break;
            }
            // set r to random int (1-100)
            r = rand() % 100 + 1;
            // if r meets condition for rating decrease
            if (r == RATING_DEC){
                // call rating decrease func
                cout << pair.first;
                rating_decrease(pair.second);
                event = true;
                break;
            }
        // call func to calculate copies sold today
        calc_daily_sold(pair.second);
        }
        // set r to random int (1-100)
        r = rand() % 100 + 1;
        // if r meets condition for new release
        if (r == NEW_ITEM){
            // call new release func
            new_item(store);
            event = true;
        }
        if (!event){
            cout << "No new updates" << endl;
        }
        print_summary(store);
        cout << endl;
    }

    // after whole simulation is completed, use for loop to display data 
    cout << "--Overall Summary--" << endl;
    cout << left << setw(SW_TITLE) << "Release Data" << setw(SW_TITLE) << "Final Data" << endl;
    for (const auto &pair : store){
        // for each item - data upon release vs. final data
        array<list<double>, AR_SIZE> item = pair.second;
        cout << pair.first << " - [" << item[0].front() << ", $" << item[1].front() << ", " << item[2].front() << "]"
            <<  "[" << item[0].back() << ", $" << item[1].back() << ", " << item[2].back() << "]" << endl;
    }
    
    return 0;
}