
#include <iostream>

#include <string>



#include <fstream>  //you must include this library if you wish to do file i/o

using namespace std;

const int SIZE = 50; //the capacity of the array which is the total amount

 //of memory allocated to the array.  The is a static

 //array, therefore the compiler will manage its memory,

 //allocate and de-allocate the memory.





class order_record

{

public:

    string cell_number;

    string item_number;

    double quantity;

    double price;

    int processing_plant;

    double tax_rate;

    double order_tax;

    double net_cost;

    double total_cost;

};





//Prototypes for your functions: input, output, process and tally_inventory will go here



void input(order_record  INV[], int& count);

void output(const order_record  INV[], const int  count);

void process(order_record  INV[], const int  count);

double tally_inventory(const order_record  INV[], const int count);


//Here is your driver to test the program

int main()

{
    // Create class object array

    order_record INV[SIZE];
    //Variable for count

    int count;

    //Call function to get records from a file
    input(INV, count);

    process(INV, count);

    output(INV, count);

    cout << "Average Total Order Cost = " << tally_inventory(INV, count) << endl;
}




//Function Implementations will go here



///*************************************************************************************

//Name:  input

//Precondition: the variables have not been initialized

//Postcondition: The variables are now initialized.

//Description:  Read contents from data file



//*************************************************************************************



void input(order_record  INV[], int& count)

{
    count = 0;
    //declare an ifstream

    ifstream in;

    //open the ifstream with the data file name

    in.open("purchase_data_Assignment6.txt");

    if (in.fail())

    {

        cout << "Input file did not open correctly" << endl;

    }

    else


        //use a while loop to read the data into the array INV

        while (!in.eof() && count < SIZE)

        {

            // //add more code to read the contents of the data file into the array
            order_record order;

            //

            in >> order.cell_number >> order.item_number >> order.quantity >> order.price >> order.processing_plant;
            INV[count] = order;


            count++;

        }

    //close ifstream

    in.close();

}

///*************************************************************************************

//Name:  output

//Precondition: All variables are initialized

//Postcondition: All variables are initialized.

//Description:  Prints the array to a datafile

//*************************************************************************************



void output(const order_record INV[], const int count)

{

    // /********************************************/

    // //declare an ofstream

    ofstream out;

    // //open the ofstream with the data file name

    out.open("myresults.txt");

    

    // //Use the following statement to help you format you our output. These statements are called the magic formula.

    out.setf(ios::showpoint); //remember, we are using out instead of cout

    out.precision(2);

    out.setf(ios::fixed);

    //

    // //use a for loop to print the data in the array INV

    for (int i = 0; i < count; i++)// do not use SIZE

    {

        out << INV[i].cell_number << " \t";

        out << INV[i].item_number << " \t";

        out << INV[i].quantity << " \t";

        out << INV[i].price << " \t";

        out << INV[i].processing_plant <<" \t";

        out << INV[i].tax_rate * 100 << " \t";

        out << INV[i].order_tax << "  \t";

        out << INV[i].net_cost << "   \t";

        out << INV[i].total_cost  << endl;

    }

    // //close the ouput file stream

    out.close();

}

//

/////*************************************************************************************

////Name:  process

////Precondition: cell_number, item_number, quantity, price, and processing_plant initialized.

//// tax_rate, tax_cost, net_cost, and total_cost not initialized.

////Postcondition: all variables are now initialized

////Description:  calculate tax rate, tax cost, net cost, and total cost.

////*************************************************************************************

//

void process(order_record INV[], const int count)

{

    for (int i = 0; i < count; i++) {
        if (0 <= INV[i].processing_plant && INV[i].processing_plant <= 50) {
            INV[i].tax_rate = .06;
        }
        else if (51 <= INV[i].processing_plant && INV[i].processing_plant <= 110) {
            INV[i].tax_rate = .07;
        }
        else if (111 <= INV[i].processing_plant && INV[i].processing_plant <= 200) {
            INV[i].tax_rate = .08;
        }
        else if (201 <= INV[i].processing_plant && INV[i].processing_plant <= 500) {
            INV[i].tax_rate = .09;
        }
        else {
            INV[i].tax_rate = .11;
        }
        INV[i].order_tax = INV[i].quantity * INV[i].price * INV[i].tax_rate;
        INV[i].net_cost = INV[i].quantity * INV[i].price;
        INV[i].total_cost = INV[i].net_cost + INV[i].order_tax;
    }
}



/////*************************************************************************************

////Name:  tally_results

////Precondition: you complete

////Postcondition: you complete

////Description: you complete

////*************************************************************************************

double tally_inventory(const order_record  INV[], const int  count)

{
    double average = 0.0;

    for (int i = 0; i < count; i++) {
        average += INV[i].total_cost;
    }
    average /= count;

    average = (average + 50) / 100 * 100;

    return average;
}




