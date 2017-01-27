//==================================================================================================//
//=01/30/2017                                                                       Alexander Alava=//
//=dynarr.h                                                                               U35432961=//
//=                                                                                                =//
//=                         This is the header file for the dynarr class                           =//
//==================================================================================================//

#include <cassert>
#include <iostream>
#include <string>

// Declaring and defining the generic run-time exception class //
class RuntimeException
{
  protected:
  // Declaring a string variable //
  std::string errorMsg;

  public:
  // Declaring and defining the constructor of the class with parameter string reference //
  RuntimeException(const std::string& err)
  {
    // Assigning the value of the parameter to the data member //
    errorMsg = err;
  }

  // Declaring and defining the getMessage function that will access a private data member //
  std::string getMessage() const
  {
    return errorMsg;
  }
};

// Declaring and defining class InvalidIndex that inherits from class RuntimeException //
class InvalidIndex : public RuntimeException
{
  public:

  InvalidIndex(const std::string& err): RuntimeException(err){}
};

// Declaring and defining the
template <class dynElem> class dynarr
{
  private:

  // Declaring an int variable and a template type pointer variable //
  int capacity;
  dynElem *A;

  public:

  // Declaring the default constructor of the class dynarr //
  dynarr() : capacity(0), A(NULL)
  {
    // Empty body constructor, variables initialized inline //
  }

  // Declaring a second constructor of the class dynarr with an int as a parameter //
  dynarr(int N): capacity(N), A(new dynElem[N])
  {
    // Empty body constructor, variables initialized inline //
  }

  // Declaring a the copy constructor //
  dynarr(const dynarr<dynElem> &other);

  // Declaring the destructor of the class dynarr //
  ~dynarr();

  // Declaring the overloading operator = function //
  dynarr<dynElem> & operator=( const dynarr<dynElem> &other);

  // Declaring the overloading operator [] function //
  dynElem & operator[](int ndx) throw(InvalidIndex);

  // Declaring the getCapacity function //
  int getCapacity();

  // Declaring the reserve function //
  void reserve(int newcap);
};


// Defining the copy constructor //
template <class dynElem> dynarr<dynElem>::dynarr(const dynarr<dynElem> &other)
{
  // Allocating memory for the new array //
  A = new dynElem[other.capacity];

  // Establishing a for loop to run through all the elements of the parameter array //
  for (int i = 0; i < other.capacity; i++)
  {
    // Copying all the elements of the parameter array into the new array //
    A[i] = other.A[i];
  }

  // Initilizing the capacity of the new
  capacity = other.capacity;
}

// Defining the destructor for the dynarr class //
template <class dynElem> dynarr<dynElem>::~dynarr()
{
  // Deleting the array //
  delete [] A;
}

// Defining the overloading operator = function //
template <class dynElem> dynarr<dynElem> & dynarr<dynElem>::operator=(const dynarr<dynElem> &other)
{
  // Checking if the parameter array is the same as the current array //
  if (this == &other)
  {
    // Returning the array unchanged //
    return *this;
  }

  // Deallocating the memory previously used for the old array //
  delete [] A;

  // Reallocating the memory needed for the array //
  A = new dynElem[other.capacity];

  // Establishing a for loop that will run through all the elements of the parameter array //
  for (int i = 0; i < other.capacity; i++)
  {
    // Copying all the elements of the paramenter array to the new array //
    A[i] = other.A[i];
  }

  // Adjusting the capacity of the new array //
  capacity = other.capacity;

  return *this;
}

// Defining the overloading operator [] function //
template <class dynElem> dynElem & dynarr<dynElem>::operator[](int ndx) throw(InvalidIndex)
{
  // Checking if the index entered as a parameter is less than zero //
  if (ndx < 0)
  {
    // Throwing custom exception for an invalid index //
    throw InvalidIndex("Array index is negative");
  }
  // Checking if the index entered as a parameter is more than the capacity //
  else if (ndx > capacity)
  {
    // Throwing custom exception for an invalid index //
    throw InvalidIndex("Array index is too large");
  }

  return A[ndx];
}

// Defining the function that will access a private data member //
template <class dynElem> int dynarr<dynElem>::getCapacity()
{
  return capacity;
}

template <class dynElem> void dynarr<dynElem>::reserve(int newcap)
{
  // Checking if the the current capacity satifies the requirement //
  if (newcap <= capacity)
  {
    return;
  }
  // Checking if the current capacity of the array is still zero //
  else if (capacity == 0)
  {
    // Allocating memory for the array that was empty //
    A = new dynElem[newcap];
  }
  // Adding extra memory to the current array //
  else
  {
    // Declaring a new array and allocating memory to it //
    dynElem *newA;
    newA = new dynElem[newcap];

    // Establishing a for loop that will run through all the elements of the array //
    for (int i = 0; i < capacity; i++)
    {
      // Copying all the elements of the array //
      newA[i] = A[i];
    }

    // Deallocating the memory of the old array and adjusting the pointer //
    delete [] A;
    A = newA;

    // Adjusting the new capacity of the array //
    capacity = newcap;
  }
}
