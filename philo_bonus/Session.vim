let SessionLoad = 1
let s:so_save = &g:so | let s:siso_save = &g:siso | setg so=0 siso=0 | setl so=-1 siso=-1
let v:this_session=expand("<sfile>:p")
silent only
silent tabonly
cd ~/hive/philo/philo
if expand('%') == '' && !&modified && line('$') <= 1 && getline(1) == ''
  let s:wipebuf = bufnr('%')
endif
let s:shortmess_save = &shortmess
if &shortmess =~ 'A'
  set shortmess=aoOA
else
  set shortmess=aoO
endif
badd +38 main.c
badd +11 ~/hive/philo/.git/info/exclude
badd +150 term://~/hive/philo/philo//3932029:/bin/zsh
badd +4 Makefile
badd +62 philo.h
badd +9 term://~/hive/minishell/dev//3283647:/bin/zsh
badd +3 term://~/hive/minishell/fix.quote//3399294:/bin/zsh
badd +107 ~/hive/minishell/dev/Makefile
badd +46 ~/hive/sample_philo/src/philo.h
badd +59 ~/hive/sample_philo/src/monitor.c
badd +44 ~/hive/sample_philo/src/routine_actions.c
badd +75 ~/hive/sample_philo/src/init.c
badd +7 man://pthread_create(3)
badd +71 ~/hive/sample_philo/src/threads.c
badd +202 /usr/include/pthread.h
badd +10070 term://~/hive/philo/philo//2146525:/bin/zsh
badd +57 ~/hive/sample_philo/src/main.c
badd +1 man://pthread_mutex_init(3posix)
badd +64 man://pthread_mutex_destroy(3posix)
badd +69 /usr/include/x86_64-linux-gnu/bits/pthreadtypes.h
badd +22 /usr/include/x86_64-linux-gnu/bits/struct_mutex.h
badd +67 term://~/hive/philo/philo//2985010:/bin/zsh
badd +45 ~/.bashrc
badd +42 term://~/hive/philo/philo//3175874:/bin/zsh
badd +125 term://~/hive/philo/philo//3781384:/bin/zsh
badd +62 parser.c
badd +14 ~/.config/nvim/init.lua
badd +42 ~/hive/pushswap/libft/ft_atoi.c
badd +25 ~/hive/pushswap/libft/libft.h
badd +20 ~/hive/pushswap/libft/ft_isany.c
badd +64 utils.c
badd +36 monitor.c
badd +44 thread_utils.c
badd +17 philo_routine.c
badd +63 init.c
badd +33 threads.c
badd +25 man://pthread_join(3)
badd +31 man://sem_open(3)
argglobal
%argdel
$argadd main.c
set stal=2
tabnew +setlocal\ bufhidden=wipe
tabrewind
edit main.c
let s:save_splitbelow = &splitbelow
let s:save_splitright = &splitright
set splitbelow splitright
wincmd _ | wincmd |
vsplit
1wincmd h
wincmd _ | wincmd |
split
1wincmd k
wincmd w
wincmd w
let &splitbelow = s:save_splitbelow
let &splitright = s:save_splitright
wincmd t
let s:save_winminheight = &winminheight
let s:save_winminwidth = &winminwidth
set winminheight=0
set winheight=1
set winminwidth=0
set winwidth=1
exe '1resize ' . ((&lines * 35 + 36) / 73)
exe 'vert 1resize ' . ((&columns * 127 + 127) / 255)
exe '2resize ' . ((&lines * 34 + 36) / 73)
exe 'vert 2resize ' . ((&columns * 127 + 127) / 255)
exe 'vert 3resize ' . ((&columns * 127 + 127) / 255)
argglobal
balt philo.h
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 38 - ((25 * winheight(0) + 17) / 35)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 38
normal! 05|
wincmd w
argglobal
if bufexists(fnamemodify("threads.c", ":p")) | buffer threads.c | else | edit threads.c | endif
if &buftype ==# 'terminal'
  silent file threads.c
endif
balt main.c
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 33 - ((0 * winheight(0) + 17) / 34)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 33
normal! 0
wincmd w
argglobal
if bufexists(fnamemodify("init.c", ":p")) | buffer init.c | else | edit init.c | endif
if &buftype ==# 'terminal'
  silent file init.c
endif
balt philo_routine.c
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 66 - ((65 * winheight(0) + 35) / 70)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 66
normal! 031|
wincmd w
exe '1resize ' . ((&lines * 35 + 36) / 73)
exe 'vert 1resize ' . ((&columns * 127 + 127) / 255)
exe '2resize ' . ((&lines * 34 + 36) / 73)
exe 'vert 2resize ' . ((&columns * 127 + 127) / 255)
exe 'vert 3resize ' . ((&columns * 127 + 127) / 255)
tabnext
edit Makefile
argglobal
balt main.c
setlocal foldmethod=manual
setlocal foldexpr=0
setlocal foldmarker={{{,}}}
setlocal foldignore=#
setlocal foldlevel=0
setlocal foldminlines=1
setlocal foldnestmax=20
setlocal foldenable
silent! normal! zE
let &fdl = &fdl
let s:l = 4 - ((3 * winheight(0) + 35) / 70)
if s:l < 1 | let s:l = 1 | endif
keepjumps exe s:l
normal! zt
keepjumps 4
normal! 087|
tabnext 1
set stal=1
if exists('s:wipebuf') && len(win_findbuf(s:wipebuf)) == 0 && getbufvar(s:wipebuf, '&buftype') isnot# 'terminal'
  silent exe 'bwipe ' . s:wipebuf
endif
unlet! s:wipebuf
set winheight=1 winwidth=20
let &shortmess = s:shortmess_save
let s:sx = expand("<sfile>:p:r")."x.vim"
if filereadable(s:sx)
  exe "source " . fnameescape(s:sx)
endif
let &g:so = s:so_save | let &g:siso = s:siso_save
set hlsearch
nohlsearch
let g:this_session = v:this_session
let g:this_obsession = v:this_session
doautoall SessionLoadPost
unlet SessionLoad
" vim: set ft=vim :
