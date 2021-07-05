package structures;

public class SetOnDynamicArray extends SetOnArray {
    public SetOnDynamicArray(){
        super(2);
    }

    public void change_size(int s)
    {
        Pair[] new_set = new Pair[s];
        int j = 0;
        for(int i = 0 ; i < size; i++)
            if(set[i] != null){
                new_set[j] = set[i];
                j++;
            }
        this.set = new_set;
        this.size = s;

    }
    @Override
    public void insert(Pair p) throws IllegalArgumentException
    {
        try{
            search(p.key);
            throw new IllegalArgumentException("This key: "+p.key+" already exists!");
        }
        catch(IllegalArgumentException e){
            if (e.getMessage().equals("This key: "+p.key+" already exists!"))
                throw e;
            if(this.size() == this.size)
                change_size(2 * this.size);
            for(int i = 0; i < size; i ++)
                if(set[i] == null){
                    set[i] = p;
                    return;
                }
        }
    }
    @Override
    public void delete (String k){
        super.delete(k);
        if(this.size() < this.size / 4.0)
            if(this.size > 2)
                change_size(this.size / 2);
    }

    @Override
    public void clear(){
        super.clear();
        if(this.size() < this.size / 4.0)
            if(this.size > 2)
                change_size(this.size / 2);
    }
}
