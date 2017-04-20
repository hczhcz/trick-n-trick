'use strict';

const callcc_yin = (func) => func((yin) => {
    process.stdout.write('@');
    callcc_yang((ret) => ret(ret), yin);
});

const callcc_yang = (func, yin) => func((yang) => {
    process.stdout.write('*');
    yin(yang);
});

callcc_yin((ret) => ret(ret));
