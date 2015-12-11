.pragma library

function calcSize(relation, componenentSize) {
    var standart = {};

    //standart.width = 640;
    //standart.height = 480;

    return Math.round(rootWindow[relation] * (componenentSize / 100));
}
