#include <iostream>

struct tuple
{
    double x, y;
};

class Method
{
    public: 
        Method();
};

class Linear_Regression :public Method
{

    private:
        double r_sqrd, a1 = 0, a0, x_avg, y_avg;
        tuple *DISP; 
        int n;
        
    
    public:
        Linear_Regression();
        template <typename T, std::size_t N> Linear_Regression(tuple (&disp)[N]);
        void set_e_sqrd();
        
        //métodos para a_1
        void set_a1();

        double sum_x_i();
        double sum_y_i();
        double sum_x_i_sqrd();
        double sum_sqrd_x_i();
        double sum_product();

        double get_a1();
        //a_1
    
        //métodos a_0
        void set_a0();

        
        double avg_x();
        double avg_y();

        double get_a0();

        //evaluación de predicción :3
        double predict_new_value(double a);
        void set_r_sqrd();
        double residual_sum_sqr();
        double difference_with_avg();
        
        double get_r_sqrd();

        
        
};