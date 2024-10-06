add (-,fixnum,fixnum) accept
add (-,flonum,fixnum) accept
add (-,flonum,flonum) accept
add (-,string,string) accept
add (-,_,_) error
sub (-,fixnum,fixnum) accept
sub (-,_,_) error
mul (-,fixnum,fixnum) accept
mul (-,fixnum,flonum) accept
mul (-,_,_) error
div (-,fixnum,fixnum) accept
div (-,_,_) error
mod (-,fixnum,fixnum) accept
mod (-,_,_) error
bitand (-,fixnum,fixnum) accept
bitand (-,_,_) error
bitor (-,fixnum,fixnum) accept
bitor (-,_,_) error
leftshift (-,fixnum,fixnum) accept
leftshift (-,_,_) error
rightshift (-,fixnum,fixnum) accept
rightshift (-,_,_) error
lessthan (-,fixnum,fixnum) accept
lessthan (-,fixnum,flonum) accept
lessthan (-,flonum,fixnum) accept
lessthan (-,flonum,flonum) accept
lessthan (-,_,_) error
lessthanequal (-,fixnum,fixnum) accept
lessthanequal (-,_,_) error
equal (-,fixnum,fixnum) accept
equal (-,string,string) accept
equal (-,_,_) error
getprop (-,string,_) accept
getprop (-,object,_) accept
getprop (-,_,_) error
new (-,array) error
new (-,object) accept
new (-,_) error
call (array,-) error
call (object,-) accept
call (_,-) error
setprop (object,_,_) accept
setprop (_,_,_) error
eq (-,_,_) error
tailcall (_,-) error
unsignedrightshift (-,_,_) error
fixnum (-,-) accept
getarg (-,-,-) accept
geta (-) accept
geterr (-) accept
getglobal (-,string) accept
getglobal (-,_) error
getglobalobj (-) accept
getlocal (-,-) accept
instanceof (-,_,_) accept
isobject (-,_) accept
isundef (-,_) accept
jump (-) accept
jumpfalse (-,_) accept
jumptrue (-,_) accept
localcall (-) accept
makeclosure (-,-) accept
makeiterator (-,_) accept
move (-,_) accept
newframe (-,-) accept
exitframe () accept
nextpropnameidx (-,_) accept
not (-,_) accept
bigprim (-,-) accept
pushhandler (-) accept
seta (_) accept
setarg (-,-,_) accept
setarray (_,-,_) accept
setfl (-) accept
setglobal (_,_) accept
setlocal (-,-,_) accept
specconst (-,-) accept
typeof (-,-) accept
end () accept
localret () accept
nop () accept
pophandler () accept
poplocal () accept
ret () accept
throw (_) accept
unknown () accept
