
function good_number(x)
{
    function get_numbers(x)
    {
        res = [];
        while(x > 0)
        {
            num = x % 10;
            x = Math.floor(x / 10);
            res.push(num);

        }
        return res;
    }

    numbers = get_numbers(x);
    sum = numbers.reduce(function(a, b) {return a + b; });

    if(x % sum != 0)
        return false;
    for(let i = 0; i < numbers.length; i++)
    {
        if(numbers[i] == 0 || x % numbers[i] != 0)
            return false;
    }

    return true;
}
ans = [];
for(let i = 1; i <= 100000 ; i ++)
{
    if(good_number(i))
        ans.push(i);
}
for(let i = 0; i <= 10; i ++)
{
    console.log(ans[i]);
}
console.log(ans.length);
