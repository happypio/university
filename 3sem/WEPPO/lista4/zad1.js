class Tree { 
    constructor(val, left, right) { 
        this.left = left; 
        this.right = right; 
        this.val = val; 
    } 
    [Symbol.iterator] = function* () { 
        var queue = [];
        queue.push(this);
        while (queue.length > 0) {
            var item = queue[0];
            queue = queue.slice(1);
            //var item = queue.pop(); teraz przechodzimy w glab (wybierajac prawy wezel) a nie w szerz
            if (item.left) queue.push(item.left);
            if (item.right) queue.push (item.right);
            yield item.val;
        }
    } 
} 

var root = new Tree(1, 
    new Tree(2, 
        new Tree(3), 
        new Tree(5)), 
    new Tree(4,
        new Tree(6),
        new Tree(7)
        )
    ); 

//      1
//     / \
//    2   4
//   /\   /\
//  3  5  6 7

for (var e of root) { 
    console.log(e); 
}

// 1 2 3 4