/* ASSGN D Polynomial test program
Author: Loi Ha
lnh56@zips.uakron.edu
Purpose: Overload operators to correctly perform polynomial tests.
*/
// Assignment D
// Polynomial test program.
#include <iostream>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <array>

using namespace std;

class Polynomial
{
public:

   static const int maxTerms = 100; // maximum number of terms

   Polynomial();
   // ****************************************************
   // overload   +     // addition  (~25 lines)
   // overload   -     // subtraction  (~35 lines)
   // overload   *     // multiplication  (~25 busy lines)
   // overload   =     // assignment (~12 lines)
   // overload   +=    (~2 lines)
   // overload   -=    (~2 lines)
   // overload   *=    (~2 lines)
   // ****************************************************
   void enterTerms();
   std::string toString() const;
   int getNumberOfTerms() const; // user can only retrieve value
   int getTermExponent(int) const;
   int getTermCoefficient(int) const;
   void setCoefficient(int, int); // set coefficient of a specific term
   ~Polynomial(); // destructor
   Polynomial operator+(const Polynomial& ) const;


private:

   size_t numberOfTerms;
   std::array<int, maxTerms> exponents; // exponent array
   std::array<int, maxTerms> coefficients; // coefficients array
   static void polynomialCombine(Polynomial&); // combine common terms
};


int main()
{
   Polynomial a;
   Polynomial b;

   a.enterTerms();
   b.enterTerms();

   cout << "First polynomial is: " << a.toString();
   cout << "\nSecond polynomial is: " << b.toString() << "\n";

   Polynomial t{a}; // save the original value of a
   Polynomial c{a + b};
   cout << "\nc = a + b yields: " << c.toString();

//   a += b;
   cout << "\n\na += b yields: " << a.toString();

   a = t;  // reset a to original value
//   c = a - b;
//   cout << "\n\nc = a - b yields: " << c.toString();

//   a -= b;
   cout << "\n\na -= b yields: " << a.toString();

   a = t;  // reset a to original value
//   c = a * b;
//   cout << "\n\nc = a * b yields: " << c.toString();

//   a *= b;
   cout << "\n\na *= b the polynomials yields: " << a.toString();
   cout << endl;
}


Polynomial::Polynomial()
   : numberOfTerms(0)
{
   for (int t{0}; t < maxTerms; ++t)
   {
      coefficients[t] = 0;
      exponents[t] = 0;
   }
}

string Polynomial::toString() const
{
   ostringstream output;
   size_t start;
   bool zero{false};

   if (coefficients[0])
    { // output constants
      output << coefficients[0];
      start = 1;
      zero = true; // at least one term exists
   }
   else
   {
      if (coefficients[1])
      {
         output << coefficients[1] << 'x';  // constant does not exist
                                          // so output first term
                                          // without a sign
         if ((exponents[1] != 0) && (exponents[1] != 1))
         {
            output << '^' << exponents[1];
         }

         zero = true;  // at least one term exists
      }

      start = 2;
   }

   // output remaining polynomial terms
   for (size_t x{start}; x < maxTerms; ++x)
   {
      if (coefficients[x] != 0)
      {
         output << showpos << coefficients[x] << noshowpos << 'x';

         if ((exponents[x] != 0) && (exponents[x] != 1)) {
            output << '^' << exponents[x];
         }

         zero = true; // at least one term exists
      }
   }

   if (!zero)
   { // no terms exist in the polynomial
      output << '0';
   }

   return output.str();
}

/* Here you can place your overloaded operators
operator=
operator+
operator+=
operator-
operator-=
operator*
operator*=
*/
Polynomial Polynomial::operator+(const Polynomial& rhs) const
{
    Polynomial sum;
    size_t largestTerm;
    if (this->numberOfTerms > rhs.numberOfTerms)
    {
        largestTerm = this->numberOfTerms;
    }
    else
    {
       largestTerm = rhs.numberOfTerms;
    }
    for (size_t x = 0; x < largestTerm; ++x)
    {
        for (size_t y = 0; y < largestTerm; ++y)
        {
            if (this->exponents[x] == rhs.exponents[y])
            {
                sum.coefficients[x] = this->coefficients[x] + rhs.coefficients[y];
                sum.exponents[x] = this->exponents[x];
            }
            else
            {


            }

        }

    }
    return sum;
}

// Use this function to combine your terms during the overload operations
void Polynomial::polynomialCombine(Polynomial& w)
{
   Polynomial temp{w};

   // zero out elements of w
   for (size_t x{0}; x < maxTerms; ++x)
   {
      w.coefficients[x] = 0;
      w.exponents[x] = 0;
   }

   for (size_t x{1}; x < maxTerms; ++x)
   {
      for (size_t y{x + 1}; y < maxTerms; ++y)
      {
         if (temp.exponents[x] == temp.exponents[y])
         {
            temp.coefficients[x] += temp.coefficients[y];
            temp.exponents[y] = 0;
            temp.coefficients[y] = 0;
         }
      }
   }

   w = temp;
}


void Polynomial::enterTerms()
{
   bool found{false};
   size_t term;
   cout << "Enter each of your polynomial terms separately ..." << endl;
   cout << "\nEnter number of polynomial terms: ";
   cin >> numberOfTerms;

   for (size_t n{0}; n < maxTerms && n < numberOfTerms; ++n)
   {
      cout << "\nEnter coefficient: ";
      int c;
      cin >> c;
      cout << "Enter exponent: ";
      int e;
      cin >> e;

      if (c != 0)
      {
         // exponents of zero are forced into first element
         if (e == 0) {
            coefficients[0] += c;
            continue;
         }

         for (term = 1; (term < maxTerms) && (coefficients[term] != 0); ++term)
         {
            if (e == exponents[term]) {
               coefficients[term] += c;
               exponents[term] = e;
               found = true;  // existing exponent updated
            }
         }

         if (!found) { // add term
            coefficients[term] += c;
            exponents[term] = e;
         }
      }
   }
}

int Polynomial::getNumberOfTerms() const
{
   return numberOfTerms;
}

int Polynomial::getTermExponent(int term) const
{
   return exponents[term];
}

int Polynomial::getTermCoefficient(int term) const
{
   return coefficients[term];
}

void Polynomial::setCoefficient(int term, int coefficient)
{
   if (coefficients[term] == 0) { // no term at this location
      cout << "No term at this location, cannot set term." << endl;
   }
   else { // otherwise, set term
      coefficients[term] = coefficient;
   }
}

// destructor
Polynomial::~Polynomial() {
   // empty destructor
}
