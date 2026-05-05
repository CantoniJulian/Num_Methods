#include "lib.h"

int main()
{
/*     GaussianElimination G;
    G.getM()-> print_matrix();


    std :: cout << std :: endl;
    G.getM()->print_matrix();
   
    std :: cout << std :: endl;
    std::cout << G.ForwardElimination() << std::endl;
    G.getM()->print_matrix();

    G.Solve(); */
    
    double puto [12] = {10, 2, -1, 15, -3, 8, 2, 11, 1, 4, 15,-6};
    Matrix *A = new Matrix(3);
/* 
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
        
    } */
   
    A->setElement(0, 0, puto[0]);
    A->setElement(0, 1, puto[1]);
    A->setElement(0, 2, puto[2]);
    A->setElement(0, 3, puto[3]);
    A->setElement(1, 0, puto[4]);
    A->setElement(1, 1, puto[5]);
    A->setElement(1, 2, puto[6]);
    A->setElement(1, 3, puto[7]);
    A->setElement(2, 0, puto[8]);
    A->setElement(2, 1, puto[9]);
    A->setElement(2, 2, puto[10]);
    A->setElement(2, 3, puto[11]);

    std ::  cout << std :: endl;
    A->print_matrix();

    

    Gauss_Seidel G2 = Gauss_Seidel(A);

    std :: cout << std :: endl;
    G2.Solve();

    std :: cout << std :: endl;
    G2.getM()->print_matrix();
    std:: cout << std:: endl;
    
    //std:: cout << G2.Is_Diagonally_Dom();
   
}