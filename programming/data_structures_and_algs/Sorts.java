public class Sorts {
	public static <T extends Comparable<T>> void bubbleSort(T[] a) {
		if(a==null) {return;}
		for(int i=0;i<a.length-1;i++) {
			boolean swapped=false;
			for(int j=0;j<a.length-1-i;j++) {
				if(a[j].compareTo(a[j+1])>0) {
					swap(a,j,j+1);
					swapped=true;
				}
			}
			if(!swapped) {return;}
		}
	}
	public static <T extends Comparable<T>> void insertionSort(T[] a) {
		if(a==null) {return;}
		for(int i=1;i<a.length;i++) {
			T x=a[i];
			int j=i-1;
			while(j>=0 && a[j].compareTo(x)>0) {
				a[j+1]=a[j];
				j--;
			}
			a[j+1]=x;
		}
	}
	public static <T extends Comparable<T>> void selectionSort(T[] a) {
		if(a==null) {return;}
		for(int i=0;i<a.length-1;i++) {
			int m=i;
			for(int j=i+1;j<a.length;j++) {
				if(a[j].compareTo(a[m])<0) {
					m=j;
				}
			}
			if(m!=i) {
				swap(a,i,m);
			}
		}
	}
	public static <T extends Comparable<T>> void heapSort(T[] a) {
		if(a==null) {return;}
		int n=a.length;
		for(int i=n/2-1;i>=0;i--) {
			heapify(a,n,i);
		}
		for(int i=n-1;i>0;i--) {
			swap(a,0,i);
			heapify(a,i,0);
		}
	}
	private static <T extends Comparable<T>> void heapify(T[] a, int n, int i) {
		int largest=i;
		int l=2*i+1;
		int r=2*i+2;
		if(l<n && a[l].compareTo(a[largest])>0) {largest=l;}
		if(r<n && a[r].compareTo(a[largest])>0) {largest=r;}
		if(largest!=i) {
			swap(a,i,largest);
			heapify(a,n,largest);
		}
	}
	public static <T extends Comparable<T>> void quickSort(T[] a) {
		if(a==null) {return;}
		quickSort(a,0,a.length-1);
	}
	private static <T extends Comparable<T>> void quickSort(T[] a, int lo, int hi) {
		if(lo>=hi) {return;}
		int p=partition(a,lo,hi);
		quickSort(a,lo,p-1);
		quickSort(a,p+1,hi);
	}
	private static <T extends Comparable<T>> int partition(T[] a, int lo, int hi) {
		T pivot=a[hi];
		int i=lo;
		for(int j=lo;j<hi;j++) {
			if(a[j].compareTo(pivot)<=0) {
				swap(a,i,j);
				i++;
			}
		}
		swap(a,i,hi);
		return i;
	}
	private static <T> void swap(T[] a, int i, int j) {
		T tmp=a[i];
		a[i]=a[j];
		a[j]=tmp;
	}
}
