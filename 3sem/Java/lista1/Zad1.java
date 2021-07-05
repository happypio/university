class Prime
{
    public static Boolean is_prime(int n)
    {
        if(n == 1)
            return false;
        if(n == 2)
            return true;
        if(n % 2 == 0)
            return false;
        for(int i = 3; i * i <= n; i += 2)
        {
            if(n % i == 0)
                return false;
        }
        return true;
    }
}

class Spirala
{
    int n;
    int[][] tab;
    public Spirala(int n)
    {
        this.n = n;
        tab = new int[n][n];
        fill();
        check_primes();
        draw();
    }

    void draw()
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(tab[i][j] == 0)
                    System.out.print("*");
                else
                    System.out.print(" ");
            }
            System.out.println();
        }
    }

    void check_primes()
    {
        for(int i = 0; i < n; i++)
        {
            for(int j = 0; j < n; j++)
            {
                if(Prime.is_prime(tab[i][j]))
                    tab[i][j] = 0;
            }
        }
    }
    void fill()
    {
        int act_x,act_y;
        if(n % 2 != 0)
        {
            act_x = n / 2;
            act_y = n / 2;
        }
        else
        {
            act_x = n / 2 - 1;
            act_y = n / 2;
        }
        int count = 1;
        int step = 1;
        int act_step = 1;
        int x_sign = -1;
        int y_sign = 1;
        tab[act_y][act_x] = 1;
        for(int i = 1; i < n * n; i ++)
        {
            if(count == 1)
            {
                if(act_step == step)
                    x_sign *= -1;
                act_x += 1 * x_sign;
            }
            if(count == 2)
            {
                if(act_step == step)
                    y_sign *= -1;
                act_y += 1 * y_sign;
            }
            tab[act_y][act_x] = i + 1;
            act_step -= 1;

            if(act_step == 0)
            {
                if(count == 2)
                    step += 1;
                act_step = step;
                count = count % 2 + 1;
            }
        }
    }

}

public class Zad1
{
    public static void main (String[] args)
    {
        String n_string = args[0];
        try{
            int n = Integer.valueOf(n_string);
            if(n < 2 || n > 200)
                throw new IllegalArgumentException("parametr spoza zakresu 2...200");
            Spirala spirala = new Spirala(n);
            
        } catch (NumberFormatException e)
        {
            System.err.println("Błędny argument " + e.getMessage());
        }   
    }
}