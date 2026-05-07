#include "lib.h"
#include <cstdlib>


 void GS(Matrix *A)
    {
        Gauss_Seidel G2 = Gauss_Seidel(A);

        std :: cout << std :: endl;
        G2.Solve();

        std :: cout << std :: endl;
        G2.getM()->print_matrix();
        std:: cout << std:: endl;
    }

void GE(Matrix *A)
{
    GaussianElimination G = GaussianElimination(A);
    G.getM()-> print_matrix();
    G.Solve();

    G.getM()->print_matrix();
}


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

    int contin = 0;
    while(contin != -1)

    {
    int n;
    std :: cout << "Ingrese tamanio de matriz: "<< std :: endl;

    std :: cin >> n;

    Matrix *A = new Matrix(n);

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

    std ::  cout << std :: endl;
    A->print_matrix();
    std ::  cout << std :: endl;

    int sel;
    
    std :: cout << "Ingrese el metodo: (0 GE, 1GS, 2LU)" << std:: endl;
    std :: cin >> sel;
    std ::  cout << std :: endl;
    switch (sel)
    {
    case 1:
        GS(A);
        break;
    case 0:
        GE(A);
        break;
    case 2:
        GS(A);
        break;
    
    default:
        break;
    }

    }

   
/*     GaussianElimination G = GaussianElimination(A);

    G.Solve();
    std:: cout << std:: endl;
    G.getM()->print_matrix();

    std ::  cout << std :: endl; */


 /*    LU Lu = LU(A);

    Lu.Solve(); */

    //std:: cout << G2.Is_Diagonally_Dom();
   


}