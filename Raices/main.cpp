#ifndef ZERO_METHOD



#include "lib.h"
#define EXPORT __attribute__((visibility("default"))) __attribute__((used))

// Acá están mis wrapeos bien putotes :3
extern "C"
{
    const double error = 0.0000001;

    double derivative_wrap(double x)
    {
        Function F;
        return F.get_derivative(x);
    }

    double func_wrap(double x)
    {
        Function F;
        return F.get_func(x);
    }

    double bisec_wrap(double a, double b)
    {
        Bisec B;
        return B.get_interval(a, b);
    }

    double fixedpoint_wrap(double a)
    {
        FixedPoint P;
        return P.get_interval(a);
    }

    double secant_wrap(double x_i, double x_prev)
    {
        Secant S;
        return S.get_interval(x_i, x_prev); 
    }

    double nr_wrap(double x_i)
    {
        Newton_Raphson NR;
        return NR.get_interval(x_i);
    }

}
double Function :: get_func(double x)
{
    return -0.074* pow(x, 2) + 1.75 * x + 2.627;
}

double Function :: get_derivative(double x)
{
    return (get_func(x+0.0000001)-get_func(x))/0.0000001; // acá fui un verdadero pelotudo, primero porque quise dividir por x (ALTO GILASO)
}


// Esto es biseccion uwu

// Caso base => Error_actual > Error_perm uwu
double Bisec :: get_interval(double a, double b)
{
    //caso base
    double curr_error = (b-a)/2;
    double c = (a+b)/2;

    if ((error > curr_error) || (function(a)*function(b) == 0))
    {
        return c;
    } 
    else if (function(a)*function(c)>0)
    {
        return (get_interval(c, b));
    }

    else if (function(b)*function(c)>0)
    {
        return (get_interval(a, c));
    }
}


// Esto es punto fijo uwu

double FixedPoint :: image(double x){
    if ( x < init ){
        return -2.627 / (-0.074*x+1.750);
    }
    return init;
}

double FixedPoint :: get_interval(double x){


    while(derivative(x) > 1)
    {
       x=abs(x)-1;
    }
    double value = std::abs(image(x)-x);
    if (value<error){
        return x;
        
    } else {
        return get_interval(image(x));
    }
}

// Esto es Secante :3

double Secant :: get_interval(double x_i, double x_prev)
{
    double x_next = x_i - (function(x_i) * (x_i - x_prev)/(function(x_i) - function(x_prev)));
    double value = std:: abs((x_prev-x_i)/x_next); // acá se calcula el error de la iteración :3
     if (value<error)
    {
        return x_next;
    }
    else
    {
        return get_interval(x_next, x_i);
    }
}


// Esto es Newton Raphson :3

double Newton_Raphson :: get_interval(double x_i)
{
    if (get_iteration() > 100){
        std:: cout << "Iteraciones excedidas, retornando x_i:";
        return x_i;
    }
    it_add();
    
    

    double x_next = x_i - (function(x_i)/(derivative(x_i)));
    double value = std:: abs((x_next-x_i)/(x_next)); 

    

    if (value<error)
    {
        return x_next;
    }
    else 
    {
        return get_interval(x_next);
    }
}



int main()
{
    std::cout << nr_wrap(200) << std:: endl;
    std:: cout << secant_wrap(20,2000) << std:: endl;
    std:: cout << fixedpoint_wrap(200) << std:: endl;
    std:: cout <<  bisec_wrap(0, 200) << std:: endl;
    

}

#endif