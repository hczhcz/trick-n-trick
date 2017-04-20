'use strict';

const callcc_yin = (func, y, t) => func((ret) => {
    yin = ret;
    yang = y;
    task = t.slice(0);
});

const callcc_yang = (func, y, t) => func((ret) => {
    yin = y;
    yang = ret;
    task = t.slice(0);
});

let yin, yang;
let task = [
    () => callcc_yin((ret) => ret(ret), yang, task),
    () => process.stdout.write('@'),
    () => callcc_yang((ret) => ret(ret), yin, task),
    () => process.stdout.write('*'),
    () => yin(yang),
];

while (true) {
    task.shift()();
}
