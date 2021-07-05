function is_prime(n)
{
    if(n == 2)
        return true;
    
    if(n % 2 == 0)
        return false;

    for(let i = 3; i * i <= n; i += 2)
    {
        if(n % i == 0)
            return false;

    }
    
    return true;
}

primes = [];
for(let i = 2; i < 100000; i ++)
{
    if(is_prime(i))
        primes.push(i);
}

for(let i = 0; i < 20; i++)
{
    console.log(primes[i]);
}
console.log(primes.length);