

#include "../../singleeyefitter/CircleFit/CircleFitHaversine.h"


std::vector<singleeyefitter::Vector3> createCirclePointsOnSphere( singleeyefitter::Vector2 center, double opening_angle_alpha,  int amount, float circle_segment_range ){

    using namespace singleeyefitter;
    using std::sin;
    using std::cos;

    // http://math.stackexchange.com/questions/643130/circle-on-sphere
    double alpha = opening_angle_alpha;
    double beta = center[0];
    double gamma = center[1];

    double sin_a = sin(alpha);
    double cos_a = cos(alpha);
    double sin_b = sin(beta);
    double cos_b = cos(beta);
    double sin_g = sin(gamma);
    double cos_g = cos(gamma);

    std::vector<Vector3> points;

    for (int i = 0; i < amount; ++i)
    {

        double t = circle_segment_range *  2.0 * M_PI * float(i)/amount;
        double cos_t = cos(t);
        double sin_t = sin(t);
        // double x = sin_a * cos_b * cos_g * cos_t + sin_a * sin_g * sin_t - cos_a * sin_b * cos_g;
        // double y = - sin_a * cos_b * sin_g * cos_t + sin_a * cos_g * sin_t + cos_a * sin_b * sin_g;
        // double z = sin_a * sin_b * cos_t + cos_a * cos_b;
        double x = sin_a * cos_b * cos_g * cos_t - sin_a * sin_g * sin_t + cos_a * sin_b * cos_g;
        double y =  sin_a * cos_b * sin_g * cos_t + sin_a * cos_g * sin_t + cos_a * sin_b * sin_g;
        double z = -sin_a * sin_b * cos_t + cos_a * cos_b;
        points.emplace_back(x,y,z);
    }

    return points;

}


singleeyefitter::Vector3 test_haversine( singleeyefitter::Vector2 center, double opening_angle_alpha,  int amount, float circle_segment_range ){

    auto points = createCirclePointsOnSphere(center , opening_angle_alpha, amount, circle_segment_range);
    for(auto& p : points)
        std::cout << p[0] << ", " << p[1] << ", " << p[2] << std::endl;
    return find_circle(points);
}