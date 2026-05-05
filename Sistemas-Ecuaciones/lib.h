#include <cmath>
#include <random>
#include <iostream>


class Matrix
{

    
    private:
        int size_m;
        double ** mtrx;

    public:
        Matrix(int n);
        Matrix(double ** M);

        double getElement(int i, int j);

        void setElement(int i, int j, double value);

        void print_matrix();

        void swap_rows(int a, int b); 

        int getSize()
        {
            return size_m;
        }
        

        
};

class Method
{
    private:
        int m_size;
        Matrix *M;
        int it;
        double *solution;

    public:
        Method()
        {
            m_size = 4;
            M = new Matrix(m_size);
            solution = new double[m_size];

            for (int i = 0; i < m_size; i++)
            {
                solution[i] = 0;
            }

        }

        Method(Matrix *A)
        {
            M = A;
            m_size = M->getSize();
            solution = new double[m_size];

            
            for (int i = 0; i < m_size; i++)
            {
                solution[i] = 0;
            }

        }

        virtual void Solve()
        {};
        Matrix *getM()
        {
            return M;
        }
        int getIterarionCount();
        int get_m_size()
        {
            return m_size;
        }
        void set_solution(double value, int a) 
        {
            solution[a] = value;
        }

        double get_sol(int a)
        {
            return solution[a];
        }

        void print_solutions()
        {
             for (int i = 0; i < m_size; i++)
            {
                std:: cout << "x_"<< i+1 <<" = " << solution[i] << std:: endl;
            }

        }

        void EpiCheck()
        {
            double sum;
            for (int i = 0; i<m_size; i++)
            {
                sum += solution[i]*getM()->getElement(0, i);
            }  
            std:: cout << "La sumita dio (funciona, pls): "<< sum;
        }    
        
};

class GaussianElimination : public Method
{
    public: 
        GaussianElimination()
        {

        }
        
        bool ForwardElimination();
        void BackwwardsSubstitution();
        double getMultiplier(int i, int j);



      

        void Solve() override
        {
            ForwardElimination();
            BackwwardsSubstitution();
            print_solutions();
            EpiCheck();
        };
        


};

class Gauss_Seidel : public Method
{
    private:
        double *errors;
        double *sol_prev;
        int *dominant_var;
    public:
     Gauss_Seidel() 
        {
            errors = new double[get_m_size()];
            sol_prev = new double[get_m_size()];
            dominant_var = new int[get_m_size()];
            for (int i = 0; i<get_m_size(); i++)
            {
                sol_prev[i] = 0;
                errors[i] = 0;
                dominant_var[i] = -1;
            }
            std:: cout << "dom iniciado en: "<< dominant_var[0] << std:: endl;
           
        }

        Gauss_Seidel(Matrix *A) : Method(A)
        {
            errors = new double[get_m_size()];
            sol_prev = new double[get_m_size()];
            dominant_var = new int[get_m_size()];
            for (int i = 0; i<get_m_size(); i++)
            {
                sol_prev[i] = 0;
                errors[i] = 0;
                dominant_var[i] = -1;
            }
        }
        void Iterate_solutions();
        void Iterate_Error();
        double get_sum_i(int i);
        bool Is_Diagonally_Dom();

        void Solve() override
        {
             std:: cout << "dom iniciado en: "<< dominant_var[0] << std:: endl;

            if (Is_Diagonally_Dom())
            {
                Iterate_Error();
                print_solutions();
                EpiCheck();
            }
            else
            {
                std:: cout << "Matriz no diagonalmente dominante. Gauss-Seidel no sirve." << std :: endl;
            }
        }
   

};

// implementacion de Matriz :3
Matrix :: Matrix(int n) : size_m(n)
{
    mtrx = new double*[n];
    int i = 0;
    for (i = 0; i < n; i++)
    {
        mtrx[i] = new double[n+1];
        for (int j = 0; j < (n+1); j++)
        {
            mtrx[i][j]= rand() % 10 + 1;

        }

    }
  
}


void Matrix :: print_matrix()
{
   for (int i = 0; i < size_m; i++)
   {
    std::cout << "| ";
    
    for (int j = 0; j < size_m+1; j++)
    {
        std::cout << mtrx[i][j] <<"  |  ";
    }
    std::cout << "\n";
   } 
}

double Matrix :: getElement(int i, int j)
{
    if (i <= size_m && j <= size_m)
    {
        return mtrx[i][j];
    }
    else
    {
        throw 400;
        
    }
    return 0;
}

void Matrix :: setElement(int i, int j, double value)
{
    mtrx[i][j] = value;
}

void Matrix :: swap_rows(int a, int b)
{
    double *aux = mtrx[a];
    mtrx[a] = mtrx[b];
    mtrx[b] = aux;
    
    // delete aux; No seas gilun y no borres el aux que es un puntero que apunta a a algo importante.
}


// implementación de pene en el orto, digo Eliminación-Gausseana :3

bool GaussianElimination :: ForwardElimination() //return false si encuentra fila nula???
{
    
    for (int a = 0; a<(get_m_size()); a++) 
    {
        for (int i = a+1; i < get_m_size(); i++)
        {
            double mult = getMultiplier(i,a);   
            for (int j = 0; j < get_m_size()+1; j++)
            {
                double mod = getM()->getElement(i,j) - (mult * getM()->getElement(a,j));
                //Salida insana que me decía todo :3//std:: cout << "Mod de "<< i << "," << j <<": " << mod << " Elemento de la fila de arriba: " << a << ","<< j << std::endl;
                getM()->setElement(i, j, mod);

            }
        }
    }


    // revisión de filas nulas
    for (int i=0; i<get_m_size(); i++)
    {
        for(int j = 0; j< get_m_size(); j++)
        {
            if (getM()->getElement(i,j) != 0)
            {
                return true;
            }
        }
    }
    return false;

}

double GaussianElimination :: getMultiplier(int i, int j)
{
    // se supone que está bien así
    return getM()->getElement(i, j) / getM()->getElement(j, j);
}   

void a()
{
    std:: cout << "hola";
}

void GaussianElimination :: BackwwardsSubstitution()
{
    double x_i = 0;
    for (int i = get_m_size()-1; i >= 0; i--)
    {
       double sum = 0; // es necesario resetear la suma, boludo. Sino, acumulás la suma en el anterior.
        for (int j = 0; j < get_m_size(); j++)
        {
            //std:: cout << "i = "<< i << " j = " << j << "sol = " << get_sol(j) << std:: endl;
            sum += getM()->getElement(i, j) * get_sol(j);
            
        }
        std:: cout << "oal"<< sum << std:: endl;
        
        x_i = (getM()->getElement(i, get_m_size()) - sum) / (getM()->getElement(i, i));
        set_solution(x_i, i);
    }
}

void Gauss_Seidel :: Iterate_solutions()
{
    for (int i = 0; i<get_m_size(); i++)
    {
        double b_i = 0;
        
        b_i = getM()->getElement(i, get_m_size());

        

        double new_solution = (b_i - get_sum_i(i)) / getM()->getElement(i, i);

        set_solution(new_solution, i);
    }
}

double Gauss_Seidel :: get_sum_i(int i)
{
    double sum = 0;
    for (int j = 0; j < get_m_size(); j++) // NO PONGAS -1 EN LOS FOR porque la condición dice meno, pajero del orto
    {
        if (j != i)
        {
            sum += getM()->getElement(i, j) * get_sol(j);
        }
        
        std :: cout << "sum: " << sum; 
    }
    return sum;
}

void Gauss_Seidel :: Iterate_Error()
{
    int it_count = 0;
/*     for (int i = 0; i < get_m_size(); i++)
    {
        errors[i] = get_sol(i) - sol_prev[i];
        Iterate_solutions();
        while (errors[i] > 0.0001 && it_count < 50)
        {
            std :: cout << get_sol(i) << std :: endl;
            errors[i] = get_sol(i) - sol_prev[i];
            Iterate_solutions();
            it_count ++;
        }

    }    */

    bool converged = false;
        while (!converged && it_count < 500)
        {
            Iterate_solutions();
            converged = true;

            for (int i = 0; i < get_m_size(); i++)
            {
                errors[i] = std::fabs(get_sol(i) - sol_prev[i]);
                if (errors[i] > 0.0000001)
                {
                    converged = false;
                }
                sol_prev[i] = get_sol(i);
            }
            it_count ++;
        }
        std :: cout << "It_count: "<< it_count << std :: endl;
}

bool Gauss_Seidel :: Is_Diagonally_Dom()
{
    
    for (int i = 0; i<get_m_size(); i++)
    {

        for (int j = 0; j<get_m_size(); j++)
        {
            double sum = 0;
            for (int k = 0; k<get_m_size(); k++)
            {
                if (k != j)
                {
                    sum += abs(getM()->getElement(i,k));
                }
                
            }
            
            if (abs(getM()->getElement(i,j)) > abs(sum))
            {
                if (dominant_var[j] == -1)
                {
                    dominant_var[j] = i;
                    std:: cout << "Dominante en fila"<< i << " es la columna : " << j << std :: endl;
                    getM()->swap_rows(j, i);
                }

                else
                {
                    return false;
                }
            }
        }
        if (dominant_var[i] == -1)
        {
            return false;
        }

    }

    std :: cout << "Bueno..." << std :: endl;
    for (int a = 0; a<get_m_size(); a++)
    {
        getM()->swap_rows(a, dominant_var[a]);
    }
    return true;
}

