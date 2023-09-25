#include<stdio.h>

typedef int dataType;

void _swap(dataType* data_1, dataType* data_2)
{
	dataType tmp = *data_1;
	*data_1 = *data_2;
	*data_2 = tmp;
}
//简单选择排序
void SimpleSelectionSort(dataType* data, int size)
{	
	for(int i = 0; i < size; i++){ 			//每一轮同后面的元素依次比较，若比自身小，则交换，一轮下来
		for(int j = i + 1; j < size; j++){	//当前子数组的最小元素置于子数组首位
			if(data[i] > data[j]) 
				_swap(&data[i], &data[j]);
		}
	  	/*printf("%d: ",i+1); //排序细节
		for(int cnt = 0; cnt < size; cnt++){
			printf("%d ", data[cnt]);
		}
		printf("\n");*/
	}
}

//简单插入排序
void SimpleInsertionSort(dataType* data, int size)
{
	for(int i = 1; i < size; i++){
		int tmp = data[i];
		for(int j = i - 1; j >= 0; j--){ 	//把当前元素存储在tmp，依次与前面已经排序好的子数组进行比较，
			if(tmp < data[j]){				//若比前面一个小，前面一个后移，若比前面一个大，直接插入空出
				data[j + 1] = data[j];		//的位置
				if(j == 0) data[0] = tmp;
			}
			else{
				data[j + 1] = tmp;
				j = -1;
			}
		}
		/*printf("%d: ",i+1); //排序细节
		for(int cnt = 0; cnt < size; cnt++){
			printf("%d ", data[cnt]);
		}
		printf("\n");*/
	}
}

//冒泡排序
void BubbleSort(dataType* data, int size)
{
	for(int i = size; i > 0; i--){ 		//从序列起始位置进行两两比较，逆序则交换，一轮下来
		for(int j = 0; j < i; j++){		//可将子数组中的最大值移到子数组最后一个元素
			if(data[j] > data[j + 1])
				_swap(&data[j], &data[j + 1]);
		}
		/*printf("%d: ",i+1); //排序细节
		for(int cnt = 0; cnt < size; cnt++){
			printf("%d ", data[cnt]);
		}
		printf("\n");*/
	}
} 

//希尔排序
void ShellSort(dataType* data, int size)
{
 	//希尔排序的性能在于步长选取；
    for (int step = size / 2; step > 0; step /= 2) {
        for (int i = step; i < size; i++) {
            dataType temp = data[i];
            int j;
            for (j = i; j >= step && data[j - step] > temp; j -= step) {
                data[j] = data[j - step];
            }
            data[j] = temp;
        }
    }
}

//堆排序，见Data-Structure/Heap.c
//void HeapSort(Heap* heap);

//归并排序
void merge(dataType* data, int left, int mid, int right)
{
	int n1 = mid - left + 1, n2 = right - mid;
	int left_arr[n1],right_arr[n2];
	for(int i = 0; i < n1; i++){
		left_arr[i] = data[left + i];
	}
	for(int i = 0; i < n2; i++){
		right_arr[i] = data[mid + 1 + i];
	}

	int l = 0, r = 0, k = left;
	while(l < n1 && r < n2){
		if(left_arr[l] > right_arr[r]){
			data[k++] = right_arr[r++];
		}else{
			data[k++] = left_arr[l++];
		}
	}
	while(l < n1){
		data[k++] = left_arr[l++];
	}
	while(r < n2){
		data[k++] = right_arr[r++];
	}
}

void MergeSort(dataType* data, int left, int right)
{
	int mid = left + (right - left)/2;
	if(left < right){
		MergeSort(data, left, mid);
		MergeSort(data, mid + 1, right);
		merge(data, left, mid, right);

    // for(int cnt = 0; cnt < 6; cnt++){     //排序细节
		// 	printf("%d ", data[cnt]);
		// }
		// printf("\n");
	}
}

//快速排序
void QuickSort(dataType* data, int left, int right)
{
	int right_sign = right, left_sign = left + 1; 	//定义左游标和右游标
	int pivot = data[left]; 	//定义基准数
	int rorl = 1;
	while(left_sign <= right_sign){ //左游标超过右游标或右游标超过左游标则停止循环
		if(rorl == 1){		//以右游标判断
			if(data[right_sign] < pivot){
				data[left_sign - 1] = data[right_sign--];
				rorl = -1; 	//右游标所指向的数移动后下次操作左游标
			}else right_sign--;	 //若右游标所指向的数并未移动，则下次继续操作右游标
		}else if(rorl == -1 && left_sign <= right_sign){	//以左游标判断
			if(data[left_sign] > pivot){
				data[right_sign + 1] = data[left_sign++];
				rorl = 1; 	//左游标所指向的数移动后下次操作右游标
			}else left_sign++; 	//若左游标所指向的数并未移动，则下次继续操作左游标
		}
	}
	if(rorl == -1 && left < right){
		data[left_sign] = pivot; 	//将基准返回数组空出的位置
		QuickSort(data, left, left_sign - 1); 	//将基准以左的数组继续递归快排
		QuickSort(data, left_sign + 1, right);	//将基准以右的数组继续递归快排
		
		// for(int cnt = 0; cnt < 9; cnt++){	//排序细节
		// 	printf("%d ", data[cnt]);
		// }
		// printf("\n");
	}else if(rorl == 1 && left < right){
		data[right_sign] = pivot;
		QuickSort(data, left, right_sign - 1);
		QuickSort(data, right_sign + 1, right);
		
		// for(int cnt = 0; cnt < 9; cnt++){
		// 	printf("%d ", data[cnt]);
		// }
		// printf("\n");
	}
}

//桶结构体
typedef struct Bucket
{
	dataType bucket[10];
	int size; 
}Bucket;

//桶排序，基于快排
void BucketSort(dataType* data, int size, int bucketNum)
{
	Bucket B[bucketNum];
	for(int i = 0; i < bucketNum; i++){ 	//初始化桶内元素个数
		B[i].size = 0;
	}
	for(int i = 0; i < 10; i++){ 		//将元素分别放入相应的桶
		B[data[i]/10].bucket[B[data[i]/10].size] = data[i];
		B[data[i]/10].size++;
	}
	for(int i = 0; i < bucketNum; i++){ 	//每个桶内元素进行快排
		QuickSort(B[i].bucket, 0, B[i].size - 1);
	}
		int k = 0, i = 0;
	while(i < 10){				//将桶内元素一一返回原数组
		for(int j = 0; j < B[k].size; j++){
			data[i] = B[k].bucket[j];
			i++;
		}
		k++;
	}
}

int main()
{
	//int data[6] = {54, 19, 4, 70, 30, 2};
	//int data[9] = {19, 54, 4, 30, 70, 2, 99, 23, 95};
	int data[10] = {5, 2, 8, 11, 26, 34, 15, 31, 25, 35};
	//SimpleSelectionSort(data, 6);
	//SimpleInsertionSort(data, 6);
	//BubbleSort(data, 6);
	//ShellSort(data, 9);
	//HeapSort(data, 6);
	//MergeSort(data, 0, 5);
	//QuickSort(data, 0, 8);
	BucketSort(data, 10, 4);
	for(int i = 0; i < 6; i++){
		printf("%d ", data[i]);
	}
	return 0;
}
