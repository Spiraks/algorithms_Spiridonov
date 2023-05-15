#include "order_statistics.hpp"

#include <algorithm>
#include <iostream>
#include <stdexcept>
#include <vector>

size_t Partition(std::vector<int>& data, size_t left, size_t right,
                 size_t pivotIndex) {
  int pivot_value = data[pivotIndex];
  std::swap(data[pivotIndex], data[right]);
  size_t store_index = left;
  for (size_t i = left; i < right; ++i) {
    if (data[i] < pivot_value) {
      std::swap(data[i], data[store_index]);
      ++store_index;
    }
  }

  std::swap(data[store_index], data[right]);
  return store_index;
}

int GetOrderStatistics(const std::vector<int>& data, size_t n) {
  if (n >= data.size()) {
    throw std::out_of_range("Invalid value of n");
  }

  std::vector<int> copy_data = data;
  size_t left = 0;
  size_t right = copy_data.size() - 1;

  while (left < right) {
    size_t pivotIndex = right; 
    size_t pivot_position = Partition(copy_data, left, right, pivotIndex);

    if (pivot_position == n) {
      return copy_data[pivot_position];  // Найдена порядковая статистика
    } else if (pivot_position < n) {
      left = pivot_position + 1;  // Искать в правой части
    } else {
      right = pivot_position - 1;  // Искать в левой части
    }
  }

  return copy_data[left];  // Возвращаем найденную порядковую статистику
}
