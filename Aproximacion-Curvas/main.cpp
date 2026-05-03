#include "lib.h"

Method :: Method()
{

}

// completar con las implementaciones de Method
//
//
///

Linear_Regression :: Linear_Regression()
{

    DISP = new tuple[3];
    DISP[0]. x = 1;
    DISP[0]. y = 2;
    DISP[1]. x = 4;
    DISP[1]. y = 5;
    DISP[2]. x = 6;
    DISP[2]. y = 7;
    n = 3;


}

template <typename T, std::size_t N> Linear_Regression ::Linear_Regression(tuple (&disp)[N])
{
    *DISP = disp;
}

void Linear_Regression :: set_a1()
{

    a1 = (((n*sum_product())-(sum_x_i()*sum_y_i()))/(n*sum_x_i_sqrd() - sum_sqrd_x_i()));
}

double Linear_Regression :: sum_x_i()
{
    double sum = 0;
    for (int i = 0; i<n; i++)
    {
        sum += DISP[i].x;
    }
    return sum;
}

double Linear_Regression :: sum_y_i()
{
    double sum = 0;
    for (int i = 0; i<n; i++)
    {
        sum += DISP[i].y;
    }
    return sum;

}

double Linear_Regression :: sum_x_i_sqrd()
{
    double sum = 0;
    for (int i = 0; i<n; i++)
    {
        sum += DISP[i].x * DISP[i].x;
    }
    return sum;
}

double Linear_Regression :: sum_sqrd_x_i()
{
    return sum_x_i()*sum_x_i();
    
}

double Linear_Regression :: sum_product()
{
    double sum = 0;
    for (int i = 0; i<n; i++)
    {
        sum += DISP[i].x * DISP[i].y;
    }
    return sum;
}

double Linear_Regression :: get_a1()
{
    return a1;
}

//implementación de métodos de a0 LR

void Linear_Regression :: set_a0()
{
    a0 = avg_y() - get_a1() * avg_x();
}

double Linear_Regression :: avg_x()
{
    return sum_x_i()/n;
}

double Linear_Regression :: avg_y()
{
    return sum_y_i()/n;
}

double Linear_Regression :: get_a0()
{
    return a0;
}

// Evaluaciones de error
double Linear_Regression :: predict_new_value(double a)
{
    return a1*a + a0;
}

void Linear_Regression :: set_r_sqrd()
{
    r_sqrd = 1-(residual_sum_sqr()/difference_with_avg());
}

double Linear_Regression :: residual_sum_sqr() //   suma de cuadrado de distancias a la predicción
{
    double sum = 0;
    for (int i = 0; i<n; i++)
    {
        double distance = DISP[i].y - predict_new_value(DISP[i].x);
        sum += distance*distance;
    }

    return sum;
}

double Linear_Regression :: difference_with_avg()
{
    double sum = 0;
    for (int i = 0; i<n; i++)
    {
        double distance = DISP[i].y - avg_y();
        sum += distance*distance;
    }

    return sum;
}

double Linear_Regression :: get_r_sqrd()
{
    return r_sqrd;
}

int main()
{
    Linear_Regression LR;
    std:: cout << LR.sum_product() << std::endl;
    std:: cout << std:: flush << LR.sum_x_i() << std::endl;
    std:: cout << std :: flush << LR.sum_y_i() << std::endl;
    std:: cout << LR.sum_x_i_sqrd() << std::endl;
    std:: cout << LR.sum_sqrd_x_i() << std::endl;


    LR.set_a1();
    LR.set_a0();
    std::cout <<"a1(pendiente) =" << LR.get_a1() << std::endl;
    std::cout << "a0(intercepto) = " << LR.get_a0() << std::endl;
    
    std:: cout << LR.avg_x() << std::endl;
    
    std:: cout << LR.avg_y() << std:: endl;

    std::cout << "Prediccion para x= 10: " << LR.predict_new_value(10) << std::endl;

    LR.set_r_sqrd();
    std::cout << "Coeficiente de determinacion: " << LR.get_r_sqrd();

}

