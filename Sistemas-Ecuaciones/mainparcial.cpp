#include "lib.h"

int main()
{
    Matrix *A = new Matrix(3);
      for (int i = 0; i < A->getSize(); i++)
    {
        for (int j = 0; j < A->getSize()+1; j++)
        {
            double in;
            std :: cout << "Elemento " << i << ", " << j;
            std :: cin >> in;
            A->setElement(i, j, in); 
            std :: cout << std :: endl;
        }
        
    }
    A->print_matrix();
     std :: cout << std :: endl;
    LU Lu = LU(A);
    Lu.Solve();

    std :: cout << std :: endl;
    
}