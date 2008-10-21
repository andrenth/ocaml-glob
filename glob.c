#include <glob.h>

#include <caml/mlvalues.h>
#include <caml/alloc.h>
#include <caml/memory.h>

CAMLprim value
ocaml_glob(value pattern)
{
    value matches;
    CAMLparam2(pattern, matches);
    int i, r;
    glob_t gl;

    r = glob(String_val(pattern), GLOB_BRACE | GLOB_TILDE, NULL, &gl);
    if (r != 0) {
        globfree(&gl);
        CAMLreturn (caml_alloc(0, 0));
    }
    matches = caml_alloc(gl.gl_pathc, 0);
    for (i = 0; i < gl.gl_pathc; i++)
        Store_field(matches, i, caml_copy_string(gl.gl_pathv[i]));
    CAMLreturn (matches);
}
