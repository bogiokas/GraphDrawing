:set colorcolumn=110

:set makeprg=make;./test

"filepath of src
:let &path.='src'
:let g:syntastic_cpp_compiler_options += ' -Isrc'

