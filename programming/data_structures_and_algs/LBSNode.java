public class LBSNode<E> {
	private E info;
	private Comparable key;
	private BSTree<E> right;
	private BSTree<E> left;
	public LBSNode(Comparable key, E info, BSTree<E> left, BSTree<E> right) {
		this.key=key;
		this.info=info;
		this.left=left;
		this.right=right;
	}
	public BSTree<E> getLeft(){return this.left;}
	public void setLeft(BSTree<E> left){this.left=left;}
	public BSTree<E> getRight(){return this.right;}
	public void setRight(BSTree<E> right){this.right=right;}
	public E getInfo(){return this.info;}
	public void setInfo(E info){this.info=info;}
	public Comparable getKey(){return this.key;}
	public void setKey(Comparable key){this.key=key;}
	public String toString() {
		if(info != null) {
			return info.toString();
		} else {
			return "";
		}
	}
}
