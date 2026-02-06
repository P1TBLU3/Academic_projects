public class BSearch {
public int binSearch(String[] a, String x) {
	int first=0;
	int half;
	int last=a.length-1;
	while(first<=last) {
		half=(first+last)/2;
		if(a[half].compareTo(x)==0) {
			return half;
		}else if(a[half].compareTo(x)<0) {
			first=half+1;
		}else if(a[half].compareTo(x)>0) {
			last=half-1;
		}	
	}
	
	
	
	return -1;
}
}
