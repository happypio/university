package structures;

public abstract class Set {
    protected Pair[] set;
    protected int size;
    
    /** metoda ma wyszukać parę z zadanym kluczem
    metoda zgłasza wyjątek, gdy nie znajdzie pary o podanym kluczu */
    public abstract Pair search (String k) throws Exception;

    /** metoda ma wstawić do zbioru nową parę
    metoda zgłasza wyjątek, gdy para o podanym kluczu już jest w zbiorze */
    public abstract void insert (Pair p) throws Exception;

    /** metoda ma usunąć ze zbioru parę o zadanym kluczu
    gdy pary o podanym kluczu nie ma w zbiorze metoda nic nie zrobi*/
    public abstract void delete (String k);

    /** metoda ma odszukać parę o zadanym kluczu i zwrócić wartość pozwiązaną
    metoda zgłasza wyjątek, gdy nie znajdzie pary o podanym kluczu */
    public abstract double read (String k) throws Exception;

    /** metoda ma wstawić do zbioru nową albo zaktualizować parę*/
    public abstract void update (Pair p) throws Exception;

    /** metoda ma usunąć wszystkie pary ze zbioru */
    public abstract void clear();

    /** metoda ma podać ile jest wszystkich par w zbiorze */
    public abstract int size();

    public int get_size(){
        return this.size;
    }
}
