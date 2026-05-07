#include <iostream>
#include <cmath>

class Function
{
    public:
    double get_func(double x);
    double get_derivative(double x);
};

class RootMethod
{
    private:
        int it_counter;
        Function *F;
    public:
        double function(double x)
        {
            return F->get_func(x);
        }

        double derivative(double x)
        {
            return F->get_derivative(x);
        }
        RootMethod(){it_counter = 0;};

        double get_interval();

        void it_add()
        {
            it_counter ++;
        }

        int get_iteration()
        {
            return it_counter;
        }

        std :: string show_iteration()
        {
        }
};

class Bisec : public RootMethod
{
    public:
        Bisec(){};
        double get_interval(double a, double b);
        std :: string show_iteration();
};

class FixedPoint : public RootMethod
{
    private:
        int init;
    public:
        FixedPoint(){};
        double image(double x);
        double get_interval(double x);
};

class Secant : public RootMethod
{
    private:

    public:
        Secant(){};
        double get_interval(double x_i, double  x_prev);

};

class Newton_Raphson : public RootMethod
{
    private:
   

    public:
        Newton_Raphson(){};

        double get_interval(double x_i);
};