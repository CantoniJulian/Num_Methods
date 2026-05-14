#include "lib.h"
#include <cstdlib>


 void GS(Matrix *C)
    {
        Gauss_Seidel G2 = Gauss_Seidel(C);

        std :: cout << std :: endl;
        G2.Solve();

        std :: cout << std :: endl;
        G2.getM()->print_matrix();
        std:: cout << std:: endl;
    }

void GE(Matrix *C)
{
    GaussianElimination G = GaussianElimination(C);
    G.getM()-> print_matrix();
    G.Solve();

    G.getM()->print_matrix();
};

void LUM(Matrix *C)
{
    LU Lu = LU(C);
    Lu.Solve();

}

int main()
{

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