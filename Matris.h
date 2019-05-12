#ifndef Matris_H
#define Matris_H

#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>
#include <initializer_list>


template <class T> class Matris {
public:
  typedef T* iterator;


   // Constructors
   Matris (): m_rows(0), m_cols(0), m_capacity(0) {
     static_assert(std::is_move_constructible<T>::value && std::is_move_assignable<T>::value, "Type is not move-constructable or assignable.");
     m_vec = new T[0];
   }
   explicit Matris (int dim): m_rows(dim), m_cols(dim), m_capacity(dim*dim) {
     static_assert(std::is_move_constructible<T>::value && std::is_move_assignable<T>::value, "Type is not move-constructable or assignable.");
     m_vec = new T[m_capacity]();
   }
   explicit Matris (int rows, int cols): m_rows(rows), m_cols(cols), m_capacity(rows*cols) {
     static_assert(std::is_move_constructible<T>::value && std::is_move_assignable<T>::value, "Type is not move-constructable or assignable.");
     m_vec = new T[m_capacity]();
   }
   // Initializer list - constructor
   Matris<T> (std::initializer_list<T>);
   // Copy constructor & copy assignment
   Matris<T> (const Matris<T> &);
   Matris<T>& operator= (const Matris<T> &);
   // Move constructor & move assignment
   Matris<T> (Matris<T> &&) noexcept;
   Matris<T>& operator= (Matris<T> &&) noexcept;
   // Destructor
   ~Matris(){ delete[] m_vec; }

   // Accessors
   unsigned int rows() const { return m_rows; }
   unsigned int cols() const { return m_cols; }

   T& operator() (const unsigned int, const unsigned int);
   const T& operator() (const unsigned int, const unsigned int) const;


   // operators
   void operator+= (const Matris<T> &);
   void operator-= (const Matris<T> &);
   void operator*= (const Matris<T> &);
   void operator*= (const T);

   // methods

   void reset(){ for (auto it = begin(); it != end(); it++){ *it = 0; }}


   Matris<T> transpose();

   Matris<T>& insert_row(unsigned int);
   Matris<T>& append_row(unsigned int);
   Matris<T>& remove_row(unsigned int);

   Matris<T>& insert_column(unsigned int);
   Matris<T>& append_column(unsigned int);
   Matris<T>& remove_column(unsigned int);

   iterator begin(){ return m_vec; }
   iterator end(){ return (m_vec + m_capacity); }

   //friend Matris<T> identity(unsigned int);

private:
   size_t m_rows;
   size_t m_cols;
   size_t m_capacity;
   T *m_vec;
   void is_valid();
};

template <class T> Matris<T> operator+ (const Matris<T> &, const Matris<T> &);
template <class T> Matris<T> operator- (const Matris<T> &, const Matris<T> &);
template <class T> Matris<T> operator* (const Matris<T> &, const Matris<T> &);
template <class T> Matris<T> operator* (const Matris<T> &, const T);

template <class T> std::ofstream& operator<< (std::ofstream&, const Matris<T> &);
template <class T> std::ostream& operator<< (std::ostream&, const Matris<T> &);
template <class T> std::ifstream& operator>> (std::ifstream&, Matris<T> &);

template <class T>
Matris<T> identity(unsigned int size){
  Matris<T> id(size);
  for (int i = 0; i < id.rows(); i++){
    id(i, i) = 1;
  }
  return id;
}


template <class T> void check_dimension(Matris<T>&, Matris<T>&, char);






// constructors

template <class T>
Matris<T>::Matris (const Matris<T> &m): m_rows(m.m_rows), m_cols(m.m_cols), m_capacity(m.m_capacity){
  static_assert(std::is_move_constructible<T>::value && std::is_move_assignable<T>::value, "Type is not move-constructable or assignable.");
  m_vec = new T[m_capacity];
  for (int i = 0; i != m_capacity; ++i){
    m_vec[i] = m.m_vec[i];
  }
}


template <class T>
Matris<T>::Matris (std::initializer_list<T> il){
  static_assert(std::is_move_constructible<T>::value && std::is_move_assignable<T>::value, "Type is not move-constructable or assignable.");
  unsigned dim = 0;
  while(il.size() > dim * dim){
    ++dim;
  }
  if (dim * dim != il.size()){
    throw std::out_of_range("Not an even square matrix. ");
  }

  m_rows = dim;
  m_cols = dim;
  m_capacity = dim * dim;
  m_vec = new T[m_capacity];
  auto it = il.begin();
  for (int i = 0; i != il.size(); ++i){
    m_vec[i] = *it;
    it++;
  }
}

template <class T>
Matris<T>& Matris<T>::operator= (const Matris<T> &rhs){
  static_assert(std::is_move_constructible<T>::value && std::is_move_assignable<T>::value, "Type is not move-constructable or assignable.");
  T new_m[rhs.m_capacity];
  std::copy(rhs.m_vec, rhs.m_vec + rhs.m_capacity, new_m);
  delete[] m_vec;
  m_vec = new T[rhs.m_capacity];
  std::move(new_m, new_m + rhs.m_capacity, m_vec);

  m_rows = rhs.m_rows;
  m_cols = rhs.m_cols;
  m_capacity = rhs.m_capacity;

  return *this;
}

template <class T>
Matris<T>::Matris (Matris<T> && rhs) noexcept :
m_rows(rhs.m_rows), m_cols(rhs.m_cols), m_capacity(rhs.m_capacity) {
  static_assert(std::is_move_constructible<T>::value && std::is_move_assignable<T>::value, "Type is not move-constructable or assignable.");
  m_vec = rhs.m_vec;
  rhs.m_rows = rhs.m_cols = rhs.m_capacity = 0;
  rhs.m_vec = nullptr;
}

template <class T>
Matris<T>& Matris<T>::operator= (Matris<T> && rhs) noexcept {
  static_assert(std::is_move_constructible<T>::value && std::is_move_assignable<T>::value, "Type is not move-constructable or assignable.");
  if (this != &rhs){
    delete[] m_vec;
    m_rows = rhs.m_rows;
    m_cols = rhs.m_cols;
    m_capacity = rhs.m_capacity;
    m_vec = rhs.m_vec;
    rhs.m_rows = rhs.m_cols = rhs.m_capacity = 0;
    rhs.m_vec = nullptr;
  }
  return *this;
}


/////////////////
//  ACCESSORS  //
/////////////////

template <class T>
T& Matris<T>::operator() (const unsigned int i, const unsigned int j){
  if (i * m_cols + j >= m_capacity || i * m_cols + j < 0){
    throw std::out_of_range("Index out of range.");
  }
  return m_vec[i * m_cols + j];
}

template <class T>
const T& Matris<T>::operator() (const unsigned int i, const unsigned int j) const {
  if (i * m_cols + j >= m_capacity || i * m_cols + j < 0){
    throw std::out_of_range("Index out of range.");
  }
  return m_vec[i * m_cols + j];
}


///////////////////////
//     OPERATORS     //
///////////////////////


/////   +    /////
template <class T>
void Matris<T>::operator+= (const Matris<T> & rhs){
  check_dimension(*this, rhs, '+');
  for (int i = 0; i < m_rows; i++){
    for (int j = 0; j < m_cols; j++){
      (*this)(i, j) += rhs(i, j);
    }
  }
}

template <class T>
Matris<T> operator+ (const Matris<T> & lhs, const Matris<T> & rhs){
  check_dimension(lhs, rhs, '+');
  Matris<T> result(lhs);
  result += rhs;
  return result;
}


/////   -    /////
template <class T>
void Matris<T>::operator-= (const Matris<T> & rhs){
  check_dimension(*this, rhs, '-');
  for (int i = 0; i < m_capacity; i++){
    m_vec[i] -= rhs.m_vec[i];
  }
}

template <class T>
Matris<T> operator- (const Matris<T> & lhs, const Matris<T> & rhs){
  check_dimension(lhs, rhs, '-');
  Matris<T> result(lhs);
  result -= rhs;
  return result;
}

/////     *     /////
template <class T>
void Matris<T>::operator*= (const Matris<T> & rhs){
  check_dimension((*this), rhs, '*');

  Matris<T> result(m_rows, rhs.cols());
  for (int i = 0; i < m_rows; i++){
    for (int j = 0; j < rhs.cols(); j++){
      for (int k = 0; k < rhs.rows(); k++){
        result(i, j) += (*this)(i, k) * rhs(k, j);
      }
    }
  }
  *this = std::move(result);
}

template <class T>
Matris<T> operator* (const Matris<T> & lhs, const Matris<T> & rhs){
  check_dimension(lhs, rhs, '*');

  Matris<T> result(lhs);
  result *= rhs;
  return result;
}

template <class T>
void Matris<T>::operator*= (const T scalar){
  for (int i = 0; i < m_rows; i++){
    for (int j = 0; j < m_cols; j++){
      (*this)(i, j) *= scalar;
    }
  }
}

template <class T>
Matris<T> operator* (const Matris<T>& lhs, const T scalar){
  Matris<T> result(lhs);
  result *= scalar;
  return result;
}








template <class T>
std::ofstream& operator<< (std::ofstream& os, const Matris<T> & rhs){
  for (int i = 0; i < rhs.rows(); i++){
    for (int j = 0; j < rhs.cols(); j++){
      os << rhs(i, j) << "\t";
    }
    os << std::endl;
  }
  return os;
}

template <class T>
std::ostream& operator<< (std::ostream& os, const Matris<T> & rhs){
  for (int i = 0; i < rhs.rows(); i++){
    for (int j = 0; j < rhs.cols(); j++){
      os << rhs(i, j) << "\t";
    }
    os << std::endl;
  }
  return os;
}


template <class T>
std::ifstream& operator>> (std::ifstream& is, Matris<T> & matris){
  std::string line;
  int value;
  std::queue<int> new_row;
  while (getline(is, line)){
    std::istringstream istrs(line);
    while (istrs >> value){
      new_row.push(value);
    }
    if (new_row.size() > matris.cols()){
      matris = Matris<T>(1, new_row.size());
    }
    else {
      matris.append_row(matris.rows()-1);
    }
    for (int i  = 0; i < matris.cols(); i++){
      matris(matris.rows()-1, i) = new_row.front();
      new_row.pop();
    }
  }
  return is;
}

// methods


template <class T>
Matris<T> Matris<T>::transpose(){
  Matris<T> transpose(m_cols, m_rows);
  for (int i = 0; i < m_rows; i++){
    for (int j = 0; j < m_cols; j++){
      transpose(j, i) = (*this)(i, j);
    }
  }
  return transpose;
}

template <class T>
Matris<T>& Matris<T>::insert_row(unsigned int index){
  Matris<T> new_matris(m_rows+1, m_cols);
  for (int i = 0; i < new_matris.rows(); i++){
    for (int j = 0; j < new_matris.cols(); j++){
      if (i < index){
        new_matris(i, j) = (*this)(i, j);
      }
      else if (i > index){
        new_matris(i, j) = (*this)(i-1, j);
      }
    }
  }
  *this = std::move(new_matris);
  return *this;
}

template <class T>
Matris<T>& Matris<T>::append_row(unsigned int index){
  Matris<T> new_matris(m_rows+1, m_cols);
  for (int i = 0; i < new_matris.rows(); i++){
    for (int j = 0; j < new_matris.cols(); j++){
      if (i <= index){
        new_matris(i, j) = (*this)(i, j);
      }
      else if (i > index + 1){
        new_matris(i, j) = (*this)(i-1, j);
      }
    }
  }
  *this = std::move(new_matris);
  return *this;
}

template <class T>
Matris<T>& Matris<T>::remove_row(unsigned int index){
  Matris<T> new_matris(m_rows-1, m_cols);
  for (int i = 0; i < new_matris.rows(); i++){
    for (int j = 0; j < new_matris.cols(); j++){
      if (i < index){
        new_matris(i, j) = (*this)(i, j);
      }
      else if (i >= index){
        new_matris(i, j) = (*this)(i+1, j);
      }
    }
  }
  *this = std::move(new_matris);
  return *this;
}

template <class T>
Matris<T>& Matris<T>::insert_column(unsigned int index){
  Matris<T> new_matris(m_rows, m_cols+1);
  for (int i = 0; i < new_matris.rows(); i++){
    for (int j = 0; j < new_matris.cols(); j++){
      if (j < index){
        new_matris(i, j) = (*this)(i, j);
      }
      else if (j > index){
        new_matris(i, j) = (*this)(i, j-1);
      }
    }
  }
  *this = std::move(new_matris);
  return *this;
}

template <class T>
Matris<T>& Matris<T>::append_column(unsigned int index){
  Matris<T> new_matris(m_rows, m_cols+1);
  for (int i = 0; i < new_matris.rows(); i++){
    for (int j = 0; j < new_matris.cols(); j++){
      if (j <= index){
        new_matris(i, j) = (*this)(i, j);
      }
      else if (j > index+1){
        new_matris(i, j) = (*this)(i, j-1);
      }
    }
  }
  *this = std::move(new_matris);
  return *this;
}

template <class T>
Matris<T>& Matris<T>::remove_column(unsigned int index){
  Matris<T> new_matris(m_rows, m_cols-1);
  for (int i = 0; i < new_matris.rows(); i++){
    for (int j = 0; j < new_matris.cols(); j++){
      if (j < index){
        new_matris(i, j) = (*this)(i, j);
      }
      else if (j >= index){
        new_matris(i, j) = (*this)(i, j+1);
      }
    }
  }
  *this = std::move(new_matris);
  return *this;
}

template <class T>
void check_dimension(const Matris<T>& lhs, const Matris<T>& rhs, const char c){
  switch (c) {
    case '+':
    case '-':
      if (lhs.rows() != rhs.rows() || lhs.cols() != rhs.cols()){
        throw std::out_of_range("Dimensions don't match.\n");
      }
      break;
    case '*':
      if (lhs.cols() != rhs.rows()){
        throw std::out_of_range("Dimensions don't match.\n");
      }
      break;
  }
}




#endif
