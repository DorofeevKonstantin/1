//-----------------------------------------------------------------------------
//
// Source code for MIPT course on informatics
// Page with slides: http://cs.mipt.ru/wp/?page_id=7775
// Licensed after GNU GPL v3
//
//-----------------------------------------------------------------------------
//
// hidden visibility
//
// try:
// > gcc -fPIC -shared -fvisibility=hidden huge-hidden.c -o libhuge-hidden.so
// > nm -CD libhuge-hidden.so
//
//-----------------------------------------------------------------------------

unsigned helper1(unsigned x) { return 0; }
unsigned helper2(unsigned x) { return 1; }

unsigned __attribute__((visibility("default"))) myfunc(unsigned n) {
  return helper1(n) + helper2(n);
}
