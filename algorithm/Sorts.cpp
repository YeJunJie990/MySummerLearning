#include <vector>
#include <iostream>
#include <limits.h>

using namespace std;



class MergeSort{
public:
    void merge(vector<int> & nums, int left, int mid, int right) { 
        //nums : 3 5 1 3 2 7 6
        //L : 3 5 1 3    R : 2 7 6
        //left = 0; mid = 3; right = 6;
        vector<int> L(mid - left + 1);
        vector<int> R(right - mid);
        int k = left;    
        for (int i = 0; i < L.size(); i++) {
            L[i] = nums[left++]; // L : 3 5 1 3
        }
        for (int i = 0; i < R.size(); i++) {
            R[i] = nums[(mid++) + 1]; // R : 2 7 6
        }
        L.push_back(INT_MAX); //两个哨兵
        R.push_back(INT_MAX); 
        int i=0, j=0;
        for ( ; k <= right; k++) {
            if (L[i] < R[j]) {
                nums[k] = L[i++];
            }
            else {
                nums[k] = R[j++];
            }
        }
    }
    void mergeSort(vector<int> & nums, int left, int right) {
        if (left >= right) return;
        else {
            int mid = (left + right) / 2;
            mergeSort(nums, left, mid);
            mergeSort(nums, mid + 1, right);
            merge(nums, left, mid, right);
        }
    }
    void Sort(vector<int> & nums) {
        mergeSort(nums, 0, nums.size() - 1);
    }
};


void InsertSort(vector<int> & nums) {
    int n = nums.size();
    for (int i = 1; i < n; i++) {
        int key = nums[i];
        int j = i - 1;
        while (j >= 0 && nums[j] > key){
            nums[j+1] = nums[j];
            j--;
        }
        nums[j+1] = key;
    }
}

int main() {
    vector<int> nums({3,5,1,3,2,7,6});
    for (auto & i : nums) {
        cout<<i<<' ';
    }
    cout<<endl;
    InsertSort(nums);
    MergeSort s;
    s.Sort(nums);
    for (auto & i : nums) {
        cout<<i<<' ';
    }
    cout<<endl;
    return 0;
}