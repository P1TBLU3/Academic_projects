
public class BNODE <E> {
	private E info;
	private BTree<E> left;
	private BTree<E> right;
	
	
	public BNODE(E info,  BTree<E> left,BTree<E> right  ) {
		this.info=info;
		this.right=right;
		this.left=left;
	}
	public BNODE() {
		this( null, null, null);
	}
	public BNODE(E info) {
		this( info, null, null);
	}
	public void setRight(BTree<E> right ) {
		this.right=right;
	}
	public void setLeft(BTree<E> left ) {
		this.left=left;
	}
	public BTree<E> getRight() {
		return this.right;
	}
	public BTree<E> getLeft() {
		return this.left;
	}
	
	
	public void setInfo(E info) {
		this.info=info;
	}
	public E getInfo() {
		return this.info;
	}
	public String toString() {
		String a= ""+ info;
		return a;
	}
		

}
