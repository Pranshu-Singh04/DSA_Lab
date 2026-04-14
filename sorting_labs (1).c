/*
 * ============================================================
 *  LAB 2 - SORTING
 * ============================================================
 *
 * AIM: To implement Insertion Sort and Selection Sort algorithms.
 *
 * ============================================================
 *  INSERTION SORT
 * ============================================================
 *
 * PRINCIPLE:
 *   - Builds the sorted array one element at a time.
 *   - For each element (starting from index 1), pick it as a
 *     "key" and shift all larger elements in the sorted portion
 *     one position to the right.
 *   - Insert the key into its correct position.
 *   - Best case: O(n) when already sorted.
 *   - Worst/Average case: O(n^2).
 *   - Stable sort — equal elements maintain original order.
 *   - In-place: uses O(1) extra space.
 */

#include <stdio.h>

void InsertionSort(int arr[], int n) {
    int i, key, j;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j   = i - 1;
        /* Shift elements greater than key one position ahead */
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main_insertion() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    InsertionSort(arr, n);

    printf("Sorted array using Insertion Sort:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}


/*
 * ============================================================
 *  SELECTION SORT
 * ============================================================
 *
 * PRINCIPLE:
 *   - Divides the array into a sorted and an unsorted region.
 *   - On each pass, find the minimum element in the unsorted
 *     region and swap it with the first unsorted element.
 *   - After k passes, the first k elements are sorted.
 *   - Time complexity: O(n^2) in all cases.
 *   - Not stable (swapping may change relative order).
 *   - In-place: O(1) extra space.
 *   - Advantage: makes at most n-1 swaps — good when write
 *     operations are expensive.
 */

void SelectionSort(int arr[], int n) {
    int i, j, min_idx, temp;
    for (i = 0; i < n - 1; i++) {
        min_idx = i;
        /* Find minimum element in unsorted portion */
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }
        /* Swap minimum with first unsorted element */
        if (min_idx != i) {
            temp           = arr[i];
            arr[i]         = arr[min_idx];
            arr[min_idx]   = temp;
        }
    }
}

int main_selection() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    SelectionSort(arr, n);

    printf("Sorted array using Selection Sort:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}


/*
 * ============================================================
 *  LAB 3 - LINEAR SORTING
 * ============================================================
 *
 * AIM: To implement Counting Sort, Radix Sort, and Bucket Sort
 *      algorithms.
 *
 * ============================================================
 *  COUNTING SORT
 * ============================================================
 *
 * PRINCIPLE:
 *   - Non-comparison based sort; works on integer keys.
 *   - Count the frequency of each distinct element.
 *   - Compute prefix sums to determine positions in output.
 *   - Build the sorted output array by placing each element
 *     at its computed position (iterate in reverse for stability).
 *   - Time complexity: O(n + k) where k = range of input.
 *   - Space complexity: O(k) for count array.
 *   - Stable sort.
 */

void CountingSort_basic(int arr[], int n) {
    /* Find maximum value to size the count array */
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];

    int count[max + 1];

    /* Initialise count array to 0 */
    for (int i = 0; i <= max; i++)
        count[i] = 0;

    /* Count occurrences */
    for (int i = 0; i < n; i++)
        count[arr[i]]++;

    /* Accumulate counts (prefix sum) */
    for (int i = 1; i <= max; i++)
        count[i] += count[i - 1];

    int output[n];
    /* Place elements in output (reverse for stability) */
    for (int i = n - 1; i >= 0; i--) {
        output[count[arr[i]] - 1] = arr[i];
        count[arr[i]]--;
    }

    /* Copy output back to arr */
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

int main_counting() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    CountingSort_basic(arr, n);

    printf("Sorted array using Counting Sort:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}


/*
 * ============================================================
 *  RADIX SORT
 * ============================================================
 *
 * PRINCIPLE:
 *   - Non-comparison based sort for integers.
 *   - Sort digit by digit from least significant to most
 *     significant (LSD radix sort).
 *   - Uses a stable digit sort (counting sort) at each pass.
 *   - Because each pass is stable, the relative order from
 *     prior passes is preserved.
 *   - Time complexity: O(d * (n + k)) where d = number of
 *     digits and k = radix (10 for decimal).
 *   - Space complexity: O(n + k).
 */

int getMax(int arr[], int n) {
    int max = arr[0];
    for (int i = 1; i < n; i++)
        if (arr[i] > max)
            max = arr[i];
    return max;
}

/* Counting sort based on digit represented by exp */
void CountingSort_radix(int arr[], int n, int exp) {
    int output[n];
    int count[10] = {0};

    /* Count occurrences of digits */
    for (int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    /* Prefix sum */
    for (int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    /* Build output (reverse for stability) */
    for (int i = n - 1; i >= 0; i--) {
        output[count[(arr[i] / exp) % 10] - 1] = arr[i];
        count[(arr[i] / exp) % 10]--;
    }

    /* Copy back */
    for (int i = 0; i < n; i++)
        arr[i] = output[i];
}

void RadixSort(int arr[], int n) {
    int max = getMax(arr, n);
    /* Process each digit position */
    for (int exp = 1; max / exp > 0; exp *= 10)
        CountingSort_radix(arr, n, exp);
}

int main_radix() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    RadixSort(arr, n);

    printf("Sorted array using Radix Sort:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}


/*
 * ============================================================
 *  BUCKET SORT
 * ============================================================
 *
 * PRINCIPLE:
 *   - Distributes elements into a number of buckets.
 *   - Each bucket is sorted individually (here using insertion
 *     sort within each bucket).
 *   - Concatenate all buckets to produce the sorted output.
 *   - Best suited for uniformly distributed floating-point
 *     values in [0, 1); adapted here for integers.
 *   - Average time complexity: O(n + k) for uniform input.
 *   - Worst case: O(n^2) if all elements fall in one bucket.
 */

/* Insertion sort used to sort individual buckets */
void InsertionSort_bucket(int bucket[], int size) {
    for (int i = 1; i < size; i++) {
        int key = bucket[i];
        int j   = i - 1;
        while (j >= 0 && bucket[j] > key) {
            bucket[j + 1] = bucket[j];
            j--;
        }
        bucket[j + 1] = key;
    }
}

/* NOTE: The notebook's bucket sort uses insertion sort per
 * bucket. A simplified integer version is shown here.
 * For floating-point [0,1) values, divide by max to get
 * a bucket index of floor(n * value). */

/*
 * ============================================================
 *  LAB 4 - DAC SORTING (Divide and Conquer)
 * ============================================================
 *
 * AIM: To implement Merge Sort and Quick Sort algorithms using
 *      the Divide & Conquer method.
 *
 * ============================================================
 *  MERGE SORT
 * ============================================================
 *
 * PRINCIPLE:
 *   - Divide the array into two halves recursively until each
 *     sub-array has a single element.
 *   - Merge the sorted halves back: compare front elements of
 *     both halves, copy the smaller one, then copy any
 *     remaining elements.
 *   - Recurrence: T(n) = 2T(n/2) + O(n)  →  O(n log n).
 *   - Stable sort.
 *   - Requires O(n) auxiliary space for temporary arrays.
 *   - Preferred for linked lists and external sorting.
 */

void Merge(int arr[], int left, int mid, int right) {
    int i, j, k;
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int L[n1], R[n2];

    /* Copy data to temporary arrays */
    for (i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    i = 0; j = 0; k = left;

    /* Merge the two halves */
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    /* Copy remaining elements of L */
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    /* Copy remaining elements of R */
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void MergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        MergeSort(arr, left, mid);
        MergeSort(arr, mid + 1, right);
        Merge(arr, left, mid, right);
    }
}

int main_mergesort() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    MergeSort(arr, 0, n - 1);

    printf("Sorted Array using Merge Sort:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}


/*
 * ============================================================
 *  LAB 5 - HEAP SORT
 * ============================================================
 *
 * AIM: To implement Heap Sort using Max Heap and Min Heap.
 *
 * ============================================================
 *  MAX HEAP SORT  (sorts in ASCENDING order)
 * ============================================================
 *
 * PRINCIPLE:
 *   - A max-heap is a complete binary tree where each parent
 *     node is >= its children.
 *   - Phase 1 (Build): Convert array into a max-heap by calling
 *     maxHeapify() on all non-leaf nodes from bottom-up.
 *   - Phase 2 (Extract): Repeatedly swap the root (max element)
 *     with the last element, shrink the heap by 1, and
 *     heapify the root to restore the heap property.
 *   - After n-1 extractions the array is sorted ascending.
 *   - Time complexity: O(n log n) in all cases.
 *   - In-place: O(1) extra space.
 *   - Not stable.
 */

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

/* Maintain max-heap property rooted at index i in heap of size n */
void maxHeapify(int arr[], int n, int i) {
    int largest = i;
    int left    = 2 * i + 1;
    int right   = 2 * i + 2;

    if (left  < n && arr[left]  > arr[largest])
        largest = left;
    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);   /* Recursively heapify affected subtree */
    }
}

void HeapSort_max(int arr[], int n) {
    /* Build max-heap: start from last non-leaf node */
    for (int i = n / 2 - 1; i >= 0; i--)
        maxHeapify(arr, n, i);

    /* Extract max element one by one */
    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);        /* Move current root (max) to end */
        maxHeapify(arr, i, 0);         /* Heapify reduced heap */
    }
}

int main_maxheap() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    HeapSort_max(arr, n);

    printf("Sorted array in ascending order:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}


/*
 * ============================================================
 *  MIN HEAP SORT  (sorts in DESCENDING order)
 * ============================================================
 *
 * PRINCIPLE:
 *   - A min-heap is a complete binary tree where each parent
 *     node is <= its children.
 *   - Phase 1 (Build): Convert array into a min-heap by calling
 *     minHeapify() on all non-leaf nodes from bottom-up.
 *   - Phase 2 (Extract): Repeatedly swap the root (min element)
 *     with the last element, shrink the heap by 1, and
 *     heapify the root to restore the heap property.
 *   - After n-1 extractions the array is sorted descending.
 *   - Time complexity: O(n log n) in all cases.
 *   - In-place: O(1) extra space.
 */

/* Maintain min-heap property rooted at index i in heap of size n */
void minHeapify(int arr[], int n, int i) {
    int smallest = i;
    int left     = 2 * i + 1;
    int right    = 2 * i + 2;

    if (left  < n && arr[left]  < arr[smallest])
        smallest = left;
    if (right < n && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, n, smallest);  /* Recursively heapify affected subtree */
    }
}

void HeapSort_min(int arr[], int n) {
    /* Build min-heap: start from last non-leaf node */
    for (int i = n / 2 - 1; i >= 0; i--)
        minHeapify(arr, n, i);

    /* Extract min element one by one */
    for (int i = n - 1; i >= 0; i--) {
        swap(&arr[0], &arr[i]);        /* Move current root (min) to end */
        minHeapify(arr, i, 0);         /* Heapify reduced heap */
    }
}

int main_minheap() {
    int n;
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    int arr[n];
    printf("Enter %d elements:\n", n);
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    HeapSort_min(arr, n);

    printf("Sorted array in descending order:\n");
    for (int i = 0; i < n; i++)
        printf("%d ", arr[i]);
    printf("\n");

    return 0;
}


/*
 * ============================================================
 *  DRIVER MAIN
 *  Uncomment the call you want to run, or rename the desired
 *  function to main() and compile individually.
 * ============================================================
 */
int main() {
    /* --- Lab 2 --- */
    // main_insertion();
    // main_selection();

    /* --- Lab 3 --- */
    // main_counting();
    // main_radix();

    /* --- Lab 4 --- */
    // main_mergesort();

    /* --- Lab 5 --- */
    main_maxheap();
    // main_minheap();

    return 0;
}
