#ifndef INC_06_HEAP_SORT_HEAPSORT_H
#define INC_06_HEAP_SORT_HEAPSORT_H

#include "heap.h"

using namespace std;


// heapSort1, �����е�Ԫ��������ӵ�����, �ڽ�����Ԫ�شӶ�������ȡ����, �����������
// �����Ǵ����ѵĹ���, ���ǴӶ�������ȡ��Ԫ�صĹ���, ʱ�临�ӶȾ�ΪO(nlogn)
// ���������������ʱ�临�Ӷ�ΪO(nlogn)
template<typename T>
void heapSort1(T arr[], int n) {

    MaxHeap<T> maxheap = MaxHeap<T>(n);
    for (int i = 0; i < n; i++)
        maxheap.insert(arr[i]);

    for (int i = n - 1; i >= 0; i--)
        arr[i] = maxheap.extractMax();

}


// heapSort2, �������ǵ�heapify���̴�����
// ��ʱ, �����ѵĹ���ʱ�临�Ӷ�ΪO(n), ������Ԫ�����δӶ���ȡ����, ʵ�����Ӷ�ΪO(nlogn)
// �����������ʱ�临�Ӷ���Ȼ��O(nlogn), ���Ǳ�����heapSort1���ܸ���, ��Ϊ�����ѵ����ܸ���
template<typename T>
void heapSort2(T arr[], int n) {

    MaxHeap<T> maxheap = MaxHeap<T>(arr, n);
    for (int i = n - 1; i >= 0; i--)
        arr[i] = maxheap.extractMax();

}

#endif //INC_06_HEAP_SORT_HEAPSORT_H