package structures;

public class SetOnArray extends Set{

    public SetOnArray(int size) throws IllegalArgumentException{
        if (size < 2)
            throw new IllegalArgumentException();
        set = new Pair[size];
        this.size = size;
    }

    public boolean exists (String k) {
        Pair tmp = (new Pair(k,0.0));
        for(int i = 0; i < size; i ++){
            if(tmp.equals(set[i]))
                return true;
        }
        return false;
    }

    public Pair search (String k) throws IllegalArgumentException{
        Pair tmp = (new Pair(k,0.0));
        for(int i = 0; i < size; i ++){
            if(tmp.equals(set[i]))
                return set[i];
        }
        throw new IllegalArgumentException("Couldn't find this key: "+k+" !");
    }

    public void insert (Pair p) throws IllegalArgumentException{
        try{
            search(p.key);
            throw new IllegalArgumentException("This key: "+p.key+" already exists!");
        }
        catch(IllegalArgumentException e){
            if (e.getMessage().equals("This key: "+p.key+" already exists!"))
                throw e;
            for(int i = 0; i < size; i ++)
                if(set[i] == null){
                    set[i] = p;
                    return;
                }
            throw new IllegalArgumentException("Not enough space in set");
        }
    }

    public void delete (String k){
        Pair tmp = (new Pair(k,0.0));
        for(int i = 0; i < size; i ++)
                if(tmp.equals(set[i])){
                    set[i] = null;
                    return;
                }

    }

    public double read (String k) throws IllegalArgumentException{
        Pair ans = search(k);
        return ans.get_value();
    }

    public void update (Pair p) throws IllegalArgumentException{
        for(int i = 0; i < size; i++)
            if(p.equals(set[i])){
                set[i] = p;
                return;
            }
        insert(p);
    }

    public void clear(){
        for(int i = 0; i < size; i++)
            set[i] = null;
    }

    public int size(){
        int ans = 0;
        for(int i = 0; i < size; i++)
            if(set[i] != null)
                ans++;
        return ans;
    }

}