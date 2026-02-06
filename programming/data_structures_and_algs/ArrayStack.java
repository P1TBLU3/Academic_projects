public class ArrayStack<E> implements Stack<E> {
	private E[] info;
	private int capacity;
	private int top;
	 public ArrayStack(int capacity) {
		 this.capacity=capacity;
		 info= (E[])  new Object[capacity];
		 this.top=-1;
	 }
	public boolean isEmpty() {
		return top<0;
	}
	public int size() {
		return top+1;
	}
	public void push(E info) {
		if(size()==capacity) {
			System.out.println("no");
		}else {
			this.info[++top]=info;
		}
	}
	public E pop() {
		if(isEmpty()) {
			System.out.println("nope");
			return null;
		}else {
			E result=this.info[top--];
			return result;
		}
		}
	
	public E top() {
		if(isEmpty()) {
			System.out.println("nope");
			return null;
		}else {
			return this.info[top];
		}
}
}
