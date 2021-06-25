"use strict";
var __awaiter = (this && this.__awaiter) || function (thisArg, _arguments, P, generator) {
    return new (P || (P = Promise))(function (resolve, reject) {
        function fulfilled(value) { try { step(generator.next(value)); } catch (e) { reject(e); } }
        function rejected(value) { try { step(generator["throw"](value)); } catch (e) { reject(e); } }
        function step(result) { result.done ? resolve(result.value) : new P(function (resolve) { resolve(result.value); }).then(fulfilled, rejected); }
        step((generator = generator.apply(thisArg, _arguments || [])).next());
    });
};
Object.defineProperty(exports, "__esModule", { value: true });
const vscode = require("vscode");
const fs = require("fs");
const path = require("path");
const semantics = require("./semantics");
const { dir } = require("console");

/**
 * determine if the file is a header file.
 * @param fileName
  */
function isHeaderFile(fileName) {
    let dotPos = fileName.lastIndexOf('.');
    let ext = fileName.substr(dotPos);
    if (ext.includes('h')) {
        return true;
    }
    return false;
}
exports.isHeaderFile = isHeaderFile;
function getDeclarationPos(content, declaration) {
    return content.indexOf(declaration);
}

exports.getDeclarationPos = getDeclarationPos;


class SourceFile {
    constructor(headerFile, ext) {
        let fileName = path.basename(headerFile);
        this.dirName = path.dirname(headerFile);
        this._srcName = fileName.split('.').slice(0, 1).join('.') + ext;
        this._path = undefined;
        this._ext = ext;
        this._headerFile = headerFile;
    }

    async writeSourceFile(callfun,par1,par2) {
        this._path = await this.sreachSourceFile(this._srcName);
        if(this._path === undefined){
            await this.createSoureFile();
        }
        callfun(par1,par2);
    }

    async sreachSourceFile(content){
        const token = new vscode.CancellationTokenSource();
        const time = setTimeout(() => {
            token.cancel();
        }, 2000);
        let resources =await vscode.workspace.findFiles('**/' + content , undefined, 1, token.token);
        clearTimeout(time);
        return resources.length > 0 ? resources[0].path : undefined;
    }
    

    async createSoureFile(){
        const uri = vscode.Uri.file(path.dirname(this._headerFile));
        let dirFiles =await vscode.workspace.fs.readDirectory(uri);
        let nextPath;
        for( var i =0; i < dirFiles.length; i++){
            if(dirFiles[i][1] === vscode.FileType.File){
                let nextFileName = dirFiles[i][0];
                let srcName = nextFileName.split('.').slice(0, 1).join('.') + this._ext;
                nextPath = await this.sreachSourceFile(srcName);
                if(nextPath === undefined){
                    continue;
                }
                break;
            }
        }
        if(nextPath === undefined){
            nextPath = this._headerFile;
        }
        this._path = path.join(path.dirname(nextPath), this._srcName);
        fs.writeFileSync(this._path, `#include "${path.basename(this._headerFile)}"\n\n`, 'utf-8');
    }
    /**
     * show c/cpp file and call updateDefinition
     * @param declaration declaration snippet
     * @param scopes for cpp, definition prefix
     */
    update(declaration, scopes) {
        return __awaiter(this, void 0, void 0, function* () {
            this._doc = yield vscode.workspace.openTextDocument(vscode.Uri.file(this._path));
            this._editor = yield vscode.window.showTextDocument(this._doc);
            yield this._updateDefinition(declaration, scopes);
        });
    }
    /**
     * // TODO c++ overload
     * find if exist a definition with same name
     * @param declaration declaration snippet
     * @param scopes for cpp, definition prefix
     */
    _getDefinitionLine(declaration, scopes) {
        let definition = semantics.getDefinition(declaration, scopes);
        let identifier = definition.getIdentifier();
        // exactly identifier
        let regexIdentifier = new RegExp('\(^|\\s+\)' + identifier + '\\s*\\(');
        let line = 0;
        let text = '';
        while (line < this._doc.lineCount) {
            text = this._doc.lineAt(line).text;
            if (regexIdentifier.exec(text)) {
                break;
            }
            ++line;
        }
        // current definition not exist
        if (line === this._doc.lineCount) {
            return -1;
        }
        if (/.+\(.*\).*\{/.exec(text)) {
            return line;
        }
        else {
            return -1;
        }
    }
    /**
     * update definition
     * @param declaration declaration snippet
     * @param scopes for cpp, definition prefix
     */
    _updateDefinition(declaration, scopes) {
        return __awaiter(this, void 0, void 0, function* () {
            let line = this._getDefinitionLine(declaration, scopes);
            let definition = semantics.getDefinition(declaration, scopes);
            if (definition.isValid && this._editor) {
                if (line === -1) {
                    let endLine = this._doc.lineCount - 1;
                    let endCh = this._doc.lineAt(endLine).text.length;
                    yield this._editor.edit(editBuilder => {
                        editBuilder.insert(new vscode.Position(endLine, endCh), definition.toString());
                    });
                    endLine = this._doc.lineCount - 1;
                    let pos = new vscode.Position(endLine - 2, 0);
                    this._editor.selection = new vscode.Selection(pos, pos);
                    vscode.commands.executeCommand('revealLine', {
                        lineNumber: pos.line,
                        at: 'center'
                    });
                }
                else {
                    let lineEnd = this._doc.lineAt(line).text.length;
                    let startPos = new vscode.Position(line, 0);
                    let endPos = new vscode.Position(line, lineEnd);
                    yield this._editor.edit(editBuilder => {
                        editBuilder.replace(new vscode.Range(startPos, endPos), definition.toString(true));
                    });
                    let pos = new vscode.Position(line + 1, 0);
                    this._editor.selection = new vscode.Selection(pos, pos);
                    vscode.commands.executeCommand('revealLine', {
                        lineNumber: pos.line,
                        at: 'center'
                    });
                }
            }
        });
    }
}
exports.SourceFile = SourceFile;
//# sourceMappingURL=cppext.js.map