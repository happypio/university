const readline = require('readline');
let rl = readline.createInterface({
  input: process.stdin,
  output: process.stdout,
});

function f (name) {
    console.log(`Witaj ${name} !`);
    rl.close();
}

rl.question('Whats your name?\n', f);