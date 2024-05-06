#include "space.hpp"
#include <fstream>

using namespace space;

void object::initialize_object(float_t x, float_t y, float_t z, float_t vx, float_t vy, float_t vz)
{
    object::x = x;
    object::y = y;
    object::z = z;
    object::vx = vx;
    object::vy = vy;
    object::vz = vz;
}
void object::calculate(int type)
{
    std::vector<float> data;
    T0 = T0 + dt;
    Eigen::Vector3d a;
    switch(type)
    {
        case 1:
            a = (VectorF(m_s, m_e, r_s, r_e) + VectorF(m_s, m_m, r_s, r_m));
            g = a/m_s;
            v = v + g*dt;
            r_s = r_s + v*dt;
            data.insert(data.end(), {T0, r_s(0), r_s(1), r_s(2), vx, vy, vz});
            break;
        case 2:
            g = (VectorF(m_s, m_e, r_e, r_s) + VectorF(m_s, m_m, r_e, r_m))/m_e;
            v = v + g*dt;
            r_e = r_e + v*dt;
            data.insert(data.end(), {T0, r_e(0), r_e(1), r_e(2), vx, vy, vz});
            break;
        case 3:
            g = (VectorF(m_s, m_e, r_m, r_s) + VectorF(m_s, m_m, r_m, r_e))/m_m;
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
Eigen::Vector3d VectorF(float m1, float m2, Eigen::Vector3f r1, Eigen::Vector3f r2)
{
    float t = G*(m1*m2);
    Eigen::Vector3f diff = r2 - r1;
    return t * diff * std::pow(diff.norm(), -3);
}
std::vector<size_t> time(float t)
{
    size_t day = size_t(t/86400);
    size_t hour = size_t((t-day*86400)/3600);
    size_t min = size_t((t-day*86400-hour*3600)/60);
    size_t sec = size_t(t-day*86400-hour*3600-min*60);
    std::vector<size_t> time;
    time.insert(time.end(), {day,hour,min,sec});
    return time;
}
