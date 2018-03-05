/*
Program: List of customers
@: hoctt
*/

#include<iostream>
#include<stdio.h>
#include<vector>
#include<string.h>
using namespace std;

// Define customer type
#define PERSIONAL_CUSTOMER "CN"
#define COMPANY_CUSTOMER "CT"
#define FOREIGNER_CUSTOMER "NN"

// Declare structure information
typedef struct customer
{
	char mName[100];
	char mCusType[3]; //Type of customer CN/CT/NN
	char mProduct[100];
	int mQuantity;
	double mPrice;
}TY_Customer;

// Declare a vector type for list of customers
typedef std::vector<TY_Customer> TY_CustomerList;

// Main functions
int input_number_of_customers(void);
void input_customers_infor(TY_CustomerList* vList, int n);
void display_list(TY_CustomerList* vList);
void sort_customer_list(TY_CustomerList* vList);

// Other supporting functions
void print_menu(void); // Print selection menu
double get_discount(char* mCusType); //Get discount information
double calculate_money(TY_Customer *tmp); //Calculate total amount of money of each customer
void print_a_customer_info(TY_Customer *tmp); //Display information of a customer
bool compare(TY_Customer tmp1, TY_Customer tmp2); // Used for vector sort
void check_valid_input(void); // Check input data is valid or not

int main(int argc, char const *argv[])
{
	int select;
	static int numberOfCustomers = 0;

	char ss[2];
	// Declare a list
	//TY_Customer *cList = NULL;
	// Use vector to store customers information
	TY_CustomerList vList;

	/* CUSTOMERS MANAGERMENT PROGRAM */
	while (1) {
		print_menu();
		cin >> select;
		
		// User input wrong data
		if(!cin)
		{
		    // user didn't input a number
		    cin.clear(); // reset failbit
		    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
		}

		switch (select) {
			case 1: //Input number of customer
				numberOfCustomers = input_number_of_customers();
				break;

			case 2:
				input_customers_infor(&vList, numberOfCustomers);
				break;
			
			case 3:
				sort_customer_list(&vList);
				break;

			case 4:
				display_list(&vList);
				break;
			
			case 5:
				vList.clear();
				exit (1);
				break;
			
			default:
				break; 
		}	
	}
	
	return 0;
}

int input_number_of_customers(void)
{
	cout << "Please input number of customers (n>=1): \t";
	int n;
		cin >> n;

	while(!cin || n <=0) {
	    // user didn't input a number
	    cout << "Please input a positive numeric data! \n";
	    cin.clear(); // reset failed bit
	    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
	    cin >> n;
	}
	return n;
}

void input_customers_infor(TY_CustomerList* vList, int n) {
	//Input information of customers
	char select;
	if (!vList->empty()) {
		cout << "List is not empty. Do you want to add more data? (Y/N): ";
		cin >> select;
		if (select == 'N' || select == 'n')
			return;
	}
	
	TY_Customer tmp;
	for (int i = 0; i < n; i++) {
		cout << "Please input information of customer #" << i+1;
		
		cout << "\nInput customer name: ";
		cin >> tmp.mName;
		cout << "Customer name = " << tmp.mName << "\n";

		do {
			cout << "\nInput customer type [CN/CT/NN]: ";
			cin >> tmp.mCusType;
			//customer type must be CN, CT or NN
		} while ((strcmp(tmp.mCusType, "CN") != 0) && strcmp(tmp.mCusType, "CT") != 0 && strcmp(tmp.mCusType, "NN") != 0);
		cout << "Customer type = " << tmp.mCusType << "\n";

		cout << "\nInput product name: ";
		cin >> tmp.mProduct;

		cout << "Product = " << tmp.mProduct << "\n";
		
		// Quantity and Price must be digit data
		cout << "\nInput product quantity (Numeric): ";
		cin >> tmp.mQuantity;

		while(!cin) {
			// user didn't input a number
		    cin.clear(); // reset failed bit
		    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
		    cin >> tmp.mQuantity;
			}
		cout << "Quantity = " << tmp.mQuantity << "\n";

		cout << "\nInput product price (Numeric): ";
		cin >> tmp.mPrice;
		while(!cin) {
			// user didn't input a number
		    cin.clear(); // reset failed bit
		    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
		    cin >> tmp.mPrice;
			}
		cout << "Price = " << tmp.mPrice << "\n";

		if(!cin) 
		{
		    // user didn't input a number
		    cin.clear(); // reset failed bit
		    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //skip bad input
		}
		vList->push_back(tmp);
	}
	return;
}	

void display_list(TY_CustomerList* vList) {
	if(vList->empty()) {
		cout << "NO RECORDS\n";
		return;
	}
	cout << "NAME\t" << "TYPE\t" << "PRODUCT\t" << "QUANTITY\t" << "PRICE\t" << "MONEY\n";
	cout << "---------------------------------------------------------------\n";

	for (auto tmp : *vList) {
		print_a_customer_info(&tmp);
	}
}

void sort_customer_list(TY_CustomerList* vList) {
	if(vList->empty()) {
		cout << "NO RECORDS\n";
		return;
	}
	cout << "Sorted customers information by DESC price\n";
	std::sort(vList->begin(), vList->end(), compare);
}


/*Supporting functions definition*/
void print_menu(void) {
	cout <<"\n\t------------------------\n";
	cout <<"\tCUSTOMERS MANAGEMENT\t\n";
	cout <<"\t________________________\n";
	cout <<"\t1. Input number of customer\n";
	cout <<"\t2. Input customers information\n";
	cout <<"\t3. Sort customers information (PRICE DESC)\n";
	cout <<"\t4. Print customers information\n";
	cout <<"\t5. Exit program\n";
	cout <<"\t************************\n";
	cout <<"Please select:\n";
}

void print_a_customer_info(TY_Customer *tmp) {
	double money = calculate_money(tmp);
	cout << tmp->mName << "\t" << tmp->mCusType << "\t" << tmp->mProduct << "\t" << tmp->mQuantity << "\t" << tmp->mPrice << "\t" << 
	money << endl;
}

double get_discount(char* mCusType) {
	//Get discount of each customer type
	double discount = 0.0;
	if (strcmp(mCusType, (const char*)PERSIONAL_CUSTOMER) == 0) {
		discount = 0.8; // SaleOff 20%
	} else if (strcmp(mCusType, (const char*)COMPANY_CUSTOMER) == 0) {
		discount = 0.9; // SaleOff 10%
	} else {
		discount = 1; // SaleOff 0%
	}
	return discount;
}

double calculate_money(TY_Customer *tmp) {
	// Calculate total money of each customers
	double money = 0;
	double discount = get_discount(tmp->mCusType);
	money = tmp->mQuantity * tmp->mPrice * discount;
	//cout << "\nMoney = " << money;
	//cout << money;
	return money;
}

bool compare(TY_Customer tmp1, TY_Customer tmp2) {
	return (tmp1.mPrice > tmp2.mPrice);
}

void check_valid_input(void) {
	/*nothing*/
	return;
}


