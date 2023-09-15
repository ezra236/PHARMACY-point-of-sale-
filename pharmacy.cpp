#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <conio.h> // Include the conio.h library for getch() (Windows-specific)

using namespace std;

class Pharmacy {
private:
    double total = 0.0;
    string productDetails;
    vector<int> productQuantities; // Use a vector instead of an array
    string adminPassword = "123"; // Administrator password

public:
    // Constructor to initialize productQuantities
    Pharmacy() : productQuantities(8, 10) {}

    void processOrder(const string& productName, double productPrice) {
        int productIndex = getProductIndex(productName);
        if (productIndex >= 0) {
            if (!productQuantities.empty() && productQuantities[productIndex] > 0) {
                total += productPrice;
                productDetails += productName + "\t\t$" + to_string(productPrice) + "\n";
                productQuantities[productIndex]--;
                cout << "Adding " << productName << " to the order. Price: $" << productPrice << endl;
            } else {
                cout << "Product " << productName << " is out of stock." << endl;
            }
        } else {
            cout << "Invalid product name. Please try again." << endl;
        }
    }

    void addProductQuantity(const string& productName, int quantity, const string& password) {
        if (adminPassword == password) {
            int productIndex = getProductIndex(productName);
            if (productIndex >= 0) {
                productQuantities[productIndex] += quantity;
                cout << "-----------------------------------------------------------------------\n";
                cout << "Added " << quantity << " packets of " << productName << " to the stock." << endl;
                cout << "\nNEW QUANTITY OF " << productName << ": " << productQuantities[productIndex] << " packets" << endl;
            } else {
                cout << "Invalid product name. Please try again." << endl;
            }
        } else {
            cout << "Incorrect password. Only the administrator can add product quantity." << endl;
        }
    }

    void printReceipt(const string& fname, const string& sname) {
        ofstream file("receipt.txt");
        if (file.is_open()) {
            file << "------ Receipt ------" << endl;
            file << fname << "\t" << sname << endl;
            file << "Product\t\tPrice" << endl;
            file << productDetails;
            file << "---------------------" << endl;
            file << "Total:\t\t$" << total << endl;
            file.close();

            cout << "\nReceipt has been stored in receipt.txt" << endl;
        } else {
            cout << "Unable to create the receipt file." << endl;
        }
    }

    void printtheReceipt(const string& fname, const string& sname) {
        cout << "" << endl;
        cout << "" << endl;
        cout << "------------------- RECEIPT ------------------" << endl;
        cout << "Customer Name: " << fname << "\t" << sname << endl;
        cout << "Product\t\tPrice" << endl;
        cout << "---------------------------------\n";
        cout << productDetails;
        cout << "--------------------------------------------" << endl;
        cout << "Total:\t\t$" << total << endl;
    }

    // Function to add a new product to the system
    void addNewProduct(const string& productName, double productPrice, const string& password) {
        if (adminPassword == password) {
            int productIndex = getProductIndex(productName);
            if (productIndex == -1) {
                productDetails += productName + "\t\t$" + to_string(productPrice) + "\n";
                productQuantities.push_back(10); // Initialize with some initial quantity
                cout<<"--------------------------------------------------------------------------";
                cout << "Added new product: " << productName << " Price: $" << productPrice << endl;
            } else {
                cout << "Product with the same name already exists. Use 'addProductQuantity' to update quantity." << endl;
            }
        } else {
            cout << "Incorrect password. Only the administrator can add a new product." << endl;
        }
    }

private:
    int getProductIndex(const string& productName) {
        if (productName == "ventrolin") {
            return 0;
        } else if (productName == "lucozade") {
            return 1;
        } else if (productName == "p-Alaxin") {
            return 2;
        } else if (productName == "paracetamol") {
            return 3;
        } else if (productName == "penicilin") {
            return 4;
        } else if (productName == "aspirin") {
            return 5;
        } else if (productName == "mara moja") {
            return 6;
        } else if (productName == "panadol") {
            return 7;
        } else {
            return -1; // Invalid product name
        }
    }
};

int main() {
    Pharmacy pharmacy;
    string role, password;
    string productName;
    string fname, sname;

    cout << "-------------------------------------WELCOME TO THE PHARMACY---------------------------------------------" << endl;
    cout << "\t--------------------------------------------------------\n";
    cout << "ENTER AS:\n";
    cout << "1. 'admin' for administrator:\n2. 'customer' for customer:\n3. 'view' to see available products: ";
    cin >> role;

    if (role == "admin") {
        cout << "-------------------------------------------------------------------- \n";
        cout << "--------------------------------------------------------------------- ";
        cout << "\nEnter the password ****: ";

        // Use getch() to read the password without displaying it on the screen
        char ch;
        password = "";
        while ((ch = _getch()) != '\r') { // Read characters until Enter (carriage return) is pressed
            password.push_back(ch);
            cout << "*"; // Display asterisks for each character entered
        }

        if (password == "123") {
            string choice;
            cout << "\nAdministrator access granted." << endl;
            cout << "ADD a new product('new') or add product Quantity('quantity'): \t";
            cin >> choice;

            if (choice == "new") {
                cout << "Enter the name of the new product: ";
                cin >> productName;
                cout << "Enter the price of the new product: ";
                double productPrice;
                cin >> productPrice;

                pharmacy.addNewProduct(productName, productPrice, password);
            } else if (choice == "quantity") {
                cout << "Enter the name of the product to add quantity (or 'done' to finish): ";
                cin >> productName;

                while (productName != "done") {
                    int quantity;
                    cout << "Enter the quantity to add for " << productName << ": ";
                    cin >> quantity;

                    pharmacy.addProductQuantity(productName, quantity, password);

                    cout << "Enter the name of the product to add quantity (or 'done' to finish): ";
                    cin >> productName;
                }
            }
        } else {
            cout << "\nIncorrect password. Exiting." << endl;
            return 0;
        }
    } else if (role == "customer") {
            cout << "-----------------------------------------------------------------------------------\n ";
        cout << "NAME: ";
        cin >> fname;
        cout << " THE OTHER NAME: ";
        cin >> sname;
        cout << "Enter the name of the product (or 'done' to finish): ";
        cin >> productName;

        while (productName != "done") {
            double productPrice = 0;

            if (productName == "ventrolin") {
                productPrice = 2.0;
            } else if (productName == "lucozade") {
                productPrice = 3.0;
            } else if (productName == "p-Alaxin") {
                productPrice = 1.5;
            } else if (productName == "paracetamol") {
                productPrice = 1.0;
            } else if (productName == "penicilin") {
                productPrice = 1.0;
            } else if (productName == "aspirin") {
                productPrice = 1.0;
            } else if (productName == "mara moja") {
                productPrice = 1.0;
            } else if (productName == "panadol") {
                productPrice = 1.0;
            } else {
                cout << "Invalid product name. Please try again." << endl;
            }

            if (productPrice > 0) {
                pharmacy.processOrder(productName, productPrice);
            }

            cout << "Enter the name of the product (or 'done' to finish): ";
            cin >> productName;
        }

        pharmacy.printReceipt(fname, sname);
        pharmacy.printtheReceipt(fname, sname);
    } else if (role == "view") {
        cout << "-------------------------------------------------------------" << endl;
        cout << "Available products: " << endl;
        cout << "-------------------------------------------------------------" << endl;
        cout << "ventrolin\t\t$2.0" << endl;
        cout << "lucozade\t\t$3.0" << endl;
        cout << "p-Alaxin\t\t$1.5" << endl;
        cout << "paracetamol\t\t$1.0" << endl;
        cout << "penicilin\t\t$1.0" << endl;
        cout << "aspirin\t\t\t$1.0" << endl;
        cout << "mara moja\t\t$1.0" << endl;
        cout << "panadol\t\t\t$1.0" << endl;
    } else {
        cout << "Invalid role. Exiting." << endl;
    }

    return 0;
}
