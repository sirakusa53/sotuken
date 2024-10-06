package ejsc;

import java.util.ArrayList;

import javax.json.JsonArray;
import javax.json.JsonNumber;
import javax.json.JsonObject;
import javax.json.JsonString;
import javax.json.JsonValue;

import ejsc.ast_node.Node;
import ejsc.ast_node.Node.ILiteral.LiteralType;

public class BabelESTreeConverter {
    boolean logging = false;
    
    public BabelESTreeConverter(boolean logging) {
        this.logging = logging;
    }
    
    public Node convert(JsonObject json) {
        assertJsonNodeType("File", json);
        return convertProgram(json.getJsonObject("program"));
    }
    
    private void error(String msg, JsonObject json) {
        throw new Error(msg + json.toString());
    }
    
    private void assertJsonNodeType(String type, JsonObject json) {
        if (!json.getString("type").equals(type))
            error("Expected type is "+type, json);
    }
    
    private Node convertProgram(JsonObject json) {
        assertJsonNodeType("Program", json);
        ArrayList<Node.IStatement> body = jsonGetStatementArray(json, "body");
        ejsc.ast_node.Program prog = new ejsc.ast_node.Program(body, logging);
        fillNode(prog, json);
        return prog;
    }
    
    private Node.ILiteral convertLiteral(JsonObject json) {
        return convertLiteral(json, false);
    }
    
    private Node.ILiteral convertLiteral(JsonObject json, boolean maybe) {
        String type = json.getString("type");
        Node.ILiteral literal;

        switch (type) {
        case "RegExpLiteral": {
            String pattern = json.getString("pattern");
            String flags = json.getString("flags");
            literal = new ejsc.ast_node.Literal(pattern, flags);
            break;
        }
        
        case "NullLiteral":
            literal = new ejsc.ast_node.Literal();
            break;
        
        case "StringLiteral":
            return convertStringLiteral(json);
        
        case "BooleanLiteral": {
            boolean value = json.getBoolean("value");
            literal = new ejsc.ast_node.Literal(value);
            break;
        }
        
        case "NumericLiteral": {
            JsonNumber number = json.getJsonNumber("value");
            literal = new ejsc.ast_node.Literal(number.doubleValue(), number.isIntegral());
            break;
        }
        
        case "BigIntLiteral":
            error("BigIntLiteral is not supported", json);
            return null;
        
        case "DecimalLiteral":
            error("DecimalLiteral is not supported", json);
            return null;
        
        default:
            if (!maybe)
                error("unknown node type", json);
            return null;
        }
        fillLiteral(literal, json);
        return literal;
    }
    
    private Node.ILiteral convertStringLiteral(JsonObject json) {
        assertJsonNodeType("StringLiteral", json);
        String value = json.getString("value");
        ejsc.ast_node.Literal literal = new ejsc.ast_node.Literal(value, LiteralType.STRING);
        fillLiteral(literal, json);
        return literal;
    }
    
    private Node.IStatement convertStmt(JsonObject json) {
        String type = json.getString("type");
        Node.IStatement stmt;
        switch (type) {
        case "ExpressionStatement": {
            Node.IExpression expr = jsonGetExpression(json, "expression");
            stmt = new ejsc.ast_node.ExpressionStatement(expr);
            break;
        }
        
        case "BlockStatement":
            return convertBlockStatement(json);
        
        case "EmptyStatement":
            stmt = new ejsc.ast_node.EmptyStatement();
            break;
        
        case "DebuggerStatement": {
            error("DebuggerStatement is not supported", json);
            return null;
        }
        
        case "WithStatement": {
            Node.IExpression object = jsonGetExpression(json, "object");
            Node.IStatement body = jsonGetStatement(json, "body");
            stmt = new ejsc.ast_node.WithStatement(object, body);
            break;
        }
        
        // Control flow
        case "ReturnStatement": {
            Node.IExpression argument = jsonGetExpression(json, "argument", true);
            stmt = new ejsc.ast_node.ReturnStatement(argument);
            break;
        }
        
        case "LabeledStatement": {
            Node.IIdentifier label = jsonGetIdentifier(json, "label");
            Node.IStatement body = jsonGetStatement(json, "body");
            switch (body.getTypeId()) {
            case Node.WHILE_STMT:
                ((ejsc.ast_node.WhileStatement) body).setLabel(label.getName());
                break;
            case Node.DO_WHILE_STMT:
                ((ejsc.ast_node.DoWhileStatement) body).setLabel(label.getName());
                break;
            case Node.FOR_STMT:
                ((ejsc.ast_node.ForStatement) body).setLabel(label.getName());
                break;
            case Node.FOR_IN_STMT:
                ((ejsc.ast_node.ForInStatement) body).setLabel(label.getName());
                break;
            }
            stmt = new ejsc.ast_node.LabeledStatement(label, body);
            break;
        }
 
        case "BreakStatement": {
            Node.IIdentifier label = jsonGetIdentifier(json, "label", true);
            stmt = new ejsc.ast_node.BreakStatement(label);
            break;
        }
        
        case "ContinueStatement": {
            Node.IIdentifier label = jsonGetIdentifier(json, "label", true);
            stmt = new ejsc.ast_node.ContinueStatement(label);
            break;
        }

        // Choice
            
        case "IfStatement": {
            Node.IExpression test = jsonGetExpression(json, "test");
            Node.IStatement consequent = jsonGetStatement(json, "consequent");
            Node.IStatement alternate = jsonGetStatement(json, "alternate", true);
            stmt = new ejsc.ast_node.IfStatement(test, consequent, alternate);
            break;
        }
            
        case "SwitchStatement": {
            ArrayList<Node.ISwitchCase> cases = jsonGetSwitchCase(json, "cases");
            Node.IExpression discriminant = jsonGetExpression(json, "discriminant");
            stmt = new ejsc.ast_node.SwitchStatement(discriminant, cases);
            break;
        }
            
        // Exceptions
            
        case "ThrowStatement": {
            Node.IExpression argument = jsonGetExpression(json, "argument");
            stmt = new ejsc.ast_node.ThrowStatement(argument);
            break;
        }
            
        case "TryStatement": {
            Node.IBlockStatement block = jsonGetBlockStatement(json, "block");
            Node.ICatchClause handler = jsonGetCatchClause(json, "handler", true);
            Node.IBlockStatement finalizer = jsonGetBlockStatement(json, "finalizer", true);
            stmt = new ejsc.ast_node.TryStatement(block, handler, finalizer);
            break;
        }
            
        // Loops
    
        case "WhileStatement": {
            Node.IExpression test = jsonGetExpression(json, "test");
            Node.IStatement body = jsonGetStatement(json, "body");
            stmt = new ejsc.ast_node.WhileStatement(test, body);
            break;
        }

        case "DoWhileStatement": {
            Node.IStatement body = jsonGetStatement(json, "body");
            Node.IExpression test = jsonGetExpression(json, "test");
            stmt = new ejsc.ast_node.DoWhileStatement(body, test);
            break;
        }
            
        case "ForStatement": {
            Node.IExpression test = jsonGetExpression(json, "test", true);
            Node.IExpression update = jsonGetExpression(json, "update", true);
            Node.IStatement body = jsonGetStatement(json, "body");
            JsonValue xjinit = json.get("init");
            if (xjinit == null || xjinit == JsonValue.NULL)
                stmt = new ejsc.ast_node.ForStatement((Node.IExpression) null, test, update, body);
            else {
                JsonObject jinit = (JsonObject) xjinit;
                if (jinit.getString("type").equals("VariableDeclaration")) {
                    Node.IVariableDeclaration init = jsonGetVariableDeclaration(json, "init");
                    stmt = new ejsc.ast_node.ForStatement(init, test, update, body);
                } else {
                    // type of init is expression
                    Node.IExpression init = jsonGetExpression(json, "init");
                    stmt = new ejsc.ast_node.ForStatement(init, test, update, body);
                }
            }
            break;
        }
            
        case "ForInStatement": {
            Node.IExpression right = jsonGetExpression(json, "right");
            Node.IStatement body = jsonGetStatement(json, "body");
            JsonObject jleft = json.getJsonObject("left");
            if (jleft.getString("type").equals("VariableDeclaration")) {
                Node.IVariableDeclaration left = jsonGetVariableDeclaration(json, "left");
                stmt = new ejsc.ast_node.ForInStatement(left, right, body);
            } else {
                // In babel/spec.md, type of "left" is Expression.
                // But we only support Pattern.
                Node.IPattern left = jsonGetPattern(json, "left");
                stmt = new ejsc.ast_node.ForInStatement(left, right, body);
            }
            break;
        }
            
        case "ForOfStatement":
            error("ForOfStatement is not supported", json);
            return null;
        
        default:
            stmt = convertDeclaration(json, true);
            if (stmt != null)
                return stmt;
            error("unkown node type for convertStmt", json);
            return null;
        }
        
        fillStatement(stmt, json);
        return stmt;
    }
    
    private Node.IBlockStatement convertBlockStatement(JsonObject json) {
        assertJsonNodeType("BlockStatement", json);
        ArrayList<Node.IStatement> body = jsonGetStatementArray(json, "body");
        ejsc.ast_node.BlockStatement stmt = new ejsc.ast_node.BlockStatement(body);
        fillStatement(stmt, json);
        return stmt;
    }
    
    private Node.ISwitchCase convertSwitchCase(JsonObject json) {
        assertJsonNodeType("SwitchCase", json);
        Node.IExpression test = jsonGetExpression(json, "test", true);
        ArrayList<Node.IStatement> consequent = jsonGetStatementArray(json, "consequent");
        ejsc.ast_node.SwitchCase sc = new ejsc.ast_node.SwitchCase(test, consequent);
        fillNode(sc, json);
        return sc;
    }
    
    private Node.IDeclaration convertDeclaration(JsonObject json, boolean maybe) {
        String type = json.getString("type");
        switch (type) {
        case "FunctionDeclaration":
            return convertFunDecl(json);

        case "VariableDeclaration":
            return convertVarDecl(json);

        default:
            if (!maybe)
                error("unkown node type for convertDeclaration", json);
            return null;
        }
    }
    
    private Node.ICatchClause convertCatchClause(JsonObject json) {
        assertJsonNodeType("CatchClause", json);
        Node.IPattern param = jsonGetPattern(json, "param");
        Node.IBlockStatement body = jsonGetBlockStatement(json, "body");
        ejsc.ast_node.CatchClause cc = new ejsc.ast_node.CatchClause(param, body);
        fillNode(cc, json);
        return cc;
    }
    
    private Node.IFunctionDeclaration convertFunDecl(JsonObject json) {
        assertJsonNodeType("FunctionDeclaration", json);
        boolean generator = json.getBoolean("generator");
        boolean async = json.getBoolean("async");
        if (generator || async)
            error("generator or async is not supported", json);
        Node.IIdentifier id = jsonGetIdentifier(json, "id");
        ArrayList<Node.IPattern> params = jsonGetPatternArray(json, "params");
        Node.IBlockStatement body = jsonGetBlockStatement(json, "body");
        ejsc.ast_node.FunctionDeclaration decl = new ejsc.ast_node.FunctionDeclaration(id, params, body, logging);
        fillDeclaration(decl, json);
        return decl;
    }
    
    private Node.IVariableDeclaration convertVarDecl(JsonObject json) {
        assertJsonNodeType("VariableDeclaration", json);
        ArrayList<Node.IVariableDeclarator> declarations = jsonGetVariableDeclaratorArray(json, "declarations");
        ejsc.ast_node.VariableDeclaration decl = new ejsc.ast_node.VariableDeclaration(declarations);
        fillDeclaration(decl, json);
        return decl;
    }

    private Node.IVariableDeclarator convertVariableDeclarator(JsonObject json) {
        assertJsonNodeType("VariableDeclarator", json);
        Node.IPattern id = jsonGetPattern(json, "id");
        Node.IExpression init = jsonGetExpression(json, "init", true);
        ejsc.ast_node.VariableDeclarator vd = new ejsc.ast_node.VariableDeclarator(id, init);
        fillNode(vd, json);
        return vd;
    }
    
    private Node.IExpression convertExpression(JsonObject json) {
        String type = json.getString("type");
        Node.IExpression expr;
        
        switch (type) {
        
        // Super: not supported
        // Import: not supported
        
        case "ThisExpression":
            expr = new ejsc.ast_node.ThisExpression();
            break;
        
        // ArrowFunctionExpression: not supported
        // YieldExpression: not supported
        // AwaitExpression: not supported
        
        case "ArrayExpression": {
            ArrayList<Node.IExpression> elements = jsonGetExpressionOptArray(json, "elements");
            expr = new ejsc.ast_node.ArrayExpression(elements);
            break;
        }
        
        case "ObjectExpression": {
            ArrayList<Node.IProperty> properties = jsonGetPropertyArray(json, "properties");
            expr = new ejsc.ast_node.ObjectExpression(properties);
            break;
        }
         
        // RecordExpression: not supported
        // TupleExpression: not supported
        
        case "FunctionExpression": {
            boolean generator = json.getBoolean("generator");
            boolean async = json.getBoolean("async");
            if (generator || async)
                error("generator or async is not supported", json);
            Node.IIdentifier id = jsonGetIdentifier(json, "id", true);
            ArrayList<Node.IPattern> params = jsonGetPatternArray(json, "params");
            Node.IBlockStatement body = jsonGetBlockStatement(json, "body");
            expr = new ejsc.ast_node.FunctionExpression(id, params, body, logging);
            break;
        }

        case "UnaryExpression":
        case "UpdateExpression": {
            String operator = json.getString("operator");
            boolean prefix = json.getBoolean("prefix");
            Node.IExpression argument = jsonGetExpression(json, "argument");
            if (type.equals("UnaryExpression"))
                expr = new ejsc.ast_node.UnaryExpression(operator, prefix, argument);
            else
                expr = new ejsc.ast_node.UpdateExpression(operator, prefix, argument);
            break;
        }

        case "BinaryExpression": {
            String operator = json.getString("operator");
            Node.IExpression left = jsonGetExpression(json, "left"); // PrivateName is not supported
            Node.IExpression right = jsonGetExpression(json, "right");
            expr = new ejsc.ast_node.BinaryExpression(operator, left, right);
            break;
        }
            
        case "AssignmentExpression": {
            String operator = json.getString("operator");
            Node.IExpression left = jsonGetExpression(json, "left"); // Only supported Pattern is Identifier, which is an Expression
            Node.IExpression right = jsonGetExpression(json, "right");
            expr = new ejsc.ast_node.AssignmentExpression(operator, left, right);
            break;
        }
        case "LogicalExpression": {
            String operator = json.getString("operator");
            Node.IExpression left = jsonGetExpression(json, "left");
            Node.IExpression right = jsonGetExpression(json, "right");
            expr = new ejsc.ast_node.LogicalExpression(operator, left, right);
            break;       
        }
            
        // SpreadElement: not supported
        // ArgumentPlaceholder: not supported
        
        case "MemberExpression": {
            Node.IExpression object = jsonGetExpression(json, "object"); // Super is not supported
            boolean computed = json.getBoolean("computed");
            if (computed) {
                // expression is like "a[b]". property is an expression
                Node.IExpression property = jsonGetExpression(json, "property");
                expr = new ejsc.ast_node.MemberExpression(object, property, computed);
            } else {
                // expression is like "a.b". property is an identifier
                Node.IIdentifier property = jsonGetIdentifier(json, "property");
                expr = new ejsc.ast_node.MemberExpression(object, property, computed);
            }
            break;
        }
            
        // OptionalMemberExpression: not supported
        // BindExpression: not supported
            
        case "ConditionalExpression": {
            Node.IExpression test = jsonGetExpression(json, "test");
            Node.IExpression alternate = jsonGetExpression(json, "alternate");
            Node.IExpression consequent = jsonGetExpression(json, "consequent");
            expr = new ejsc.ast_node.ConditionalExpression(test, consequent, alternate);
            break;       
        }
        
        case "CallExpression":
        case "NewExpression": {
            Node.IExpression callee = jsonGetExpression(json, "callee"); // Super or Import is not supported
            ArrayList<Node.IExpression> arguments = jsonGetExpressionArray(json, "arguments"); // SpreadElement is not supported
            if (type.equals("CallExpression"))
                expr = new ejsc.ast_node.CallExpression(callee, arguments);
            else
                expr = new ejsc.ast_node.NewExpression(callee, arguments);
            break;
        }
            
        // OptionalCallExpression: not supported
            
        case "SequenceExpression": {
            ArrayList<Node.IExpression> expressions = jsonGetExpressionArray(json, "expressions");
            expr = new ejsc.ast_node.SequenceExpression(expressions);
            break;
        }
        
        // ParenthesizedExpression: not supported
        // DoExpression: not supported
        // ModuleExpression: not supported
        // TopicReference: not supported
        // TemplateLiteral: not supported
        // TaggedTemplateExpression: not supported

        default: {
            expr = convertIdentifier(json, true);
            if (expr != null)
                return expr;
            expr = convertLiteral(json, true);
            if (expr != null)
                return expr;
            error("unknown node type", json);
            return null;
        }
        }
        
        fillExpression(expr, json);
        return expr;
    }
    
    private Node.IProperty convertObjectProperty(JsonObject json) {
        JsonObject jvalue = json.getJsonObject("value");
        Node.IExpression value = convertExpression(jvalue);
        ejsc.ast_node.Property prop;
        switch (json.getJsonObject("key").getString("type")) {
        case "Identifier": {
            Node.IIdentifier key = jsonGetIdentifier(json, "key"); // in babel/spec.md, key is an Expression
            prop = new ejsc.ast_node.Property(key, value, "init");
            break;
        }
        case "NullLiteral":
        case "NumericLiteral":
        case "StringLiteral":
        case "BooleanLiteral": {
            JsonObject jkey = json.getJsonObject("key");
            Node.ILiteral key = convertLiteral(jkey);
            prop = new ejsc.ast_node.Property(key, value, "init");
            break;
        }
        default:
            error("unknwon node type", json);
            return null;
        }
        fillNode(prop, json);
        return prop;
    }
    
    private Node.IIdentifier convertIdentifier(JsonObject json) {
        return convertIdentifier(json, false);
    }
    
    private Node.IIdentifier convertIdentifier(JsonObject json, boolean maybe) {
        if (!json.getString("type").equals("Identifier") && maybe)
            return null;
        assertJsonNodeType("Identifier", json);
        String name = json.getString("name");
        ejsc.ast_node.Identifier id = new ejsc.ast_node.Identifier(name);
        fillExpression(id, json);
        return id;
    }
    
    private Node.IPattern convertPattern(JsonObject json) {
        String type = json.getString("type");
        switch (type) {
        case "Identifier":
            return convertIdentifier(json);
        default:
            error("unkown node type", json);
            return null;
        }
    }
    
    private void fillLiteral(Node.ILiteral literal, JsonObject json) {
        fillExpression(literal, json);
    }
    
    private void fillStatement(Node.IStatement stmt, JsonObject json) {
        fillNode(stmt, json);
    }
    
    private void fillExpression(Node.IExpression exp, JsonObject json) {
        fillNode(exp, json);
    }
    
    private void fillDeclaration(Node.IDeclaration decl, JsonObject json) {
        fillStatement(decl, json);
    }
    
    private void fillNode(Node.INode node, JsonObject json) {
        JsonObject loc = json.getJsonObject("loc");
        if (loc == null)
            error("no location infomation", json);
        String source = jsonGetString(loc, "source", true);
        int startLine = loc.getJsonObject("start").getJsonNumber("line").intValue();
        int startColumn = loc.getJsonObject("start").getJsonNumber("column").intValue();
        int endLine = loc.getJsonObject("end").getJsonNumber("line").intValue();
        int endColumn = loc.getJsonObject("end").getJsonNumber("column").intValue();
        node.setSourceLocation(source, startLine, startColumn, endLine, endColumn);
    }
    

    private Node.IIdentifier jsonGetIdentifier(JsonObject json, String field) {
        return jsonGetIdentifier(json, field, false);
    }

    private Node.IIdentifier jsonGetIdentifier(JsonObject json, String field, boolean isOptional) {
        JsonValue xjid = json.get(field);
        if (xjid == null || xjid == JsonValue.NULL) {
            if (!isOptional)
                error("missing field: "+field, json);
            return null;
        }
        JsonObject jid = (JsonObject) xjid;
        return convertIdentifier(jid);
    }
    
    private Node.IPattern jsonGetPattern(JsonObject json, String field) {
        // the only supported Pattern is Identifier
        return jsonGetIdentifier(json, field);
    }
    
    private Node.IExpression jsonGetExpression(JsonObject json, String field) {
        return jsonGetExpression(json, field, false);
    }
    
    private Node.IExpression jsonGetExpression(JsonObject json, String field, boolean isOptional) {
        JsonValue xjexpr = json.get(field);
        if (xjexpr == null || xjexpr == JsonValue.NULL) {
            if (!isOptional)
                error("missing field: "+field, json);
            return null;
        }
        JsonObject jexpr = (JsonObject) xjexpr;
        return convertExpression(jexpr);
    }
    
    private Node.IStatement jsonGetStatement(JsonObject json, String field) {
        return jsonGetStatement(json, field, false);
    }
    
    private Node.IStatement jsonGetStatement(JsonObject json, String field, boolean isOptional) {
        JsonValue xjstmt = json.get(field);
        if (xjstmt == null || xjstmt == JsonValue.NULL) {
            if (!isOptional)
                error("missing field: "+field, json);
            return null;
        }
        JsonObject jstmt = (JsonObject) xjstmt;
        return convertStmt(jstmt);
    }
    
    private Node.IBlockStatement jsonGetBlockStatement(JsonObject json, String field) {
        return jsonGetBlockStatement(json, field, false);
    }
    
    private Node.IBlockStatement jsonGetBlockStatement(JsonObject json, String field, boolean isOptional) {
        JsonValue xjblock = json.get(field);
        if (xjblock == null || xjblock == JsonValue.NULL) {
            if (!isOptional)
                error("missing field: "+field, json);
            return null;
        }
        JsonObject jblock = (JsonObject) xjblock;
        Node.IBlockStatement block = convertBlockStatement(jblock);
        return block;
    }
    
    private ArrayList<Node.ISwitchCase> jsonGetSwitchCase(JsonObject json, String field) {
        JsonArray jcases = json.getJsonArray(field);
        ArrayList<Node.ISwitchCase> cases = new ArrayList<Node.ISwitchCase>();
        for (JsonValue xi: jcases) {
            JsonObject i = (JsonObject) xi;
            Node.ISwitchCase switchCase = convertSwitchCase(i);
            cases.add(switchCase);
        }
        return cases;
    }
    
    private Node.ICatchClause jsonGetCatchClause(JsonObject json, String field, boolean isOptional) {
        JsonValue xjcc = json.get(field);
        if (xjcc == null || xjcc == JsonValue.NULL) {
            if (!isOptional)
                error("missing field: "+field, json);
            return null;
        }
        JsonObject jcc = (JsonObject) xjcc;
        return convertCatchClause(jcc);

    }
    
    private Node.IVariableDeclaration jsonGetVariableDeclaration(JsonObject json, String field) {
        JsonObject jdecl = json.getJsonObject(field);
        return convertVarDecl(jdecl);
    }
    
    private ArrayList<Node.IPattern> jsonGetPatternArray(JsonObject json, String field) {
        JsonArray jparams = json.getJsonArray(field);
        ArrayList<Node.IPattern> params = new ArrayList<Node.IPattern>();
        for (JsonValue xi: jparams) {
            JsonObject i = (JsonObject) xi;
            Node.IPattern param = convertPattern(i);
            params.add(param);
        }
        return params;
    }
        
    private ArrayList<Node.IExpression> jsonGetExpressionArray(JsonObject json, String field) {
        JsonArray jarray = json.getJsonArray(field);
        ArrayList<Node.IExpression> array = new ArrayList<Node.IExpression>();
        for (JsonValue xi: jarray) {
            JsonObject i = (JsonObject) xi;
            Node.IExpression expr = convertExpression(i);
            array.add(expr);
        }
        return array;
    }
    
    private ArrayList<Node.IExpression> jsonGetExpressionOptArray(JsonObject json, String field) {
        JsonArray jelements = json.getJsonArray(field);
        ArrayList<Node.IExpression> elements = new ArrayList<Node.IExpression>();
        for (JsonValue xi: jelements) {
            if (xi == null || xi == JsonValue.NULL)
                elements.add(null);
            else {
                try {
                JsonObject i = (JsonObject) xi;
                Node.IExpression elem = convertExpression(i);
                elements.add(elem);
                } catch (Exception e) {
                    error("error", json);
                }
            }
        }
        return elements;
    }
    
    private ArrayList<Node.IStatement> jsonGetStatementArray(JsonObject json, String field) {
        JsonArray jarray = json.getJsonArray(field);
        ArrayList<Node.IStatement> array = new ArrayList<Node.IStatement>();
        for (JsonValue xi: jarray) {
            JsonObject i = (JsonObject) xi;
            Node.IStatement stmt = convertStmt(i);
            array.add(stmt);
        }
        return array;        
    }
    
    private ArrayList<Node.IVariableDeclarator> jsonGetVariableDeclaratorArray(JsonObject json, String field) {
        JsonArray jdeclarations = json.getJsonArray(field);
        ArrayList<Node.IVariableDeclarator> declarations = new ArrayList<Node.IVariableDeclarator>();
        for (JsonValue xi: jdeclarations) {
            JsonObject i = (JsonObject) xi;
            Node.IVariableDeclarator declarator = convertVariableDeclarator(i);
            declarations.add(declarator);
        }
        return declarations;
    }

    private ArrayList<Node.IProperty> jsonGetPropertyArray(JsonObject json, String field) {
        JsonArray jproperties = json.getJsonArray(field);
        ArrayList<Node.IProperty> properties = new ArrayList<Node.IProperty>();
        for (JsonValue xi: jproperties) {
            JsonObject i = (JsonObject) xi;
            if (i.getString("type").equals("ObjectProperty")) {
                Node.IProperty prop = convertObjectProperty(i);
                properties.add(prop);
            } else if (i.getString("type").equals("ObjectMethod"))
                error("ObjectMethod is not supported", json);
            else
                error("unkown node type", json);
        }
        return properties;
    }
    
    private String jsonGetString(JsonObject json, String field, boolean isOptional) {
        JsonValue xjstr = json.get(field);
        if (xjstr == null || xjstr == JsonValue.NULL) {
            if (!isOptional)
                error("missing field: "+field, json);
            return null;
        }
        return xjstr.toString();
    }
}
