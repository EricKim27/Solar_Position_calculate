#include <cmath>
#include <eigen3/Eigen/Dense>
#include <vector>

#ifndef SPACE_HPP
#define SPACE_HPP
namespace space {
    extern float vx_e;
    extern float vy_e;
    extern float vz_e;
    extern float vx_s;
    extern float vy_s;
    extern float vz_s;
    extern float vx_m;
    extern float vy_m;
    extern float vz_m;
    extern Eigen::Vector3f r_s;
    extern Eigen::Vector3f r_m;
    extern Eigen::Vector3f r_e;
    const long double G=6.6739974877 * (std::pow(10, -11));

    class object {
        private:
            float T0=0;
            const float dt=0.0625;
            int dt_list=3600;
            float x, y, z, vx, vy, vz;
            Eigen::Vector3f g;
            Eigen::Vector3f v = Eigen::Vector3f(vx, vy, vz);
            float m_s=1.988500 * (std::pow(10, 30));    
            float m_m=7.349 * (std::pow(10, 22));       
            float m_e=81.3005690769 * (m_m); 
        public:
            std::vector<std::vector<float>> log;
            //initializing the object.
            void initialize_object(float x, float y, float z, int type);
            //calculates stuff and pushes to the log. (type: 1=Sun, 2=Earth, 3=Moon)
            void calculate(int type);
            //writes log data to a csv file. (type: 1=Sun, 2=Earth, 3=Moon)
            void write_to_csv(int type);
    };
    extern void initvars();
    Eigen::Vector3d VectorF(float m1, float m2, Eigen::Vector3f r1, Eigen::Vector3f r2);
    extern std::vector<size_t> time(float t);
};
#endif