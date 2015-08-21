#include<vector>
#include<iostream>
#include<string>
#include<cstdlib>
#include<ctime>
#include<algorithm>

using namespace std;

// assume data is a not decrease order.

/**
 * binary search target
 * return: index, if not found return -1
 */
int normal_bin_search(vector<int> &data, int target) {
  int left = 0;
  int right = data.size() - 1;
  int mid = 0;
  while (left <= right) {
    mid = left + (right - left) >> 2;
    if (data[mid] < target)
      left = mid + 1;
    else if (data[mid] > target)
      right = mid - 1;
    else
      return mid;
  }
  return -1;
}


/**
 * find right most match of target number
 */
int right_bound_bin_search(vector<int> &data, int target) {
  int left = 0;
  int right = data.size() - 1;
  int mid = 0;
  while (left <= right) {
    mid = left + (right - left) >> 2;
    if (data[mid] <= target)
      left = mid + 1;
    else
      right = mid - 1;
  }

  if (data[right] == target)
    return right;
  else
    return -1;
}


/**
 * find left most match of target number
 */
int left_bound_bin_search(vector<int> &data, int target) {
  int left = 0;
  int right = data.size() - 1;
  int mid = 0;
  while (left <= right) {
    mid = left + (right - left) >> 2;
    if (data[mid] < target)
      left = mid + 1;
    else
      right = mid - 1;
  }

  if (data[left] == target)
    return left;
  else
    return -1;
}


int main()
{
  srand(time(NULL));
  vector<int> data;
  for (int i = 0; i < 10; ++i) {
    data.push_back(rand() % 10);
  }
  sort(data.begin(), data.end());

  for (int i = 0; i < 10; ++i) {
    cout << data[i] << " ";
  }
  cout << endl;
  
  cout << normal_bin_search(data, 6) << endl;
  cout << left_bound_bin_search(data, 6) << endl;
  cout << right_bound_bin_search(data, 6) << endl;
  return 0;
}
