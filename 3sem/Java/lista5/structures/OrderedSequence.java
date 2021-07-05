package structures;

public interface OrderedSequence<T extends Comparable<T>> {
    public void insert(T e1) throws Exception;
    public void remove(T e1) throws Exception;
    public T min() throws Exception;
    public T max() throws Exception;
    public T at(int pos) throws Exception;
    public boolean search(T e1) throws Exception;
    public int index(T e1) throws Exception;
}