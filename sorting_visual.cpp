#include "graphics.h" 
#include <bits/stdc++.h> // collection f w
using namespace std; // stl

vector<int> arr; 
int size = 400 , n = 100 , gap = 6; 

// Function for swapping the lines graphically 
void swapline(int x1, int y1, int x2, int y2) 
{ 
	// x1 → The x-coordinate of the first line.
	// y1 → The hight of the first line.

	// x2 → The x-coordinate of the second line.
	// y2 → The hight of the second line..

	//step 1-> Erasing the old line (by redrawing it in black).
	//step 2-> Drawing the new line (with the updated height in white).

	//swaping the firts line
	setcolor(BLACK); 
	line(x1, size, x1, size - y2); // Erase the old line (draw it in black)
	setcolor(WHITE); 
	line(x1, size, x1, size - y1); // Draw the new line with the updated height

	// Swapping the second line (y → x)
	setcolor(BLACK); 
	line(x2, size, x2, size - y1); // Erase the old line (draw it in black)
	setcolor(WHITE); 
	line(x2, size, x2, size - y2); // Draw the new line with the updated height
} 

void bubble_sort() 
{ 
	int temp, i, j; 

	for (i = 1; i < n; i++) { //nuber of pass
		for (j = 0; j < n - i; j++) { // sap elements
			if (arr[j] > arr[j + 1]) { 
				delay(1);
				swap(arr[j] , arr[j+1]);
				swapline(gap * j + 1, arr[j],gap * (j + 1) + 1, arr[j + 1] ); 
			} 
		} 
	} 
} 

void selection_sort()
{
	for(int i = 0;i < n-1;i += 1)
	{
		int minu = arr[i];
		int idx = -1;
		for(int j = i+1;j < n;j += 1)
		{
			if(arr[j] < minu)idx = j,minu = arr[j];
		}
		if(minu < arr[i])
		{
			delay(20);
			swap(arr[i] , arr[idx]);
			swapline(gap * i + 1, arr[i],gap * (idx) + 1, arr[idx] );
		}
	}
}

void insertion_sort()
{
	for(int i = 1;i < n;i += 1)
	{
		int j = i;
		while(j > 0 && arr[j-1] > arr[j])
		{
			delay(5);
			swap(arr[j] , arr[j-1]);
			swapline(gap * j + 1, arr[j], gap * (j - 1) + 1, arr[j - 1] );
			j--;
		}
	}
}

void merge(int low, int mid, int high) {
    vector<int> temp(high - low + 1);
    int l = low, r = mid + 1, i = 0;
    
    while (l <= mid && r <= high) {
        if (arr[l] <= arr[r]) {
            temp[i] = arr[l];
            l++;
        } else {
            temp[i] = arr[r];
            r++;
        }
        i++;
    }
    
    while (l <= mid) {
        temp[i] = arr[l];
        l++, i++;
    }
    
    while (r <= high) {
        temp[i] = arr[r];
        r++, i++;
    }
    
    i = 0;
    for (int l = low; l <= high; l++) {
		delay(8);//for better visualization
        swapline(gap * l + 1, arr[l],gap * l + 1, temp[i]); // erase prev value update with new one
        arr[l] = temp[i];
        i++;
    }
}

void merge_sort(int l , int h)
{
	if(l < h)
	{
		int mid = l + (h-l)/2;
		merge_sort(l , mid);
		merge_sort(mid+1 , h);
		merge(l , mid , h);
	}
}

int find_pivot_idx(int low,int high)
{
	int pivot_elem = arr[low];
	int i = low , j = high;
	while(i < j)
	{
		while(i <= high && arr[i] <= pivot_elem)i++;
		while(j >= low && arr[j] > pivot_elem)j--;
		if(i < j)
		{
			swap(arr[i],arr[j]);
			delay(100);
			swapline(gap * i + 1 , arr[i] , gap * j + 1 , arr[j]);
		}
	}
	swap(arr[low] , arr[j]);
	delay(100);
	swapline(gap * low + 1 , arr[low] , gap * j + 1 , arr[j]);
	return j;
}

void quick_sort(int l,int h)
{
	if(l < h)
	{
		int pivot_idx = find_pivot_idx( l , h);
		quick_sort(l , pivot_idx - 1);
		quick_sort(pivot_idx + 1 , h);
	}
}

int main() 
{ 
	// Initializing arr 
	for (int i = 1; i <= n; i++) arr.push_back(i); 

	unsigned seed = chrono::system_clock::now().time_since_epoch().count(); 
	shuffle(arr.begin(), arr.end(), default_random_engine(seed)); 
	
	cout<<"arr before sort\n";
	for (int i = 0; i < n; i++) cout << arr[i] << " "; 

	delay(5); 
	int wid1; 

	// window size (gap*size) * (size) 
	wid1 = initwindow(gap * n + 1, size + 1); 
	setcurrentwindow(wid1); 

	// plot i as x-axis and its corresponding value will be the height of line. 
	for (int i = 1; i <= gap * n; i += gap) line(i, size, i, (size - arr[i / gap]));

	delay(5);
	
	// Call sort 
	// bubble_sort(); 
	// selection_sort();
	// insertion_sort();
	merge_sort(0 , n-1);
	// quick_sort(0 , n-1);

	getch();
	closegraph(); 

	return 0; 
} 
