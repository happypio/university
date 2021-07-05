// dane server_logs z https://github.com/ocatak/apache-http-logs/
var readline = require('readline');
var fs = require('fs');
var file = readline.createInterface({
    input: fs.createReadStream('./server_logs.txt')
});

var ips = {};
file.on('line', function (line) {
    s = line.split(' ')[1];
    //console.log(s);
    if (ips[s] == undefined) {
        ips[s] = 1;
    }
    else {
        ips[s] += 1;
    }
});

file.on('close', function() {
    ans = []
    for(let i in ips) {
        ans.push( {ip : i, value: ips[i]});
        }
    ans.sort(function(a,b) { 
        return b.value - a.value; 
    })
    for(let a in ans.slice(0,3)) {
        console.log("IP: " + ans[a].ip + " logs: " + ans[a].value);
    }
});

console.log(ips); // jeszcze sie nie zaladowaly