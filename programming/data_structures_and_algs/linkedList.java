public class linkedList <E>{
	private Node<E> first;

	public linkedList(Node<E> first) {
		this.first=first;
	}
	public linkedList() {
		this(null);
	}
	public boolean isEmpty() {
		return first==null;
	}
	public void insert(E info) {
		Node<E> tmp= new Node<E>(info);
		if(isEmpty()) {
			first= tmp;
		}else {
			tmp.setNext(first);
			first=tmp;
		}
	}
	public void insert(E info, Node<E> previous) {
		if(isEmpty()||previous==null) {
			insert(info);
		}else {
			Node<E> tmp = new Node<E>(info, previous.getNext());
			previous.setNext(tmp);
		}
	}
	public E extract() {
		if(isEmpty()) {
			return null;
		}else {
			E result = first.getInfo();
			first=first.getNext();
			return result;
		}
	}
	public E extract(Node<E> previous) {
		if(isEmpty()||previous==null||previous.getNext()==null) {
			return null;
		}else {
			E result= previous.getNext().getInfo();
			previous.setNext(previous.getNext().getNext());
			return result;
		}
	}
	public int size() {
		int result=0;
		Node<E> tmp=first;
		while(tmp!=null) {
			result++;
			tmp=tmp.getNext();
		}
		return result;
	}
	public String toString() {
		if(isEmpty()) {
			return "";
		}else{
			Node<E> tmp= first;
			String result=""+ tmp.getInfo();
			while(tmp.getNext()!=null) {
				tmp=tmp.getNext();
				result= result+ " -> "+tmp.getInfo();
			}
			return result;
		}
	}
	public void print() {
		System.out.println(toString());
	}
	public Node<E> searchNode(E info){
		Node<E> tmp=first;
		while(tmp!=null) {
			if(info==null) {
				if(tmp.getInfo()==null) {return tmp;}
			}else if(info.equals(tmp.getInfo())) {
				return tmp;
			}
			tmp=tmp.getNext();
		}
		return null;
	}
	public Node<E> searchNode(int pos){
		if(pos<0) {return null;}
		Node<E> tmp=first;
		int i=0;
		while(tmp!=null && i<pos) {
			tmp=tmp.getNext();
			i++;
		}
		return tmp;
	}
	public Node <E> searchLastNode(){
		Node<E>  tmp= first;
		if(tmp==null) {return null;}
		while(tmp.getNext()!=null) {
			tmp=tmp.getNext();
		}
		return tmp;
	}
	public int search(E info) {
		int result=0;
		Node <E> tmp= first;
		while(tmp!=null) {
			if(info==null) {
				if(tmp.getInfo()==null) {return result;}
			}else if(info.equals(tmp.getInfo())) {
				return result;
			}
			tmp=tmp.getNext();
			result++;				
		}
		return -1;
	}
	public void insert(E info, int pos) {
		if(pos<=0) {
			insert(info);
		}else {
			Node<E> tmp= searchNode(pos-1);
			if(tmp==null) {
				insertLast(info);
			}else {
				insert(info, tmp);
			}
		}
	}
	public E extract(int pos) {
		if(pos<0||isEmpty()) {
			return null;
		}
		if(pos==0) {
			return extract();
		}
		Node<E> tmp= searchNode(pos-1);
		return extract(tmp);
	}
	public void insertLast(E info){
		Node<E> tmp= searchLastNode();
		if(tmp==null) {
			insert(info);
		}else {
			insert(info,tmp);
		}
	}
	public E removeLast() {
		int n=size();
		if(n==0) {
			return null;
		}else if(n==1) {
			return extract();
		}else {
			Node<E> tmp= searchNode(n-2);
			return extract(tmp);
		}
	}
	public void print(int pos) {
		Node <E> tmp= searchNode(pos);
		if(tmp!=null) {
			linkedList<E> aux=new linkedList<E>(tmp);
			System.out.println(aux.toString());
		}
	}
}
