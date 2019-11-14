"column 110 made gray
:set colorcolumn=110
:highlight ColorColumn ctermbg=darkgray

:set makeprg=make;./test

"filepath of src
:let &path.='src'
:let g:syntastic_cpp_compiler_options += ' -Isrc'

