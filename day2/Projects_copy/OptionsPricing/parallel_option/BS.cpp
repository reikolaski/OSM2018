/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 *
 * This file contains routines to serially compute the call and
 * put price of an European option.
 *
 * Simon Scheidegger -- 06/17.
 ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include <algorithm>    // Needed for the "max" function
#include <cmath>
#include <iostream>


/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 A simple implementation of the Box-Muller algorithm, used to
generate gaussian random numbers; necessary for the Monte Carlo
method below. */

double gaussian_box_muller() {
  double x = 0.0;
  double y = 0.0;
  double euclid_sq = 0.0;

  // Continue generating two uniform random variables
  // until the square of their "euclidean distance"
  // is less than unity
  do {
    x = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    y = 2.0 * rand() / static_cast<double>(RAND_MAX)-1;
    euclid_sq = x*x + y*y;
  } while (euclid_sq >= 1.0);

  return x*sqrt(-2*log(euclid_sq)/euclid_sq);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Pricing a European vanilla call option with a Monte Carlo method

double call_price_European(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T) {
  double S_adjust = S * exp(T*(r-0.5*v*v));
  double S_cur = 0.0;
  double payoff_sum = 0.0;

  for (int i=0; i<num_sims; i++) {
    double gauss_bm = gaussian_box_muller();
    S_cur = S_adjust * exp(sqrt(v*v*T)*gauss_bm);
    payoff_sum += std::max(S_cur - K, 0.0);
  }

  return (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Pricing a European vanilla put option with a Monte Carlo method

double put_price_European(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T) {
  double S_adjust = S * exp(T*(r-0.5*v*v));
  double S_cur = 0.0;
  double payoff_sum = 0.0;

  for (int i=0; i<num_sims; i++) {
    double gauss_bm = gaussian_box_muller();
    S_cur = S_adjust * exp(sqrt(v*v*T)*gauss_bm);
    payoff_sum += std::max(K - S_cur, 0.0);
  }

  return (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Pricing a Asian vanilla call option with a Monte Carlo method

double call_price_Asian(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T, const int& m) {
  double adjust = exp((T/m)*(r-0.5*v*v));
  double S_tj1;
  double S_bar;
  double S_tj;
  double payoff_sum = 0.0;

  for (int i=0; i<num_sims; i++) {
    S_bar = 0.0;
    S_tj1 = S;
    for (int j=0; j<m; j++) {
      double gauss_bm = gaussian_box_muller();
      S_tj = adjust * S_tj1 * exp(sqrt(v*v*(T/m))*gauss_bm);
      S_bar += S_tj;
      S_tj1 = S_tj;
    }
    S_bar /= m;
    payoff_sum += std::max(S_bar - K, 0.0);
  }

  return (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// Pricing a Asian vanilla put option with a Monte Carlo method

double put_price_Asian(const int& num_sims, const double& S, const double& K, const double& r, const double& v, const double& T, const int& m) {
  double adjust = exp((T/m)*(r-0.5*v*v));
  double S_tj1;
  double S_bar;
  double S_tj;
  double payoff_sum = 0.0;

  for (int i=0; i<num_sims; i++) {
    S_bar = 0.0;
    S_tj1 = S;
    for (int j=0; j<m; j++) {
      double gauss_bm = gaussian_box_muller();
      S_tj = adjust * S_tj1 * exp(sqrt(v*v*(T/m))*gauss_bm);
      S_bar += S_tj;
      S_tj1 = S_tj;
    }
    S_bar /= m;
    payoff_sum += std::max(K - S_bar, 0.0);
  }

  return (payoff_sum / static_cast<double>(num_sims)) * exp(-r*T);
}

// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

int main(int argc, char **argv) {

  // Parameters
  //int num_sims = 10000000;   // Number of simulated asset paths
  int num_sims = 1000;
  double S = 100.0;  // Option price
  double K = 100.0;  // Strike price
  double r = 0.05;   // Risk-free rate (5%)
  double v = 0.2;    // Volatility of the underlying (20%)
  double T = 1.0;    // One year until expiry
  int m = 1;

  // Then we calculate the call/put values via Monte Carlo
  double call_E = call_price_European(num_sims, S, K, r, v, T);
  double put_E = put_price_European(num_sims, S, K, r, v, T);

  // Finally we output the parameters and prices
  std::cout << "Number of Paths: " << num_sims << std::endl;
  std::cout << "Underlying:      " << S << std::endl;
  std::cout << "Strike:          " << K << std::endl;
  std::cout << "Risk-Free Rate:  " << r << std::endl;
  std::cout << "Volatility:      " << v << std::endl;
  std::cout << "Maturity:        " << T << std::endl;

  std::cout << "Call Price:      " << call_E << std::endl;
  std::cout << "Put Price:       " << put_E << std::endl;

  double call_A = call_price_Asian(num_sims, S, K, r, v, T, m);
  double put_A = put_price_Asian(num_sims, S, K, r, v, T, m);

  // Finally we output the parameters and prices
  std::cout << "Number of Paths: " << num_sims << std::endl;
  std::cout << "Underlying:      " << S << std::endl;
  std::cout << "Strike:          " << K << std::endl;
  std::cout << "Risk-Free Rate:  " << r << std::endl;
  std::cout << "Volatility:      " << v << std::endl;
  std::cout << "Maturity:        " << T << std::endl;

  std::cout << "Call Price:      " << call_A << std::endl;
  std::cout << "Put Price:       " << put_A << std::endl;

  return 0;
}
