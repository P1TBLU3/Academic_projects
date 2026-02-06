public interface BTree<E> {
    public static final int LEFT = 0;
    public static final int RIGHT = 1;

    boolean isEmpty();
    int size();
    int height();

    E getInfo() throws BTreeException;
    BTree<E> getLeft() throws BTreeException;
    BTree<E> getRight() throws BTreeException;

    void insert(BTree<E> tree, int side) throws BTreeException;
    BTree<E> extract(int side) throws BTreeException;

    String toStringInOrder();
    String toStringPreOrder();
    String toStringPostOrder();
    String toString();

    boolean equals(BTree<E> tree);
    boolean find(BTree<E> tree);
}
