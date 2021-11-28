//
// Created by liuyubobobo on 20/04/2017.
//

#ifndef MERGESORT2_MERGESORT2_H
#define MERGESORT2_MERGESORT2_H

#include <iostream>
#include"insertionSort.h"
using namespace std;


// ��arr[l...mid]��arr[mid+1...r]�����ֽ��й鲢
// ����auxΪ���merge��������Ҫ�ĸ����ռ�
template<typename  T>
void __merge2(T arr[], T aux[], int l, int mid, int r) {

    // ����aux�Ĵ�С��arrһ��, ��������Ҳ����Ҫ����aux������ƫ����
    // ��һ����ʡ�˼�����:)
    for (int i = l; i <= r; i++)
        aux[i] = arr[i];

    // ��ʼ����iָ����벿�ֵ���ʼ����λ��l��jָ���Ұ벿����ʼ����λ��mid+1
    int i = l, j = mid + 1;
    for (int k = l; k <= r; k++) {

        if (i > mid) {  // �����벿��Ԫ���Ѿ�ȫ���������
            arr[k] = aux[j]; j++;
        }
        else if (j > r) {  // ����Ұ벿��Ԫ���Ѿ�ȫ���������
            arr[k] = aux[i]; i++;
        }
        else if (aux[i] < aux[j]) {  // ��벿����ָԪ�� < �Ұ벿����ָԪ��
            arr[k] = aux[i]; i++;
        }
        else {  // ��벿����ָԪ�� >= �Ұ벿����ָԪ��
            arr[k] = aux[j]; j++;
        }
    }

}

// ʹ���Ż��Ĺ鲢�����㷨, ��arr[l...r]�ķ�Χ��������
// ����auxΪ���merge��������Ҫ�ĸ����ռ�
template<typename T>
void __mergeSort2(T arr[], T aux[], int l, int r) {

    // ����С��ģ����, ʹ�ò�������
    if (r - l <= 15) {
        insertionSort2(arr, l, r);
        return;
    }

    int mid = (l + r) / 2;
    __mergeSort2(arr, aux, l, mid);
    __mergeSort2(arr, aux, mid + 1, r);

    // ����arr[mid] <= arr[mid+1]�����,������merge
    // ���ڽ������������ǳ���Ч,���Ƕ���һ�����,��һ����������ʧ
    if (arr[mid] > arr[mid + 1])
        __merge2(arr, aux, l, mid, r);
}


template<typename T>
void mergeSort2(T arr[], int n) {

    // �� mergeSort2��, ����һ��������aux�ռ�,
    // ������������ռ��Բ�����ʽ���ݸ���ɹ鲢����ĸ����Ӻ���
    T* aux = new T[n];

    __mergeSort2(arr, aux, 0, n - 1);

    delete[] aux;   // ʹ��C++, new�����Ŀռ䲻Ҫ�����ͷŵ�:)
}

#endif //MERGESORT2_MERGESORT2_H