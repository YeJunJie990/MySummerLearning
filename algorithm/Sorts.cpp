#include <vector>
#include <iostream>
#include <limits.h>

using namespace std;

class MergeSort{
public:
    /*
        归并排序
        排序时间稳定： O(nlgn)
        额外空间需要：O(n) + 递归的栈空间  
    */
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
            mergeSort(nums, left, mid); //分
            mergeSort(nums, mid + 1, right); //分
            merge(nums, left, mid, right); //治
        }
    }
    void Sort(vector<int> & nums) {
        mergeSort(nums, 0, nums.size() - 1);
    }
};


void InsertSort(vector<int> & nums) {
    /*
        插入排序
        排序时间不稳定， 最坏是O(n^2)
        空间复杂度 O(1)
    */
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

void bubbleSort(vector<int> & nums) {
    /*
        冒泡排序
        稳定性：稳定
        平均时间复杂度：n方
        空间复杂度：1
    */
   for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < nums.size() - 1 - i; j++) {
            if (nums[j] > nums[j+1]) swap(nums[j], nums[j+1]);
        } 
   }
}

void chooseSort(vector<int> & nums) {
    /*
        选择排序
        稳定性：不稳定
        平均时间复杂度：n方
        空间复杂度：1
    */
    for (int i = 0; i < nums.size(); i++) {
        int toSwapIdx = i;
        for (int j = i; j < nums.size(); j++) {
            toSwapIdx = nums[j] < nums[toSwapIdx] ? j : toSwapIdx;
        }
        swap(nums[i], nums[toSwapIdx]);
    }
}

void quickSort(vector<int> & nums, int start, int end) {
    if (start >= end) return;
    int base = nums[start];
    int j = start;
    for (int i = start + 1; i <= end; i++) {
        if (nums[i] <= base) swap(nums[i], nums[++j]); //一定是j先增
    }
    //循环结束后： 3(start/base), 1, 3, 2(j), 5, 7, 6
    //base元素一直在start处，从未动过
    //循环结束后，j后面的第一个元素是大于base的，j当前的元素是小于base的，而base的坑在start处，没有动过（因为第一次碰到小于base的数时候，j先自增了）
    //所以把start处的元素和j处的小于base的元素互换，此时，base左边全是小于等于base的，右边
    swap(nums[j], nums[start]);
    quickSort(nums, start, j - 1);
    quickSort(nums, j + 1, end);
}

int main() {
    vector<int> nums({3,5,1,3,2,7,6});
    for (auto & i : nums) {
        cout<<i<<' ';
    }
    cout<<endl;
    // InsertSort(nums); //插入排序
    // MergeSort s; //归并排序
    // s.Sort(nums);
    //bubbleSort(nums); //冒泡排序
    //chooseSort(nums); //选择排序
    //quickSort(nums, 0, nums.size() - 1); //快排
    for (auto & i : nums) {
        cout<<i<<' ';
    }
    cout<<endl;
    return 0;
}