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
            for (int a = 0; a < m_size; a++)
            {
                sum = 0;
                for (int i = 0; i<m_size; i++)
                {
                sum += solution[i]*getM()->getElement(a, i);
                }  
            std:: cout << "La sumita dio (funciona, pls): "<< sum << std :: endl;
            }
        }    
        
};

class GaussianElimination : public Method
{
    private:
        double *modifiers;
    public:
        GaussianElimination()
        {
            modifiers = new double[(get_m_size()*(get_m_size()))/2];
        }

        double get_modifiers(int i)
        {
            return modifiers[i];
        }

        GaussianElimination(Matrix *A) : Method(A)
        {
            modifiers = new double[(get_m_size()*(get_m_size()))/2];
        }
        
        bool ForwardElimination();
        void BackwardsSubstitution();
        double getMultiplier(int i, int j);



      

        void Solve() override
        {
            std :: cout << "eliminando";
            ForwardElimination();

            BackwardsSubstitution();
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

class LU : public Method
{
    private:
        Matrix *L, *U;
        GaussianElimination Elim = GaussianElimination(getM());
        double *y_i;

    public:
        LU()
        {
        }
        void generateL();
        LU(Matrix *A) : Method(A)
        {
            y_i = new double[get_m_size()];
            for (int i = 0; i<get_m_size(); i++)
            {
                y_i[i] = 0;
            }
            std :: cout << "oal" << std :: endl;
            L = new Matrix(get_m_size());
            U = new Matrix(get_m_size());
            
            for (int j = 0; j<get_m_size(); j++)
            {
        
                get_L()->setElement(j, get_m_size(), getM()->getElement(j, get_m_size()));
                y_i[j] = 0;
            }
         
            
        }

        void Solve() override
        {
            
            Elim.ForwardElimination();
            generateL();
            U = Elim.getM();
            U->print_matrix();
            L->print_matrix();
            ForwardSubstitution();
            Elim.Solve();

        }
        Matrix *get_U()
        {
            return U;
        }
        Matrix *get_L()
        {
            return L;
        }

        void ForwardSubstitution();
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
            mtrx[i][j]= 0;//rand() % 10 + 1;

        }

    }
  
}


void Matrix :: print_matrix()
{
    std:: cout << "imprimiendo" << size_m << std :: endl;
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

bool GaussianElimination :: ForwardElimination() //return false si encuentra fila nula??? Yes, papu :v
{
    int mod_count = 0;
    for (int a = 0; a<(get_m_size()); a++) 
    {
        for (int i = a+1; i < get_m_size(); i++)
        {
            double mult = getMultiplier(i,a);   
            for (int j = 0; j < get_m_size()+1; j++)
            {

                double mod = getM()->getElement(i,j) - (mult * getM()->getElement(a,j));
                
                getM()->setElement(i, j, mod);

                std :: cout << "m" << i  <<", "<< j <<" = " << mult << std :: endl;
                
                
            }

             if (i > a)
            {
                    modifiers[mod_count] = mult;
                    mod_count++;
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

void GaussianElimination :: BackwardsSubstitution()
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
    for (int j = 0; j < get_m_size(); j++) // NO HAY QUE PONER -1 EN LOS FOR porque la condición dice meno, pajero del orto
    {
        if (j != i)
        {
            sum += getM()->getElement(i, j) * get_sol(j);
        }
        
        std :: cout << "sumatoria de fila: " << i << sum << std :: endl; 
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
    bool *swapped = new bool[get_m_size()]; 
    
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
                }

                else
                {
                    return false;
                }
            }
        }
     

    }

     for (int a = 0; a<get_m_size(); a++)
    {
        if (dominant_var[0] == -1)
        {
            return false;
        }

    }
 // Parte con Gemini para Swapeo porque no tengo tiempo :(
    std :: cout << "Veredicto: Matriz diagonalmente dominante." << std :: endl;
   for (int i = 0; i < get_m_size(); i++) {
        
        // 1. Miramos la fila que está actualmente en la posición 'i'
        // ¿Es estricamemente dominante para la columna 'i'?
        double sum_actual = 0;
        for (int k = 0; k < get_m_size(); k++) {
            if (k != i) {
                sum_actual += abs(getM()->getElement(i, k));
            }
        }

        // 2. Si NO es dominante, buscamos a su reemplazo más abajo
        if (abs(getM()->getElement(i, i)) <= sum_actual) {
            
            // Empezamos a buscar desde la fila de abajo (i + 1) hasta el final
            for (int j = i + 1; j < get_m_size(); j++) {
                
                // Calculamos si esta fila 'j' sería dominante si la pusiéramos en 'i'
                double sum_candidato = 0;
                for (int k = 0; k < get_m_size(); k++) {
                    if (k != i) {
                        sum_candidato += abs(getM()->getElement(j, k));
                    }
                }

                // Si encontramos a la fila dominante para esta columna, ¡la subimos!
                if (abs(getM()->getElement(j, i)) > sum_candidato) {
                    getM()->swap_rows(i, j);
                    break; // Ya arreglamos esta diagonal, cortamos la búsqueda
                }
            }
        }
    }
        
    return true;
}

void LU :: generateL()
{
    int mod_count = 0;
    for (int i = 0; i< get_m_size(); i++)
    {
       
        L->setElement(i, i, 1);
        for (int j = 0; j < i; j++)
        {
            
            L->setElement(i, j, Elim.get_modifiers(mod_count));
            mod_count ++;
        }    
    }

    
}

void LU :: ForwardSubstitution()
{
 
    double y = 0;
    for (int i = 0; i < get_m_size(); i++)
    {
       double sum = 0; // es necesario resetear la suma, boludo. Sino, acumulás la suma en el anterior.
        for (int j = 0; j < i; j++)
        {
            //std:: cout << "i = "<< i << " j = " << j << "sol = " << get_sol(j) << std:: endl;
            sum += L->getElement(i, j) * y_i[j];
            
        }
        std :: cout << sum;
        y = (L->getElement(i, get_m_size()) - sum) / (L->getElement(i, i));
        y_i[i] = y;
    
    }

    for (int i = 0; i<get_m_size(); i++)
    {
        std:: cout << "y_" <<i <<": "<< y_i[i]<< std:: endl;
    }
}