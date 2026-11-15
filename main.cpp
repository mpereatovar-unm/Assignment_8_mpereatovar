
/*Source code for the Electric_Field and Magnetic_Field classes
https://www.learncpp.com/cpp-tutorial/destructors/, https://www.w3schools.com/cpp/cpp_constructors.asp?
https://www.learncpp.com/cpp-tutorial/shallow-vs-deep-copying/, https://www.geeksforgeeks.org/cpp/c-plus-plus/
AI: Chat GPT, Claude AI*/


#include <iostream>  // For cout and endl
#include <cmath>     // For sqrt()
using namespace std;

// BASE CLASS - Stores x, y, z for both fields
class Field {
protected:
    double *value;  // Array for the 3 components

public:
    // Default constructor: starts at zero
    Field() {
        value = new double[3]{0, 0, 0};
    }

    // Constructor with x, y, z values
    Field(double x, double y, double z) {
        value = new double[3]{x, y, z};
    }

    // Copy constructor: makes a new copy of the array
    Field(const Field& other) {
        value = new double[3]{
            other.value[0], other.value[1], other.value[2]
        };
    }

    // Copy assignment: copies values between existing objects
    Field& operator=(const Field& other) {
        if (this != &other) {
            for (int i = 0; i < 3; i++) {
                value[i] = other.value[i];
            }
        }
        return *this;
    }

    // Destructor: frees the memory
    virtual ~Field() {
        delete[] value;
    }

    // Setters: change each component
    void setX(double x) { value[0] = x; }
    void setY(double y) { value[1] = y; }
    void setZ(double z) { value[2] = z; }

    // Getters: return each component
    double getX() const { return value[0]; }
    double getY() const { return value[1]; }
    double getZ() const { return value[2]; }

    // Calculate the magnitude of the vector
    double calculateMagnitude() const {
        return sqrt(value[0]*value[0] +
                    value[1]*value[1] +
                    value[2]*value[2]);
    }

    // Print the three components and magnitude
    void printMagnitude() const {
        cout << "x = " << value[0]
             << ", y = " << value[1]
             << ", z = " << value[2] << endl;

        cout << "Magnitude = " << calculateMagnitude() << endl;
    }
};

// ELECTRIC FIELD CLASS - Inherits from Field
class Electric_Field : public Field {
private:
    double electricResult;  // Stores the calculated electric field

public:
    // Default constructor
    Electric_Field() : Field() {
        electricResult = 0;
    }

    // Constructor with 3 components
    Electric_Field(double x, double y, double z) : Field(x, y, z) {
        electricResult = 0;
    }

    // Copy constructor
    Electric_Field(const Electric_Field& other) : Field(other) {
        electricResult = other.electricResult;
    }

    // Copy assignment uses Field's safe copying
    Electric_Field& operator=(const Electric_Field& other) = default;

    // Calculate electric field using Gauss' Law
    void calculateElectric(double Q, double r) {
        const double pi = 3.141592653589793;
        const double epsilon0 = 8.8541878128e-12;

        if (r <= 0) {
            cout << "Distance must be positive" << endl;
            return;
        }

        // E = Q / (4*pi*r^2*epsilon0)
        electricResult = Q / (4 * pi * r * r * epsilon0);
    }

    // Return calculated electric field
    double getElectricResult() const {
        return electricResult;
    }

    // + operator: adds two electric field vectors
    Electric_Field operator+(const Electric_Field& other) const {
        return Electric_Field(
            value[0] + other.value[0],
            value[1] + other.value[1],
            value[2] + other.value[2]
        );
    }

    // << operator: allows cout to print the components
    friend ostream& operator<<(ostream& out, const Electric_Field& e) {
        out << "(" << e.value[0] << ", "
            << e.value[1] << ", " << e.value[2] << ")";
        return out;
    }
};

// MAGNETIC FIELD CLASS - Inherits from Field
class Magnetic_Field : public Field {
private:
    double magneticResult;  // Stores the calculated magnetic field

public:
    // Default constructor
    Magnetic_Field() : Field() {
        magneticResult = 0;
    }

    // Constructor with 3 components
    Magnetic_Field(double x, double y, double z) : Field(x, y, z) {
        magneticResult = 0;
    }

    // Copy constructor
    Magnetic_Field(const Magnetic_Field& other) : Field(other) {
        magneticResult = other.magneticResult;
    }

    // Copy assignment uses Field's safe copying
    Magnetic_Field& operator=(const Magnetic_Field& other) = default;

    // Calculate magnetic field using the assignment formula
    void calculateMagnetic(double I, double r) {
        const double pi = 3.141592653589793;
        const double mu0 = 4 * pi * 1e-7;

        if (r <= 0) {
            cout << "Distance must be positive" << endl;
            return;
        }

        // B = I / (2*pi*r*mu0) as written in the assignment
        magneticResult = I / (2 * pi * r * mu0);
    }

    // Return calculated magnetic field
    double getMagneticResult() const {
        return magneticResult;
    }

    // + operator: adds two magnetic field vectors
    Magnetic_Field operator+(const Magnetic_Field& other) const {
        return Magnetic_Field(
            value[0] + other.value[0],
            value[1] + other.value[1],
            value[2] + other.value[2]
        );
    }

    // << operator: allows cout to print the components
    friend ostream& operator<<(ostream& out, const Magnetic_Field& b) {
        out << "(" << b.value[0] << ", "
            << b.value[1] << ", " << b.value[2] << ")";
        return out;
    }
};

// MAIN FUNCTION - Tests both classes
int main() {

    // Create electric field objects
    Electric_Field E1(3, 4, 12);
    Electric_Field E2(1, 2, 3);
    Electric_Field E3;

    // Create magnetic field objects
    Magnetic_Field B1(2, 3, 6);
    Magnetic_Field B2(1, 1, 1);
    Magnetic_Field B3;

    // Print the components and magnitude
    cout << "Electric Field 1:" << endl;
    E1.printMagnitude();

    cout << "Magnetic Field 1:" << endl;
    B1.printMagnitude();

    // Calculate electric field using charge and distance
    // Q = 1e-9 Coulombs, r = 0.5 meters
    E1.calculateElectric(1e-9, 0.5);

    // Calculate magnetic field using current and distance
    // I = 2 Amps, r = 0.1 meters
    B1.calculateMagnetic(2, 0.1);

    // Display calculated results
    cout << "Electric field from Gauss' Law: "
         << E1.getElectricResult() << endl;

    cout << "Magnetic field from assignment formula: "
         << B1.getMagneticResult() << endl;

    // Use + operator to add the fields
    E3 = E1 + E2;
    B3 = B1 + B2;

    // Use << operator to print the results
    cout << "E1 + E2 = " << E3 << endl;
    cout << "B1 + B2 = " << B3 << endl;

    // Test copy constructors
    Electric_Field Ecopy(E1);
    Magnetic_Field Bcopy(B1);

    cout << "Copy of E1 = " << Ecopy << endl;
    cout << "Copy of B1 = " << Bcopy << endl;

    return 0;
}
/*Personal notes about Assignment 8
1. Base Class (class Field)
The Field class is the main class used to store the x, y, and z components of both electric and magnetic fields.
Instead of creating separate arrays for each class like in Assignment 7, one pointer called value that points to a dynamically allocated 
array with three numbers. It's protected so the electric and magnetic field classes can access these values through inheritance.
This makes the code easier to organize because both classes can use the same functions.

2. Constructors (Field() and Field(double x, double y, double z))
The constructors are used to create and initialize the field objects. The default constructor creates an array with three components set to zero, 
while the second constructor allows me to assign the x, y, and z values when creating an object. For example, Electric_Field E1(3, 4, 12) 
passes these values to the base class constructor, which stores them in the array.

3. Copy Constructor (Field(const Field& other))
The copy constructor creates a new object using the values from another object. Since the array is dynamically allocated, 
It needed to make a separate copy so both objects don't share the same memory. This prevents problems when one of the objects is destroyed or changed. 
The electric and magnetic field classes also have their own copy constructors, which call the base class copy constructor 
and copy their calculated field results.

4. Copy Assignment Operator (operator=)
The copy assignment operator is used when It wants to copy the values of one object into another object that already exists.
It checks that It's not copying an object into itself and then copies the three components. The derived classes also copy their stored 
electric or magnetic results. Unlike the copy constructor, this function does not create a new object.

5. Destructor (virtual ~Field())
The destructor releases the memory that was allocated when the object was created. Since the program uses new double[3] to create an array, 
the destructor uses delete[] value to free that memory. The keyword virtual makes sure the correct destructor is called if an object is deleted 
through a pointer to the base class.

6. Setters and Getters
The setter functions, setX(), setY(), and setZ(), allow me to change the three components of a field after creating an object.
The getter functions, getX(), getY(), and getZ(), return the values stored in the array. Because these functions belong to the base class,
both electric and magnetic field objects can use them without having to write the functions again.

7. Calculate Magnitude (calculateMagnitude())
The calculateMagnitude() function finds the length of the field vector using the x, y, and z components. It squares each component,
adds the results, and takes the square root using sqrt(). For example, if the components are (3, 4, 12), the magnitude is 13. 
This function returns the calculated number so it can be used elsewhere in the program.

8. Print Magnitude (printMagnitude())
The printMagnitude() function displays the x, y, and z components along with the magnitude of the field. Instead of calculating everything again, 
it calls calculateMagnitude() to get the result. Since this function is in the base class, both electric and magnetic field objects can use it.

9. Electric Field Class (class Electric_Field : public Field)
The Electric_Field class inherits from the Field class, meaning it can use the array, getters, setters, and magnitude functions already created. 
It also added a private variable called electricResult to store the electric field calculated using Gauss' Law. This class has its own constructors, 
which call the base class constructors to initialize the components.

10. Electric Field Calculation (calculateElectric())
The calculateElectric() function uses Gauss' Law to calculate the electric field based on a given charge and distance. 
It takes two values, Q for the charge in Coulombs and r for the distance in meters. The function uses the permittivity of free space, epsilon0, 
in the formula and stores the result in electricResult. It also included a check to make sure the distance is greater than zero so the program
doesn't divide by zero. The getElectricResult() function returns the stored result.

11. Magnetic Field Class (class Magnetic_Field : public Field)
The Magnetic_Field class also inherits from the base class, so it uses the same array structure and common functions. 
The main difference is that it has a private variable called magneticResult, which stores the magnetic field calculated from the current 
and distance. The constructors initialize this result to zero and pass the x, y, and z components to the base class.

12. Magnetic Field Calculation (calculateMagnetic())
The calculateMagnetic() function uses the formula provided in the assignment to calculate the magnetic field. It receives 
the current I in amperes and distance r in meters. The function uses the constant mu0, which represents the permeability of free space, 
and stores the calculated result in magneticResult. The getMagneticResult() function returns this value so it can be displayed on the screen.

13. Addition Operator (operator+)
The overloaded + operator allows it to add two electric fields or two magnetic fields using the normal addition symbol. Instead of 
adding single numbers, the program adds the corresponding x, y, and z components of the two objects. For example, adding (3, 4, 12) 
and (1, 2, 3) gives (4, 6, 15). The function then creates and returns a new field object with those values.

14. Output Operator (operator<<)
The overloaded << operator allows it to print a field object directly using cout. Normally, C++ doesn't automatically know how to
display an entire object, so It created this function to tell the program what to print. For example, cout << E1 displays the electric
field components as (3, 4, 12). The friend keyword allows this function to access the components of the object.

15. Main Function (int main())
The main() function is where the program starts running and tests the classes. It created three electric field objects and three 
magnetic field objects using both the default and parameterized constructors. The program first displays the components and magnitudes 
of the fields. Then, It uses example values for charge, current, and distance to calculate the electric and magnetic fields. After that, 
It test the overloaded + operator by adding two field objects and the << operator by displaying the results. Finally, It create copies of the 
electric and magnetic field objects to test the copy constructors.
*/