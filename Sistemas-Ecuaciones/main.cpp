#include "lib.h"

int main()
{
    GaussianElimination G;
    G.getM()-> print_matrix();


    std :: cout << std :: endl;
    G.getM()->print_matrix();
   
    std :: cout << std :: endl;
    std::cout << G.ForwardElimination() << std::endl;
    G.getM()->print_matrix();

    G.Solve();
    
}