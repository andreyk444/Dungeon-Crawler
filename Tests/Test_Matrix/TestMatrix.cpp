#include <gtest/gtest.h>

#include <Matrix/matrix.hpp>
#include <iostream>

//#include <Dungeon/Dungeon.h>
//using namespace Tramp;


TEST(ConstructorTest, Matrix){
    Matrix<int> matrix1;
    Matrix<int> matrix2(100);
    Matrix<int> matrix3(10, 20);

    ASSERT_EQ(matrix1.capacity(), 0);
    ASSERT_EQ(matrix2.capacity(), 100);
    ASSERT_EQ(matrix3.capacity(), 200);

    ASSERT_EQ(matrix1.rows(), 0);
    ASSERT_EQ(matrix2.rows(), 0);
    ASSERT_EQ(matrix3.rows(), 10);

    ASSERT_EQ(matrix1.columns(), 0);
    ASSERT_EQ(matrix2.columns(), 0);
    ASSERT_EQ(matrix3.columns(), 20);

    matrix3.clear();
    ASSERT_EQ(matrix3.empty(), true);
    ASSERT_EQ(matrix3.rows(), 0);
    ASSERT_EQ(matrix3.columns(), 0);
    ASSERT_EQ(matrix3.capacity(), 0);

    matrix3.reserve(1234);
    ASSERT_EQ(matrix3.capacity(), 1234);


    const Matrix<int>& matrix4 = matrix1;
    ASSERT_EQ(matrix4.capacity(), 0);
    ASSERT_EQ(matrix4.rows(), 0);
    ASSERT_EQ(matrix4.columns(), 0);

    Matrix<int> matrix5 = std::move(matrix3);
    ASSERT_EQ(matrix5.capacity(), 1234);
    ASSERT_EQ(matrix5.rows(), 0);
    ASSERT_EQ(matrix5.columns(), 0);

}


TEST(CopyConstructorTest, Matrix){
    Matrix<int> matrix1;

    Matrix<int> matrix2 = matrix1;
    Matrix<int> matrix3(matrix1);

    ASSERT_EQ(matrix1.capacity(), 0);
    ASSERT_EQ(matrix2.capacity(), 0);
    ASSERT_EQ(matrix3.capacity(), 0);

    ASSERT_EQ(matrix1.rows(), 0);
    ASSERT_EQ(matrix2.rows(), 0);
    ASSERT_EQ(matrix3.rows(), 0);

    ASSERT_EQ(matrix1.columns(), 0);
    ASSERT_EQ(matrix2.columns(), 0);
    ASSERT_EQ(matrix3.columns(), 0);

    ASSERT_EQ(matrix1.empty(), true);
    ASSERT_EQ(matrix2.empty(), true);
    ASSERT_EQ(matrix3.empty(), true);

    ASSERT_TRUE(matrix1 == matrix2);
    ASSERT_TRUE(matrix3 == matrix2);


}



TEST(OperatorCopyTest, MatrixEqual){
    Matrix<int> matrix1(10, 20);
    Matrix<int> matrix2(23, 34);

    Matrix<int> matrix3;
    Matrix<int> matrix4;


    matrix3 = matrix1;
    matrix4 = matrix2;

    ASSERT_TRUE(matrix1 == matrix3);

    ASSERT_TRUE(matrix2 == matrix4);
    ASSERT_TRUE(matrix4 == matrix4);

    ASSERT_FALSE(matrix4 == matrix1);



    ASSERT_FALSE(matrix1.begin() == matrix4.begin());
    ASSERT_FALSE(matrix1.cbegin() == matrix4.cbegin());
    ASSERT_FALSE(matrix1.cbegin() == matrix4.begin());
    ASSERT_FALSE(matrix4.cbegin() == matrix1.begin());




    ASSERT_TRUE(matrix1 == matrix3);
    ASSERT_TRUE(matrix2 == matrix4);
    ASSERT_TRUE(matrix4.end() == matrix4.end());
    ASSERT_TRUE(matrix4.cend() == matrix4.end());
    ASSERT_TRUE(matrix4.begin() == matrix4.cbegin());
    ASSERT_TRUE(matrix4.begin() == matrix4.begin());

}

TEST(OperatorMoveTest, MatrixEqual){
    Matrix<int> matrix1(10, 20);
    Matrix<int> matrix2(23, 34);

    Matrix<int> matrix3;
    Matrix<int> matrix4;

    matrix3 = std::move(matrix1);
    matrix4 = std::move(matrix2);

    ASSERT_FALSE(matrix1 == matrix3);
    ASSERT_FALSE(matrix2 == matrix4);
    ASSERT_TRUE(matrix4 == matrix4);

    ASSERT_FALSE(matrix4 == matrix1);



    ASSERT_FALSE(matrix1.begin() == matrix4.begin());
    ASSERT_FALSE(matrix1.cbegin() == matrix4.cbegin());
    ASSERT_FALSE(matrix1.cbegin() == matrix4.begin());
    ASSERT_FALSE(matrix4.cbegin() == matrix1.begin());




    ASSERT_FALSE(matrix1 == matrix3);
    ASSERT_FALSE(matrix2 == matrix4);
    ASSERT_TRUE(matrix4.end() == matrix4.end());
    ASSERT_TRUE(matrix4.cend() == matrix4.end());
    ASSERT_TRUE(matrix4.begin() == matrix4.cbegin());
    ASSERT_TRUE(matrix4.begin() == matrix4.begin());


}


TEST(AddRowAndColumn, MatrixEqual){
    Matrix<int> matrix2(5, 6);
    matrix2.addRow(20);

    matrix2.addRow(15);
    matrix2.addRow(0);
    matrix2.addRow(12);
    matrix2.addColumn(11);
    matrix2.addColumn(12);
    matrix2.addColumn(0);
    matrix2.addColumn(33);




    for (size_t i = 0; i < matrix2.rows(); ++i) {
        for (size_t j = 0; j < matrix2.columns(); ++j) {
            ASSERT_EQ(matrix2.at(i,j), matrix2[i][j]);
         //   std::cout << matrix2.at(i,j) << " ";
        }
       // std::cout << std::endl;
    }

    ASSERT_EQ(matrix2.at(7,7), 12);
    ASSERT_THROW(matrix2.at(1123, 1), std::out_of_range);


    ASSERT_TRUE(matrix2[7] > matrix2[6]);
    ASSERT_TRUE(matrix2[5] > matrix2[4]);
    ASSERT_TRUE(matrix2[7] == matrix2[7]);
    ASSERT_TRUE(matrix2[7] != (matrix2[7] - 1));
    ASSERT_TRUE(matrix2[7] == matrix2[7]);

    matrix2[1][1] = 5;
    ASSERT_EQ(matrix2[1][1], 5);



}

TEST(MoveConstructorTest, Matrix){
    Matrix<int> matrix1(10, 20);
    Matrix<int> matrix2(23, 34);

    Matrix<int> matrix3 = std::move(matrix1);
    Matrix<int> matrix4 = std::move(matrix2);

    ASSERT_EQ(matrix1.empty(), true);
    ASSERT_EQ(matrix2.empty(), true);


    ASSERT_EQ(matrix3.capacity(), 200);
    ASSERT_EQ(matrix4.capacity(), 23 * 34);

    ASSERT_EQ(matrix3.rows(), 10);
    ASSERT_EQ(matrix4.rows(),23);

    ASSERT_EQ(matrix3.columns(), 20);
    ASSERT_EQ(matrix4.columns(), 34);

    matrix3.reserve(1);
    matrix3.reserve(1234567);
    matrix4.reserve(342123);

    ASSERT_EQ(matrix3.capacity(), 1234567);
    ASSERT_EQ(matrix4.capacity(), 342123);

    ASSERT_NO_THROW(Matrix<int> matrix5 = std::move(matrix2));

}
TEST(MoveConstructorTest, MatrixAt){
    Matrix<int> matrix1(10, 20);

    matrix1.addColumn();
    matrix1.addRow();
    matrix1[1][1]= 2;
    const Matrix<int> m2=  matrix1;

    auto it = matrix1.begin();
    it++;
    ++it;
    it--;
    --it;
    ASSERT_FALSE(m2.end() == m2.begin());
    ASSERT_FALSE(m2.cend() == m2.cbegin());
    ASSERT_TRUE(m2.cend() == m2.cend());



    const int& a = m2[1][1];
    ASSERT_EQ(a, 2);
    ASSERT_EQ(m2.at(1, 1), 2);
    ASSERT_THROW(m2.at(1312,1), std::out_of_range);

}
TEST(MoveConstructorTest, MatrixIter) {

    Matrix<int> matrix1(10, 20);

    auto it = matrix1.begin();
    it++;
    ++it;
    it--;
    --it;
    auto it2 = matrix1.end();
    const auto it3 = it;
    auto it4 = it2 - it3;
    auto it5 = it2 + 6 ;
    //it5 =  6 + it2 ;

    it5 += 1;

    Iterator<int, false> it7;
    auto it8 = std::move(it7);





//    auto it3 = 4 + it2;
//    size_t diff= it3 - it;

    ASSERT_EQ(it, matrix1.begin());
    ASSERT_EQ(0 ,*it);
}