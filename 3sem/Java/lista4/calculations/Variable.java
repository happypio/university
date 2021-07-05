package calculations;
import structures.*;

public class Variable extends Expression{
    private static SetOnDynamicArray cache;
    static {
        cache = new SetOnDynamicArray();
    }

    public static void update (String key, int  value) {
        cache.update(new Pair(key, value));
    }

    public static void delete(String key) {
        cache.delete(key);
    }

    public static boolean exists(String key) {
        return cache.exists(key);
    }

    public static Pair search(String key) {
        return cache.search(key);
    }
    
    private final String name;

    public Variable(String name) {
        this.name = name;
    }

    @Override
    public int calculate() {
        return (int) cache.read(name);
    }
    
    @Override
    public String toString() {
        return name;
    }
}

