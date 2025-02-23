//this search function uses bineary search algorithm to find the element in the array.
#include <iostream>
#include <vector>

bool binary_search(std::vector<int>& array, int target)
{
    int len  = array.size();
    int left = 0;
    int right = len -1;

    while(left <= right)
    {
        int mid = (left +right)/2;
        if (array[mid] == target){
            return true;
        }
        else if (target < array[mid])
        {
            right = mid -1;
        }
        else 
        {
            left = mid +1;
        }
    }
    return false;

}

int main(){
    std::vector<int> array = {1,2,3,4,5,6,7,8,9,10};
    int target = 7;
    bool index = binary_search(array, target);
    if (index)
    {
        std::cout << "True" << std::endl;
    }
    else
    {
        std::cout << "False" << std::endl;
    }
    return 0;
}