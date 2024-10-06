// Generated from ECMAScript.g4 by ANTLR 4.5.3
package ejsc.antlr;
import org.antlr.v4.runtime.atn.*;
import org.antlr.v4.runtime.dfa.DFA;
import org.antlr.v4.runtime.*;
import org.antlr.v4.runtime.misc.*;
import org.antlr.v4.runtime.tree.*;
import java.util.List;
import java.util.Iterator;
import java.util.ArrayList;

@SuppressWarnings({"all", "warnings", "unchecked", "unused", "cast"})
public class ECMAScriptParser extends Parser {
	static { RuntimeMetaData.checkVersion("4.5.3", RuntimeMetaData.VERSION); }

	protected static final DFA[] _decisionToDFA;
	protected static final PredictionContextCache _sharedContextCache =
		new PredictionContextCache();
	public static final int
		RegularExpressionLiteral=1, LineTerminator=2, OpenBracket=3, CloseBracket=4, 
		OpenParen=5, CloseParen=6, OpenBrace=7, CloseBrace=8, SemiColon=9, Comma=10, 
		Assign=11, QuestionMark=12, Colon=13, Dot=14, PlusPlus=15, MinusMinus=16, 
		Plus=17, Minus=18, BitNot=19, Not=20, Multiply=21, Divide=22, Modulus=23, 
		RightShiftArithmetic=24, LeftShiftArithmetic=25, RightShiftLogical=26, 
		LessThan=27, MoreThan=28, LessThanEquals=29, GreaterThanEquals=30, Equals=31, 
		NotEquals=32, IdentityEquals=33, IdentityNotEquals=34, BitAnd=35, BitXOr=36, 
		BitOr=37, And=38, Or=39, MultiplyAssign=40, DivideAssign=41, ModulusAssign=42, 
		PlusAssign=43, MinusAssign=44, LeftShiftArithmeticAssign=45, RightShiftArithmeticAssign=46, 
		RightShiftLogicalAssign=47, BitAndAssign=48, BitXorAssign=49, BitOrAssign=50, 
		NullLiteral=51, BooleanLiteral=52, DecimalLiteral=53, HexIntegerLiteral=54, 
		OctalIntegerLiteral=55, Break=56, Do=57, Instanceof=58, Typeof=59, Case=60, 
		Else=61, New=62, Var=63, Catch=64, Finally=65, Return=66, Void=67, Continue=68, 
		For=69, Switch=70, While=71, Debugger=72, Function=73, This=74, With=75, 
		Default=76, If=77, Throw=78, Delete=79, In=80, Try=81, Class=82, Enum=83, 
		Extends=84, Super=85, Const=86, Export=87, Import=88, Implements=89, Let=90, 
		Private=91, Public=92, Interface=93, Package=94, Protected=95, Static=96, 
		Yield=97, Identifier=98, StringLiteral=99, WhiteSpaces=100, MultiLineComment=101, 
		SingleLineComment=102, UnexpectedCharacter=103;
	public static final int
		RULE_program = 0, RULE_sourceElements = 1, RULE_sourceElement = 2, RULE_statement = 3, 
		RULE_block = 4, RULE_statementList = 5, RULE_variableStatement = 6, RULE_variableDeclarationList = 7, 
		RULE_variableDeclaration = 8, RULE_initialiser = 9, RULE_emptyStatement = 10, 
		RULE_expressionStatement = 11, RULE_ifStatement = 12, RULE_expressionSequenceOpt = 13, 
		RULE_iterationStatement = 14, RULE_continueStatement = 15, RULE_breakStatement = 16, 
		RULE_returnStatement = 17, RULE_withStatement = 18, RULE_switchStatement = 19, 
		RULE_caseBlock = 20, RULE_caseClauses = 21, RULE_caseClause = 22, RULE_defaultClause = 23, 
		RULE_labelledStatement = 24, RULE_throwStatement = 25, RULE_tryStatement = 26, 
		RULE_catchProduction = 27, RULE_finallyProduction = 28, RULE_debuggerStatement = 29, 
		RULE_functionDeclaration = 30, RULE_formalParameterList = 31, RULE_functionBody = 32, 
		RULE_arrayLiteral = 33, RULE_elementList = 34, RULE_elision = 35, RULE_objectLiteral = 36, 
		RULE_propertyNameAndValueList = 37, RULE_propertyAssignment = 38, RULE_propertyName = 39, 
		RULE_propertySetParameterList = 40, RULE_arguments = 41, RULE_argumentList = 42, 
		RULE_expressionSequence = 43, RULE_singleExpression = 44, RULE_assignmentOperator = 45, 
		RULE_literal = 46, RULE_numericLiteral = 47, RULE_identifierName = 48, 
		RULE_reservedWord = 49, RULE_keyword = 50, RULE_futureReservedWord = 51, 
		RULE_getter = 52, RULE_setter = 53, RULE_eos = 54, RULE_eof = 55;
	public static final String[] ruleNames = {
		"program", "sourceElements", "sourceElement", "statement", "block", "statementList", 
		"variableStatement", "variableDeclarationList", "variableDeclaration", 
		"initialiser", "emptyStatement", "expressionStatement", "ifStatement", 
		"expressionSequenceOpt", "iterationStatement", "continueStatement", "breakStatement", 
		"returnStatement", "withStatement", "switchStatement", "caseBlock", "caseClauses", 
		"caseClause", "defaultClause", "labelledStatement", "throwStatement", 
		"tryStatement", "catchProduction", "finallyProduction", "debuggerStatement", 
		"functionDeclaration", "formalParameterList", "functionBody", "arrayLiteral", 
		"elementList", "elision", "objectLiteral", "propertyNameAndValueList", 
		"propertyAssignment", "propertyName", "propertySetParameterList", "arguments", 
		"argumentList", "expressionSequence", "singleExpression", "assignmentOperator", 
		"literal", "numericLiteral", "identifierName", "reservedWord", "keyword", 
		"futureReservedWord", "getter", "setter", "eos", "eof"
	};

	private static final String[] _LITERAL_NAMES = {
		null, null, null, "'['", "']'", "'('", "')'", "'{'", "'}'", "';'", "','", 
		"'='", "'?'", "':'", "'.'", "'++'", "'--'", "'+'", "'-'", "'~'", "'!'", 
		"'*'", "'/'", "'%'", "'>>'", "'<<'", "'>>>'", "'<'", "'>'", "'<='", "'>='", 
		"'=='", "'!='", "'==='", "'!=='", "'&'", "'^'", "'|'", "'&&'", "'||'", 
		"'*='", "'/='", "'%='", "'+='", "'-='", "'<<='", "'>>='", "'>>>='", "'&='", 
		"'^='", "'|='", "'null'", null, null, null, null, "'break'", "'do'", "'instanceof'", 
		"'typeof'", "'case'", "'else'", "'new'", "'var'", "'catch'", "'finally'", 
		"'return'", "'void'", "'continue'", "'for'", "'switch'", "'while'", "'debugger'", 
		"'function'", "'this'", "'with'", "'default'", "'if'", "'throw'", "'delete'", 
		"'in'", "'try'", "'class'", "'enum'", "'extends'", "'super'", "'const'", 
		"'export'", "'import'"
	};
	private static final String[] _SYMBOLIC_NAMES = {
		null, "RegularExpressionLiteral", "LineTerminator", "OpenBracket", "CloseBracket", 
		"OpenParen", "CloseParen", "OpenBrace", "CloseBrace", "SemiColon", "Comma", 
		"Assign", "QuestionMark", "Colon", "Dot", "PlusPlus", "MinusMinus", "Plus", 
		"Minus", "BitNot", "Not", "Multiply", "Divide", "Modulus", "RightShiftArithmetic", 
		"LeftShiftArithmetic", "RightShiftLogical", "LessThan", "MoreThan", "LessThanEquals", 
		"GreaterThanEquals", "Equals", "NotEquals", "IdentityEquals", "IdentityNotEquals", 
		"BitAnd", "BitXOr", "BitOr", "And", "Or", "MultiplyAssign", "DivideAssign", 
		"ModulusAssign", "PlusAssign", "MinusAssign", "LeftShiftArithmeticAssign", 
		"RightShiftArithmeticAssign", "RightShiftLogicalAssign", "BitAndAssign", 
		"BitXorAssign", "BitOrAssign", "NullLiteral", "BooleanLiteral", "DecimalLiteral", 
		"HexIntegerLiteral", "OctalIntegerLiteral", "Break", "Do", "Instanceof", 
		"Typeof", "Case", "Else", "New", "Var", "Catch", "Finally", "Return", 
		"Void", "Continue", "For", "Switch", "While", "Debugger", "Function", 
		"This", "With", "Default", "If", "Throw", "Delete", "In", "Try", "Class", 
		"Enum", "Extends", "Super", "Const", "Export", "Import", "Implements", 
		"Let", "Private", "Public", "Interface", "Package", "Protected", "Static", 
		"Yield", "Identifier", "StringLiteral", "WhiteSpaces", "MultiLineComment", 
		"SingleLineComment", "UnexpectedCharacter"
	};
	public static final Vocabulary VOCABULARY = new VocabularyImpl(_LITERAL_NAMES, _SYMBOLIC_NAMES);

	/**
	 * @deprecated Use {@link #VOCABULARY} instead.
	 */
	@Deprecated
	public static final String[] tokenNames;
	static {
		tokenNames = new String[_SYMBOLIC_NAMES.length];
		for (int i = 0; i < tokenNames.length; i++) {
			tokenNames[i] = VOCABULARY.getLiteralName(i);
			if (tokenNames[i] == null) {
				tokenNames[i] = VOCABULARY.getSymbolicName(i);
			}

			if (tokenNames[i] == null) {
				tokenNames[i] = "<INVALID>";
			}
		}
	}

	@Override
	@Deprecated
	public String[] getTokenNames() {
		return tokenNames;
	}

	@Override

	public Vocabulary getVocabulary() {
		return VOCABULARY;
	}

	@Override
	public String getGrammarFileName() { return "ECMAScript.g4"; }

	@Override
	public String[] getRuleNames() { return ruleNames; }

	@Override
	public String getSerializedATN() { return _serializedATN; }

	@Override
	public ATN getATN() { return _ATN; }


	  
	    /**
	     * Returns {@code true} iff on the current index of the parser's
	     * token stream a token of the given {@code type} exists on the
	     * {@code HIDDEN} channel.
	     *
	     * @param type
	     *         the type of the token on the {@code HIDDEN} channel
	     *         to check.
	     *
	     * @return {@code true} iff on the current index of the parser's
	     * token stream a token of the given {@code type} exists on the
	     * {@code HIDDEN} channel.
	     */
	    private boolean here(final int type) {

	        // Get the token ahead of the current index.
	        int possibleIndexEosToken = this.getCurrentToken().getTokenIndex() - 1;
	        Token ahead = _input.get(possibleIndexEosToken);

	        // Check if the token resides on the HIDDEN channel and if it's of the
	        // provided type.
	        return (ahead.getChannel() == Lexer.HIDDEN) && (ahead.getType() == type);
	    }

	    /**
	     * Returns {@code true} iff on the current index of the parser's
	     * token stream a token exists on the {@code HIDDEN} channel which
	     * either is a line terminator, or is a multi line comment that
	     * contains a line terminator.
	     *
	     * @return {@code true} iff on the current index of the parser's
	     * token stream a token exists on the {@code HIDDEN} channel which
	     * either is a line terminator, or is a multi line comment that
	     * contains a line terminator.
	     */
	    private boolean lineTerminatorAhead() {

	        // Get the token ahead of the current index.
	        int possibleIndexEosToken = this.getCurrentToken().getTokenIndex() - 1;
	        Token ahead = _input.get(possibleIndexEosToken);

	        if (ahead.getChannel() != Lexer.HIDDEN) {
	            // We're only interested in tokens on the HIDDEN channel.
	            return false;
	        }

	        if (ahead.getType() == LineTerminator) {
	            // There is definitely a line terminator ahead.
	            return true;
	        }

	        if (ahead.getType() == WhiteSpaces) {
	            // Get the token ahead of the current whitespaces.
	            possibleIndexEosToken = this.getCurrentToken().getTokenIndex() - 2;
	            ahead = _input.get(possibleIndexEosToken);
	        }

	        // Get the token's text and type.
	        String text = ahead.getText();
	        int type = ahead.getType();

	        // Check if the token is, or contains a line terminator.
	        return (type == MultiLineComment && (text.contains("\r") || text.contains("\n"))) ||
	                (type == LineTerminator);
	    }                                

	public ECMAScriptParser(TokenStream input) {
		super(input);
		_interp = new ParserATNSimulator(this,_ATN,_decisionToDFA,_sharedContextCache);
	}
	public static class ProgramContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(ECMAScriptParser.EOF, 0); }
		public SourceElementsContext sourceElements() {
			return getRuleContext(SourceElementsContext.class,0);
		}
		public ProgramContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_program; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitProgram(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ProgramContext program() throws RecognitionException {
		ProgramContext _localctx = new ProgramContext(_ctx, getState());
		enterRule(_localctx, 0, RULE_program);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(113);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,0,_ctx) ) {
			case 1:
				{
				setState(112);
				sourceElements();
				}
				break;
			}
			setState(115);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class SourceElementsContext extends ParserRuleContext {
		public List<SourceElementContext> sourceElement() {
			return getRuleContexts(SourceElementContext.class);
		}
		public SourceElementContext sourceElement(int i) {
			return getRuleContext(SourceElementContext.class,i);
		}
		public SourceElementsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_sourceElements; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitSourceElements(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SourceElementsContext sourceElements() throws RecognitionException {
		SourceElementsContext _localctx = new SourceElementsContext(_ctx, getState());
		enterRule(_localctx, 2, RULE_sourceElements);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(118); 
			_errHandler.sync(this);
			_alt = 1;
			do {
				switch (_alt) {
				case 1:
					{
					{
					setState(117);
					sourceElement();
					}
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				setState(120); 
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,1,_ctx);
			} while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class SourceElementContext extends ParserRuleContext {
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public FunctionDeclarationContext functionDeclaration() {
			return getRuleContext(FunctionDeclarationContext.class,0);
		}
		public SourceElementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_sourceElement; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitSourceElement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SourceElementContext sourceElement() throws RecognitionException {
		SourceElementContext _localctx = new SourceElementContext(_ctx, getState());
		enterRule(_localctx, 4, RULE_sourceElement);
		try {
			setState(125);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,2,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(122);
				if (!(_input.LA(1) != Function)) throw new FailedPredicateException(this, "_input.LA(1) != Function");
				setState(123);
				statement();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(124);
				functionDeclaration();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class StatementContext extends ParserRuleContext {
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public VariableStatementContext variableStatement() {
			return getRuleContext(VariableStatementContext.class,0);
		}
		public EmptyStatementContext emptyStatement() {
			return getRuleContext(EmptyStatementContext.class,0);
		}
		public ExpressionStatementContext expressionStatement() {
			return getRuleContext(ExpressionStatementContext.class,0);
		}
		public IfStatementContext ifStatement() {
			return getRuleContext(IfStatementContext.class,0);
		}
		public IterationStatementContext iterationStatement() {
			return getRuleContext(IterationStatementContext.class,0);
		}
		public ContinueStatementContext continueStatement() {
			return getRuleContext(ContinueStatementContext.class,0);
		}
		public BreakStatementContext breakStatement() {
			return getRuleContext(BreakStatementContext.class,0);
		}
		public ReturnStatementContext returnStatement() {
			return getRuleContext(ReturnStatementContext.class,0);
		}
		public WithStatementContext withStatement() {
			return getRuleContext(WithStatementContext.class,0);
		}
		public LabelledStatementContext labelledStatement() {
			return getRuleContext(LabelledStatementContext.class,0);
		}
		public SwitchStatementContext switchStatement() {
			return getRuleContext(SwitchStatementContext.class,0);
		}
		public ThrowStatementContext throwStatement() {
			return getRuleContext(ThrowStatementContext.class,0);
		}
		public TryStatementContext tryStatement() {
			return getRuleContext(TryStatementContext.class,0);
		}
		public DebuggerStatementContext debuggerStatement() {
			return getRuleContext(DebuggerStatementContext.class,0);
		}
		public StatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statement; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StatementContext statement() throws RecognitionException {
		StatementContext _localctx = new StatementContext(_ctx, getState());
		enterRule(_localctx, 6, RULE_statement);
		try {
			setState(143);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,3,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(127);
				block();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(128);
				variableStatement();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(129);
				emptyStatement();
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(130);
				if (!(_input.LA(1) != OpenBrace)) throw new FailedPredicateException(this, "_input.LA(1) != OpenBrace");
				setState(131);
				expressionStatement();
				}
				break;
			case 5:
				enterOuterAlt(_localctx, 5);
				{
				setState(132);
				ifStatement();
				}
				break;
			case 6:
				enterOuterAlt(_localctx, 6);
				{
				setState(133);
				iterationStatement();
				}
				break;
			case 7:
				enterOuterAlt(_localctx, 7);
				{
				setState(134);
				continueStatement();
				}
				break;
			case 8:
				enterOuterAlt(_localctx, 8);
				{
				setState(135);
				breakStatement();
				}
				break;
			case 9:
				enterOuterAlt(_localctx, 9);
				{
				setState(136);
				returnStatement();
				}
				break;
			case 10:
				enterOuterAlt(_localctx, 10);
				{
				setState(137);
				withStatement();
				}
				break;
			case 11:
				enterOuterAlt(_localctx, 11);
				{
				setState(138);
				labelledStatement();
				}
				break;
			case 12:
				enterOuterAlt(_localctx, 12);
				{
				setState(139);
				switchStatement();
				}
				break;
			case 13:
				enterOuterAlt(_localctx, 13);
				{
				setState(140);
				throwStatement();
				}
				break;
			case 14:
				enterOuterAlt(_localctx, 14);
				{
				setState(141);
				tryStatement();
				}
				break;
			case 15:
				enterOuterAlt(_localctx, 15);
				{
				setState(142);
				debuggerStatement();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class BlockContext extends ParserRuleContext {
		public StatementListContext statementList() {
			return getRuleContext(StatementListContext.class,0);
		}
		public BlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_block; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitBlock(this);
			else return visitor.visitChildren(this);
		}
	}

	public final BlockContext block() throws RecognitionException {
		BlockContext _localctx = new BlockContext(_ctx, getState());
		enterRule(_localctx, 8, RULE_block);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(145);
			match(OpenBrace);
			setState(147);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,4,_ctx) ) {
			case 1:
				{
				setState(146);
				statementList();
				}
				break;
			}
			setState(149);
			match(CloseBrace);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class StatementListContext extends ParserRuleContext {
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public StatementListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_statementList; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitStatementList(this);
			else return visitor.visitChildren(this);
		}
	}

	public final StatementListContext statementList() throws RecognitionException {
		StatementListContext _localctx = new StatementListContext(_ctx, getState());
		enterRule(_localctx, 10, RULE_statementList);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(152); 
			_errHandler.sync(this);
			_alt = 1;
			do {
				switch (_alt) {
				case 1:
					{
					{
					setState(151);
					statement();
					}
					}
					break;
				default:
					throw new NoViableAltException(this);
				}
				setState(154); 
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,5,_ctx);
			} while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class VariableStatementContext extends ParserRuleContext {
		public TerminalNode Var() { return getToken(ECMAScriptParser.Var, 0); }
		public VariableDeclarationListContext variableDeclarationList() {
			return getRuleContext(VariableDeclarationListContext.class,0);
		}
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public VariableStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variableStatement; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitVariableStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final VariableStatementContext variableStatement() throws RecognitionException {
		VariableStatementContext _localctx = new VariableStatementContext(_ctx, getState());
		enterRule(_localctx, 12, RULE_variableStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(156);
			match(Var);
			setState(157);
			variableDeclarationList();
			setState(158);
			eos();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class VariableDeclarationListContext extends ParserRuleContext {
		public List<VariableDeclarationContext> variableDeclaration() {
			return getRuleContexts(VariableDeclarationContext.class);
		}
		public VariableDeclarationContext variableDeclaration(int i) {
			return getRuleContext(VariableDeclarationContext.class,i);
		}
		public VariableDeclarationListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variableDeclarationList; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitVariableDeclarationList(this);
			else return visitor.visitChildren(this);
		}
	}

	public final VariableDeclarationListContext variableDeclarationList() throws RecognitionException {
		VariableDeclarationListContext _localctx = new VariableDeclarationListContext(_ctx, getState());
		enterRule(_localctx, 14, RULE_variableDeclarationList);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(160);
			variableDeclaration();
			setState(165);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,6,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(161);
					match(Comma);
					setState(162);
					variableDeclaration();
					}
					} 
				}
				setState(167);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,6,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class VariableDeclarationContext extends ParserRuleContext {
		public TerminalNode Identifier() { return getToken(ECMAScriptParser.Identifier, 0); }
		public InitialiserContext initialiser() {
			return getRuleContext(InitialiserContext.class,0);
		}
		public VariableDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_variableDeclaration; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitVariableDeclaration(this);
			else return visitor.visitChildren(this);
		}
	}

	public final VariableDeclarationContext variableDeclaration() throws RecognitionException {
		VariableDeclarationContext _localctx = new VariableDeclarationContext(_ctx, getState());
		enterRule(_localctx, 16, RULE_variableDeclaration);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(168);
			match(Identifier);
			setState(170);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,7,_ctx) ) {
			case 1:
				{
				setState(169);
				initialiser();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class InitialiserContext extends ParserRuleContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public InitialiserContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_initialiser; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitInitialiser(this);
			else return visitor.visitChildren(this);
		}
	}

	public final InitialiserContext initialiser() throws RecognitionException {
		InitialiserContext _localctx = new InitialiserContext(_ctx, getState());
		enterRule(_localctx, 18, RULE_initialiser);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(172);
			match(Assign);
			setState(173);
			singleExpression(0);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class EmptyStatementContext extends ParserRuleContext {
		public TerminalNode SemiColon() { return getToken(ECMAScriptParser.SemiColon, 0); }
		public EmptyStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_emptyStatement; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitEmptyStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final EmptyStatementContext emptyStatement() throws RecognitionException {
		EmptyStatementContext _localctx = new EmptyStatementContext(_ctx, getState());
		enterRule(_localctx, 20, RULE_emptyStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(175);
			match(SemiColon);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExpressionStatementContext extends ParserRuleContext {
		public ExpressionSequenceContext expressionSequence() {
			return getRuleContext(ExpressionSequenceContext.class,0);
		}
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public ExpressionStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expressionStatement; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitExpressionStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ExpressionStatementContext expressionStatement() throws RecognitionException {
		ExpressionStatementContext _localctx = new ExpressionStatementContext(_ctx, getState());
		enterRule(_localctx, 22, RULE_expressionStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(177);
			expressionSequence();
			setState(178);
			eos();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class IfStatementContext extends ParserRuleContext {
		public TerminalNode If() { return getToken(ECMAScriptParser.If, 0); }
		public ExpressionSequenceContext expressionSequence() {
			return getRuleContext(ExpressionSequenceContext.class,0);
		}
		public List<StatementContext> statement() {
			return getRuleContexts(StatementContext.class);
		}
		public StatementContext statement(int i) {
			return getRuleContext(StatementContext.class,i);
		}
		public TerminalNode Else() { return getToken(ECMAScriptParser.Else, 0); }
		public IfStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_ifStatement; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitIfStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final IfStatementContext ifStatement() throws RecognitionException {
		IfStatementContext _localctx = new IfStatementContext(_ctx, getState());
		enterRule(_localctx, 24, RULE_ifStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(180);
			match(If);
			setState(181);
			match(OpenParen);
			setState(182);
			expressionSequence();
			setState(183);
			match(CloseParen);
			setState(184);
			statement();
			setState(187);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,8,_ctx) ) {
			case 1:
				{
				setState(185);
				match(Else);
				setState(186);
				statement();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExpressionSequenceOptContext extends ParserRuleContext {
		public ExpressionSequenceContext expressionSequence() {
			return getRuleContext(ExpressionSequenceContext.class,0);
		}
		public ExpressionSequenceOptContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expressionSequenceOpt; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitExpressionSequenceOpt(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ExpressionSequenceOptContext expressionSequenceOpt() throws RecognitionException {
		ExpressionSequenceOptContext _localctx = new ExpressionSequenceOptContext(_ctx, getState());
		enterRule(_localctx, 26, RULE_expressionSequenceOpt);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(190);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << RegularExpressionLiteral) | (1L << OpenBracket) | (1L << OpenParen) | (1L << OpenBrace) | (1L << PlusPlus) | (1L << MinusMinus) | (1L << Plus) | (1L << Minus) | (1L << BitNot) | (1L << Not) | (1L << NullLiteral) | (1L << BooleanLiteral) | (1L << DecimalLiteral) | (1L << HexIntegerLiteral) | (1L << OctalIntegerLiteral) | (1L << Typeof) | (1L << New))) != 0) || ((((_la - 67)) & ~0x3f) == 0 && ((1L << (_la - 67)) & ((1L << (Void - 67)) | (1L << (Function - 67)) | (1L << (This - 67)) | (1L << (Delete - 67)) | (1L << (Identifier - 67)) | (1L << (StringLiteral - 67)))) != 0)) {
				{
				setState(189);
				expressionSequence();
				}
			}

			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class IterationStatementContext extends ParserRuleContext {
		public IterationStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_iterationStatement; }
	 
		public IterationStatementContext() { }
		public void copyFrom(IterationStatementContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class DoStatementContext extends IterationStatementContext {
		public TerminalNode Do() { return getToken(ECMAScriptParser.Do, 0); }
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public TerminalNode While() { return getToken(ECMAScriptParser.While, 0); }
		public ExpressionSequenceContext expressionSequence() {
			return getRuleContext(ExpressionSequenceContext.class,0);
		}
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public DoStatementContext(IterationStatementContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitDoStatement(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class ForVarStatementContext extends IterationStatementContext {
		public TerminalNode For() { return getToken(ECMAScriptParser.For, 0); }
		public TerminalNode Var() { return getToken(ECMAScriptParser.Var, 0); }
		public VariableDeclarationListContext variableDeclarationList() {
			return getRuleContext(VariableDeclarationListContext.class,0);
		}
		public List<ExpressionSequenceOptContext> expressionSequenceOpt() {
			return getRuleContexts(ExpressionSequenceOptContext.class);
		}
		public ExpressionSequenceOptContext expressionSequenceOpt(int i) {
			return getRuleContext(ExpressionSequenceOptContext.class,i);
		}
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public ForVarStatementContext(IterationStatementContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitForVarStatement(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class ForVarInStatementContext extends IterationStatementContext {
		public TerminalNode For() { return getToken(ECMAScriptParser.For, 0); }
		public TerminalNode Var() { return getToken(ECMAScriptParser.Var, 0); }
		public VariableDeclarationContext variableDeclaration() {
			return getRuleContext(VariableDeclarationContext.class,0);
		}
		public TerminalNode In() { return getToken(ECMAScriptParser.In, 0); }
		public ExpressionSequenceContext expressionSequence() {
			return getRuleContext(ExpressionSequenceContext.class,0);
		}
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public ForVarInStatementContext(IterationStatementContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitForVarInStatement(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class WhileStatementContext extends IterationStatementContext {
		public TerminalNode While() { return getToken(ECMAScriptParser.While, 0); }
		public ExpressionSequenceContext expressionSequence() {
			return getRuleContext(ExpressionSequenceContext.class,0);
		}
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public WhileStatementContext(IterationStatementContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitWhileStatement(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class ForStatementContext extends IterationStatementContext {
		public TerminalNode For() { return getToken(ECMAScriptParser.For, 0); }
		public List<ExpressionSequenceOptContext> expressionSequenceOpt() {
			return getRuleContexts(ExpressionSequenceOptContext.class);
		}
		public ExpressionSequenceOptContext expressionSequenceOpt(int i) {
			return getRuleContext(ExpressionSequenceOptContext.class,i);
		}
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public ForStatementContext(IterationStatementContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitForStatement(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class ForInStatementContext extends IterationStatementContext {
		public TerminalNode For() { return getToken(ECMAScriptParser.For, 0); }
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public TerminalNode In() { return getToken(ECMAScriptParser.In, 0); }
		public ExpressionSequenceContext expressionSequence() {
			return getRuleContext(ExpressionSequenceContext.class,0);
		}
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public ForInStatementContext(IterationStatementContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitForInStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final IterationStatementContext iterationStatement() throws RecognitionException {
		IterationStatementContext _localctx = new IterationStatementContext(_ctx, getState());
		enterRule(_localctx, 28, RULE_iterationStatement);
		try {
			setState(244);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,10,_ctx) ) {
			case 1:
				_localctx = new DoStatementContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(192);
				match(Do);
				setState(193);
				statement();
				setState(194);
				match(While);
				setState(195);
				match(OpenParen);
				setState(196);
				expressionSequence();
				setState(197);
				match(CloseParen);
				setState(198);
				eos();
				}
				break;
			case 2:
				_localctx = new WhileStatementContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(200);
				match(While);
				setState(201);
				match(OpenParen);
				setState(202);
				expressionSequence();
				setState(203);
				match(CloseParen);
				setState(204);
				statement();
				}
				break;
			case 3:
				_localctx = new ForStatementContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(206);
				match(For);
				setState(207);
				match(OpenParen);
				setState(208);
				expressionSequenceOpt();
				setState(209);
				match(SemiColon);
				setState(210);
				expressionSequenceOpt();
				setState(211);
				match(SemiColon);
				setState(212);
				expressionSequenceOpt();
				setState(213);
				match(CloseParen);
				setState(214);
				statement();
				}
				break;
			case 4:
				_localctx = new ForVarStatementContext(_localctx);
				enterOuterAlt(_localctx, 4);
				{
				setState(216);
				match(For);
				setState(217);
				match(OpenParen);
				setState(218);
				match(Var);
				setState(219);
				variableDeclarationList();
				setState(220);
				match(SemiColon);
				setState(221);
				expressionSequenceOpt();
				setState(222);
				match(SemiColon);
				setState(223);
				expressionSequenceOpt();
				setState(224);
				match(CloseParen);
				setState(225);
				statement();
				}
				break;
			case 5:
				_localctx = new ForInStatementContext(_localctx);
				enterOuterAlt(_localctx, 5);
				{
				setState(227);
				match(For);
				setState(228);
				match(OpenParen);
				setState(229);
				singleExpression(0);
				setState(230);
				match(In);
				setState(231);
				expressionSequence();
				setState(232);
				match(CloseParen);
				setState(233);
				statement();
				}
				break;
			case 6:
				_localctx = new ForVarInStatementContext(_localctx);
				enterOuterAlt(_localctx, 6);
				{
				setState(235);
				match(For);
				setState(236);
				match(OpenParen);
				setState(237);
				match(Var);
				setState(238);
				variableDeclaration();
				setState(239);
				match(In);
				setState(240);
				expressionSequence();
				setState(241);
				match(CloseParen);
				setState(242);
				statement();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ContinueStatementContext extends ParserRuleContext {
		public TerminalNode Continue() { return getToken(ECMAScriptParser.Continue, 0); }
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public TerminalNode Identifier() { return getToken(ECMAScriptParser.Identifier, 0); }
		public ContinueStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_continueStatement; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitContinueStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ContinueStatementContext continueStatement() throws RecognitionException {
		ContinueStatementContext _localctx = new ContinueStatementContext(_ctx, getState());
		enterRule(_localctx, 30, RULE_continueStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(246);
			match(Continue);
			setState(249);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,11,_ctx) ) {
			case 1:
				{
				setState(247);
				if (!(!here(LineTerminator))) throw new FailedPredicateException(this, "!here(LineTerminator)");
				setState(248);
				match(Identifier);
				}
				break;
			}
			setState(251);
			eos();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class BreakStatementContext extends ParserRuleContext {
		public TerminalNode Break() { return getToken(ECMAScriptParser.Break, 0); }
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public TerminalNode Identifier() { return getToken(ECMAScriptParser.Identifier, 0); }
		public BreakStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_breakStatement; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitBreakStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final BreakStatementContext breakStatement() throws RecognitionException {
		BreakStatementContext _localctx = new BreakStatementContext(_ctx, getState());
		enterRule(_localctx, 32, RULE_breakStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(253);
			match(Break);
			setState(256);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,12,_ctx) ) {
			case 1:
				{
				setState(254);
				if (!(!here(LineTerminator))) throw new FailedPredicateException(this, "!here(LineTerminator)");
				setState(255);
				match(Identifier);
				}
				break;
			}
			setState(258);
			eos();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ReturnStatementContext extends ParserRuleContext {
		public TerminalNode Return() { return getToken(ECMAScriptParser.Return, 0); }
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public ExpressionSequenceContext expressionSequence() {
			return getRuleContext(ExpressionSequenceContext.class,0);
		}
		public ReturnStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_returnStatement; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitReturnStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ReturnStatementContext returnStatement() throws RecognitionException {
		ReturnStatementContext _localctx = new ReturnStatementContext(_ctx, getState());
		enterRule(_localctx, 34, RULE_returnStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(260);
			match(Return);
			setState(263);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,13,_ctx) ) {
			case 1:
				{
				setState(261);
				if (!(!here(LineTerminator))) throw new FailedPredicateException(this, "!here(LineTerminator)");
				setState(262);
				expressionSequence();
				}
				break;
			}
			setState(265);
			eos();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class WithStatementContext extends ParserRuleContext {
		public TerminalNode With() { return getToken(ECMAScriptParser.With, 0); }
		public ExpressionSequenceContext expressionSequence() {
			return getRuleContext(ExpressionSequenceContext.class,0);
		}
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public WithStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_withStatement; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitWithStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final WithStatementContext withStatement() throws RecognitionException {
		WithStatementContext _localctx = new WithStatementContext(_ctx, getState());
		enterRule(_localctx, 36, RULE_withStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(267);
			match(With);
			setState(268);
			match(OpenParen);
			setState(269);
			expressionSequence();
			setState(270);
			match(CloseParen);
			setState(271);
			statement();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class SwitchStatementContext extends ParserRuleContext {
		public TerminalNode Switch() { return getToken(ECMAScriptParser.Switch, 0); }
		public ExpressionSequenceContext expressionSequence() {
			return getRuleContext(ExpressionSequenceContext.class,0);
		}
		public CaseBlockContext caseBlock() {
			return getRuleContext(CaseBlockContext.class,0);
		}
		public SwitchStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_switchStatement; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitSwitchStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SwitchStatementContext switchStatement() throws RecognitionException {
		SwitchStatementContext _localctx = new SwitchStatementContext(_ctx, getState());
		enterRule(_localctx, 38, RULE_switchStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(273);
			match(Switch);
			setState(274);
			match(OpenParen);
			setState(275);
			expressionSequence();
			setState(276);
			match(CloseParen);
			setState(277);
			caseBlock();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class CaseBlockContext extends ParserRuleContext {
		public List<CaseClausesContext> caseClauses() {
			return getRuleContexts(CaseClausesContext.class);
		}
		public CaseClausesContext caseClauses(int i) {
			return getRuleContext(CaseClausesContext.class,i);
		}
		public DefaultClauseContext defaultClause() {
			return getRuleContext(DefaultClauseContext.class,0);
		}
		public CaseBlockContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_caseBlock; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitCaseBlock(this);
			else return visitor.visitChildren(this);
		}
	}

	public final CaseBlockContext caseBlock() throws RecognitionException {
		CaseBlockContext _localctx = new CaseBlockContext(_ctx, getState());
		enterRule(_localctx, 40, RULE_caseBlock);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(279);
			match(OpenBrace);
			setState(281);
			_la = _input.LA(1);
			if (_la==Case) {
				{
				setState(280);
				caseClauses();
				}
			}

			setState(287);
			_la = _input.LA(1);
			if (_la==Default) {
				{
				setState(283);
				defaultClause();
				setState(285);
				_la = _input.LA(1);
				if (_la==Case) {
					{
					setState(284);
					caseClauses();
					}
				}

				}
			}

			setState(289);
			match(CloseBrace);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class CaseClausesContext extends ParserRuleContext {
		public List<CaseClauseContext> caseClause() {
			return getRuleContexts(CaseClauseContext.class);
		}
		public CaseClauseContext caseClause(int i) {
			return getRuleContext(CaseClauseContext.class,i);
		}
		public CaseClausesContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_caseClauses; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitCaseClauses(this);
			else return visitor.visitChildren(this);
		}
	}

	public final CaseClausesContext caseClauses() throws RecognitionException {
		CaseClausesContext _localctx = new CaseClausesContext(_ctx, getState());
		enterRule(_localctx, 42, RULE_caseClauses);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(292); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(291);
				caseClause();
				}
				}
				setState(294); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==Case );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class CaseClauseContext extends ParserRuleContext {
		public TerminalNode Case() { return getToken(ECMAScriptParser.Case, 0); }
		public ExpressionSequenceContext expressionSequence() {
			return getRuleContext(ExpressionSequenceContext.class,0);
		}
		public StatementListContext statementList() {
			return getRuleContext(StatementListContext.class,0);
		}
		public CaseClauseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_caseClause; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitCaseClause(this);
			else return visitor.visitChildren(this);
		}
	}

	public final CaseClauseContext caseClause() throws RecognitionException {
		CaseClauseContext _localctx = new CaseClauseContext(_ctx, getState());
		enterRule(_localctx, 44, RULE_caseClause);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(296);
			match(Case);
			setState(297);
			expressionSequence();
			setState(298);
			match(Colon);
			setState(300);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,18,_ctx) ) {
			case 1:
				{
				setState(299);
				statementList();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class DefaultClauseContext extends ParserRuleContext {
		public TerminalNode Default() { return getToken(ECMAScriptParser.Default, 0); }
		public StatementListContext statementList() {
			return getRuleContext(StatementListContext.class,0);
		}
		public DefaultClauseContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_defaultClause; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitDefaultClause(this);
			else return visitor.visitChildren(this);
		}
	}

	public final DefaultClauseContext defaultClause() throws RecognitionException {
		DefaultClauseContext _localctx = new DefaultClauseContext(_ctx, getState());
		enterRule(_localctx, 46, RULE_defaultClause);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(302);
			match(Default);
			setState(303);
			match(Colon);
			setState(305);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,19,_ctx) ) {
			case 1:
				{
				setState(304);
				statementList();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LabelledStatementContext extends ParserRuleContext {
		public TerminalNode Identifier() { return getToken(ECMAScriptParser.Identifier, 0); }
		public StatementContext statement() {
			return getRuleContext(StatementContext.class,0);
		}
		public LabelledStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_labelledStatement; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitLabelledStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final LabelledStatementContext labelledStatement() throws RecognitionException {
		LabelledStatementContext _localctx = new LabelledStatementContext(_ctx, getState());
		enterRule(_localctx, 48, RULE_labelledStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(307);
			match(Identifier);
			setState(308);
			match(Colon);
			setState(309);
			statement();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ThrowStatementContext extends ParserRuleContext {
		public TerminalNode Throw() { return getToken(ECMAScriptParser.Throw, 0); }
		public ExpressionSequenceContext expressionSequence() {
			return getRuleContext(ExpressionSequenceContext.class,0);
		}
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public ThrowStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_throwStatement; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitThrowStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ThrowStatementContext throwStatement() throws RecognitionException {
		ThrowStatementContext _localctx = new ThrowStatementContext(_ctx, getState());
		enterRule(_localctx, 50, RULE_throwStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(311);
			match(Throw);
			setState(312);
			if (!(!here(LineTerminator))) throw new FailedPredicateException(this, "!here(LineTerminator)");
			setState(313);
			expressionSequence();
			setState(314);
			eos();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class TryStatementContext extends ParserRuleContext {
		public TerminalNode Try() { return getToken(ECMAScriptParser.Try, 0); }
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public CatchProductionContext catchProduction() {
			return getRuleContext(CatchProductionContext.class,0);
		}
		public FinallyProductionContext finallyProduction() {
			return getRuleContext(FinallyProductionContext.class,0);
		}
		public TryStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_tryStatement; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitTryStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final TryStatementContext tryStatement() throws RecognitionException {
		TryStatementContext _localctx = new TryStatementContext(_ctx, getState());
		enterRule(_localctx, 52, RULE_tryStatement);
		try {
			setState(329);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,20,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(316);
				match(Try);
				setState(317);
				block();
				setState(318);
				catchProduction();
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(320);
				match(Try);
				setState(321);
				block();
				setState(322);
				finallyProduction();
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(324);
				match(Try);
				setState(325);
				block();
				setState(326);
				catchProduction();
				setState(327);
				finallyProduction();
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class CatchProductionContext extends ParserRuleContext {
		public TerminalNode Catch() { return getToken(ECMAScriptParser.Catch, 0); }
		public TerminalNode Identifier() { return getToken(ECMAScriptParser.Identifier, 0); }
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public CatchProductionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_catchProduction; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitCatchProduction(this);
			else return visitor.visitChildren(this);
		}
	}

	public final CatchProductionContext catchProduction() throws RecognitionException {
		CatchProductionContext _localctx = new CatchProductionContext(_ctx, getState());
		enterRule(_localctx, 54, RULE_catchProduction);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(331);
			match(Catch);
			setState(332);
			match(OpenParen);
			setState(333);
			match(Identifier);
			setState(334);
			match(CloseParen);
			setState(335);
			block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FinallyProductionContext extends ParserRuleContext {
		public TerminalNode Finally() { return getToken(ECMAScriptParser.Finally, 0); }
		public BlockContext block() {
			return getRuleContext(BlockContext.class,0);
		}
		public FinallyProductionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_finallyProduction; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitFinallyProduction(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FinallyProductionContext finallyProduction() throws RecognitionException {
		FinallyProductionContext _localctx = new FinallyProductionContext(_ctx, getState());
		enterRule(_localctx, 56, RULE_finallyProduction);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(337);
			match(Finally);
			setState(338);
			block();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class DebuggerStatementContext extends ParserRuleContext {
		public TerminalNode Debugger() { return getToken(ECMAScriptParser.Debugger, 0); }
		public EosContext eos() {
			return getRuleContext(EosContext.class,0);
		}
		public DebuggerStatementContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_debuggerStatement; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitDebuggerStatement(this);
			else return visitor.visitChildren(this);
		}
	}

	public final DebuggerStatementContext debuggerStatement() throws RecognitionException {
		DebuggerStatementContext _localctx = new DebuggerStatementContext(_ctx, getState());
		enterRule(_localctx, 58, RULE_debuggerStatement);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(340);
			match(Debugger);
			setState(341);
			eos();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FunctionDeclarationContext extends ParserRuleContext {
		public TerminalNode Function() { return getToken(ECMAScriptParser.Function, 0); }
		public TerminalNode Identifier() { return getToken(ECMAScriptParser.Identifier, 0); }
		public FunctionBodyContext functionBody() {
			return getRuleContext(FunctionBodyContext.class,0);
		}
		public FormalParameterListContext formalParameterList() {
			return getRuleContext(FormalParameterListContext.class,0);
		}
		public FunctionDeclarationContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionDeclaration; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitFunctionDeclaration(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FunctionDeclarationContext functionDeclaration() throws RecognitionException {
		FunctionDeclarationContext _localctx = new FunctionDeclarationContext(_ctx, getState());
		enterRule(_localctx, 60, RULE_functionDeclaration);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(343);
			match(Function);
			setState(344);
			match(Identifier);
			setState(345);
			match(OpenParen);
			setState(347);
			_la = _input.LA(1);
			if (_la==Identifier) {
				{
				setState(346);
				formalParameterList();
				}
			}

			setState(349);
			match(CloseParen);
			setState(350);
			match(OpenBrace);
			setState(351);
			functionBody();
			setState(352);
			match(CloseBrace);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FormalParameterListContext extends ParserRuleContext {
		public List<TerminalNode> Identifier() { return getTokens(ECMAScriptParser.Identifier); }
		public TerminalNode Identifier(int i) {
			return getToken(ECMAScriptParser.Identifier, i);
		}
		public FormalParameterListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_formalParameterList; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitFormalParameterList(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FormalParameterListContext formalParameterList() throws RecognitionException {
		FormalParameterListContext _localctx = new FormalParameterListContext(_ctx, getState());
		enterRule(_localctx, 62, RULE_formalParameterList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(354);
			match(Identifier);
			setState(359);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Comma) {
				{
				{
				setState(355);
				match(Comma);
				setState(356);
				match(Identifier);
				}
				}
				setState(361);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FunctionBodyContext extends ParserRuleContext {
		public SourceElementsContext sourceElements() {
			return getRuleContext(SourceElementsContext.class,0);
		}
		public FunctionBodyContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_functionBody; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitFunctionBody(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FunctionBodyContext functionBody() throws RecognitionException {
		FunctionBodyContext _localctx = new FunctionBodyContext(_ctx, getState());
		enterRule(_localctx, 64, RULE_functionBody);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(363);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,23,_ctx) ) {
			case 1:
				{
				setState(362);
				sourceElements();
				}
				break;
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ArrayLiteralContext extends ParserRuleContext {
		public ElementListContext elementList() {
			return getRuleContext(ElementListContext.class,0);
		}
		public ElisionContext elision() {
			return getRuleContext(ElisionContext.class,0);
		}
		public ArrayLiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arrayLiteral; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitArrayLiteral(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ArrayLiteralContext arrayLiteral() throws RecognitionException {
		ArrayLiteralContext _localctx = new ArrayLiteralContext(_ctx, getState());
		enterRule(_localctx, 66, RULE_arrayLiteral);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(365);
			match(OpenBracket);
			setState(367);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,24,_ctx) ) {
			case 1:
				{
				setState(366);
				elementList();
				}
				break;
			}
			setState(370);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,25,_ctx) ) {
			case 1:
				{
				setState(369);
				match(Comma);
				}
				break;
			}
			setState(373);
			_la = _input.LA(1);
			if (_la==Comma) {
				{
				setState(372);
				elision();
				}
			}

			setState(375);
			match(CloseBracket);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ElementListContext extends ParserRuleContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public List<ElisionContext> elision() {
			return getRuleContexts(ElisionContext.class);
		}
		public ElisionContext elision(int i) {
			return getRuleContext(ElisionContext.class,i);
		}
		public ElementListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elementList; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitElementList(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ElementListContext elementList() throws RecognitionException {
		ElementListContext _localctx = new ElementListContext(_ctx, getState());
		enterRule(_localctx, 68, RULE_elementList);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(378);
			_la = _input.LA(1);
			if (_la==Comma) {
				{
				setState(377);
				elision();
				}
			}

			setState(380);
			singleExpression(0);
			setState(388);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,29,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(381);
					match(Comma);
					setState(383);
					_la = _input.LA(1);
					if (_la==Comma) {
						{
						setState(382);
						elision();
						}
					}

					setState(385);
					singleExpression(0);
					}
					} 
				}
				setState(390);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,29,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ElisionContext extends ParserRuleContext {
		public ElisionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_elision; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitElision(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ElisionContext elision() throws RecognitionException {
		ElisionContext _localctx = new ElisionContext(_ctx, getState());
		enterRule(_localctx, 70, RULE_elision);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(392); 
			_errHandler.sync(this);
			_la = _input.LA(1);
			do {
				{
				{
				setState(391);
				match(Comma);
				}
				}
				setState(394); 
				_errHandler.sync(this);
				_la = _input.LA(1);
			} while ( _la==Comma );
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ObjectLiteralContext extends ParserRuleContext {
		public PropertyNameAndValueListContext propertyNameAndValueList() {
			return getRuleContext(PropertyNameAndValueListContext.class,0);
		}
		public ObjectLiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_objectLiteral; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitObjectLiteral(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ObjectLiteralContext objectLiteral() throws RecognitionException {
		ObjectLiteralContext _localctx = new ObjectLiteralContext(_ctx, getState());
		enterRule(_localctx, 72, RULE_objectLiteral);
		int _la;
		try {
			setState(405);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,32,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(396);
				match(OpenBrace);
				setState(397);
				match(CloseBrace);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(398);
				match(OpenBrace);
				setState(399);
				propertyNameAndValueList();
				setState(401);
				_la = _input.LA(1);
				if (_la==Comma) {
					{
					setState(400);
					match(Comma);
					}
				}

				setState(403);
				match(CloseBrace);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class PropertyNameAndValueListContext extends ParserRuleContext {
		public List<PropertyAssignmentContext> propertyAssignment() {
			return getRuleContexts(PropertyAssignmentContext.class);
		}
		public PropertyAssignmentContext propertyAssignment(int i) {
			return getRuleContext(PropertyAssignmentContext.class,i);
		}
		public PropertyNameAndValueListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_propertyNameAndValueList; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitPropertyNameAndValueList(this);
			else return visitor.visitChildren(this);
		}
	}

	public final PropertyNameAndValueListContext propertyNameAndValueList() throws RecognitionException {
		PropertyNameAndValueListContext _localctx = new PropertyNameAndValueListContext(_ctx, getState());
		enterRule(_localctx, 74, RULE_propertyNameAndValueList);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(407);
			propertyAssignment();
			setState(412);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,33,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(408);
					match(Comma);
					setState(409);
					propertyAssignment();
					}
					} 
				}
				setState(414);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,33,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class PropertyAssignmentContext extends ParserRuleContext {
		public PropertyAssignmentContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_propertyAssignment; }
	 
		public PropertyAssignmentContext() { }
		public void copyFrom(PropertyAssignmentContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class PropertyExpressionAssignmentContext extends PropertyAssignmentContext {
		public PropertyNameContext propertyName() {
			return getRuleContext(PropertyNameContext.class,0);
		}
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public PropertyExpressionAssignmentContext(PropertyAssignmentContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitPropertyExpressionAssignment(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class PropertySetterContext extends PropertyAssignmentContext {
		public SetterContext setter() {
			return getRuleContext(SetterContext.class,0);
		}
		public PropertySetParameterListContext propertySetParameterList() {
			return getRuleContext(PropertySetParameterListContext.class,0);
		}
		public FunctionBodyContext functionBody() {
			return getRuleContext(FunctionBodyContext.class,0);
		}
		public PropertySetterContext(PropertyAssignmentContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitPropertySetter(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class PropertyGetterContext extends PropertyAssignmentContext {
		public GetterContext getter() {
			return getRuleContext(GetterContext.class,0);
		}
		public FunctionBodyContext functionBody() {
			return getRuleContext(FunctionBodyContext.class,0);
		}
		public PropertyGetterContext(PropertyAssignmentContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitPropertyGetter(this);
			else return visitor.visitChildren(this);
		}
	}

	public final PropertyAssignmentContext propertyAssignment() throws RecognitionException {
		PropertyAssignmentContext _localctx = new PropertyAssignmentContext(_ctx, getState());
		enterRule(_localctx, 76, RULE_propertyAssignment);
		try {
			setState(434);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,34,_ctx) ) {
			case 1:
				_localctx = new PropertyExpressionAssignmentContext(_localctx);
				enterOuterAlt(_localctx, 1);
				{
				setState(415);
				propertyName();
				setState(416);
				match(Colon);
				setState(417);
				singleExpression(0);
				}
				break;
			case 2:
				_localctx = new PropertyGetterContext(_localctx);
				enterOuterAlt(_localctx, 2);
				{
				setState(419);
				getter();
				setState(420);
				match(OpenParen);
				setState(421);
				match(CloseParen);
				setState(422);
				match(OpenBrace);
				setState(423);
				functionBody();
				setState(424);
				match(CloseBrace);
				}
				break;
			case 3:
				_localctx = new PropertySetterContext(_localctx);
				enterOuterAlt(_localctx, 3);
				{
				setState(426);
				setter();
				setState(427);
				match(OpenParen);
				setState(428);
				propertySetParameterList();
				setState(429);
				match(CloseParen);
				setState(430);
				match(OpenBrace);
				setState(431);
				functionBody();
				setState(432);
				match(CloseBrace);
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class PropertyNameContext extends ParserRuleContext {
		public IdentifierNameContext identifierName() {
			return getRuleContext(IdentifierNameContext.class,0);
		}
		public TerminalNode StringLiteral() { return getToken(ECMAScriptParser.StringLiteral, 0); }
		public NumericLiteralContext numericLiteral() {
			return getRuleContext(NumericLiteralContext.class,0);
		}
		public PropertyNameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_propertyName; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitPropertyName(this);
			else return visitor.visitChildren(this);
		}
	}

	public final PropertyNameContext propertyName() throws RecognitionException {
		PropertyNameContext _localctx = new PropertyNameContext(_ctx, getState());
		enterRule(_localctx, 78, RULE_propertyName);
		try {
			setState(439);
			switch (_input.LA(1)) {
			case NullLiteral:
			case BooleanLiteral:
			case Break:
			case Do:
			case Instanceof:
			case Typeof:
			case Case:
			case Else:
			case New:
			case Var:
			case Catch:
			case Finally:
			case Return:
			case Void:
			case Continue:
			case For:
			case Switch:
			case While:
			case Debugger:
			case Function:
			case This:
			case With:
			case Default:
			case If:
			case Throw:
			case Delete:
			case In:
			case Try:
			case Class:
			case Enum:
			case Extends:
			case Super:
			case Const:
			case Export:
			case Import:
			case Implements:
			case Let:
			case Private:
			case Public:
			case Interface:
			case Package:
			case Protected:
			case Static:
			case Yield:
			case Identifier:
				enterOuterAlt(_localctx, 1);
				{
				setState(436);
				identifierName();
				}
				break;
			case StringLiteral:
				enterOuterAlt(_localctx, 2);
				{
				setState(437);
				match(StringLiteral);
				}
				break;
			case DecimalLiteral:
			case HexIntegerLiteral:
			case OctalIntegerLiteral:
				enterOuterAlt(_localctx, 3);
				{
				setState(438);
				numericLiteral();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class PropertySetParameterListContext extends ParserRuleContext {
		public TerminalNode Identifier() { return getToken(ECMAScriptParser.Identifier, 0); }
		public PropertySetParameterListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_propertySetParameterList; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitPropertySetParameterList(this);
			else return visitor.visitChildren(this);
		}
	}

	public final PropertySetParameterListContext propertySetParameterList() throws RecognitionException {
		PropertySetParameterListContext _localctx = new PropertySetParameterListContext(_ctx, getState());
		enterRule(_localctx, 80, RULE_propertySetParameterList);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(441);
			match(Identifier);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ArgumentsContext extends ParserRuleContext {
		public ArgumentListContext argumentList() {
			return getRuleContext(ArgumentListContext.class,0);
		}
		public ArgumentsContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_arguments; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitArguments(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ArgumentsContext arguments() throws RecognitionException {
		ArgumentsContext _localctx = new ArgumentsContext(_ctx, getState());
		enterRule(_localctx, 82, RULE_arguments);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(443);
			match(OpenParen);
			setState(445);
			_la = _input.LA(1);
			if ((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << RegularExpressionLiteral) | (1L << OpenBracket) | (1L << OpenParen) | (1L << OpenBrace) | (1L << PlusPlus) | (1L << MinusMinus) | (1L << Plus) | (1L << Minus) | (1L << BitNot) | (1L << Not) | (1L << NullLiteral) | (1L << BooleanLiteral) | (1L << DecimalLiteral) | (1L << HexIntegerLiteral) | (1L << OctalIntegerLiteral) | (1L << Typeof) | (1L << New))) != 0) || ((((_la - 67)) & ~0x3f) == 0 && ((1L << (_la - 67)) & ((1L << (Void - 67)) | (1L << (Function - 67)) | (1L << (This - 67)) | (1L << (Delete - 67)) | (1L << (Identifier - 67)) | (1L << (StringLiteral - 67)))) != 0)) {
				{
				setState(444);
				argumentList();
				}
			}

			setState(447);
			match(CloseParen);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ArgumentListContext extends ParserRuleContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public ArgumentListContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_argumentList; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitArgumentList(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ArgumentListContext argumentList() throws RecognitionException {
		ArgumentListContext _localctx = new ArgumentListContext(_ctx, getState());
		enterRule(_localctx, 84, RULE_argumentList);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(449);
			singleExpression(0);
			setState(454);
			_errHandler.sync(this);
			_la = _input.LA(1);
			while (_la==Comma) {
				{
				{
				setState(450);
				match(Comma);
				setState(451);
				singleExpression(0);
				}
				}
				setState(456);
				_errHandler.sync(this);
				_la = _input.LA(1);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ExpressionSequenceContext extends ParserRuleContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public ExpressionSequenceContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_expressionSequence; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitExpressionSequence(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ExpressionSequenceContext expressionSequence() throws RecognitionException {
		ExpressionSequenceContext _localctx = new ExpressionSequenceContext(_ctx, getState());
		enterRule(_localctx, 86, RULE_expressionSequence);
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(457);
			singleExpression(0);
			setState(462);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,38,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					{
					{
					setState(458);
					match(Comma);
					setState(459);
					singleExpression(0);
					}
					} 
				}
				setState(464);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,38,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class SingleExpressionContext extends ParserRuleContext {
		public SingleExpressionContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_singleExpression; }
	 
		public SingleExpressionContext() { }
		public void copyFrom(SingleExpressionContext ctx) {
			super.copyFrom(ctx);
		}
	}
	public static class TernaryExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public TernaryExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitTernaryExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class LogicalAndExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public LogicalAndExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitLogicalAndExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class PreIncrementExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public PreIncrementExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitPreIncrementExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class ObjectLiteralExpressionContext extends SingleExpressionContext {
		public ObjectLiteralContext objectLiteral() {
			return getRuleContext(ObjectLiteralContext.class,0);
		}
		public ObjectLiteralExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitObjectLiteralExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class InExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public TerminalNode In() { return getToken(ECMAScriptParser.In, 0); }
		public InExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitInExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class LogicalOrExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public LogicalOrExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitLogicalOrExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class NotExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public NotExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitNotExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class PreDecreaseExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public PreDecreaseExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitPreDecreaseExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class ArgumentsExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public ArgumentsContext arguments() {
			return getRuleContext(ArgumentsContext.class,0);
		}
		public ArgumentsExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitArgumentsExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class ThisExpressionContext extends SingleExpressionContext {
		public TerminalNode This() { return getToken(ECMAScriptParser.This, 0); }
		public ThisExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitThisExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class FunctionExpressionContext extends SingleExpressionContext {
		public TerminalNode Function() { return getToken(ECMAScriptParser.Function, 0); }
		public FunctionBodyContext functionBody() {
			return getRuleContext(FunctionBodyContext.class,0);
		}
		public TerminalNode Identifier() { return getToken(ECMAScriptParser.Identifier, 0); }
		public FormalParameterListContext formalParameterList() {
			return getRuleContext(FormalParameterListContext.class,0);
		}
		public FunctionExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitFunctionExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class UnaryMinusExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public UnaryMinusExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitUnaryMinusExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class AssignmentExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public AssignmentExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitAssignmentExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class PostDecreaseExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public PostDecreaseExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitPostDecreaseExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class TypeofExpressionContext extends SingleExpressionContext {
		public TerminalNode Typeof() { return getToken(ECMAScriptParser.Typeof, 0); }
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public TypeofExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitTypeofExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class InstanceofExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public TerminalNode Instanceof() { return getToken(ECMAScriptParser.Instanceof, 0); }
		public InstanceofExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitInstanceofExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class UnaryPlusExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public UnaryPlusExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitUnaryPlusExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class DeleteExpressionContext extends SingleExpressionContext {
		public TerminalNode Delete() { return getToken(ECMAScriptParser.Delete, 0); }
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public DeleteExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitDeleteExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class EqualityExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public EqualityExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitEqualityExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class BitXOrExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public BitXOrExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitBitXOrExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class MultiplicativeExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public MultiplicativeExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitMultiplicativeExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class BitShiftExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public BitShiftExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitBitShiftExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class ParenthesizedExpressionContext extends SingleExpressionContext {
		public ExpressionSequenceContext expressionSequence() {
			return getRuleContext(ExpressionSequenceContext.class,0);
		}
		public ParenthesizedExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitParenthesizedExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class AdditiveExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public AdditiveExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitAdditiveExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class RelationalExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public RelationalExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitRelationalExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class PostIncrementExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public PostIncrementExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitPostIncrementExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class BitNotExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public BitNotExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitBitNotExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class NewExpressionContext extends SingleExpressionContext {
		public TerminalNode New() { return getToken(ECMAScriptParser.New, 0); }
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public ArgumentsContext arguments() {
			return getRuleContext(ArgumentsContext.class,0);
		}
		public NewExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitNewExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class LiteralExpressionContext extends SingleExpressionContext {
		public LiteralContext literal() {
			return getRuleContext(LiteralContext.class,0);
		}
		public LiteralExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitLiteralExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class ArrayLiteralExpressionContext extends SingleExpressionContext {
		public ArrayLiteralContext arrayLiteral() {
			return getRuleContext(ArrayLiteralContext.class,0);
		}
		public ArrayLiteralExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitArrayLiteralExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class MemberDotExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public IdentifierNameContext identifierName() {
			return getRuleContext(IdentifierNameContext.class,0);
		}
		public MemberDotExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitMemberDotExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class MemberIndexExpressionContext extends SingleExpressionContext {
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public ExpressionSequenceContext expressionSequence() {
			return getRuleContext(ExpressionSequenceContext.class,0);
		}
		public MemberIndexExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitMemberIndexExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class IdentifierExpressionContext extends SingleExpressionContext {
		public TerminalNode Identifier() { return getToken(ECMAScriptParser.Identifier, 0); }
		public IdentifierExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitIdentifierExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class BitAndExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public BitAndExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitBitAndExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class BitOrExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public BitOrExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitBitOrExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class AssignmentOperatorExpressionContext extends SingleExpressionContext {
		public List<SingleExpressionContext> singleExpression() {
			return getRuleContexts(SingleExpressionContext.class);
		}
		public SingleExpressionContext singleExpression(int i) {
			return getRuleContext(SingleExpressionContext.class,i);
		}
		public AssignmentOperatorContext assignmentOperator() {
			return getRuleContext(AssignmentOperatorContext.class,0);
		}
		public AssignmentOperatorExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitAssignmentOperatorExpression(this);
			else return visitor.visitChildren(this);
		}
	}
	public static class VoidExpressionContext extends SingleExpressionContext {
		public TerminalNode Void() { return getToken(ECMAScriptParser.Void, 0); }
		public SingleExpressionContext singleExpression() {
			return getRuleContext(SingleExpressionContext.class,0);
		}
		public VoidExpressionContext(SingleExpressionContext ctx) { copyFrom(ctx); }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitVoidExpression(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SingleExpressionContext singleExpression() throws RecognitionException {
		return singleExpression(0);
	}

	private SingleExpressionContext singleExpression(int _p) throws RecognitionException {
		ParserRuleContext _parentctx = _ctx;
		int _parentState = getState();
		SingleExpressionContext _localctx = new SingleExpressionContext(_ctx, _parentState);
		SingleExpressionContext _prevctx = _localctx;
		int _startState = 88;
		enterRecursionRule(_localctx, 88, RULE_singleExpression, _p);
		int _la;
		try {
			int _alt;
			enterOuterAlt(_localctx, 1);
			{
			setState(511);
			switch (_input.LA(1)) {
			case Function:
				{
				_localctx = new FunctionExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;

				setState(466);
				match(Function);
				setState(468);
				_la = _input.LA(1);
				if (_la==Identifier) {
					{
					setState(467);
					match(Identifier);
					}
				}

				setState(470);
				match(OpenParen);
				setState(472);
				_la = _input.LA(1);
				if (_la==Identifier) {
					{
					setState(471);
					formalParameterList();
					}
				}

				setState(474);
				match(CloseParen);
				setState(475);
				match(OpenBrace);
				setState(476);
				functionBody();
				setState(477);
				match(CloseBrace);
				}
				break;
			case New:
				{
				_localctx = new NewExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(479);
				match(New);
				setState(480);
				singleExpression(0);
				setState(482);
				_errHandler.sync(this);
				switch ( getInterpreter().adaptivePredict(_input,41,_ctx) ) {
				case 1:
					{
					setState(481);
					arguments();
					}
					break;
				}
				}
				break;
			case Delete:
				{
				_localctx = new DeleteExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(484);
				match(Delete);
				setState(485);
				singleExpression(30);
				}
				break;
			case Void:
				{
				_localctx = new VoidExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(486);
				match(Void);
				setState(487);
				singleExpression(29);
				}
				break;
			case Typeof:
				{
				_localctx = new TypeofExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(488);
				match(Typeof);
				setState(489);
				singleExpression(28);
				}
				break;
			case PlusPlus:
				{
				_localctx = new PreIncrementExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(490);
				match(PlusPlus);
				setState(491);
				singleExpression(27);
				}
				break;
			case MinusMinus:
				{
				_localctx = new PreDecreaseExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(492);
				match(MinusMinus);
				setState(493);
				singleExpression(26);
				}
				break;
			case Plus:
				{
				_localctx = new UnaryPlusExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(494);
				match(Plus);
				setState(495);
				singleExpression(25);
				}
				break;
			case Minus:
				{
				_localctx = new UnaryMinusExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(496);
				match(Minus);
				setState(497);
				singleExpression(24);
				}
				break;
			case BitNot:
				{
				_localctx = new BitNotExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(498);
				match(BitNot);
				setState(499);
				singleExpression(23);
				}
				break;
			case Not:
				{
				_localctx = new NotExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(500);
				match(Not);
				setState(501);
				singleExpression(22);
				}
				break;
			case This:
				{
				_localctx = new ThisExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(502);
				match(This);
				}
				break;
			case Identifier:
				{
				_localctx = new IdentifierExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(503);
				match(Identifier);
				}
				break;
			case RegularExpressionLiteral:
			case NullLiteral:
			case BooleanLiteral:
			case DecimalLiteral:
			case HexIntegerLiteral:
			case OctalIntegerLiteral:
			case StringLiteral:
				{
				_localctx = new LiteralExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(504);
				literal();
				}
				break;
			case OpenBracket:
				{
				_localctx = new ArrayLiteralExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(505);
				arrayLiteral();
				}
				break;
			case OpenBrace:
				{
				_localctx = new ObjectLiteralExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(506);
				objectLiteral();
				}
				break;
			case OpenParen:
				{
				_localctx = new ParenthesizedExpressionContext(_localctx);
				_ctx = _localctx;
				_prevctx = _localctx;
				setState(507);
				match(OpenParen);
				setState(508);
				expressionSequence();
				setState(509);
				match(CloseParen);
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
			_ctx.stop = _input.LT(-1);
			setState(580);
			_errHandler.sync(this);
			_alt = getInterpreter().adaptivePredict(_input,44,_ctx);
			while ( _alt!=2 && _alt!=org.antlr.v4.runtime.atn.ATN.INVALID_ALT_NUMBER ) {
				if ( _alt==1 ) {
					if ( _parseListeners!=null ) triggerExitRuleEvent();
					_prevctx = _localctx;
					{
					setState(578);
					_errHandler.sync(this);
					switch ( getInterpreter().adaptivePredict(_input,43,_ctx) ) {
					case 1:
						{
						_localctx = new MultiplicativeExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(513);
						if (!(precpred(_ctx, 21))) throw new FailedPredicateException(this, "precpred(_ctx, 21)");
						setState(514);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << Multiply) | (1L << Divide) | (1L << Modulus))) != 0)) ) {
						_errHandler.recoverInline(this);
						} else {
							consume();
						}
						setState(515);
						singleExpression(22);
						}
						break;
					case 2:
						{
						_localctx = new AdditiveExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(516);
						if (!(precpred(_ctx, 20))) throw new FailedPredicateException(this, "precpred(_ctx, 20)");
						setState(517);
						_la = _input.LA(1);
						if ( !(_la==Plus || _la==Minus) ) {
						_errHandler.recoverInline(this);
						} else {
							consume();
						}
						setState(518);
						singleExpression(21);
						}
						break;
					case 3:
						{
						_localctx = new BitShiftExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(519);
						if (!(precpred(_ctx, 19))) throw new FailedPredicateException(this, "precpred(_ctx, 19)");
						setState(520);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << RightShiftArithmetic) | (1L << LeftShiftArithmetic) | (1L << RightShiftLogical))) != 0)) ) {
						_errHandler.recoverInline(this);
						} else {
							consume();
						}
						setState(521);
						singleExpression(20);
						}
						break;
					case 4:
						{
						_localctx = new RelationalExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(522);
						if (!(precpred(_ctx, 18))) throw new FailedPredicateException(this, "precpred(_ctx, 18)");
						setState(523);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << LessThan) | (1L << MoreThan) | (1L << LessThanEquals) | (1L << GreaterThanEquals))) != 0)) ) {
						_errHandler.recoverInline(this);
						} else {
							consume();
						}
						setState(524);
						singleExpression(19);
						}
						break;
					case 5:
						{
						_localctx = new InstanceofExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(525);
						if (!(precpred(_ctx, 17))) throw new FailedPredicateException(this, "precpred(_ctx, 17)");
						setState(526);
						match(Instanceof);
						setState(527);
						singleExpression(18);
						}
						break;
					case 6:
						{
						_localctx = new InExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(528);
						if (!(precpred(_ctx, 16))) throw new FailedPredicateException(this, "precpred(_ctx, 16)");
						setState(529);
						match(In);
						setState(530);
						singleExpression(17);
						}
						break;
					case 7:
						{
						_localctx = new EqualityExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(531);
						if (!(precpred(_ctx, 15))) throw new FailedPredicateException(this, "precpred(_ctx, 15)");
						setState(532);
						_la = _input.LA(1);
						if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << Equals) | (1L << NotEquals) | (1L << IdentityEquals) | (1L << IdentityNotEquals))) != 0)) ) {
						_errHandler.recoverInline(this);
						} else {
							consume();
						}
						setState(533);
						singleExpression(16);
						}
						break;
					case 8:
						{
						_localctx = new BitAndExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(534);
						if (!(precpred(_ctx, 14))) throw new FailedPredicateException(this, "precpred(_ctx, 14)");
						setState(535);
						match(BitAnd);
						setState(536);
						singleExpression(15);
						}
						break;
					case 9:
						{
						_localctx = new BitXOrExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(537);
						if (!(precpred(_ctx, 13))) throw new FailedPredicateException(this, "precpred(_ctx, 13)");
						setState(538);
						match(BitXOr);
						setState(539);
						singleExpression(14);
						}
						break;
					case 10:
						{
						_localctx = new BitOrExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(540);
						if (!(precpred(_ctx, 12))) throw new FailedPredicateException(this, "precpred(_ctx, 12)");
						setState(541);
						match(BitOr);
						setState(542);
						singleExpression(13);
						}
						break;
					case 11:
						{
						_localctx = new LogicalAndExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(543);
						if (!(precpred(_ctx, 11))) throw new FailedPredicateException(this, "precpred(_ctx, 11)");
						setState(544);
						match(And);
						setState(545);
						singleExpression(12);
						}
						break;
					case 12:
						{
						_localctx = new LogicalOrExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(546);
						if (!(precpred(_ctx, 10))) throw new FailedPredicateException(this, "precpred(_ctx, 10)");
						setState(547);
						match(Or);
						setState(548);
						singleExpression(11);
						}
						break;
					case 13:
						{
						_localctx = new TernaryExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(549);
						if (!(precpred(_ctx, 9))) throw new FailedPredicateException(this, "precpred(_ctx, 9)");
						setState(550);
						match(QuestionMark);
						setState(551);
						singleExpression(0);
						setState(552);
						match(Colon);
						setState(553);
						singleExpression(10);
						}
						break;
					case 14:
						{
						_localctx = new AssignmentExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(555);
						if (!(precpred(_ctx, 8))) throw new FailedPredicateException(this, "precpred(_ctx, 8)");
						setState(556);
						match(Assign);
						setState(557);
						singleExpression(8);
						}
						break;
					case 15:
						{
						_localctx = new AssignmentOperatorExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(558);
						if (!(precpred(_ctx, 7))) throw new FailedPredicateException(this, "precpred(_ctx, 7)");
						setState(559);
						assignmentOperator();
						setState(560);
						singleExpression(7);
						}
						break;
					case 16:
						{
						_localctx = new MemberIndexExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(562);
						if (!(precpred(_ctx, 36))) throw new FailedPredicateException(this, "precpred(_ctx, 36)");
						setState(563);
						match(OpenBracket);
						setState(564);
						expressionSequence();
						setState(565);
						match(CloseBracket);
						}
						break;
					case 17:
						{
						_localctx = new MemberDotExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(567);
						if (!(precpred(_ctx, 35))) throw new FailedPredicateException(this, "precpred(_ctx, 35)");
						setState(568);
						match(Dot);
						setState(569);
						identifierName();
						}
						break;
					case 18:
						{
						_localctx = new ArgumentsExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(570);
						if (!(precpred(_ctx, 34))) throw new FailedPredicateException(this, "precpred(_ctx, 34)");
						setState(571);
						arguments();
						}
						break;
					case 19:
						{
						_localctx = new PostIncrementExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(572);
						if (!(precpred(_ctx, 32))) throw new FailedPredicateException(this, "precpred(_ctx, 32)");
						setState(573);
						if (!(!here(LineTerminator))) throw new FailedPredicateException(this, "!here(LineTerminator)");
						setState(574);
						match(PlusPlus);
						}
						break;
					case 20:
						{
						_localctx = new PostDecreaseExpressionContext(new SingleExpressionContext(_parentctx, _parentState));
						pushNewRecursionContext(_localctx, _startState, RULE_singleExpression);
						setState(575);
						if (!(precpred(_ctx, 31))) throw new FailedPredicateException(this, "precpred(_ctx, 31)");
						setState(576);
						if (!(!here(LineTerminator))) throw new FailedPredicateException(this, "!here(LineTerminator)");
						setState(577);
						match(MinusMinus);
						}
						break;
					}
					} 
				}
				setState(582);
				_errHandler.sync(this);
				_alt = getInterpreter().adaptivePredict(_input,44,_ctx);
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			unrollRecursionContexts(_parentctx);
		}
		return _localctx;
	}

	public static class AssignmentOperatorContext extends ParserRuleContext {
		public AssignmentOperatorContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_assignmentOperator; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitAssignmentOperator(this);
			else return visitor.visitChildren(this);
		}
	}

	public final AssignmentOperatorContext assignmentOperator() throws RecognitionException {
		AssignmentOperatorContext _localctx = new AssignmentOperatorContext(_ctx, getState());
		enterRule(_localctx, 90, RULE_assignmentOperator);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(583);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << MultiplyAssign) | (1L << DivideAssign) | (1L << ModulusAssign) | (1L << PlusAssign) | (1L << MinusAssign) | (1L << LeftShiftArithmeticAssign) | (1L << RightShiftArithmeticAssign) | (1L << RightShiftLogicalAssign) | (1L << BitAndAssign) | (1L << BitXorAssign) | (1L << BitOrAssign))) != 0)) ) {
			_errHandler.recoverInline(this);
			} else {
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class LiteralContext extends ParserRuleContext {
		public TerminalNode NullLiteral() { return getToken(ECMAScriptParser.NullLiteral, 0); }
		public TerminalNode BooleanLiteral() { return getToken(ECMAScriptParser.BooleanLiteral, 0); }
		public TerminalNode StringLiteral() { return getToken(ECMAScriptParser.StringLiteral, 0); }
		public TerminalNode RegularExpressionLiteral() { return getToken(ECMAScriptParser.RegularExpressionLiteral, 0); }
		public NumericLiteralContext numericLiteral() {
			return getRuleContext(NumericLiteralContext.class,0);
		}
		public LiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_literal; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitLiteral(this);
			else return visitor.visitChildren(this);
		}
	}

	public final LiteralContext literal() throws RecognitionException {
		LiteralContext _localctx = new LiteralContext(_ctx, getState());
		enterRule(_localctx, 92, RULE_literal);
		int _la;
		try {
			setState(587);
			switch (_input.LA(1)) {
			case RegularExpressionLiteral:
			case NullLiteral:
			case BooleanLiteral:
			case StringLiteral:
				enterOuterAlt(_localctx, 1);
				{
				setState(585);
				_la = _input.LA(1);
				if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << RegularExpressionLiteral) | (1L << NullLiteral) | (1L << BooleanLiteral))) != 0) || _la==StringLiteral) ) {
				_errHandler.recoverInline(this);
				} else {
					consume();
				}
				}
				break;
			case DecimalLiteral:
			case HexIntegerLiteral:
			case OctalIntegerLiteral:
				enterOuterAlt(_localctx, 2);
				{
				setState(586);
				numericLiteral();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class NumericLiteralContext extends ParserRuleContext {
		public TerminalNode DecimalLiteral() { return getToken(ECMAScriptParser.DecimalLiteral, 0); }
		public TerminalNode HexIntegerLiteral() { return getToken(ECMAScriptParser.HexIntegerLiteral, 0); }
		public TerminalNode OctalIntegerLiteral() { return getToken(ECMAScriptParser.OctalIntegerLiteral, 0); }
		public NumericLiteralContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_numericLiteral; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitNumericLiteral(this);
			else return visitor.visitChildren(this);
		}
	}

	public final NumericLiteralContext numericLiteral() throws RecognitionException {
		NumericLiteralContext _localctx = new NumericLiteralContext(_ctx, getState());
		enterRule(_localctx, 94, RULE_numericLiteral);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(589);
			_la = _input.LA(1);
			if ( !((((_la) & ~0x3f) == 0 && ((1L << _la) & ((1L << DecimalLiteral) | (1L << HexIntegerLiteral) | (1L << OctalIntegerLiteral))) != 0)) ) {
			_errHandler.recoverInline(this);
			} else {
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class IdentifierNameContext extends ParserRuleContext {
		public TerminalNode Identifier() { return getToken(ECMAScriptParser.Identifier, 0); }
		public ReservedWordContext reservedWord() {
			return getRuleContext(ReservedWordContext.class,0);
		}
		public IdentifierNameContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_identifierName; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitIdentifierName(this);
			else return visitor.visitChildren(this);
		}
	}

	public final IdentifierNameContext identifierName() throws RecognitionException {
		IdentifierNameContext _localctx = new IdentifierNameContext(_ctx, getState());
		enterRule(_localctx, 96, RULE_identifierName);
		try {
			setState(593);
			switch (_input.LA(1)) {
			case Identifier:
				enterOuterAlt(_localctx, 1);
				{
				setState(591);
				match(Identifier);
				}
				break;
			case NullLiteral:
			case BooleanLiteral:
			case Break:
			case Do:
			case Instanceof:
			case Typeof:
			case Case:
			case Else:
			case New:
			case Var:
			case Catch:
			case Finally:
			case Return:
			case Void:
			case Continue:
			case For:
			case Switch:
			case While:
			case Debugger:
			case Function:
			case This:
			case With:
			case Default:
			case If:
			case Throw:
			case Delete:
			case In:
			case Try:
			case Class:
			case Enum:
			case Extends:
			case Super:
			case Const:
			case Export:
			case Import:
			case Implements:
			case Let:
			case Private:
			case Public:
			case Interface:
			case Package:
			case Protected:
			case Static:
			case Yield:
				enterOuterAlt(_localctx, 2);
				{
				setState(592);
				reservedWord();
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class ReservedWordContext extends ParserRuleContext {
		public KeywordContext keyword() {
			return getRuleContext(KeywordContext.class,0);
		}
		public FutureReservedWordContext futureReservedWord() {
			return getRuleContext(FutureReservedWordContext.class,0);
		}
		public TerminalNode NullLiteral() { return getToken(ECMAScriptParser.NullLiteral, 0); }
		public TerminalNode BooleanLiteral() { return getToken(ECMAScriptParser.BooleanLiteral, 0); }
		public ReservedWordContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_reservedWord; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitReservedWord(this);
			else return visitor.visitChildren(this);
		}
	}

	public final ReservedWordContext reservedWord() throws RecognitionException {
		ReservedWordContext _localctx = new ReservedWordContext(_ctx, getState());
		enterRule(_localctx, 98, RULE_reservedWord);
		int _la;
		try {
			setState(598);
			switch (_input.LA(1)) {
			case Break:
			case Do:
			case Instanceof:
			case Typeof:
			case Case:
			case Else:
			case New:
			case Var:
			case Catch:
			case Finally:
			case Return:
			case Void:
			case Continue:
			case For:
			case Switch:
			case While:
			case Debugger:
			case Function:
			case This:
			case With:
			case Default:
			case If:
			case Throw:
			case Delete:
			case In:
			case Try:
				enterOuterAlt(_localctx, 1);
				{
				setState(595);
				keyword();
				}
				break;
			case Class:
			case Enum:
			case Extends:
			case Super:
			case Const:
			case Export:
			case Import:
			case Implements:
			case Let:
			case Private:
			case Public:
			case Interface:
			case Package:
			case Protected:
			case Static:
			case Yield:
				enterOuterAlt(_localctx, 2);
				{
				setState(596);
				futureReservedWord();
				}
				break;
			case NullLiteral:
			case BooleanLiteral:
				enterOuterAlt(_localctx, 3);
				{
				setState(597);
				_la = _input.LA(1);
				if ( !(_la==NullLiteral || _la==BooleanLiteral) ) {
				_errHandler.recoverInline(this);
				} else {
					consume();
				}
				}
				break;
			default:
				throw new NoViableAltException(this);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class KeywordContext extends ParserRuleContext {
		public TerminalNode Break() { return getToken(ECMAScriptParser.Break, 0); }
		public TerminalNode Do() { return getToken(ECMAScriptParser.Do, 0); }
		public TerminalNode Instanceof() { return getToken(ECMAScriptParser.Instanceof, 0); }
		public TerminalNode Typeof() { return getToken(ECMAScriptParser.Typeof, 0); }
		public TerminalNode Case() { return getToken(ECMAScriptParser.Case, 0); }
		public TerminalNode Else() { return getToken(ECMAScriptParser.Else, 0); }
		public TerminalNode New() { return getToken(ECMAScriptParser.New, 0); }
		public TerminalNode Var() { return getToken(ECMAScriptParser.Var, 0); }
		public TerminalNode Catch() { return getToken(ECMAScriptParser.Catch, 0); }
		public TerminalNode Finally() { return getToken(ECMAScriptParser.Finally, 0); }
		public TerminalNode Return() { return getToken(ECMAScriptParser.Return, 0); }
		public TerminalNode Void() { return getToken(ECMAScriptParser.Void, 0); }
		public TerminalNode Continue() { return getToken(ECMAScriptParser.Continue, 0); }
		public TerminalNode For() { return getToken(ECMAScriptParser.For, 0); }
		public TerminalNode Switch() { return getToken(ECMAScriptParser.Switch, 0); }
		public TerminalNode While() { return getToken(ECMAScriptParser.While, 0); }
		public TerminalNode Debugger() { return getToken(ECMAScriptParser.Debugger, 0); }
		public TerminalNode Function() { return getToken(ECMAScriptParser.Function, 0); }
		public TerminalNode This() { return getToken(ECMAScriptParser.This, 0); }
		public TerminalNode With() { return getToken(ECMAScriptParser.With, 0); }
		public TerminalNode Default() { return getToken(ECMAScriptParser.Default, 0); }
		public TerminalNode If() { return getToken(ECMAScriptParser.If, 0); }
		public TerminalNode Throw() { return getToken(ECMAScriptParser.Throw, 0); }
		public TerminalNode Delete() { return getToken(ECMAScriptParser.Delete, 0); }
		public TerminalNode In() { return getToken(ECMAScriptParser.In, 0); }
		public TerminalNode Try() { return getToken(ECMAScriptParser.Try, 0); }
		public KeywordContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_keyword; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitKeyword(this);
			else return visitor.visitChildren(this);
		}
	}

	public final KeywordContext keyword() throws RecognitionException {
		KeywordContext _localctx = new KeywordContext(_ctx, getState());
		enterRule(_localctx, 100, RULE_keyword);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(600);
			_la = _input.LA(1);
			if ( !(((((_la - 56)) & ~0x3f) == 0 && ((1L << (_la - 56)) & ((1L << (Break - 56)) | (1L << (Do - 56)) | (1L << (Instanceof - 56)) | (1L << (Typeof - 56)) | (1L << (Case - 56)) | (1L << (Else - 56)) | (1L << (New - 56)) | (1L << (Var - 56)) | (1L << (Catch - 56)) | (1L << (Finally - 56)) | (1L << (Return - 56)) | (1L << (Void - 56)) | (1L << (Continue - 56)) | (1L << (For - 56)) | (1L << (Switch - 56)) | (1L << (While - 56)) | (1L << (Debugger - 56)) | (1L << (Function - 56)) | (1L << (This - 56)) | (1L << (With - 56)) | (1L << (Default - 56)) | (1L << (If - 56)) | (1L << (Throw - 56)) | (1L << (Delete - 56)) | (1L << (In - 56)) | (1L << (Try - 56)))) != 0)) ) {
			_errHandler.recoverInline(this);
			} else {
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class FutureReservedWordContext extends ParserRuleContext {
		public TerminalNode Class() { return getToken(ECMAScriptParser.Class, 0); }
		public TerminalNode Enum() { return getToken(ECMAScriptParser.Enum, 0); }
		public TerminalNode Extends() { return getToken(ECMAScriptParser.Extends, 0); }
		public TerminalNode Super() { return getToken(ECMAScriptParser.Super, 0); }
		public TerminalNode Const() { return getToken(ECMAScriptParser.Const, 0); }
		public TerminalNode Export() { return getToken(ECMAScriptParser.Export, 0); }
		public TerminalNode Import() { return getToken(ECMAScriptParser.Import, 0); }
		public TerminalNode Implements() { return getToken(ECMAScriptParser.Implements, 0); }
		public TerminalNode Let() { return getToken(ECMAScriptParser.Let, 0); }
		public TerminalNode Private() { return getToken(ECMAScriptParser.Private, 0); }
		public TerminalNode Public() { return getToken(ECMAScriptParser.Public, 0); }
		public TerminalNode Interface() { return getToken(ECMAScriptParser.Interface, 0); }
		public TerminalNode Package() { return getToken(ECMAScriptParser.Package, 0); }
		public TerminalNode Protected() { return getToken(ECMAScriptParser.Protected, 0); }
		public TerminalNode Static() { return getToken(ECMAScriptParser.Static, 0); }
		public TerminalNode Yield() { return getToken(ECMAScriptParser.Yield, 0); }
		public FutureReservedWordContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_futureReservedWord; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitFutureReservedWord(this);
			else return visitor.visitChildren(this);
		}
	}

	public final FutureReservedWordContext futureReservedWord() throws RecognitionException {
		FutureReservedWordContext _localctx = new FutureReservedWordContext(_ctx, getState());
		enterRule(_localctx, 102, RULE_futureReservedWord);
		int _la;
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(602);
			_la = _input.LA(1);
			if ( !(((((_la - 82)) & ~0x3f) == 0 && ((1L << (_la - 82)) & ((1L << (Class - 82)) | (1L << (Enum - 82)) | (1L << (Extends - 82)) | (1L << (Super - 82)) | (1L << (Const - 82)) | (1L << (Export - 82)) | (1L << (Import - 82)) | (1L << (Implements - 82)) | (1L << (Let - 82)) | (1L << (Private - 82)) | (1L << (Public - 82)) | (1L << (Interface - 82)) | (1L << (Package - 82)) | (1L << (Protected - 82)) | (1L << (Static - 82)) | (1L << (Yield - 82)))) != 0)) ) {
			_errHandler.recoverInline(this);
			} else {
				consume();
			}
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class GetterContext extends ParserRuleContext {
		public TerminalNode Identifier() { return getToken(ECMAScriptParser.Identifier, 0); }
		public PropertyNameContext propertyName() {
			return getRuleContext(PropertyNameContext.class,0);
		}
		public GetterContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_getter; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitGetter(this);
			else return visitor.visitChildren(this);
		}
	}

	public final GetterContext getter() throws RecognitionException {
		GetterContext _localctx = new GetterContext(_ctx, getState());
		enterRule(_localctx, 104, RULE_getter);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(604);
			if (!(_input.LT(1).getText().equals("get"))) throw new FailedPredicateException(this, "_input.LT(1).getText().equals(\"get\")");
			setState(605);
			match(Identifier);
			setState(606);
			propertyName();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class SetterContext extends ParserRuleContext {
		public TerminalNode Identifier() { return getToken(ECMAScriptParser.Identifier, 0); }
		public PropertyNameContext propertyName() {
			return getRuleContext(PropertyNameContext.class,0);
		}
		public SetterContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_setter; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitSetter(this);
			else return visitor.visitChildren(this);
		}
	}

	public final SetterContext setter() throws RecognitionException {
		SetterContext _localctx = new SetterContext(_ctx, getState());
		enterRule(_localctx, 106, RULE_setter);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(608);
			if (!(_input.LT(1).getText().equals("set"))) throw new FailedPredicateException(this, "_input.LT(1).getText().equals(\"set\")");
			setState(609);
			match(Identifier);
			setState(610);
			propertyName();
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class EosContext extends ParserRuleContext {
		public TerminalNode SemiColon() { return getToken(ECMAScriptParser.SemiColon, 0); }
		public TerminalNode EOF() { return getToken(ECMAScriptParser.EOF, 0); }
		public EosContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_eos; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitEos(this);
			else return visitor.visitChildren(this);
		}
	}

	public final EosContext eos() throws RecognitionException {
		EosContext _localctx = new EosContext(_ctx, getState());
		enterRule(_localctx, 108, RULE_eos);
		try {
			setState(616);
			_errHandler.sync(this);
			switch ( getInterpreter().adaptivePredict(_input,48,_ctx) ) {
			case 1:
				enterOuterAlt(_localctx, 1);
				{
				setState(612);
				match(SemiColon);
				}
				break;
			case 2:
				enterOuterAlt(_localctx, 2);
				{
				setState(613);
				match(EOF);
				}
				break;
			case 3:
				enterOuterAlt(_localctx, 3);
				{
				setState(614);
				if (!(lineTerminatorAhead())) throw new FailedPredicateException(this, "lineTerminatorAhead()");
				}
				break;
			case 4:
				enterOuterAlt(_localctx, 4);
				{
				setState(615);
				if (!(_input.LT(1).getType() == CloseBrace)) throw new FailedPredicateException(this, "_input.LT(1).getType() == CloseBrace");
				}
				break;
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public static class EofContext extends ParserRuleContext {
		public TerminalNode EOF() { return getToken(ECMAScriptParser.EOF, 0); }
		public EofContext(ParserRuleContext parent, int invokingState) {
			super(parent, invokingState);
		}
		@Override public int getRuleIndex() { return RULE_eof; }
		@Override
		public <T> T accept(ParseTreeVisitor<? extends T> visitor) {
			if ( visitor instanceof ECMAScriptVisitor ) return ((ECMAScriptVisitor<? extends T>)visitor).visitEof(this);
			else return visitor.visitChildren(this);
		}
	}

	public final EofContext eof() throws RecognitionException {
		EofContext _localctx = new EofContext(_ctx, getState());
		enterRule(_localctx, 110, RULE_eof);
		try {
			enterOuterAlt(_localctx, 1);
			{
			setState(618);
			match(EOF);
			}
		}
		catch (RecognitionException re) {
			_localctx.exception = re;
			_errHandler.reportError(this, re);
			_errHandler.recover(this, re);
		}
		finally {
			exitRule();
		}
		return _localctx;
	}

	public boolean sempred(RuleContext _localctx, int ruleIndex, int predIndex) {
		switch (ruleIndex) {
		case 2:
			return sourceElement_sempred((SourceElementContext)_localctx, predIndex);
		case 3:
			return statement_sempred((StatementContext)_localctx, predIndex);
		case 15:
			return continueStatement_sempred((ContinueStatementContext)_localctx, predIndex);
		case 16:
			return breakStatement_sempred((BreakStatementContext)_localctx, predIndex);
		case 17:
			return returnStatement_sempred((ReturnStatementContext)_localctx, predIndex);
		case 25:
			return throwStatement_sempred((ThrowStatementContext)_localctx, predIndex);
		case 44:
			return singleExpression_sempred((SingleExpressionContext)_localctx, predIndex);
		case 52:
			return getter_sempred((GetterContext)_localctx, predIndex);
		case 53:
			return setter_sempred((SetterContext)_localctx, predIndex);
		case 54:
			return eos_sempred((EosContext)_localctx, predIndex);
		}
		return true;
	}
	private boolean sourceElement_sempred(SourceElementContext _localctx, int predIndex) {
		switch (predIndex) {
		case 0:
			return _input.LA(1) != Function;
		}
		return true;
	}
	private boolean statement_sempred(StatementContext _localctx, int predIndex) {
		switch (predIndex) {
		case 1:
			return _input.LA(1) != OpenBrace;
		}
		return true;
	}
	private boolean continueStatement_sempred(ContinueStatementContext _localctx, int predIndex) {
		switch (predIndex) {
		case 2:
			return !here(LineTerminator);
		}
		return true;
	}
	private boolean breakStatement_sempred(BreakStatementContext _localctx, int predIndex) {
		switch (predIndex) {
		case 3:
			return !here(LineTerminator);
		}
		return true;
	}
	private boolean returnStatement_sempred(ReturnStatementContext _localctx, int predIndex) {
		switch (predIndex) {
		case 4:
			return !here(LineTerminator);
		}
		return true;
	}
	private boolean throwStatement_sempred(ThrowStatementContext _localctx, int predIndex) {
		switch (predIndex) {
		case 5:
			return !here(LineTerminator);
		}
		return true;
	}
	private boolean singleExpression_sempred(SingleExpressionContext _localctx, int predIndex) {
		switch (predIndex) {
		case 6:
			return precpred(_ctx, 21);
		case 7:
			return precpred(_ctx, 20);
		case 8:
			return precpred(_ctx, 19);
		case 9:
			return precpred(_ctx, 18);
		case 10:
			return precpred(_ctx, 17);
		case 11:
			return precpred(_ctx, 16);
		case 12:
			return precpred(_ctx, 15);
		case 13:
			return precpred(_ctx, 14);
		case 14:
			return precpred(_ctx, 13);
		case 15:
			return precpred(_ctx, 12);
		case 16:
			return precpred(_ctx, 11);
		case 17:
			return precpred(_ctx, 10);
		case 18:
			return precpred(_ctx, 9);
		case 19:
			return precpred(_ctx, 8);
		case 20:
			return precpred(_ctx, 7);
		case 21:
			return precpred(_ctx, 36);
		case 22:
			return precpred(_ctx, 35);
		case 23:
			return precpred(_ctx, 34);
		case 24:
			return precpred(_ctx, 32);
		case 25:
			return !here(LineTerminator);
		case 26:
			return precpred(_ctx, 31);
		case 27:
			return !here(LineTerminator);
		}
		return true;
	}
	private boolean getter_sempred(GetterContext _localctx, int predIndex) {
		switch (predIndex) {
		case 28:
			return _input.LT(1).getText().equals("get");
		}
		return true;
	}
	private boolean setter_sempred(SetterContext _localctx, int predIndex) {
		switch (predIndex) {
		case 29:
			return _input.LT(1).getText().equals("set");
		}
		return true;
	}
	private boolean eos_sempred(EosContext _localctx, int predIndex) {
		switch (predIndex) {
		case 30:
			return lineTerminatorAhead();
		case 31:
			return _input.LT(1).getType() == CloseBrace;
		}
		return true;
	}

	public static final String _serializedATN =
		"\3\u0430\ud6d1\u8206\uad2d\u4417\uaef1\u8d80\uaadd\3i\u026f\4\2\t\2\4"+
		"\3\t\3\4\4\t\4\4\5\t\5\4\6\t\6\4\7\t\7\4\b\t\b\4\t\t\t\4\n\t\n\4\13\t"+
		"\13\4\f\t\f\4\r\t\r\4\16\t\16\4\17\t\17\4\20\t\20\4\21\t\21\4\22\t\22"+
		"\4\23\t\23\4\24\t\24\4\25\t\25\4\26\t\26\4\27\t\27\4\30\t\30\4\31\t\31"+
		"\4\32\t\32\4\33\t\33\4\34\t\34\4\35\t\35\4\36\t\36\4\37\t\37\4 \t \4!"+
		"\t!\4\"\t\"\4#\t#\4$\t$\4%\t%\4&\t&\4\'\t\'\4(\t(\4)\t)\4*\t*\4+\t+\4"+
		",\t,\4-\t-\4.\t.\4/\t/\4\60\t\60\4\61\t\61\4\62\t\62\4\63\t\63\4\64\t"+
		"\64\4\65\t\65\4\66\t\66\4\67\t\67\48\t8\49\t9\3\2\5\2t\n\2\3\2\3\2\3\3"+
		"\6\3y\n\3\r\3\16\3z\3\4\3\4\3\4\5\4\u0080\n\4\3\5\3\5\3\5\3\5\3\5\3\5"+
		"\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\3\5\5\5\u0092\n\5\3\6\3\6\5\6\u0096"+
		"\n\6\3\6\3\6\3\7\6\7\u009b\n\7\r\7\16\7\u009c\3\b\3\b\3\b\3\b\3\t\3\t"+
		"\3\t\7\t\u00a6\n\t\f\t\16\t\u00a9\13\t\3\n\3\n\5\n\u00ad\n\n\3\13\3\13"+
		"\3\13\3\f\3\f\3\r\3\r\3\r\3\16\3\16\3\16\3\16\3\16\3\16\3\16\5\16\u00be"+
		"\n\16\3\17\5\17\u00c1\n\17\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20"+
		"\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20"+
		"\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20"+
		"\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20\3\20"+
		"\3\20\5\20\u00f7\n\20\3\21\3\21\3\21\5\21\u00fc\n\21\3\21\3\21\3\22\3"+
		"\22\3\22\5\22\u0103\n\22\3\22\3\22\3\23\3\23\3\23\5\23\u010a\n\23\3\23"+
		"\3\23\3\24\3\24\3\24\3\24\3\24\3\24\3\25\3\25\3\25\3\25\3\25\3\25\3\26"+
		"\3\26\5\26\u011c\n\26\3\26\3\26\5\26\u0120\n\26\5\26\u0122\n\26\3\26\3"+
		"\26\3\27\6\27\u0127\n\27\r\27\16\27\u0128\3\30\3\30\3\30\3\30\5\30\u012f"+
		"\n\30\3\31\3\31\3\31\5\31\u0134\n\31\3\32\3\32\3\32\3\32\3\33\3\33\3\33"+
		"\3\33\3\33\3\34\3\34\3\34\3\34\3\34\3\34\3\34\3\34\3\34\3\34\3\34\3\34"+
		"\3\34\5\34\u014c\n\34\3\35\3\35\3\35\3\35\3\35\3\35\3\36\3\36\3\36\3\37"+
		"\3\37\3\37\3 \3 \3 \3 \5 \u015e\n \3 \3 \3 \3 \3 \3!\3!\3!\7!\u0168\n"+
		"!\f!\16!\u016b\13!\3\"\5\"\u016e\n\"\3#\3#\5#\u0172\n#\3#\5#\u0175\n#"+
		"\3#\5#\u0178\n#\3#\3#\3$\5$\u017d\n$\3$\3$\3$\5$\u0182\n$\3$\7$\u0185"+
		"\n$\f$\16$\u0188\13$\3%\6%\u018b\n%\r%\16%\u018c\3&\3&\3&\3&\3&\5&\u0194"+
		"\n&\3&\3&\5&\u0198\n&\3\'\3\'\3\'\7\'\u019d\n\'\f\'\16\'\u01a0\13\'\3"+
		"(\3(\3(\3(\3(\3(\3(\3(\3(\3(\3(\3(\3(\3(\3(\3(\3(\3(\3(\5(\u01b5\n(\3"+
		")\3)\3)\5)\u01ba\n)\3*\3*\3+\3+\5+\u01c0\n+\3+\3+\3,\3,\3,\7,\u01c7\n"+
		",\f,\16,\u01ca\13,\3-\3-\3-\7-\u01cf\n-\f-\16-\u01d2\13-\3.\3.\3.\5.\u01d7"+
		"\n.\3.\3.\5.\u01db\n.\3.\3.\3.\3.\3.\3.\3.\3.\5.\u01e5\n.\3.\3.\3.\3."+
		"\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3."+
		"\5.\u0202\n.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3."+
		"\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3."+
		"\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3.\3."+
		"\7.\u0245\n.\f.\16.\u0248\13.\3/\3/\3\60\3\60\5\60\u024e\n\60\3\61\3\61"+
		"\3\62\3\62\5\62\u0254\n\62\3\63\3\63\3\63\5\63\u0259\n\63\3\64\3\64\3"+
		"\65\3\65\3\66\3\66\3\66\3\66\3\67\3\67\3\67\3\67\38\38\38\38\58\u026b"+
		"\n8\39\39\39\2\3Z:\2\4\6\b\n\f\16\20\22\24\26\30\32\34\36 \"$&(*,.\60"+
		"\62\64\668:<>@BDFHJLNPRTVXZ\\^`bdfhjlnp\2\r\3\2\27\31\3\2\23\24\3\2\32"+
		"\34\3\2\35 \3\2!$\3\2*\64\5\2\3\3\65\66ee\3\2\679\3\2\65\66\3\2:S\3\2"+
		"Tc\u029f\2s\3\2\2\2\4x\3\2\2\2\6\177\3\2\2\2\b\u0091\3\2\2\2\n\u0093\3"+
		"\2\2\2\f\u009a\3\2\2\2\16\u009e\3\2\2\2\20\u00a2\3\2\2\2\22\u00aa\3\2"+
		"\2\2\24\u00ae\3\2\2\2\26\u00b1\3\2\2\2\30\u00b3\3\2\2\2\32\u00b6\3\2\2"+
		"\2\34\u00c0\3\2\2\2\36\u00f6\3\2\2\2 \u00f8\3\2\2\2\"\u00ff\3\2\2\2$\u0106"+
		"\3\2\2\2&\u010d\3\2\2\2(\u0113\3\2\2\2*\u0119\3\2\2\2,\u0126\3\2\2\2."+
		"\u012a\3\2\2\2\60\u0130\3\2\2\2\62\u0135\3\2\2\2\64\u0139\3\2\2\2\66\u014b"+
		"\3\2\2\28\u014d\3\2\2\2:\u0153\3\2\2\2<\u0156\3\2\2\2>\u0159\3\2\2\2@"+
		"\u0164\3\2\2\2B\u016d\3\2\2\2D\u016f\3\2\2\2F\u017c\3\2\2\2H\u018a\3\2"+
		"\2\2J\u0197\3\2\2\2L\u0199\3\2\2\2N\u01b4\3\2\2\2P\u01b9\3\2\2\2R\u01bb"+
		"\3\2\2\2T\u01bd\3\2\2\2V\u01c3\3\2\2\2X\u01cb\3\2\2\2Z\u0201\3\2\2\2\\"+
		"\u0249\3\2\2\2^\u024d\3\2\2\2`\u024f\3\2\2\2b\u0253\3\2\2\2d\u0258\3\2"+
		"\2\2f\u025a\3\2\2\2h\u025c\3\2\2\2j\u025e\3\2\2\2l\u0262\3\2\2\2n\u026a"+
		"\3\2\2\2p\u026c\3\2\2\2rt\5\4\3\2sr\3\2\2\2st\3\2\2\2tu\3\2\2\2uv\7\2"+
		"\2\3v\3\3\2\2\2wy\5\6\4\2xw\3\2\2\2yz\3\2\2\2zx\3\2\2\2z{\3\2\2\2{\5\3"+
		"\2\2\2|}\6\4\2\2}\u0080\5\b\5\2~\u0080\5> \2\177|\3\2\2\2\177~\3\2\2\2"+
		"\u0080\7\3\2\2\2\u0081\u0092\5\n\6\2\u0082\u0092\5\16\b\2\u0083\u0092"+
		"\5\26\f\2\u0084\u0085\6\5\3\2\u0085\u0092\5\30\r\2\u0086\u0092\5\32\16"+
		"\2\u0087\u0092\5\36\20\2\u0088\u0092\5 \21\2\u0089\u0092\5\"\22\2\u008a"+
		"\u0092\5$\23\2\u008b\u0092\5&\24\2\u008c\u0092\5\62\32\2\u008d\u0092\5"+
		"(\25\2\u008e\u0092\5\64\33\2\u008f\u0092\5\66\34\2\u0090\u0092\5<\37\2"+
		"\u0091\u0081\3\2\2\2\u0091\u0082\3\2\2\2\u0091\u0083\3\2\2\2\u0091\u0084"+
		"\3\2\2\2\u0091\u0086\3\2\2\2\u0091\u0087\3\2\2\2\u0091\u0088\3\2\2\2\u0091"+
		"\u0089\3\2\2\2\u0091\u008a\3\2\2\2\u0091\u008b\3\2\2\2\u0091\u008c\3\2"+
		"\2\2\u0091\u008d\3\2\2\2\u0091\u008e\3\2\2\2\u0091\u008f\3\2\2\2\u0091"+
		"\u0090\3\2\2\2\u0092\t\3\2\2\2\u0093\u0095\7\t\2\2\u0094\u0096\5\f\7\2"+
		"\u0095\u0094\3\2\2\2\u0095\u0096\3\2\2\2\u0096\u0097\3\2\2\2\u0097\u0098"+
		"\7\n\2\2\u0098\13\3\2\2\2\u0099\u009b\5\b\5\2\u009a\u0099\3\2\2\2\u009b"+
		"\u009c\3\2\2\2\u009c\u009a\3\2\2\2\u009c\u009d\3\2\2\2\u009d\r\3\2\2\2"+
		"\u009e\u009f\7A\2\2\u009f\u00a0\5\20\t\2\u00a0\u00a1\5n8\2\u00a1\17\3"+
		"\2\2\2\u00a2\u00a7\5\22\n\2\u00a3\u00a4\7\f\2\2\u00a4\u00a6\5\22\n\2\u00a5"+
		"\u00a3\3\2\2\2\u00a6\u00a9\3\2\2\2\u00a7\u00a5\3\2\2\2\u00a7\u00a8\3\2"+
		"\2\2\u00a8\21\3\2\2\2\u00a9\u00a7\3\2\2\2\u00aa\u00ac\7d\2\2\u00ab\u00ad"+
		"\5\24\13\2\u00ac\u00ab\3\2\2\2\u00ac\u00ad\3\2\2\2\u00ad\23\3\2\2\2\u00ae"+
		"\u00af\7\r\2\2\u00af\u00b0\5Z.\2\u00b0\25\3\2\2\2\u00b1\u00b2\7\13\2\2"+
		"\u00b2\27\3\2\2\2\u00b3\u00b4\5X-\2\u00b4\u00b5\5n8\2\u00b5\31\3\2\2\2"+
		"\u00b6\u00b7\7O\2\2\u00b7\u00b8\7\7\2\2\u00b8\u00b9\5X-\2\u00b9\u00ba"+
		"\7\b\2\2\u00ba\u00bd\5\b\5\2\u00bb\u00bc\7?\2\2\u00bc\u00be\5\b\5\2\u00bd"+
		"\u00bb\3\2\2\2\u00bd\u00be\3\2\2\2\u00be\33\3\2\2\2\u00bf\u00c1\5X-\2"+
		"\u00c0\u00bf\3\2\2\2\u00c0\u00c1\3\2\2\2\u00c1\35\3\2\2\2\u00c2\u00c3"+
		"\7;\2\2\u00c3\u00c4\5\b\5\2\u00c4\u00c5\7I\2\2\u00c5\u00c6\7\7\2\2\u00c6"+
		"\u00c7\5X-\2\u00c7\u00c8\7\b\2\2\u00c8\u00c9\5n8\2\u00c9\u00f7\3\2\2\2"+
		"\u00ca\u00cb\7I\2\2\u00cb\u00cc\7\7\2\2\u00cc\u00cd\5X-\2\u00cd\u00ce"+
		"\7\b\2\2\u00ce\u00cf\5\b\5\2\u00cf\u00f7\3\2\2\2\u00d0\u00d1\7G\2\2\u00d1"+
		"\u00d2\7\7\2\2\u00d2\u00d3\5\34\17\2\u00d3\u00d4\7\13\2\2\u00d4\u00d5"+
		"\5\34\17\2\u00d5\u00d6\7\13\2\2\u00d6\u00d7\5\34\17\2\u00d7\u00d8\7\b"+
		"\2\2\u00d8\u00d9\5\b\5\2\u00d9\u00f7\3\2\2\2\u00da\u00db\7G\2\2\u00db"+
		"\u00dc\7\7\2\2\u00dc\u00dd\7A\2\2\u00dd\u00de\5\20\t\2\u00de\u00df\7\13"+
		"\2\2\u00df\u00e0\5\34\17\2\u00e0\u00e1\7\13\2\2\u00e1\u00e2\5\34\17\2"+
		"\u00e2\u00e3\7\b\2\2\u00e3\u00e4\5\b\5\2\u00e4\u00f7\3\2\2\2\u00e5\u00e6"+
		"\7G\2\2\u00e6\u00e7\7\7\2\2\u00e7\u00e8\5Z.\2\u00e8\u00e9\7R\2\2\u00e9"+
		"\u00ea\5X-\2\u00ea\u00eb\7\b\2\2\u00eb\u00ec\5\b\5\2\u00ec\u00f7\3\2\2"+
		"\2\u00ed\u00ee\7G\2\2\u00ee\u00ef\7\7\2\2\u00ef\u00f0\7A\2\2\u00f0\u00f1"+
		"\5\22\n\2\u00f1\u00f2\7R\2\2\u00f2\u00f3\5X-\2\u00f3\u00f4\7\b\2\2\u00f4"+
		"\u00f5\5\b\5\2\u00f5\u00f7\3\2\2\2\u00f6\u00c2\3\2\2\2\u00f6\u00ca\3\2"+
		"\2\2\u00f6\u00d0\3\2\2\2\u00f6\u00da\3\2\2\2\u00f6\u00e5\3\2\2\2\u00f6"+
		"\u00ed\3\2\2\2\u00f7\37\3\2\2\2\u00f8\u00fb\7F\2\2\u00f9\u00fa\6\21\4"+
		"\2\u00fa\u00fc\7d\2\2\u00fb\u00f9\3\2\2\2\u00fb\u00fc\3\2\2\2\u00fc\u00fd"+
		"\3\2\2\2\u00fd\u00fe\5n8\2\u00fe!\3\2\2\2\u00ff\u0102\7:\2\2\u0100\u0101"+
		"\6\22\5\2\u0101\u0103\7d\2\2\u0102\u0100\3\2\2\2\u0102\u0103\3\2\2\2\u0103"+
		"\u0104\3\2\2\2\u0104\u0105\5n8\2\u0105#\3\2\2\2\u0106\u0109\7D\2\2\u0107"+
		"\u0108\6\23\6\2\u0108\u010a\5X-\2\u0109\u0107\3\2\2\2\u0109\u010a\3\2"+
		"\2\2\u010a\u010b\3\2\2\2\u010b\u010c\5n8\2\u010c%\3\2\2\2\u010d\u010e"+
		"\7M\2\2\u010e\u010f\7\7\2\2\u010f\u0110\5X-\2\u0110\u0111\7\b\2\2\u0111"+
		"\u0112\5\b\5\2\u0112\'\3\2\2\2\u0113\u0114\7H\2\2\u0114\u0115\7\7\2\2"+
		"\u0115\u0116\5X-\2\u0116\u0117\7\b\2\2\u0117\u0118\5*\26\2\u0118)\3\2"+
		"\2\2\u0119\u011b\7\t\2\2\u011a\u011c\5,\27\2\u011b\u011a\3\2\2\2\u011b"+
		"\u011c\3\2\2\2\u011c\u0121\3\2\2\2\u011d\u011f\5\60\31\2\u011e\u0120\5"+
		",\27\2\u011f\u011e\3\2\2\2\u011f\u0120\3\2\2\2\u0120\u0122\3\2\2\2\u0121"+
		"\u011d\3\2\2\2\u0121\u0122\3\2\2\2\u0122\u0123\3\2\2\2\u0123\u0124\7\n"+
		"\2\2\u0124+\3\2\2\2\u0125\u0127\5.\30\2\u0126\u0125\3\2\2\2\u0127\u0128"+
		"\3\2\2\2\u0128\u0126\3\2\2\2\u0128\u0129\3\2\2\2\u0129-\3\2\2\2\u012a"+
		"\u012b\7>\2\2\u012b\u012c\5X-\2\u012c\u012e\7\17\2\2\u012d\u012f\5\f\7"+
		"\2\u012e\u012d\3\2\2\2\u012e\u012f\3\2\2\2\u012f/\3\2\2\2\u0130\u0131"+
		"\7N\2\2\u0131\u0133\7\17\2\2\u0132\u0134\5\f\7\2\u0133\u0132\3\2\2\2\u0133"+
		"\u0134\3\2\2\2\u0134\61\3\2\2\2\u0135\u0136\7d\2\2\u0136\u0137\7\17\2"+
		"\2\u0137\u0138\5\b\5\2\u0138\63\3\2\2\2\u0139\u013a\7P\2\2\u013a\u013b"+
		"\6\33\7\2\u013b\u013c\5X-\2\u013c\u013d\5n8\2\u013d\65\3\2\2\2\u013e\u013f"+
		"\7S\2\2\u013f\u0140\5\n\6\2\u0140\u0141\58\35\2\u0141\u014c\3\2\2\2\u0142"+
		"\u0143\7S\2\2\u0143\u0144\5\n\6\2\u0144\u0145\5:\36\2\u0145\u014c\3\2"+
		"\2\2\u0146\u0147\7S\2\2\u0147\u0148\5\n\6\2\u0148\u0149\58\35\2\u0149"+
		"\u014a\5:\36\2\u014a\u014c\3\2\2\2\u014b\u013e\3\2\2\2\u014b\u0142\3\2"+
		"\2\2\u014b\u0146\3\2\2\2\u014c\67\3\2\2\2\u014d\u014e\7B\2\2\u014e\u014f"+
		"\7\7\2\2\u014f\u0150\7d\2\2\u0150\u0151\7\b\2\2\u0151\u0152\5\n\6\2\u0152"+
		"9\3\2\2\2\u0153\u0154\7C\2\2\u0154\u0155\5\n\6\2\u0155;\3\2\2\2\u0156"+
		"\u0157\7J\2\2\u0157\u0158\5n8\2\u0158=\3\2\2\2\u0159\u015a\7K\2\2\u015a"+
		"\u015b\7d\2\2\u015b\u015d\7\7\2\2\u015c\u015e\5@!\2\u015d\u015c\3\2\2"+
		"\2\u015d\u015e\3\2\2\2\u015e\u015f\3\2\2\2\u015f\u0160\7\b\2\2\u0160\u0161"+
		"\7\t\2\2\u0161\u0162\5B\"\2\u0162\u0163\7\n\2\2\u0163?\3\2\2\2\u0164\u0169"+
		"\7d\2\2\u0165\u0166\7\f\2\2\u0166\u0168\7d\2\2\u0167\u0165\3\2\2\2\u0168"+
		"\u016b\3\2\2\2\u0169\u0167\3\2\2\2\u0169\u016a\3\2\2\2\u016aA\3\2\2\2"+
		"\u016b\u0169\3\2\2\2\u016c\u016e\5\4\3\2\u016d\u016c\3\2\2\2\u016d\u016e"+
		"\3\2\2\2\u016eC\3\2\2\2\u016f\u0171\7\5\2\2\u0170\u0172\5F$\2\u0171\u0170"+
		"\3\2\2\2\u0171\u0172\3\2\2\2\u0172\u0174\3\2\2\2\u0173\u0175\7\f\2\2\u0174"+
		"\u0173\3\2\2\2\u0174\u0175\3\2\2\2\u0175\u0177\3\2\2\2\u0176\u0178\5H"+
		"%\2\u0177\u0176\3\2\2\2\u0177\u0178\3\2\2\2\u0178\u0179\3\2\2\2\u0179"+
		"\u017a\7\6\2\2\u017aE\3\2\2\2\u017b\u017d\5H%\2\u017c\u017b\3\2\2\2\u017c"+
		"\u017d\3\2\2\2\u017d\u017e\3\2\2\2\u017e\u0186\5Z.\2\u017f\u0181\7\f\2"+
		"\2\u0180\u0182\5H%\2\u0181\u0180\3\2\2\2\u0181\u0182\3\2\2\2\u0182\u0183"+
		"\3\2\2\2\u0183\u0185\5Z.\2\u0184\u017f\3\2\2\2\u0185\u0188\3\2\2\2\u0186"+
		"\u0184\3\2\2\2\u0186\u0187\3\2\2\2\u0187G\3\2\2\2\u0188\u0186\3\2\2\2"+
		"\u0189\u018b\7\f\2\2\u018a\u0189\3\2\2\2\u018b\u018c\3\2\2\2\u018c\u018a"+
		"\3\2\2\2\u018c\u018d\3\2\2\2\u018dI\3\2\2\2\u018e\u018f\7\t\2\2\u018f"+
		"\u0198\7\n\2\2\u0190\u0191\7\t\2\2\u0191\u0193\5L\'\2\u0192\u0194\7\f"+
		"\2\2\u0193\u0192\3\2\2\2\u0193\u0194\3\2\2\2\u0194\u0195\3\2\2\2\u0195"+
		"\u0196\7\n\2\2\u0196\u0198\3\2\2\2\u0197\u018e\3\2\2\2\u0197\u0190\3\2"+
		"\2\2\u0198K\3\2\2\2\u0199\u019e\5N(\2\u019a\u019b\7\f\2\2\u019b\u019d"+
		"\5N(\2\u019c\u019a\3\2\2\2\u019d\u01a0\3\2\2\2\u019e\u019c\3\2\2\2\u019e"+
		"\u019f\3\2\2\2\u019fM\3\2\2\2\u01a0\u019e\3\2\2\2\u01a1\u01a2\5P)\2\u01a2"+
		"\u01a3\7\17\2\2\u01a3\u01a4\5Z.\2\u01a4\u01b5\3\2\2\2\u01a5\u01a6\5j\66"+
		"\2\u01a6\u01a7\7\7\2\2\u01a7\u01a8\7\b\2\2\u01a8\u01a9\7\t\2\2\u01a9\u01aa"+
		"\5B\"\2\u01aa\u01ab\7\n\2\2\u01ab\u01b5\3\2\2\2\u01ac\u01ad\5l\67\2\u01ad"+
		"\u01ae\7\7\2\2\u01ae\u01af\5R*\2\u01af\u01b0\7\b\2\2\u01b0\u01b1\7\t\2"+
		"\2\u01b1\u01b2\5B\"\2\u01b2\u01b3\7\n\2\2\u01b3\u01b5\3\2\2\2\u01b4\u01a1"+
		"\3\2\2\2\u01b4\u01a5\3\2\2\2\u01b4\u01ac\3\2\2\2\u01b5O\3\2\2\2\u01b6"+
		"\u01ba\5b\62\2\u01b7\u01ba\7e\2\2\u01b8\u01ba\5`\61\2\u01b9\u01b6\3\2"+
		"\2\2\u01b9\u01b7\3\2\2\2\u01b9\u01b8\3\2\2\2\u01baQ\3\2\2\2\u01bb\u01bc"+
		"\7d\2\2\u01bcS\3\2\2\2\u01bd\u01bf\7\7\2\2\u01be\u01c0\5V,\2\u01bf\u01be"+
		"\3\2\2\2\u01bf\u01c0\3\2\2\2\u01c0\u01c1\3\2\2\2\u01c1\u01c2\7\b\2\2\u01c2"+
		"U\3\2\2\2\u01c3\u01c8\5Z.\2\u01c4\u01c5\7\f\2\2\u01c5\u01c7\5Z.\2\u01c6"+
		"\u01c4\3\2\2\2\u01c7\u01ca\3\2\2\2\u01c8\u01c6\3\2\2\2\u01c8\u01c9\3\2"+
		"\2\2\u01c9W\3\2\2\2\u01ca\u01c8\3\2\2\2\u01cb\u01d0\5Z.\2\u01cc\u01cd"+
		"\7\f\2\2\u01cd\u01cf\5Z.\2\u01ce\u01cc\3\2\2\2\u01cf\u01d2\3\2\2\2\u01d0"+
		"\u01ce\3\2\2\2\u01d0\u01d1\3\2\2\2\u01d1Y\3\2\2\2\u01d2\u01d0\3\2\2\2"+
		"\u01d3\u01d4\b.\1\2\u01d4\u01d6\7K\2\2\u01d5\u01d7\7d\2\2\u01d6\u01d5"+
		"\3\2\2\2\u01d6\u01d7\3\2\2\2\u01d7\u01d8\3\2\2\2\u01d8\u01da\7\7\2\2\u01d9"+
		"\u01db\5@!\2\u01da\u01d9\3\2\2\2\u01da\u01db\3\2\2\2\u01db\u01dc\3\2\2"+
		"\2\u01dc\u01dd\7\b\2\2\u01dd\u01de\7\t\2\2\u01de\u01df\5B\"\2\u01df\u01e0"+
		"\7\n\2\2\u01e0\u0202\3\2\2\2\u01e1\u01e2\7@\2\2\u01e2\u01e4\5Z.\2\u01e3"+
		"\u01e5\5T+\2\u01e4\u01e3\3\2\2\2\u01e4\u01e5\3\2\2\2\u01e5\u0202\3\2\2"+
		"\2\u01e6\u01e7\7Q\2\2\u01e7\u0202\5Z. \u01e8\u01e9\7E\2\2\u01e9\u0202"+
		"\5Z.\37\u01ea\u01eb\7=\2\2\u01eb\u0202\5Z.\36\u01ec\u01ed\7\21\2\2\u01ed"+
		"\u0202\5Z.\35\u01ee\u01ef\7\22\2\2\u01ef\u0202\5Z.\34\u01f0\u01f1\7\23"+
		"\2\2\u01f1\u0202\5Z.\33\u01f2\u01f3\7\24\2\2\u01f3\u0202\5Z.\32\u01f4"+
		"\u01f5\7\25\2\2\u01f5\u0202\5Z.\31\u01f6\u01f7\7\26\2\2\u01f7\u0202\5"+
		"Z.\30\u01f8\u0202\7L\2\2\u01f9\u0202\7d\2\2\u01fa\u0202\5^\60\2\u01fb"+
		"\u0202\5D#\2\u01fc\u0202\5J&\2\u01fd\u01fe\7\7\2\2\u01fe\u01ff\5X-\2\u01ff"+
		"\u0200\7\b\2\2\u0200\u0202\3\2\2\2\u0201\u01d3\3\2\2\2\u0201\u01e1\3\2"+
		"\2\2\u0201\u01e6\3\2\2\2\u0201\u01e8\3\2\2\2\u0201\u01ea\3\2\2\2\u0201"+
		"\u01ec\3\2\2\2\u0201\u01ee\3\2\2\2\u0201\u01f0\3\2\2\2\u0201\u01f2\3\2"+
		"\2\2\u0201\u01f4\3\2\2\2\u0201\u01f6\3\2\2\2\u0201\u01f8\3\2\2\2\u0201"+
		"\u01f9\3\2\2\2\u0201\u01fa\3\2\2\2\u0201\u01fb\3\2\2\2\u0201\u01fc\3\2"+
		"\2\2\u0201\u01fd\3\2\2\2\u0202\u0246\3\2\2\2\u0203\u0204\f\27\2\2\u0204"+
		"\u0205\t\2\2\2\u0205\u0245\5Z.\30\u0206\u0207\f\26\2\2\u0207\u0208\t\3"+
		"\2\2\u0208\u0245\5Z.\27\u0209\u020a\f\25\2\2\u020a\u020b\t\4\2\2\u020b"+
		"\u0245\5Z.\26\u020c\u020d\f\24\2\2\u020d\u020e\t\5\2\2\u020e\u0245\5Z"+
		".\25\u020f\u0210\f\23\2\2\u0210\u0211\7<\2\2\u0211\u0245\5Z.\24\u0212"+
		"\u0213\f\22\2\2\u0213\u0214\7R\2\2\u0214\u0245\5Z.\23\u0215\u0216\f\21"+
		"\2\2\u0216\u0217\t\6\2\2\u0217\u0245\5Z.\22\u0218\u0219\f\20\2\2\u0219"+
		"\u021a\7%\2\2\u021a\u0245\5Z.\21\u021b\u021c\f\17\2\2\u021c\u021d\7&\2"+
		"\2\u021d\u0245\5Z.\20\u021e\u021f\f\16\2\2\u021f\u0220\7\'\2\2\u0220\u0245"+
		"\5Z.\17\u0221\u0222\f\r\2\2\u0222\u0223\7(\2\2\u0223\u0245\5Z.\16\u0224"+
		"\u0225\f\f\2\2\u0225\u0226\7)\2\2\u0226\u0245\5Z.\r\u0227\u0228\f\13\2"+
		"\2\u0228\u0229\7\16\2\2\u0229\u022a\5Z.\2\u022a\u022b\7\17\2\2\u022b\u022c"+
		"\5Z.\f\u022c\u0245\3\2\2\2\u022d\u022e\f\n\2\2\u022e\u022f\7\r\2\2\u022f"+
		"\u0245\5Z.\n\u0230\u0231\f\t\2\2\u0231\u0232\5\\/\2\u0232\u0233\5Z.\t"+
		"\u0233\u0245\3\2\2\2\u0234\u0235\f&\2\2\u0235\u0236\7\5\2\2\u0236\u0237"+
		"\5X-\2\u0237\u0238\7\6\2\2\u0238\u0245\3\2\2\2\u0239\u023a\f%\2\2\u023a"+
		"\u023b\7\20\2\2\u023b\u0245\5b\62\2\u023c\u023d\f$\2\2\u023d\u0245\5T"+
		"+\2\u023e\u023f\f\"\2\2\u023f\u0240\6.\33\2\u0240\u0245\7\21\2\2\u0241"+
		"\u0242\f!\2\2\u0242\u0243\6.\35\2\u0243\u0245\7\22\2\2\u0244\u0203\3\2"+
		"\2\2\u0244\u0206\3\2\2\2\u0244\u0209\3\2\2\2\u0244\u020c\3\2\2\2\u0244"+
		"\u020f\3\2\2\2\u0244\u0212\3\2\2\2\u0244\u0215\3\2\2\2\u0244\u0218\3\2"+
		"\2\2\u0244\u021b\3\2\2\2\u0244\u021e\3\2\2\2\u0244\u0221\3\2\2\2\u0244"+
		"\u0224\3\2\2\2\u0244\u0227\3\2\2\2\u0244\u022d\3\2\2\2\u0244\u0230\3\2"+
		"\2\2\u0244\u0234\3\2\2\2\u0244\u0239\3\2\2\2\u0244\u023c\3\2\2\2\u0244"+
		"\u023e\3\2\2\2\u0244\u0241\3\2\2\2\u0245\u0248\3\2\2\2\u0246\u0244\3\2"+
		"\2\2\u0246\u0247\3\2\2\2\u0247[\3\2\2\2\u0248\u0246\3\2\2\2\u0249\u024a"+
		"\t\7\2\2\u024a]\3\2\2\2\u024b\u024e\t\b\2\2\u024c\u024e\5`\61\2\u024d"+
		"\u024b\3\2\2\2\u024d\u024c\3\2\2\2\u024e_\3\2\2\2\u024f\u0250\t\t\2\2"+
		"\u0250a\3\2\2\2\u0251\u0254\7d\2\2\u0252\u0254\5d\63\2\u0253\u0251\3\2"+
		"\2\2\u0253\u0252\3\2\2\2\u0254c\3\2\2\2\u0255\u0259\5f\64\2\u0256\u0259"+
		"\5h\65\2\u0257\u0259\t\n\2\2\u0258\u0255\3\2\2\2\u0258\u0256\3\2\2\2\u0258"+
		"\u0257\3\2\2\2\u0259e\3\2\2\2\u025a\u025b\t\13\2\2\u025bg\3\2\2\2\u025c"+
		"\u025d\t\f\2\2\u025di\3\2\2\2\u025e\u025f\6\66\36\2\u025f\u0260\7d\2\2"+
		"\u0260\u0261\5P)\2\u0261k\3\2\2\2\u0262\u0263\6\67\37\2\u0263\u0264\7"+
		"d\2\2\u0264\u0265\5P)\2\u0265m\3\2\2\2\u0266\u026b\7\13\2\2\u0267\u026b"+
		"\7\2\2\3\u0268\u026b\68 \2\u0269\u026b\68!\2\u026a\u0266\3\2\2\2\u026a"+
		"\u0267\3\2\2\2\u026a\u0268\3\2\2\2\u026a\u0269\3\2\2\2\u026bo\3\2\2\2"+
		"\u026c\u026d\7\2\2\3\u026dq\3\2\2\2\63sz\177\u0091\u0095\u009c\u00a7\u00ac"+
		"\u00bd\u00c0\u00f6\u00fb\u0102\u0109\u011b\u011f\u0121\u0128\u012e\u0133"+
		"\u014b\u015d\u0169\u016d\u0171\u0174\u0177\u017c\u0181\u0186\u018c\u0193"+
		"\u0197\u019e\u01b4\u01b9\u01bf\u01c8\u01d0\u01d6\u01da\u01e4\u0201\u0244"+
		"\u0246\u024d\u0253\u0258\u026a";
	public static final ATN _ATN =
		new ATNDeserializer().deserialize(_serializedATN.toCharArray());
	static {
		_decisionToDFA = new DFA[_ATN.getNumberOfDecisions()];
		for (int i = 0; i < _ATN.getNumberOfDecisions(); i++) {
			_decisionToDFA[i] = new DFA(_ATN.getDecisionState(i), i);
		}
	}
}
