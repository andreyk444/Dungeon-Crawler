#ifndef vector_hpp
#define vector_hpp

#include <iostream>
#include <limits>



template<class T>
class Matrix;


template<class T, bool is_const>
class Iterator {
private:
    typedef std::conditional_t<is_const, const T, T> *ptr_t;

    ptr_t ptr_;


    friend Matrix<T>;
    friend Iterator<T, !is_const>;

public:
    typedef ptrdiff_t difference_type;
    typedef T value_type;
    typedef T element_type;
    typedef std::conditional_t<is_const, const T, T> *pointer;
    typedef std::conditional_t<is_const, const T, T> &reference;
    typedef std::contiguous_iterator_tag iterator_category;


    Iterator() noexcept;


    explicit Iterator(ptr_t ptr);

    template<bool other_const>
    explicit Iterator(const Iterator<T, other_const> &o) noexcept requires (is_const >= other_const);

    // 0 0+
    // 0 1 иначет  терям  конст
    // 1 0+
    // 1 1+
    template<bool other_const>
    explicit Iterator(Iterator<T, other_const> &&o) noexcept requires (is_const >= other_const);

    template<bool other_const>
    Iterator &operator=(const Iterator<T, other_const> &o) noexcept requires (is_const >= other_const);

    template<bool other_const>
    Iterator &operator=(Iterator<T, other_const> &&o) noexcept requires (is_const >= other_const);//change

    reference operator*() const noexcept;

    pointer operator->() const noexcept;

    template<bool other_const>
    bool operator==(const Iterator<T, other_const> &o) const noexcept;

//    template<bool other_const>
//    bool operator!=(const Iterator<T, other_const> &o) const noexcept;

    template<bool other_const>
    auto operator<=>(const Iterator<T, other_const> &o) const noexcept {return ptr_ <=> o.ptr_;};


    Iterator &operator++() noexcept;

    Iterator operator++(int) noexcept;

    Iterator &operator--() noexcept;

    Iterator operator--(int) noexcept;


    Iterator &operator+=( difference_type movement);

    Iterator &operator-=( difference_type movement);

    template<bool other_const>
    difference_type operator-(const Iterator<T, other_const> &o) const;

    Iterator operator-(difference_type other) const;

    //friend Iterator operator-(difference_type other, const Iterator &);
// it - num = it -> it = it + num
// it - it = num -> it = num + it

    Iterator operator+(difference_type other) const;

    friend Iterator operator+(difference_type other, const Iterator &);


    reference operator[](difference_type other) const noexcept;


};


static_assert(std::contiguous_iterator<Iterator<int, true>>);
static_assert(std::contiguous_iterator<Iterator<int, false>>);

template<class T, bool is_const>
Iterator<T, is_const>::Iterator(ptr_t ptr) : ptr_(ptr) {}


template<class T, bool is_const>
Iterator<T, is_const>::Iterator() noexcept:ptr_(nullptr) {}

template<class T, bool is_const>
template<bool other_const>
Iterator<T, is_const>::Iterator(const Iterator<T, other_const> &other)
noexcept requires (is_const >= other_const): ptr_{other.ptr_} {}

template<class T, bool is_const>
template<bool other_const>
Iterator<T, is_const>::Iterator(Iterator<T, other_const> &&other) noexcept requires (is_const >= other_const) :ptr_{std::move(other.ptr_)} {

}


template<class T, bool is_const>
template<bool other_const>
Iterator<T, is_const> &Iterator<T, is_const>::operator=(Iterator<T, other_const> &&o)
        noexcept requires (is_const >= other_const) {
    ptr_ = std::move(o.ptr_);
    return *this;
}

template<class T, bool is_const>
template<bool other_const>
Iterator<T, is_const> &Iterator<T, is_const>::operator=(const Iterator<T, other_const> &o)
noexcept requires (is_const >= other_const) {
    ptr_ = o.ptr_;
    return *this;
}

//template<class T, bool is_const>
//template<bool other_const>
//std::strong_ordering Iterator<T, is_const>::operator<=>(const Iterator<T, other_const> &o) const noexcept{
//    if (ptr_ > o.ptr_){
//        return std::strong_ordering::greater;
//    }
//    else if(ptr_ < o.ptr_){
//        return std::strong_ordering::less;
//    }
//    else{
//        return std::strong_ordering::equal;
//
//    }
//}

template<class T, bool is_const>
typename Iterator<T, is_const>::reference Iterator<T, is_const>::operator*() const noexcept {
    return *ptr_;
}

template<class T, bool is_const>
typename Iterator<T, is_const>::pointer Iterator<T, is_const>::operator->() const noexcept {
    return ptr_;
}

template<class T, bool is_const>
template<bool other_const>
bool Iterator<T, is_const>::operator==(const Iterator<T, other_const> &o) const noexcept {
    return ptr_ == o.ptr_;
}

//template<class T, bool is_const>
//template<bool other_const>
//bool Iterator<T, is_const>::operator!=(const Iterator<T, other_const> &o) const noexcept {
//    return ptr_ != o.ptr_;
//}

template<class T, bool is_const>
Iterator<T, is_const> &Iterator<T, is_const>::operator++() noexcept {
    ++ptr_;// check
    return *this;
}

template<class T, bool is_const>
Iterator<T, is_const> Iterator<T, is_const>::operator++(int) noexcept {
    Iterator res(ptr_);
    ++ptr_;
    return res;
}

template<class T, bool is_const>
Iterator<T, is_const> &Iterator<T, is_const>::operator--() noexcept {
    --ptr_;
    return *this;
}

template<class T, bool is_const>
Iterator<T, is_const> Iterator<T, is_const>::operator + (Iterator<T, is_const>::difference_type other) const {
    Iterator res(ptr_);
    res += other;
    return res;
}

template<class T, bool is_const>
Iterator<T, is_const> Iterator<T, is_const>::operator - (Iterator<T, is_const>::difference_type other) const{
    Iterator res(ptr_);
    res -= other;
    return res;
}

template<class T, bool is_const>
Iterator<T, is_const> Iterator<T, is_const>::operator--(int) noexcept {
    Iterator res(ptr_);
    --ptr_;
    return res;
}


template<class T, bool is_const>
Iterator<T, is_const>&  Iterator<T, is_const>::operator+=(difference_type movement){
    ptr_ += movement;
    return *this;
}

template<class T, bool is_const>
Iterator<T, is_const>&  Iterator<T, is_const>::operator-=(difference_type movement){
    ptr_ -= movement;
    return *this;
}

template<class T, bool is_const>
template<bool other_const>
typename Iterator<T, is_const>::difference_type Iterator<T, is_const>::operator-(const Iterator<T, other_const> &o) const{
    return ptr_ - o.ptr_;
}


template<class T, bool is_const>
Iterator<T, is_const> operator+(typename Iterator<T, is_const>::difference_type other, const Iterator<T, is_const> &iter) {
    return iter + other;
}

template<class T, bool is_const>
typename Iterator<T, is_const>::reference Iterator<T, is_const>::operator[](Iterator<T, is_const>::difference_type other) const noexcept{
    return *(ptr_ + other);
}




///////////////////////////////////////////////////////////////////////////////////////////
template <class T>
class Matrix {
private:
    T *data_;

    size_t rows_;
    size_t columns_;

    size_t capacity_;

    [[nodiscard]] size_t size() const noexcept { return rows_ * columns_; }

//    void check_size() {
//        while (size() >= capacity_) {
//            size_t newCapacity = capacity_ == 0 ? 1 : capacity_ * 2;
//            reserve(newCapacity);
//        }
//    }

public:
    typedef T value_type;
    typedef T &reference;
    typedef const T &const_reference;
    typedef Iterator<T, false> iterator;
    typedef Iterator<T, true> const_iterator;
    typedef ptrdiff_t difference_type;
    typedef size_t size_type;

    Matrix()
        : data_(nullptr), rows_(0), capacity_(0), columns_(0) {};

    explicit Matrix(size_t initialCapacity);

    Matrix(const size_t length, const size_t width)
        : rows_(length), columns_(width), capacity_(length * width),
                                                      data_(new T[length * width]) {
        for (size_t i = 0; i < rows_ * columns_; i++){
            data_[i] = T();
        }
    }


    Matrix(const Matrix& other);


    Matrix(Matrix&& other) noexcept
            : rows_(other.rows_), columns_(other.columns_), capacity_(other.capacity_), data_(std::move(other.data_)) {
        other.rows_ = 0;
        other.columns_ = 0;
        other.data_ = nullptr;
    }


    Matrix& operator=(const Matrix& other);


    Matrix& operator=(Matrix&& other) noexcept;


    ~Matrix() {delete[] data_; }


    [[nodiscard]] size_type capacity() const noexcept {
        return capacity_;
    }

    [[nodiscard]] size_type rows() const noexcept {
        return rows_;
    }
    [[nodiscard]] size_type columns() const noexcept {
        return columns_;
    }

    iterator begin() {
        return Iterator<T, false>(data_);

    }

    const_iterator begin() const {
        return Iterator<T, true>(data_);
    }

    iterator end() {
        return Iterator<T, false>(data_ + size());
    }

    const_iterator end() const {
        return Iterator<T, true>(data_ + size());
    }

    const_iterator cbegin() const {
        return Iterator<T, true>(data_);
    }

    const_iterator cend() const {
        return Iterator<T, true>(data_ + size());
    }

    iterator operator[](const size_t index) {
        return Iterator<T, false>(data_ + index * columns_);
    }

    const_iterator operator[](const size_t index) const {
        return Iterator<T, true>(data_ + index * columns_);
    }

    reference at(size_type row, size_type column);
    const_reference at(size_type row, size_type column) const;

    void reserve(size_t newCapacity);

    [[nodiscard]] bool empty() const noexcept;
    void clear() noexcept;

    bool operator == (const Matrix<T>& other) const;

    void addRow(const T&);
    void addColumn(const T& );
    void addRow();
    void addColumn();


};


//////////////////////////////////////////////////////////////////////
template <class T>
Matrix<T>& Matrix<T>::operator = (const Matrix<T>& other) {
    if (this != &other) {
        rows_ = other.rows_;
        columns_ = other.columns_;
        capacity_ = other.capacity_;

        T* newData = new T[rows_ * columns_];
        delete[] data_;
        data_ = newData;


        std::copy(other.data_, other.data_ + rows_ * columns_, data_);
    }
    return *this;
}


template <class T>
Matrix<T>& Matrix<T>::operator = (Matrix<T>&& other) noexcept {
    if (this != &other) {
        delete[] data_;
        rows_ = other.rows_;
        columns_ = other.columns_;
        capacity_ = other.capacity_;

        data_ = other.data_;

        other.rows_ = 0;
        other.columns_ = 0;
        other.data_ = nullptr;
    }
    return *this;
}

template <class T>
void Matrix<T>::addRow(const T& element ){
    T* newData = new T[(rows_ + 1) * columns_];

    std::move(data_, data_ + rows_ * columns_, newData);

    delete[] data_;
    data_ = newData;

    for (size_type i = 0; i < columns_; ++i) {
        data_[rows_*columns_ + i] = T(element);

//        new (&data_[(rows_)*columns_ + i]) T(element);
    }

    ++rows_;
    capacity_ = columns_ * rows_;

}

template <class T>
void Matrix<T>::addColumn(const T& element ) {
    //T* newData = std::allocator<T>{}.allocate(rows_ * (columns_ + 1))
    T* newData = new T[rows_ * (columns_ + 1)];

    for (size_type i = 0; i < rows_; ++i) {
//        for(size_type j = 0; j < columns_; ++j) {
//            // арифметика указателей
//            new (newData + i*columns_ + 1) T(std::move(data[j]));
//        }
        std::move(data_ + i * columns_, data_ + i * columns_ + columns_, newData + i * (columns_ + 1));
        newData[i * (columns_ + 1) + columns_] = T(element);
        //new (&newData[i * (columns_ + 1) + columns_]) T(element);
    }
//destruct + deallocate
    delete[] data_;
    data_ = newData;
    ++columns_;
    capacity_ = columns_ * rows_;
}


template <class T>
void Matrix<T>::addRow(){
    T* newData = new T[(rows_ + 1) * columns_];

    std::move(data_, data_ + rows_ * columns_, newData);

    delete[] data_;
    data_ = newData;

    for (size_type i = 0; i < columns_; ++i) {
        data_[rows_*columns_ + i] = T();
        //new (&data_[(rows_)*columns_ + i]) T();
    }

    ++rows_;
    capacity_ = columns_ * rows_;

}

template <class T>
void Matrix<T>::addColumn() {
    T* newData = new T[rows_ * (columns_ + 1)];

    for (size_type i = 0; i < rows_; ++i) {
        std::move(data_ + i * columns_, data_ + i * columns_ + columns_, newData + i * (columns_ + 1));
        newData[i * (columns_ + 1) + columns_] = T();

//        new (&newData[i * (columns_ + 1) + columns_]) T();
    }

    delete[] data_;
    data_ = newData;
    ++columns_;
    capacity_ = columns_ * rows_;

}


template <class T>
T& Matrix<T>::at(size_type row, size_type column){
    size_type index = row * columns_ + column;
    if (index < size()) {
        return data_[index];
    }
    throw std::out_of_range("Index out of range");
}


template <class T>
const T& Matrix<T>::at(size_type row, size_type column) const{
    size_type index = row * columns_ + column;
    if (index < size()) {
        return data_[index];
    }
    throw std::out_of_range("Index out of range");
}


template <class T>
void Matrix<T>::reserve(size_t newCapacity){
    if ( newCapacity > capacity_) {
        T *newData = new T[newCapacity];
//std::move
//        for (size_t i = 0; i < size(); i++) {
//            newData[i] = std::move(data_[i]);
//        }
       std::move(data_, data_ + size(), newData);


        delete[] data_;
        data_ = newData;
        capacity_ = newCapacity;
    }
}


template<typename T>
bool Matrix<T>::operator== (const Matrix<T>& other) const{
    if (columns_ != other.columns_ || rows_ != other.rows_){
        return false;
    }
    return std::equal(data_, data_ + rows_ * columns_, other.data_);

}


template <class T>
bool Matrix<T>::empty() const noexcept{
    return size() == 0;
}

template <class T>
void Matrix<T>::clear() noexcept{
    rows_ = 0;
    columns_ = 0;
    capacity_ = 0;

    delete[] data_;
    data_ = nullptr;
}

template<class T>
Matrix<T>::Matrix(const Matrix &other)
    : rows_(other.rows_), columns_(other.columns_),capacity_(other.capacity_) ,data_(new T[other.rows_ * other.columns_])  {
    std::copy(other.data_, other.data_ + rows_ * columns_, data_);
}

template<class T>
Matrix<T>::Matrix(size_t initialCapacity)
    : data_(new T[initialCapacity]), rows_(0), columns_(0),
            capacity_(initialCapacity) {}




#endif /* vector_hpp */
