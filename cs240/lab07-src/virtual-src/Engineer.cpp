#include "Engineer.h"

/*
	To Do: Implement class Engineer
*/

/**
 * Constructor
 * Parameters:
 *      id - The Employee ID of this new employee
 *      name - A pointer to a character string containing the Engineer's name
 *      salary - The Engineer's salary (This will be lower than the Manager's salary....)
 * Remarks:
 *
 */
Engineer::Engineer(int id, char* name, double salary) : Employee(id, name, salary) {

}


/**
 * Assign a given Product to an Engineer
 * Parameter:
 *      product - The Product to be managed
 * Returns:
 *      true if the product was added successfully, false otherwise
 */
bool Engineer::addProduct(const Product& product) {
    return true;
}

/**
 * Remove a given Product from the Engineer
 * Returns:
 *      true if the project was found and removed from
 *      the list of managed projects, false otherwise
 */
bool Engineer::removeProduct(const Product& product) {
    return false;
}

/**
 * Print out the information about the Engineer
 * Remarks:
 *      Print out the Engineer's information in the following
 *      format 'Employee ID: %d\nName: %s\nSalary: %d' and print
 *      each product in the following format 'Has Product Data: %d Cost: %f\n'
 *
 */
void Engineer::print() {

}

/**
 * Return the value of the Engineer
 * Returns:
 *      The total cost of all the products the engineer is working on
 */
double Engineer::valueOf() {
    return 0.0;
}
