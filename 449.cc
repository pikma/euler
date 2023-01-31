// https://projecteuler.net/problem=449

#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <limits>
#include <numbers>

double EstimateVolume(double a, double b, uint64_t num_points) {
  // We compute the volume of the region in the half-plane z >= 0.
  // To do that, we break it down in cylinders whose central axis is the z-axis.
  // We iterate over points on the surface restricted to y=0, x>=0, and each
  // pair of consecutive points defines a tiny cylinder that is added to the
  // total volume.

  double previous_x_surface, previous_y_surface;
  double volume = 0;
  for (uint64_t i = 0; i < num_points; ++i) {
    double angle = std::numbers::pi / 2 * i / (num_points - 1);
    double x = a * std::cos(angle);
    double y = b * std::sin(angle);

    // The tangent to the ellipse at (x,y), equal to d(x,y)/dangle.
    double tangent_x = -a * std::sin(angle);
    double tangent_y = b * std::cos(angle);

    // The normal to the ellipse at (x, y).
    double normal_x = tangent_y;
    double normal_y = -tangent_x;

    double normal_norm = std::sqrt(normal_x * normal_x + normal_y * normal_y);

    double x_surface = x + normal_x / normal_norm;
    double y_surface = y + normal_y / normal_norm;

    if (i != 0) {
      double mid_x_surface = (x_surface + previous_x_surface) / 2;
      double delta_y = y_surface - previous_y_surface;
      volume += delta_y * std::numbers::pi * mid_x_surface * mid_x_surface;

      // double mid_y_surface = (y_surface + previous_y_surface) / 2;
      // double delta_x = previous_x_surface - x_surface;
      // volume += delta_x * std::numbers::pi * mid_y_surface * mid_y_surface;
    }
    previous_x_surface = x_surface;
    previous_y_surface = y_surface;
  }
  // We only computed the volume of the region z>=0.
  volume *= 2;

  // Now we remove the volume of the inner ellipse.
  volume -= std::numbers::pi * a * a * b * 4 / 3;

  return volume;
}

int main() {
  constexpr double kA = 3, kB = 1;
  // After some trial and error, ~50'000'000 seems to be a good spot. After
  // that, we run into some numerical issues with the sin/cos.
  for (uint64_t n = 1'024; n <= 100'000'000; n *= 4) {
    std::cout.precision(std::numeric_limits<double>::max_digits10);
    std::cout << std::setw(12) << std::setfill(' ') << n << " samples: ";
    std::cout << EstimateVolume(kA, kB, n) << std::endl;
  }
  return EXIT_SUCCESS;
}
