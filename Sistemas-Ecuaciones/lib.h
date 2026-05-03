#include <ctime>
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
        

        
};

class Method
{
    private:
        int m_size;
        Matrix *M ;
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

        };

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
    return mtrx[i][j];
}

void Matrix :: setElement(int i, int j, double value)
{
    mtrx[i][j] = value;
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
        std:: cout << sum << std:: endl;
        
        x_i = (getM()->getElement(i, get_m_size()) - sum) / (getM()->getElement(i, i));
        set_solution(x_i, i);
    }
}

