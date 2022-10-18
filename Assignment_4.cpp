//02-13-2022
//This is a vending machine program that displays a type of snack to
//be purchased, its price, and it's quantity in stock. The user will then
//enter quarters and choose a snack to buy. If it is not exact the change
//will be dispensed. At the end of the purchases a closing report will
//display the number of a snack left in stock, the number of a snack bought,
//and the time it was bought.

#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#pragma warning(disable:4996)

using namespace std;

class Snack {
private:
    string name;
    double price;
    int quantity;
    int itemsSold;
    string* ptr;

public:
    void setName(string Name)
        {name = Name;}
    void setPrice(double Price)
        {price = Price;}
    void setQuantity(int Quantity){
        quantity = Quantity;
        ptr = new string[quantity];
    }
    void setItemsSold(int ItemsSold)
        {itemsSold = ItemsSold;}

    string getName() const
        {return name ;}
    double getPrice() const
        {return price;}
    int getQuantity() const
        {return quantity;}

    //receives and returns nothing, and initializes Snack class variables
    Snack() {
        name = " ", price = 0, quantity = 0, itemsSold = 0;
    }

    //receives a string, double, int, and int variable, returns nothing,
    //and assigned inputted variables to private class variables. Also
    //creates array of strings.
    Snack(string Name, double Price, int Quantity, int ItemsSold = 0) {
        name = Name;
        price = Price;
        quantity = Quantity;
        itemsSold = ItemsSold;

        ptr = new string[quantity];
    }

    //Destructor: receives and returns nothing, displays the closing report
    //of quantity,items sold, time purchased of snacks.
    ~Snack() {
        cout << "\nClosing info for " << name << ":" << endl;
        cout << "       " << quantity << " in stock" << endl;
        cout << "       " << itemsSold << " sold for a profit of $"
             << price * itemsSold << endl;
        cout << "\nTransactions occurred at:" << endl;
        for(int i = 0; i < itemsSold; i++){
            cout << "       " << ptr[i] << endl;
        }
    }

    //Received a double variable representing the number of quarters entered
    //and returns a bool variable (either 1 or 0) either true or false. This
    //function tells the user if they are able to buy the item they want, and
    //dispenses change if needed.
    bool buyItem(double& moneyEntered) {
        if (quantity == 0) {
            cout << "Unfortunately this snack is sold-out.\n" << endl;
            return false;
        }
        else {
            if (moneyEntered >= price) {
                moneyEntered -= price;
                quantity -= 1;
                itemsSold += 1;
                cout << "Item has been dispensed below" << endl;

                ptr[itemsSold - 1] = getCurrentTime();

                if(moneyEntered == 0) {
                    cout << endl;
                    return true;
                }
                else {
                    cout << "$" << moneyEntered
                         << " dispensed below\n" << endl;
                }
            }
            else if (moneyEntered < price) {
                cout << "You did not enter enough "
                        "money to buy this item.\n" << endl;
                return false;
            }
        }
    }

    //Receives nothing and returns a string that represents the time
    //at which the user bought the snack.
    string getCurrentTime() {
        time_t t = time(0);
        struct tm ts;
        char buff[10];
        ts = *localtime(&t);
        strftime(buff, sizeof(buff), "%X", &ts);
        return buff;
    }

};

void userBuyItem(Snack [], int);
void displayVendingMachine(const Snack [], int);
bool promptToContinue();
int getQuarter();

int main() {
    int const elem = 3;
    Snack snackArr[elem] = {Snack (),
                            Snack ("Candy", 1.25, 5),
                            Snack ("Soda", 1.00, 2) };

    snackArr[0].setName("Chips");
    snackArr[0].setPrice(1.75);
    snackArr[0].setQuantity(3);

    do {
        userBuyItem(snackArr, elem);
    } while (promptToContinue());

    return 0;
}

//This function receives the array of snack info and the number of snacks.
//It does not return anything and asked the user to pick an item to buy.
//The function will repeat if number choice is invalid
void userBuyItem(Snack arr[], int elem) {
    int repeat;
    int itemNum = 0;
    displayVendingMachine(arr, elem);
    double quarter = getQuarter();
    quarter /= 4;
    cout << "Amount Entered: $" << fixed << setprecision(2)
         << quarter << endl;
    do {
        repeat = 0;
        cout << "\nEnter an item number between 1 and 3 to purchase: ";
        cin >> itemNum;
        if (itemNum < 1 || itemNum > 3) {
            cout << "Please selection an item "
                    "number between 1 and 3." << endl;
            repeat = 1;
        }
        else {
            if(itemNum == 1){
                arr[0].buyItem(quarter);
            }
            else if(itemNum == 2){
                arr[1].buyItem(quarter);
            }
            else if(itemNum == 3){
                arr[2].buyItem(quarter);
            }
        }
    }while (repeat == 1);
}

//This function displays the vending machine options of snack,
//with price, and quantity, after receiving the array of snack
//info and number of snacks. Returns nothing.
void displayVendingMachine(const Snack arr[], int num) {
    cout
            << left << setw(10) << "Item #"
            << left << setw(14) << "Item Name"
            << left << setw(10) << "Price"
            << left << setw(8) << "# in-stock" << endl;
    cout << "---------------------------------------------" << endl;

    for(int i = 0; i < num; i++){
        cout
                << left << "  " << setw(8) << i + 1
                << left << setw(14) << arr[i].getName()
                << left << setw(12) << setprecision(2)
                << fixed<< arr[i].getPrice()
                << left << setw(10) << arr[i].getQuantity() << endl;
    }
}

//This function receives nothing and ask user to
//enter a number of quarters and repeats if number
//is less than one. Returns the number of quarters entered.
int getQuarter() {
    int quarters;
    int repeat = 0;
    do {
        cout << "\nEnter a number of quarters: ";
        cin >> quarters;
        if(quarters < 1) {
            cout << "Please enter a number of quarters more than 0" << endl;
            repeat = 1;
        }
        else {
            return quarters;
        }
    }while(repeat == 1);

}

//This function receives nothing and asks the user if they would
//like to exit the vending machine and returns their
//decision in true or false.
bool promptToContinue(){
    char exit;
    bool repeat = false;
    do {
        if(repeat){
            cout << "Please enter either 'Y' or 'N'" << endl;
        }
        cout << "Would you like to exit? (Y / N): ";
        cin >> exit;
        if (exit == 'N' || exit == 'n') {
            cout << endl;
            return true;
        }
        else if (exit == 'Y' || exit == 'y') {
            return false;
        }
        else
            repeat = true;

    } while(repeat);
}

/*
Item #    Item Name     Price     # in-stock
---------------------------------------------
  1       Chips         1.75        3
  2       Candy         1.25        5
  3       Soda          1.00        2

Enter a number of quarters: 3
Amount Entered: $0.75

Enter an item number between 1 and 3 to purchase: 3
You did not enter enough money to buy this item.

Would you like to exit? (Y / N): n

Item #    Item Name     Price     # in-stock
---------------------------------------------
  1       Chips         1.75        3
  2       Candy         1.25        5
  3       Soda          1.00        2

Enter a number of quarters: -1
Please enter a number of quarters more than 0

Enter a number of quarters: 4
Amount Entered: $1.00

Enter an item number between 1 and 3 to purchase: 3
Item has been dispensed below

Would you like to exit? (Y / N): n

Item #    Item Name     Price     # in-stock
---------------------------------------------
  1       Chips         1.75        3
  2       Candy         1.25        5
  3       Soda          1.00        1

Enter a number of quarters: 8
Amount Entered: $2.00

Enter an item number between 1 and 3 to purchase: 2
Item has been dispensed below
$0.75 dispensed below

Would you like to exit? (Y / N): N

Item #    Item Name     Price     # in-stock
---------------------------------------------
  1       Chips         1.75        3
  2       Candy         1.25        4
  3       Soda          1.00        1

Enter a number of quarters: 6
Amount Entered: $1.50

Enter an item number between 1 and 3 to purchase: 3
Item has been dispensed below
$0.50 dispensed below

Would you like to exit? (Y / N): n

Item #    Item Name     Price     # in-stock
---------------------------------------------
  1       Chips         1.75        3
  2       Candy         1.25        4
  3       Soda          1.00        0

Enter a number of quarters: 4
Amount Entered: $1.00

Enter an item number between 1 and 3 to purchase: 3
Unfortunately this snack is sold-out.

Would you like to exit? (Y / N): y

Closing info for Soda:
       0 in stock
       2 sold for a profit of $2.00

Transactions occurred at:
       17:38:40
       17:38:56

Closing info for Candy:
       4 in stock
       1 sold for a profit of $1.25

Transactions occurred at:
       17:38:48

Closing info for Chips:
       3 in stock
       0 sold for a profit of $0.00

Transactions occurred at:

Process finished with exit code 0
 */