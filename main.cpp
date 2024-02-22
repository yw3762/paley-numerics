#include <functional>
#include <iostream>

#include "helpers.cpp"
#include "lovasz.cpp"
#include "block_diagonal.cpp"

const long long MIN_P = 821;
const long long MAX_P = 997;

void compute_and_write(int lower_bound, int upper_bound) {
  auto primes = paley::helper::get_suitable_primes(lower_bound, upper_bound);
  auto n_primes = primes.size();

  std::vector<double> theta(n_primes), l2(n_primes), l3(n_primes);
  for (int i = 0; i < n_primes; i++) {
    auto A = paley::helper::get_paley_adjacency(primes[i]);
    theta[i] = paley::relaxation::lovasz_theta(A);
    l2[i] = paley::relaxation::l2(A);
  }
}

int main() {
  std::vector<std::vector<bool>> resultMatrix = paley::helper::get_paley_adjacency(13);

  // Display the result
  for (const auto& row : resultMatrix) {
    for (int val : row) {
      std::cout << val << " ";
    }
    std::cout << std::endl;
  }
  return 0;
}
