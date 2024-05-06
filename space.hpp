#include <cmath>
#include <eigen3/Eigen/Dense>
#include <vector>

namespace space {
    float_t vx_e=-2.983302263902714*1000*std::pow(10, 1);
    float_t vy_e=-5.138481408411204*1000*std::pow(10, 0);
    float_t vz_e = 1.105037462794778*1000*std::pow(10, -3);
    float_t vx_s=8.441016159655652*1000*std::pow(10,-3);
    float_t vy_s=-1.221912155158748*1000*std::pow(10, -2);
    float_t vz_s=-7.918737699351246*1000*std::pow(10, -5);
    float_t vx_m=-3.024279048864922*1000*std::pow(10, 1);
    float_t vy_m=-6.014108452553830*1000*std::pow(10, 0);
    float_t vz_m=-5.816013309114965*1000*std::pow(10, -2);
    Eigen::Vector3f r_s=Eigen::Vector3f(vx_s, vy_s, vz_s);
    Eigen::Vector3f r_m=Eigen::Vector3f(vx_m, vy_m, vz_m);
    Eigen::Vector3f r_e = Eigen::Vector3f(vx_e, vy_e, vz_e);
    const long double G=6.6739974877 * (std::pow(10, -11));

    class object {
        private:
            float_t T0=0;
            const float dt=0.0625;
            int dt_list=3600;
            float_t x, y, z, vx, vy, vz;
            Eigen::Vector3f g;
            Eigen::Vector3f v = Eigen::Vector3f(vx, vy, vz);
            const double m_s=1.988500 * (std::pow(10, 30));    
            const float m_m=7.349 * (std::pow(10, 22));       
            const long double m_e=81.3005690769 * (m_m); 
        public:
            std::vector<std::vector<float>> log;
            //initializing the object.
            void initialize_object(float_t x, float_t y, float_t z, float_t vx, float_t vy, float_t vz);
            //calculates stuff and pushes to the log. (type: 1=Sun, 2=Earth, 3=Moon)
            void calculate(int type);
            //writes log data to a csv file. (type: 1=Sun, 2=Earth, 3=Moon)
            void write_to_csv(int type);
    };

    Eigen::Vector3d VectorF(float m1, float m2, Eigen::Vector3f r1, Eigen::Vector3f r2);
    std::vector<size_t> time(float t);
};