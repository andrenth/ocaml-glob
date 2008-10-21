/*
 * Copyright (c) 2008 Andre Nathan <andre@sneakymustard.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

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
