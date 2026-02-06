public class LBNode<E> {
	private E info;
	private BTree<E> left;
	private BTree<E> right;

	public LBNode(E info,BTree<E> left, BTree<E> right) {
		this.info=info;
		this.right=(right==null)? new LBTree<E>() : right;
		this.left=(left==null)? new LBTree<E>() : left;
	}
	public LBNode(E info) {
		this(info,new LBTree<E>(),new LBTree<E>());
	}	
	public E getInfo() {
		return this.info;
	}
	public void setInfo(E info) {
		this.info=info;
	}
	public BTree<E> getRight() {
		return this.right;
	}	
	public void setRight(BTree<E> tree) {
		this.right=(tree==null)? new LBTree<E>() : tree;
	}
	public BTree<E> getLeft() {
		return this.left;
	}
	public void setLeft(BTree<E> tree) {
		this.left=(tree==null)? new LBTree<E>() : tree;
	}
}
