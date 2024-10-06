%% bit width def
Instruction 64
JSValue 64
Align 64
%% insn representation def
sbc
obc
%% datatype def
string 4 4
fixnum 7 -1
flonum 5 5
special 6 -1
simple_object 0 6
array 0 7
function 0 8
builtin 0 9
iterator 0 10
regexp 0 11
string_object 0 12
number_object 0 13
boolean_object 0 14
%% instruction def
fixnum SMALLPRIMITIVE Register int
specconst SMALLPRIMITIVE Register int
bigprim BIGPRIMITIVE Register ConstantDisplacement
add THREEOP Register JSValue JSValue
sub THREEOP Register JSValue JSValue
mul THREEOP Register JSValue JSValue
div THREEOP Register JSValue JSValue
mod THREEOP Register JSValue JSValue
bitand THREEOP Register JSValue JSValue
bitor THREEOP Register JSValue JSValue
leftshift THREEOP Register JSValue JSValue
rightshift THREEOP Register JSValue JSValue
unsignedrightshift THREEOP Register JSValue JSValue
lessthan THREEOP Register JSValue JSValue
lessthanequal THREEOP Register JSValue JSValue
eq THREEOP Register JSValue JSValue
equal THREEOP Register JSValue JSValue
getarg THREEOP Register int Subscript
setarg THREEOP int Subscript JSValue
getprop THREEOP Register JSValue JSValue
setprop THREEOP JSValue JSValue JSValue
getglobal TWOOP Register JSValue
setglobal TWOOP JSValue JSValue
instanceof THREEOP Register JSValue JSValue
move TWOOP Register JSValue
typeof TWOOP Register Register
not TWOOP Register JSValue
isundef TWOOP Register JSValue
isobject TWOOP Register JSValue
setfl ONEOP int
seta ONEOP JSValue
geta ONEOP Register
getnewa ONEOP Register
geterr ONEOP Register
getglobalobj ONEOP Register
newframe TWOOP int int
exitframe ZEROOP
ret ZEROOP
nop ZEROOP
jump UNCONDJUMP InstructionDisplacement
jumptrue CONDJUMP JSValue InstructionDisplacement
jumpfalse CONDJUMP JSValue InstructionDisplacement
getlocal GETVAR Register int Subscript
setlocal SETVAR int Subscript JSValue
makeclosure MAKECLOSUREOP Register Subscript
makeiterator TWOOP Register JSValue
nextpropnameidx TWOOP Register JSValue
send CALLOP LABELONLY
call CALLOP JSValue int
tailsend CALLOP LABELONLY
tailcall CALLOP JSValue int
construct THREEOP Register JSValue int
pushhandler UNCONDJUMP InstructionDisplacement
pophandler ZEROOP
throw ONEOP JSValue
localcall UNCONDJUMP InstructionDisplacement
localret ZEROOP
poplocal ZEROOP
unknown UNKNOWNOP
end ZEROOP
%% superinstruction spec
