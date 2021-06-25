"use strict";
Object.defineProperty(exports, "__esModule", { value: true });
const fs = require("fs");
function lines(file) {
    let content = fs.readFileSync(file, 'utf-8');
    return content.split(/\r\n|\r|\n/).length;
}
exports.lines = lines;
function linesOfContent(content) {
    return content.split(/\r\n|\r|\n/).length;
}
exports.linesOfContent = linesOfContent;
//# sourceMappingURL=tools.js.map