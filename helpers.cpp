#include <algorithm>
#include <cassert>
#include <functional>
#include <iostream>

namespace paley::helper {

/**
 * @param n number to test
 * @return whether n is prime or not
 */
bool is_prime(int n) {
  if (n <= 1) {
    return false;
  }
  if (n == 2 || n == 3) {
    return true;
  }
  if (n % 2 == 0 || n % 3 == 0) {
    return false;
  }

  // Use 6k +/- 1 optimization for efficiency
  for (int i = 5; i * i <= n; i += 6) {
    if (n % i == 0 || n % (i + 2) == 0) {
      return false;
    }
  }

  return true;
}

/**
 * Get a list of prime number between lower_bound and upper_bound that can be associated with a
 * Paley graph, i.e., those $mod 4 \equiv 1$
 *
 * @return a vector of valid prime numbers described above
 */
std::vector<int> get_suitable_primes(int lower_bound, int upper_bound) {
  std::vector<int> primes = {};
  for (int candidate = lower_bound; candidate <= upper_bound; candidate++) {
    if ((candidate % 4 != 1) || !is_prime(candidate)) {  // filter invalid p's
      continue;
    }
    primes.push_back(candidate);
  }
  return primes;
}

/**
 * Compute quadratic residue sequence for prime p
 * @return a vector of 0-1's
 */
std::vector<bool> quadratic_residues(int p) {
  assert(is_prime(p) && p > 2);
  std::vector<bool> ans(p);
  for (size_t i = 1; i <= (p - 1) / 2; i++) {
    ans[(i * i) % p] = true;
  }
  return ans;
}

/**
 * Get the adjacency matrix for Paley graph of p vertices
 * @return
 */
std::vector<std::vector<bool>> get_paley_adjacency(int p) {
  const auto row = quadratic_residues(p);
  std::vector<std::vector<bool>> adj(p, std::vector<bool>(p));
  for (int i = 0; i < p; i++) {
    // Circularly shift the entry of adj to right by i, then assign the result to i-th row of adjacency matrix
    std::rotate_copy(row.rbegin(), row.rbegin() + i, row.rend(),
                     adj[i].rbegin());
  }
  return adj;
}
} // paley::helper