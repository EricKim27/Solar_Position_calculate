#include <cmath>
#include <eigen3/Eigen/Dense>
#include <vector>

namespace space {
    extern double vx_e;
    extern double vy_e;
    extern double vz_e;
    extern double vx_s;
    extern double vy_s;
    extern double vz_s;
    extern double vx_m;
    extern double vy_m;
    extern double vz_m;
    extern Eigen::Vector3d r_s;
    extern Eigen::Vector3d r_m;
    extern Eigen::Vector3d r_e;
    extern long double G;
    Eigen::Vector3d VectorF(float m1, float m2, Eigen::Vector3d r1, Eigen::Vector3d r2);
    extern std::vector<size_t> time(float t);

    class object {
        private:
            double x,y,z,vx,vy,vz;
            float T0=0;
            const float dt=0.0625;
            int dt_list=3600;
            Eigen::Vector3d v;
            Eigen::Vector3d g;
            float m_s=1.988500 * (std::pow(10, 30));    
            float m_m=7.349 * (std::pow(10, 22));       
            float m_e=81.3005690769 * (m_m);
        public:
            std::vector<std::vector<double>> log;
            //initializing the object.
            void initialize_object(double ax, double ay, double az, int type);
            //calculates stuff and pushes to the log. (type: 1=Sun, 2=Earth, 3=Moon)
            void calculate(int type);
            //writes log data to a csv file. (type: 1=Sun, 2=Earth, 3=Moon)
            void write_to_csv(int type);
    };
}