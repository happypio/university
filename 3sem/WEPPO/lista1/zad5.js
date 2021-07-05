//Fibonacci iteracyjnie
let k = console.time("iteracyjnie");
function Fib_iter(n)
{
    let a = 0;
    let b = 1;
    for(let i = 2; i < n; i ++)
    {
        let tmp = a;
        a = b;
        b += tmp;
    }
    return b;

}

//Fibonacci rekurencyjnie
function Fib_rec(n)
{
    if(n == 1)
        return 0;
    if (n == 2)
        return 1;
    return Fib_rec(n-1) + Fib_rec(n - 2);
}
//widoczna różnica w czasach między iteracją, a rekursją. Gdy uruchamiam
//kod za pomocą node.js trwa dłużej niż w przypadku chrome. Juz dla n = 40
//widać, który jest szybszy
for(let i = 10; i < 40; i ++)
{
    console.time('ITERACJA');
    console.log(Fib_iter(i), 'dla n = ', i);
    console.timeEnd('ITERACJA');
    console.time('REKURSJA');
    console.log(Fib_rec(i), 'dla n = ', i);
    console.timeEnd('REKURSJA');
}