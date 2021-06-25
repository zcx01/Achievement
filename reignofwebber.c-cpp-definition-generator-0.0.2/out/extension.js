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
// The module 'vscode' contains the VS Code extensibility API
// Import the module and reference it with the alias vscode in your code below
const vscode = require("vscode");
const cppHelper = require("./cppext");
const semantics = require("./semantics");
// this method is called when your extension is activated
// your extension is activated the very first time the command is executed

function createSource(source,scope){
    vscode.window.showInformationMessage("ddddddddssss");
    let editor = vscode.window.activeTextEditor;
    if (!editor) {
        return;
    }
    let document = editor.document;
    for (let line = 0; line < document.lineCount; ++line) {
        let declaration = document.lineAt(line).text;
        if (semantics.isDeclaration(declaration)) {
            let declarationPos = document.offsetAt(new vscode.Position(line, 0));
            let scopes = scope.getScopes(declarationPos);
            source.update(declaration, scopes);
        }
    }
}

function getSource(source,scope){
    let editor = vscode.window.activeTextEditor;
    if (!editor) {
        return;
    }
    let document = editor.document;
    let position = editor.selection.active.line;
    let declaration = document.lineAt(position).text;
    let declarationPos = document.offsetAt(editor.selection.active);
    // TEST
    if (!semantics.isDeclaration(declaration)) {
        return;
    }
    // TEST
    let scopes = scope.getScopes(declarationPos);
    source.update(declaration, scopes);
}

function activate(context) {
    let generateSouce = vscode.commands.registerCommand('Cppext.generateSource', () => __awaiter(this, void 0, void 0, function* () {
        let editor = vscode.window.activeTextEditor;
        if (!editor) {
            return;
        }
        let document = editor.document;
        if (document.languageId !== 'cpp' || !cppHelper.isHeaderFile(document.fileName)) {
            return;
        }
        let scope = semantics.Scope.createScope(document.getText());
        let source = new cppHelper.SourceFile(document.fileName, scope.isEmpty() ? '.c' : '.cpp');
        source.writeSourceFile(createSource,source,scope);
    }));
    let gotoDefinition = vscode.commands.registerCommand('Cppext.gotodefinition', () => __awaiter(this, void 0, void 0, function* () {
        let editor = vscode.window.activeTextEditor;
        if (!editor) {
            return;
        }
        // if has document
        let document = editor.document;
        // if c/c++ header file
        if (document.languageId !== "cpp" || !cppHelper.isHeaderFile(document.fileName)) {
            return;
        }
        let scope = semantics.Scope.createScope(document.getText());
        let source = new cppHelper.SourceFile(document.fileName, scope.isEmpty() ? '.c' : '.cpp');
        source.writeSourceFile(getSource,source,scope);
    }));
    context.subscriptions.push(generateSouce);
    context.subscriptions.push(gotoDefinition);
}
exports.activate = activate;
// this method is called when your extension is deactivated
function deactivate() { }
exports.deactivate = deactivate;
//# sourceMappingURL=extension.js.map