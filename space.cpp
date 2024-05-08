#include "space.hpp"
#include <fstream>

void space::initvars(){
    space::vx_e=-2.983302263902714*1000*std::pow(10, 1);
    space::vy_e=-5.138481408411204*1000*std::pow(10, 0);
    space::vz_e = 1.105037462794778*1000*std::pow(10, -3);
    space::vx_s=8.441016159655652*1000*std::pow(10,-3);
    space::vy_s=-1.221912155158748*1000*std::pow(10, -2);
    space::vz_s=-7.918737699351246*1000*std::pow(10, -5);
    space::vx_m=-3.024279048864922*1000*std::pow(10, 1);
    space::vy_m=-6.014108452553830*1000*std::pow(10, 0);
    space::vz_m=-5.816013309114965*1000*std::pow(10, -2);
    space::r_s=Eigen::Vector3f(vx_s, vy_s, vz_s);
    space::r_m=Eigen::Vector3f(vx_m, vy_m, vz_m);
    space::r_e = Eigen::Vector3f(vx_e, vy_e, vz_e);
}

using namespace space;

void object::initialize_object(float x, float y, float z, int type)
{
    object::x = x;
    object::y = y;
    object::z = z;
    switch(type)
    {
        case 1:
            object::vx = vx_s;
            object::vy = vy_s;
            object::vz = vz_s;
        case 2:
            object::vx = vx_e;
            object::vy = vy_e;
            object::vz = vz_e;
        case 3:
            object::vx = vx_m;
            object::vy = vy_m;
            object::vz = vz_m;
    }
}
void object::calculate(int type)
{
    std::vector<float> data;
    T0 = T0 + dt;
    Eigen::Vector3f a;
    switch(type)
    {
        case 1:
            g = ((VectorF(m_s, m_e, r_s, r_e) + VectorF(m_s, m_m, r_s, r_m))/m_s).cast<float>();
            v = v + g*dt;
            r_s = r_s + v*dt;
            data.insert(data.end(), {T0, r_s(0), r_s(1), r_s(2), vx, vy, vz});
            break;
        case 2:
            g = ((VectorF(m_s, m_e, r_e, r_s) + VectorF(m_s, m_m, r_e, r_m))/m_e).cast<float>();
            v = v + g*dt;
            r_e = r_e + v*dt;
            data.insert(data.end(), {T0, r_e(0), r_e(1), r_e(2), vx, vy, vz});
            break;
        case 3:
            g = ((VectorF(m_s, m_e, r_m, r_s) + VectorF(m_s, m_m, r_m, r_e))/m_m).cast<float>();
            v = v + g*dt;
            r_m = r_m + v*dt;
            data.insert(data.end(), {T0, r_m(0), r_m(1), r_m(2), vx, vy, vz});
            break;
    }
    log.push_back(data);
}
void object::write_to_csv(int type)
{
    std::string name;
    switch(type)
    {
        case 1:
            name = "sun_data.csv";
            break;
        case 2:
            name = "Earth_data.csv";
            break;
        case 3:
            name = "Moon_data.csv";
            break;
    }
    std::fstream csv;
    csv.open(name, std::ios::in | std::ios::out | std::ios::app);
    if(!csv.is_open())
    {
        csv.clear();
        csv.open(name, std::ios::out);
        csv.close();
        csv.open(name, std::ios::in | std::ios::out | std::ios::app);
    }
    if(!csv)
    {
        return;
    }
    for (const auto& row : log) {
        for (const auto& elem : row) {
            csv << elem << ',';
        }
        csv << '\n';
    }
}
Eigen::Vector3d space::VectorF(float m1, float m2, Eigen::Vector3f r1, Eigen::Vector3f r2)
{
    float t = G*(m1*m2);
    Eigen::Vector3f diff = r2 - r1;
    return (t * diff * std::pow(diff.norm(), -3)).cast<double>();
}
std::vector<size_t> space::time(float t)
{
    size_t day = size_t(t/86400);
    size_t hour = size_t((t-day*86400)/3600);
    size_t min = size_t((t-day*86400-hour*3600)/60);
    size_t sec = size_t(t-day*86400-hour*3600-min*60);
    std::vector<size_t> time;
    time.insert(time.end(), {day,hour,min,sec});
    return time;
}