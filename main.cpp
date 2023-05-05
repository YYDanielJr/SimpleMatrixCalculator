#include <iostream>
#include <vector>
#include <memory>

typedef std::vector<std::vector<int>> IntMat;

class BadMultiplyMatrixException : public std::exception
{
    const char* what()
    {
        return "是否输入了不能相乘的矩阵？\n";
    }
};

class Matrix
{
private:
    std::shared_ptr<IntMat> matrix;
public:
    Matrix(IntMat origin)
    {
        matrix = std::make_shared<IntMat>(origin);
    }
    Matrix(int row, int column)
    {
        matrix = std::make_shared<IntMat>(row, std::vector<int>(column, 0));
    }
    ~Matrix()
    {
        // 智能指针会自动析构。
    }
    std::shared_ptr<IntMat> getMatrix()
    {
        return matrix;
    }
    std::vector<int> operator[](int i)
    {
        return matrix->at(i);
    }
    void set(int i, int j, int val)
    {
        matrix->at(i).at(j) = val;
    }
    Matrix multiply(Matrix& origin)
    {
        IntMat temp;
        for(int i = 0; i < matrix->size(); i++)
        {
            temp.push_back(std::vector<int>());
            for(int j = 0; j < origin.getMatrix()->at(0).size(); j++)
            {
                int sum = 0;
                for(int k = 0; k < matrix->at(0).size(); k++)
                {
                    sum += matrix->at(i).at(k) * origin.getMatrix()->at(k).at(j);
                }
                temp[i].push_back(sum);
            }
        }
        Matrix ret(temp);
        return ret;
    }

    Matrix pow(int n)
    {
        Matrix ret = *this;
        for(int i = 1; i < n; i++)
        {
            ret = ret.multiply(ret);
        }
        return ret;
    }

    void print()
    {
        for(int i = 0; i < matrix->size(); i++)
        {
            for(int j = 0; j < matrix->at(i).size(); j++)
            {
                std::cout << matrix->at(i).at(j) << "\t";
            }
            std::cout << std::endl;
        }
    }
};

int main()
{
    int row = 0;
    int column = 0;
    std::cout << "输入左矩阵的行数和列数：  ";
    std::cin >> row >> column;
    std::shared_ptr<Matrix> left = std::make_shared<Matrix>(row, column);
    std::cout << "输入左矩阵：\n";
    try
    {
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < column; j++)
            {
                int temp;
                std::cin >> temp;
                left->set(i, j, temp);
            }
        }
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << "输入的矩阵元素溢出。" << '\n';
        return 0;
    }
    
    std::cout << "输入右矩阵的行数和列数：  ";
    std::cin >> row >> column;
    std::shared_ptr<Matrix> right = std::make_shared<Matrix>(row, column);
    std::cout << "输入右矩阵：\n";
    try
    {
        for(int i = 0; i < row; i++)
        {
            for(int j = 0; j < column; j++)
            {
                int temp;
                std::cin >> temp;
                right->set(i, j, temp);
            }
        }
    }
    catch(const std::out_of_range& e)
    {
        std::cerr << "输入的矩阵元素溢出。" << '\n';
        return 0;
    }
    left->multiply(*right).print();
    return 0;
}