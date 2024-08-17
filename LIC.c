#include <stdio.h>
#include <stdlib.h>

int lengthOfLIS(int nums[], int numsSize) {
    if (nums == NULL || numsSize == 0) {
        return 0;
    }

    int dp[numsSize];
    for (int i = 0; i < numsSize; ++i) {
        dp[i] = 1;
    }

    for (int i = 1; i < numsSize; ++i) {
        for (int j = 0; j < i; ++j) {
            if (nums[i] > nums[j]) {
                dp[i] = (dp[i] > dp[j] + 1) ? dp[i] : dp[j] + 1;
            }
        }
    }

    int maxLength = 0;
    for (int i = 0; i < numsSize; ++i) {
        if (dp[i] > maxLength) {
            maxLength = dp[i];
        }
    }

    return maxLength;
}

int main() {
    // Example usage
    int nums[] = {10, 9, 2, 5, 3, 7, 101, 18};
    int numsSize = sizeof(nums) / sizeof(nums[0]);

    int result = lengthOfLIS(nums, numsSize);
    printf("Length of Longest Increasing Subsequence: %d\n", result);

    return 0;
}
