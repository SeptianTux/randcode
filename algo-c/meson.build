project('algo-c', 'c',
  version : '0.1',
  default_options : ['warning_level=3'])

sort_src = [
            'sort.c',
            'lib/sort.c',
            'lib/my-rand.c']
executable('sort',
           sort_src,
           install : true)


linear_search_src = [
            'linear-search.c',
            'lib/search.c',
            'lib/my-rand.c']
executable('linear-search',
           linear_search_src,
           install : false)

binary_search_recursive_src = [
            'binary-search-recursive.c',
            'lib/search.c',
            'lib/my-rand.c',
            'lib/sort.c']
executable('binary-search-recursive',
           binary_search_recursive_src,
           install : false)

binary_search_iterative_src = [
            'binary-search-iterative.c',
            'lib/search.c',
            'lib/my-rand.c',
            'lib/sort.c']
executable('binary-search-iterative',
           binary_search_iterative_src,
           install : false)
