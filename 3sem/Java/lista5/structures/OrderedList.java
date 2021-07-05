package structures;
import java.util.Iterator;
public class OrderedList <T extends Comparable <T>> implements OrderedSequence<T>, Iterable<T> {
    
    private class Node <K extends Comparable<K>> {
        private Node<K> next;
        private K data;
        public Node(K e) {
            this.data = e;
        }
        public Node <K> get_next() {
            return this.next;
        }
        public void set_next(Node <K> next) {
            this.next = next;
        }
        public K get_data() {
            return this.data;
        }
    }
    private Node<T> start;
    private int size;

    public OrderedList(){
        this.size = 0;
    }

    @Override
    public void insert(T e1) throws NullPointerException {
        if (e1 == null) {
            throw new NullPointerException();
        }
        if (size == 0) {
            this.start = new Node<T>(e1);
            size += 1;
            return;
        }
        Node<T> act = start;
        if (e1.compareTo(act.get_data() ) < 0) {
            this.start = new Node<T>(e1);
            start.set_next(act);
            size += 1;
            return;
        }
        Node<T> bef = start;
        while (act != null) {
            if (e1.compareTo(act.get_data() ) < 0) {
                Node<T> new_node = new Node<T>(e1);
                bef.set_next(new_node);
                new_node.set_next(act);
                size += 1;
                return;
            }
            bef = act;
            act = act.get_next();
        }
        bef.set_next(new Node<T>(e1));
        size += 1;

    }

    @Override
    public void remove(T e1) throws NullPointerException {
        if (e1 == null) {
            throw new NullPointerException();
        }
        if (size == 0)
            return;
        Node<T> act = start;
        if(e1.compareTo(act.get_data()) == 0) {
            start = start.get_next();
            size -= 1; 
            return;
        }
        Node<T> bef = start;
        while(act != null) {
            if (e1.compareTo(act.get_data() ) == 0) {
                bef.set_next(act.get_next());
                size -= 1;
                return;
            }
            bef = act;
            act = act.get_next();
        }
    }

    @Override
    public T min() throws IllegalAccessException {
        if (size == 0) {
            throw new IllegalAccessException("Sequence is empty!");
        }
        T mini = start.get_data();
        Node<T> act = start;
        while(act != null) {
            if (mini.compareTo(act.get_data()) > 0)
                mini = act.get_data();
            act = act.get_next();
        }
        return mini;
    }

    @Override
    public T max() throws IllegalAccessException {
        if (size == 0) {
            throw new IllegalAccessException("Sequence is empty!");
        }
        T maxi = start.get_data();
        Node<T> act = start;
        while(act != null) {
            if (maxi.compareTo(act.get_data()) < 0)
                maxi = act.get_data();
            act = act.get_next();
        }
        return maxi;
    }

    @Override
    public T at(int pos) throws IllegalArgumentException {
        if (pos >= size) {
            throw new IllegalArgumentException("To small sequence!");
        }
        int act = 0;
        Node<T> result = start;
        while(act != pos) {
            result = result.get_next();
            act += 1;
        }
        return result.get_data();
    }

    @Override
    public boolean search(T e1) throws NullPointerException {
        if (e1 == null) {
            throw new NullPointerException();
        }
        Node<T> act = start;
        while(act != null) {
            if (e1.compareTo(act.get_data()) == 0)
                return true;
            act = act.get_next();
        }
        return false;
    }

    @Override
    public int index(T e1) throws IllegalArgumentException {
        int res = 0;
        Node<T> act = start;
        while(act != null) {
            if (e1.compareTo(act.get_data()) == 0)
                return res;
            act = act.get_next();
            res += 1;
        }
        throw new IllegalArgumentException("There is no such element!");
    }


    @Override
    public String toString () { 
        String res = "[";
        Node<T> act = start;
        while(act != null && act.get_next() != null) {
            res += String.valueOf(act.get_data()) + ", ";
            act = act.get_next();
        }
        if (act != null)
            res += String.valueOf(act.get_data());
        return res + "]" + " size: " + String.valueOf(this.size);
    }

    private Node<T> get_start() {
        return this.start;
    }

    private class SeqIterator implements Iterator<T> {
        private OrderedList<T> list;
        private Node<T> act;
        public SeqIterator (OrderedList<T> list) throws IllegalArgumentException {
            this.list = list;
            act = list.get_start();
            if (act == null)
                throw new IllegalArgumentException("Empty sequence");
            

        }
        public boolean hasNext() {
            if(act == null)
                return false;
            return true;
        }

        public T next() {
            T res = act.get_data();
            act = act.get_next();
            return res;
        }
        public void remove() {
            list.remove(act.get_data());
        }
    }

    @Override
    public Iterator<T> iterator() {
        return new SeqIterator(this);
    }
}
