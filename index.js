"use strict";

const { busyLoop } = require("./index.node");

const delay = n => new Promise(r => setTimeout(r, n));

async function run() {
    await delay(1000);

    for (let i = 0; i < 10; i++) {
        busyLoop();
    }
}

run();
