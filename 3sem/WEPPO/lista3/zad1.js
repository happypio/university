//defining an object
var p = {
    n :  null,

    f : function(x) {
        return Math.pow(this.n ,x);
    },

    get nnn() {
        return this.n;
        //return p.n;
    },

    set nnn(x) {
        p.n = x;
    }

};

p.nnn = 4;
p.nnn = p.f(p.nnn);
console.log(p.nnn);

//adding properties and methods

// alternatively: p['q'] = null;
Object.defineProperty(p , 'q' , {
    value : 2,
    enumerable: true,
    writable : true
});
/* alternatively: p.g = function(x) {
    return Math.pow(this.q , x);
};*/

Object.defineProperty(p , 'g' , {
    value : function(x) {
        return Math.pow(this.q , x);
    },
    enumerable: true 
});


Object.defineProperty(p , 'qqq' , {
    get : function() {
        return this.q;
    },
    set : function(x) {
        p.q = x;
    },
    enumerable: true
});

p.qqq = 3;
p.qqq = p.g(p.qqq);
console.log(p.qqq);

console.log("POLE, METODA, WLASCIWOSC moze byc dodane przez Object.defineProperty");
console.log("WLASCIWOSC z akcesorami get/set musi byc dodana przez Object.defineProperty");

//console.log(p)



